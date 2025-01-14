#pragma once

#include <utils/error_log_utils.hpp>

#include <string>
#include <vector>

namespace redfish
{
namespace hw_isolation_utils
{

/**
 * @brief API used to isolate the given resource
 *
 * @param[in] aResp - The redfish response to return to the caller.
 * @param[in] resourceName - The redfish resource name which trying to isolate.
 * @param[in] resourceId - The redfish resource id which trying to isolate.
 * @param[in] resourceObjPath - The redfish resource dbus object path.
 * @param[in] hwIsolationDbusName - The HardwareIsolation dbus name which is
 *                                  hosting isolation dbus interfaces.
 *
 * @return The redfish response in given response buffer.
 *
 * @note This function will return the appropriate error based on the isolation
 *       dbus "Create" interface error.
 */
inline void
    isolateResource(const std::shared_ptr<bmcweb::AsyncResp>& aResp,
                    const std::string& resourceName,
                    const std::string& resourceId,
                    const sdbusplus::message::object_path& resourceObjPath,
                    const std::string& hwIsolationDbusName)
{
    crow::connections::systemBus->async_method_call(
        [aResp, resourceName, resourceId,
         resourceObjPath](const boost::system::error_code ec,
                          const sdbusplus::message::message& msg) {
            if (!ec)
            {
                messages::success(aResp->res);
                return;
            }

            BMCWEB_LOG_ERROR << "DBUS response error [" << ec.value() << " : "
                             << ec.message()
                             << "] when tried to isolate the given resource: "
                             << resourceObjPath.str;

            const sd_bus_error* dbusError = msg.get_error();
            if (dbusError == nullptr)
            {
                messages::internalError(aResp->res);
                return;
            }

            BMCWEB_LOG_ERROR << "DBus ErrorName: " << dbusError->name
                             << " ErrorMsg: " << dbusError->message;

            if (strcmp(dbusError->name, "xyz.openbmc_project.Common.Error."
                                        "InvalidArgument") == 0)
            {
                constexpr bool isolate = false;
                messages::propertyValueIncorrect(aResp->res, "@odata.id",
                                                 std::to_string(isolate));
            }
            else if (strcmp(dbusError->name, "xyz.openbmc_project.Common.Error."
                                             "NotAllowed") == 0)
            {
                messages::propertyNotWritable(aResp->res, "Enabled");
            }
            else if (strcmp(dbusError->name, "xyz.openbmc_project.Common.Error."
                                             "Unavailable") == 0)
            {
                messages::resourceInStandby(aResp->res);
            }
            else if (strcmp(dbusError->name, "xyz.openbmc_project."
                                             "HardwareIsolation.Error."
                                             "IsolatedAlready") == 0)
            {
                messages::resourceAlreadyExists(aResp->res, "@odata.id",
                                                resourceName, resourceId);
            }
            else if (strcmp(dbusError->name, "xyz.openbmc_project.Common.Error."
                                             "TooManyResources") == 0)
            {
                messages::createLimitReachedForResource(aResp->res);
            }
            else
            {
                BMCWEB_LOG_ERROR << "DBus Error is unsupported so "
                                    "returning as Internal Error";
                messages::internalError(aResp->res);
            }
            return;
        },
        hwIsolationDbusName, "/xyz/openbmc_project/hardware_isolation",
        "xyz.openbmc_project.HardwareIsolation.Create", "Create",
        resourceObjPath,
        "xyz.openbmc_project.HardwareIsolation.Entry.Type.Manual");
}

/**
 * @brief API used to deisolate the given resource
 *
 * @param[in] aResp - The redfish response to return to the caller.
 * @param[in] resourceObjPath - The redfish resource dbus object path.
 * @param[in] hwIsolationDbusName - The HardwareIsolation dbus name which is
 *                                  hosting isolation dbus interfaces.
 *
 * @return The redfish response in given response buffer.
 *
 * @note - This function will try to identify the hardware isolated dbus entry
 *         from associations endpoints by using the given resource dbus object
 *         of "isolated_hw_entry".
 *       - This function will use the last endpoint from the list since the
 *         HardwareIsolation manager may be used the "Resolved" dbus entry
 *         property to indicate the deisolation instead of delete
 *         the entry object.
 */
inline void
    deisolateResource(const std::shared_ptr<bmcweb::AsyncResp>& aResp,
                      const sdbusplus::message::object_path& resourceObjPath,
                      const std::string& hwIsolationDbusName)
{
    // Get the HardwareIsolation entry by using the given resource
    // associations endpoints
    crow::connections::systemBus->async_method_call(
        [aResp, resourceObjPath, hwIsolationDbusName](
            boost::system::error_code ec,
            const std::variant<std::vector<std::string>>& vEndpoints) {
            if (ec)
            {
                BMCWEB_LOG_ERROR << "DBus response error [" << ec.value()
                                 << " : " << ec.message()
                                 << "] when tried to get the hardware "
                                    "isolation entry for the given "
                                    "resource dbus object path: "
                                 << resourceObjPath.str;
                messages::internalError(aResp->res);
                return;
            }

            std::string resourceIsolatedHwEntry;
            const std::vector<std::string>* endpoints =
                std::get_if<std::vector<std::string>>(&(vEndpoints));
            if (endpoints == nullptr)
            {
                BMCWEB_LOG_ERROR << "Failed to get Associations endpoints "
                                    "for the given object path: "
                                 << resourceObjPath.str;
                messages::internalError(aResp->res);
                return;
            }
            resourceIsolatedHwEntry = endpoints->back();

            // De-isolate the given resource
            crow::connections::systemBus->async_method_call(
                [aResp, resourceIsolatedHwEntry](
                    const boost::system::error_code ec,
                    const sdbusplus::message::message& msg) {
                    if (!ec)
                    {
                        messages::success(aResp->res);
                        return;
                    }

                    BMCWEB_LOG_ERROR << "DBUS response error [" << ec.value()
                                     << " : " << ec.message()
                                     << "] when tried to isolate the given "
                                     << "resource: " << resourceIsolatedHwEntry;

                    const sd_bus_error* dbusError = msg.get_error();

                    if (dbusError == nullptr)
                    {
                        messages::internalError(aResp->res);
                        return;
                    }

                    BMCWEB_LOG_ERROR << "DBus ErrorName: " << dbusError->name
                                     << " ErrorMsg: " << dbusError->message;

                    if (strcmp(dbusError->name,
                               "xyz.openbmc_project.Common.Error."
                               "NotAllowed") == 0)
                    {
                        messages::propertyNotWritable(aResp->res, "Entry");
                    }
                    else if (strcmp(dbusError->name,
                                    "xyz.openbmc_project.Common.Error."
                                    "Unavailable") == 0)
                    {
                        messages::resourceInStandby(aResp->res);
                    }
                    else
                    {
                        BMCWEB_LOG_ERROR << "DBus Error is unsupported so "
                                            "returning as Internal Error";
                        messages::internalError(aResp->res);
                    }
                    return;
                },
                hwIsolationDbusName, resourceIsolatedHwEntry,
                "xyz.openbmc_project.Object.Delete", "Delete");
        },
        "xyz.openbmc_project.ObjectMapper",
        resourceObjPath.str + "/isolated_hw_entry",
        "org.freedesktop.DBus.Properties", "Get",
        "xyz.openbmc_project.Association", "endpoints");
}

/**
 * @brief API used to process hardware (aka resource) isolation request
 *        This API can be used to any redfish resource if that redfish
 *        supporting isolation feature (the resource can be isolate
 *        from system boot)
 *
 * @param[in] aResp - The redfish response to return to the caller.
 * @param[in] resourceName - The redfish resource name which trying to isolate.
 * @param[in] resourceId - The redfish resource id which trying to isolate.
 * @param[in] enabled - The redfish resource "Enabled" property value.
 * @param[in] interfaces - The redfish resource dbus interfaces which will use
 *                         to get the given resource dbus objects from
 *                         the inventory.
 *
 * @return The redfish response in given response buffer.
 *
 * @note - This function will identify the given resource dbus object from
 *         the inventory by using the given resource dbus interfaces along
 *         with "Object:Enable" interface (which is used to map the "Enabled"
 *         redfish property to dbus "Enabled" property - The "Enabled" is
 *         used to do isolate the resource from system boot) and the given
 *         redfish resource "Id".
 *       - This function will do either isolate or deisolate based on the
 *         given "Enabled" property value.
 */
inline void
    processHardwareIsolationReq(const std::shared_ptr<bmcweb::AsyncResp>& aResp,
                                const std::string& resourceName,
                                const std::string& resourceId, bool enabled,
                                const std::vector<const char*>& interfaces)
{
    std::vector<const char*> resourceIfaces(interfaces.begin(),
                                            interfaces.end());
    resourceIfaces.push_back("xyz.openbmc_project.Object.Enable");

    // Make sure the given resourceId is present in inventory
    crow::connections::systemBus->async_method_call(
        [aResp, resourceName, resourceId,
         enabled](boost::system::error_code ec,
                  const std::vector<std::string>& objects) {
            if (ec)
            {
                BMCWEB_LOG_ERROR << "DBus response error [" << ec.value()
                                 << " : " << ec.message()
                                 << "] when tried to check the given resource "
                                    "is present in tne inventory";
                messages::internalError(aResp->res);
                return;
            }

            sdbusplus::message::object_path resourceObjPath;
            for (const auto& object : objects)
            {
                sdbusplus::message::object_path path(object);
                if (path.filename() == resourceId)
                {
                    resourceObjPath = path;
                    break;
                }
            }

            if (resourceObjPath.str.empty())
            {
                messages::resourceNotFound(aResp->res, resourceName,
                                           resourceId);
                return;
            }

            // Get the HardwareIsolation DBus name
            crow::connections::systemBus->async_method_call(
                [aResp, resourceObjPath, enabled, resourceName,
                 resourceId](const boost::system::error_code ec,
                             const GetObjectType& objType) {
                    if (ec)
                    {
                        BMCWEB_LOG_ERROR
                            << "DBUS response error [" << ec.value() << " : "
                            << ec.message()
                            << "] when tried to get the HardwareIsolation "
                               "dbus name to isolate: "
                            << resourceObjPath.str;
                        messages::internalError(aResp->res);
                        return;
                    }

                    if (objType.size() > 1)
                    {
                        BMCWEB_LOG_ERROR << "More than one dbus service "
                                         << "implemented HardwareIsolation";
                        messages::internalError(aResp->res);
                        return;
                    }

                    if (objType[0].first.empty())
                    {
                        BMCWEB_LOG_ERROR << "The retrieved HardwareIsolation "
                                         << "dbus name is empty";
                        messages::internalError(aResp->res);
                        return;
                    }

                    // Make sure whether need to isolate or de-isolate
                    // the given resource
                    if (!enabled)
                    {
                        isolateResource(aResp, resourceName, resourceId,
                                        resourceObjPath, objType[0].first);
                    }
                    else
                    {
                        deisolateResource(aResp, resourceObjPath,
                                          objType[0].first);
                    }
                },
                "xyz.openbmc_project.ObjectMapper",
                "/xyz/openbmc_project/object_mapper",
                "xyz.openbmc_project.ObjectMapper", "GetObject",
                "/xyz/openbmc_project/hardware_isolation",
                std::array<const char*, 1>{
                    "xyz.openbmc_project.HardwareIsolation.Create"});
        },
        "xyz.openbmc_project.ObjectMapper",
        "/xyz/openbmc_project/object_mapper",
        "xyz.openbmc_project.ObjectMapper", "GetSubTreePaths",
        "/xyz/openbmc_project/inventory", 0, resourceIfaces);
}

/*
 * @brief The helper API to set the Redfish severity level base on
 *        the given severity.
 *
 * @param[in] aResp - The redfish response to return.
 * @param[in] objPath - The D-Bus object path of the given severity.
 * @param[in] severityPropPath - The Redfish severity property json path.
 * @param[in] severityVal - The D-Bus object severity.
 *
 * @return True on success
 *         False on failure and set the error in the redfish response.
 */
inline bool
    setSeverity(const std::shared_ptr<bmcweb::AsyncResp>& aResp,
                const sdbusplus::message::object_path& objPath,
                const nlohmann::json_pointer<nlohmann::json>& severityPropPath,
                const std::string& severityVal)
{
    if (severityVal == "xyz.openbmc_project.Logging.Event."
                       "SeverityLevel.Critical")
    {
        aResp->res.jsonValue[severityPropPath] = "Critical";
    }
    else if ((severityVal == "xyz.openbmc_project.Logging."
                             "Event.SeverityLevel.Warning") ||
             (severityVal == "xyz.openbmc_project.Logging."
                             "Event.SeverityLevel.Unknown"))
    {
        aResp->res.jsonValue[severityPropPath] = "Warning";
    }
    else if (severityVal == "xyz.openbmc_project.Logging."
                            "Event.SeverityLevel.Ok")
    {
        aResp->res.jsonValue[severityPropPath] = "OK";
    }
    else
    {
        BMCWEB_LOG_ERROR << "Unsupported Severity[ " << severityVal
                         << "] from object: " << objPath.str;
        messages::internalError(aResp->res);
        return false;
    }
    return true;
}

/*
 * @brief The helper API to set the Redfish Status conditions based on
 *        the given resource event log association.
 *
 * @param[in] aResp - The redfish response to return.
 * @param[in] resourceObjPath - The resource D-Bus object object.
 *
 * @return NULL
 */
inline void
    getHwIsolationStatus(const std::shared_ptr<bmcweb::AsyncResp>& aResp,
                         const sdbusplus::message::object_path& resourceObjPath)
{
    crow::connections::systemBus->async_method_call(
        [aResp, resourceObjPath](
            boost::system::error_code ec,
            const std::variant<std::vector<std::string>>& vEndpoints) {
            if (ec)
            {
                if (ec.value() == EBADR)
                {
                    // No event so the respective hardware status doesn't need
                    // any Redfish status condition
                    return;
                }
                BMCWEB_LOG_ERROR << "DBus response error [" << ec.value()
                                 << " : " << ec.message()
                                 << "] when tried to get the hardware "
                                    "status event for the given "
                                    "resource dbus object path: "
                                 << resourceObjPath.str << "EBADR: " << EBADR;
                messages::internalError(aResp->res);
                return;
            }

            const std::vector<std::string>* endpoints =
                std::get_if<std::vector<std::string>>(&(vEndpoints));
            if (endpoints == nullptr)
            {
                BMCWEB_LOG_ERROR << "Failed to get Associations endpoints "
                                    "for the given object path: "
                                 << resourceObjPath.str;
                messages::internalError(aResp->res);
                return;
            }

            bool found = false;
            std::string hwStatusEventObj;
            for (const auto& endpoint : *endpoints)
            {
                if (sdbusplus::message::object_path(endpoint)
                        .parent_path()
                        .filename() == "hw_isolation_status")
                {
                    hwStatusEventObj = endpoint;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                // No event so the respective hardware status doesn't need
                // any Redfish status condition
                return;
            }

            // Get the dbus service name of the hardware status event object
            crow::connections::systemBus->async_method_call(
                [aResp, hwStatusEventObj](const boost::system::error_code ec,
                                          const GetObjectType& objType) {
                    if (ec)
                    {
                        BMCWEB_LOG_ERROR
                            << "DBUS response error [" << ec.value() << " : "
                            << ec.message()
                            << "] when tried to get the dbus name "
                            << "of the hardware status event object "
                            << hwStatusEventObj;
                        messages::internalError(aResp->res);
                        return;
                    }

                    if (objType.size() > 1)
                    {
                        BMCWEB_LOG_ERROR << "More than one dbus service "
                                         << "implemented the same hardware "
                                         << "status event object "
                                         << hwStatusEventObj;
                        messages::internalError(aResp->res);
                        return;
                    }

                    if (objType[0].first.empty())
                    {
                        BMCWEB_LOG_ERROR << "The retrieved hardware status "
                                         << "event object dbus name is empty";
                        messages::internalError(aResp->res);
                        return;
                    }

                    using AssociationsValType = std::vector<
                        std::tuple<std::string, std::string, std::string>>;
                    using HwStausEventPropertiesType =
                        boost::container::flat_map<
                            std::string, std::variant<std::string, uint64_t,
                                                      AssociationsValType>>;

                    // Get event properties and fill into status conditions
                    crow::connections::systemBus->async_method_call(
                        [aResp, hwStatusEventObj](
                            const boost::system::error_code ec,
                            const HwStausEventPropertiesType& properties) {
                            if (ec)
                            {
                                BMCWEB_LOG_ERROR
                                    << "DBUS response error [" << ec.value()
                                    << " : " << ec.message() << "] when tried "
                                    << "to get the hardware status event "
                                    << "object properties " << hwStatusEventObj;
                                messages::internalError(aResp->res);
                                return;
                            }

                            // Event is exist and that will get created when
                            // the respective hardware is not functional so
                            // set the state as "Disabled".
                            aResp->res.jsonValue["Status"]["State"] =
                                "Disabled";

                            nlohmann::json& conditions =
                                aResp->res.jsonValue["Status"]["Conditions"];
                            conditions = nlohmann::json::array();
                            conditions.push_back(nlohmann::json::object());
                            nlohmann::json& condition = conditions.back();

                            for (const auto& property : properties)
                            {
                                if (property.first == "Associations")
                                {
                                    const AssociationsValType* associations =
                                        std::get_if<AssociationsValType>(
                                            &property.second);
                                    if (associations == nullptr)
                                    {
                                        BMCWEB_LOG_ERROR
                                            << "Failed to get the Associations "
                                            << "from object: "
                                            << hwStatusEventObj;
                                        messages::internalError(aResp->res);
                                        return;
                                    }

                                    for (const auto& assoc : *associations)
                                    {
                                        if (std::get<0>(assoc) == "error_log")
                                        {
                                            sdbusplus::message::object_path
                                                errPath = std::get<2>(assoc);
                                            // we have only one condition
                                            nlohmann::json_pointer logEntryPropPath =
                                                "/Status/Conditions/0/LogEntry"_json_pointer;
                                            error_log_utils::setErrorLogUri(
                                                aResp, errPath,
                                                logEntryPropPath, true);
                                        }
                                    }
                                }
                                else if (property.first == "Timestamp")
                                {
                                    const uint64_t* timestamp =
                                        std::get_if<uint64_t>(&property.second);
                                    if (timestamp == nullptr)
                                    {
                                        BMCWEB_LOG_ERROR
                                            << "Failed to get the Timestamp "
                                            << "from object: "
                                            << hwStatusEventObj;
                                        messages::internalError(aResp->res);
                                        return;
                                    }
                                    condition["Timestamp"] =
                                        crow::utility::getDateTime(
                                            static_cast<std::time_t>(
                                                *timestamp));
                                }
                                else if (property.first == "Message")
                                {
                                    const std::string* msgPropVal =
                                        std::get_if<std::string>(
                                            &property.second);
                                    if (msgPropVal == nullptr)
                                    {
                                        BMCWEB_LOG_ERROR
                                            << "Failed to get the Message "
                                            << "from object: "
                                            << hwStatusEventObj;
                                        messages::internalError(aResp->res);
                                        return;
                                    }

                                    const message_registries::Message* msgReg =
                                        message_registries::getMessage(
                                            "OpenBMC.0.2."
                                            "HardwareIsolationReason");

                                    if (msgReg == nullptr)
                                    {
                                        BMCWEB_LOG_ERROR
                                            << "Failed to get "
                                            << "the HardwareIsolationReason "
                                            << "message registry to add "
                                            << "in the condition";
                                        messages::internalError(aResp->res);
                                        return;
                                    }

                                    // Prepare MessageArgs as per defined in the
                                    // MessageRegistries
                                    std::vector<std::string> messageArgs{
                                        *msgPropVal};

                                    // Fill the "msgPropVal" as reason
                                    std::string message = msgReg->message;
                                    int i = 0;
                                    for (const std::string& messageArg :
                                         messageArgs)
                                    {
                                        std::string argIndex =
                                            "%" + std::to_string(++i);
                                        size_t argPos = message.find(argIndex);
                                        if (argPos != std::string::npos)
                                        {
                                            message.replace(argPos,
                                                            argIndex.length(),
                                                            messageArg);
                                        }
                                    }
                                    // Severity will be added based on the event
                                    // object property
                                    condition["Message"] = message;
                                    condition["MessageArgs"] = messageArgs;
                                    condition["MessageId"] =
                                        "OpenBMC.0.2.HardwareIsolationReason";
                                }
                                else if (property.first == "Severity")
                                {
                                    const std::string* severity =
                                        std::get_if<std::string>(
                                            &property.second);
                                    if (severity == nullptr)
                                    {
                                        BMCWEB_LOG_ERROR
                                            << "Failed to get the Severity "
                                            << "from object: "
                                            << hwStatusEventObj;
                                        messages::internalError(aResp->res);
                                        return;
                                    }

                                    // we have only one condition
                                    nlohmann::json_pointer severityPropPath =
                                        "/Status/Conditions/0/Severity"_json_pointer;
                                    if (!setSeverity(aResp, hwStatusEventObj,
                                                     severityPropPath,
                                                     *severity))
                                    {
                                        // Failed to set the severity
                                        return;
                                    }
                                }
                            }
                        },
                        objType[0].first, hwStatusEventObj,
                        "org.freedesktop.DBus.Properties", "GetAll", "");
                },
                "xyz.openbmc_project.ObjectMapper",
                "/xyz/openbmc_project/object_mapper",
                "xyz.openbmc_project.ObjectMapper", "GetObject",
                hwStatusEventObj,
                std::array<const char*, 1>{
                    "xyz.openbmc_project.Logging.Event"});
        },
        "xyz.openbmc_project.ObjectMapper", resourceObjPath.str + "/event_log",
        "org.freedesktop.DBus.Properties", "Get",
        "xyz.openbmc_project.Association", "endpoints");
}

} // namespace hw_isolation_utils
} // namespace redfish

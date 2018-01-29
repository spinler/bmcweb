/*
// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/
/****************************************************************
 * This is an auto-generated header which contains definitions
 * to use Redfish DMTF defined messages.
 *
 * This header contains preprocessor defines which wrap
 * preparation functions for message with given id. The message
 * ids can be retrieved from Base.__ver__.json file.
 ***************************************************************/
#pragma once
#include <nlohmann/json.hpp>

namespace redfish {

namespace messages {

constexpr const char* MESSAGE_VERSION_PREFIX = "Base.1.2.0.";
constexpr const char* MESSAGE_ANNOTATION = "@Message.ExtendedInfo";

/**
 * @brief Adds Message JSON object to error object
 *
 * @param[out] target   Target JSON to which message will be added
 * @param[in]  message  Message JSON that should be added to target
 *
 * @return None
 */
void addMessageToErrorJson(nlohmann::json& target,
                           const nlohmann::json& message);

/**
 * @brief Adds Message JSON object to target JSON
 *
 * @internal
 * This function has similar implementation to addMessageToJson(...), but
 * does not use nlohmann::json_pointer to avoid costly construction
 * @endinternal
 *
 * @param[out] target   Target JSON to which message will be added
 * @param[in]  message  Message JSON that should be added to target
 *
 * @return None
 */
void addMessageToJsonRoot(nlohmann::json& target,
                          const nlohmann::json& message);

/**
 * @brief Adds Message JSON object connected with specific field to target JSON
 *
 * @param[out] target      Target JSON to which message will be added
 * @param[in]  message     Message JSON that should be added to target
 * @param[in]  fieldPath   Path of related field
 *
 * @return None
 */
void addMessageToJson(nlohmann::json& target, const nlohmann::json& message,
                      const std::string& fieldPath);

/*********************************
 * AUTOGENERATED FUNCTIONS START *
 *********************************/

/**
 * @brief Formats ResourceInUse message into JSON
 * Message body: "The change to the requested resource failed because the
 * resource is in use or in transition."
 *
 *
 * @returns Message ResourceInUse formatted to JSON */
nlohmann::json resourceInUse();

/**
 * @brief Formats MalformedJSON message into JSON
 * Message body: "The request body submitted was malformed JSON and could not be
 * parsed by the receiving service."
 *
 *
 * @returns Message MalformedJSON formatted to JSON */
nlohmann::json malformedJSON();

/**
 * @brief Formats ResourceMissingAtURI message into JSON
 * Message body: "The resource at the URI <arg0> was not found."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message ResourceMissingAtURI formatted to JSON */
nlohmann::json resourceMissingAtURI(const std::string& arg1);

/**
 * @brief Formats ActionParameterValueFormatError message into JSON
 * Message body: "The value <arg0> for the parameter <arg1> in the action <arg2>
 * is of a different format than the parameter can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 * @param[in] arg3 Parameter of message that will replace %3 in its body.
 *
 * @returns Message ActionParameterValueFormatError formatted to JSON */
nlohmann::json actionParameterValueFormatError(const std::string& arg1,
                                               const std::string& arg2,
                                               const std::string& arg3);

/**
 * @brief Formats InternalError message into JSON
 * Message body: "The request failed due to an internal service error.  The
 * service is still operational."
 *
 *
 * @returns Message InternalError formatted to JSON */
nlohmann::json internalError();

/**
 * @brief Formats UnrecognizedRequestBody message into JSON
 * Message body: "The service detected a malformed request body that it was
 * unable to interpret."
 *
 *
 * @returns Message UnrecognizedRequestBody formatted to JSON */
nlohmann::json unrecognizedRequestBody();

/**
 * @brief Formats ResourceAtUriUnauthorized message into JSON
 * Message body: "While accessing the resource at <arg0>, the service received
 * an authorization error <arg1>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ResourceAtUriUnauthorized formatted to JSON */
nlohmann::json resourceAtUriUnauthorized(const std::string& arg1,
                                         const std::string& arg2);

/**
 * @brief Formats ActionParameterUnknown message into JSON
 * Message body: "The action <arg0> was submitted with the invalid parameter
 * <arg1>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ActionParameterUnknown formatted to JSON */
nlohmann::json actionParameterUnknown(const std::string& arg1,
                                      const std::string& arg2);

/**
 * @brief Formats ResourceCannotBeDeleted message into JSON
 * Message body: "The delete request failed because the resource requested
 * cannot be deleted."
 *
 *
 * @returns Message ResourceCannotBeDeleted formatted to JSON */
nlohmann::json resourceCannotBeDeleted();

/**
 * @brief Formats PropertyDuplicate message into JSON
 * Message body: "The property <arg0> was duplicated in the request."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message PropertyDuplicate formatted to JSON */
nlohmann::json propertyDuplicate(const std::string& arg1);

/**
 * @brief Formats ServiceTemporarilyUnavailable message into JSON
 * Message body: "The service is temporarily unavailable.  Retry in <arg0>
 * seconds."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message ServiceTemporarilyUnavailable formatted to JSON */
nlohmann::json serviceTemporarilyUnavailable(const std::string& arg1);

/**
 * @brief Formats ResourceAlreadyExists message into JSON
 * Message body: "The requested resource of type <arg0> with the property <arg1>
 * with the value <arg2> already exists."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 * @param[in] arg3 Parameter of message that will replace %3 in its body.
 *
 * @returns Message ResourceAlreadyExists formatted to JSON */
nlohmann::json resourceAlreadyExists(const std::string& arg1,
                                     const std::string& arg2,
                                     const std::string& arg3);

/**
 * @brief Formats AccountForSessionNoLongerExists message into JSON
 * Message body: "The account for the current session has been removed, thus the
 * current session has been removed as well."
 *
 *
 * @returns Message AccountForSessionNoLongerExists formatted to JSON */
nlohmann::json accountForSessionNoLongerExists();

/**
 * @brief Formats CreateFailedMissingReqProperties message into JSON
 * Message body: "The create operation failed because the required property
 * <arg0> was missing from the request."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message CreateFailedMissingReqProperties formatted to JSON */
nlohmann::json createFailedMissingReqProperties(const std::string& arg1);

/**
 * @brief Formats PropertyValueFormatError message into JSON
 * Message body: "The value <arg0> for the property <arg1> is of a different
 * format than the property can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message PropertyValueFormatError formatted to JSON */
nlohmann::json propertyValueFormatError(const std::string& arg1,
                                        const std::string& arg2);

/**
 * @brief Formats PropertyValueNotInList message into JSON
 * Message body: "The value <arg0> for the property <arg1> is not in the list of
 * acceptable values."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message PropertyValueNotInList formatted to JSON */
nlohmann::json propertyValueNotInList(const std::string& arg1,
                                      const std::string& arg2);

/**
 * @brief Formats ResourceAtUriInUnknownFormat message into JSON
 * Message body: "The resource at <arg0> is in a format not recognized by the
 * service."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message ResourceAtUriInUnknownFormat formatted to JSON */
nlohmann::json resourceAtUriInUnknownFormat(const std::string& arg1);

/**
 * @brief Formats ServiceInUnknownState message into JSON
 * Message body: "The operation failed because the service is in an unknown
 * state and can no longer take incoming requests."
 *
 *
 * @returns Message ServiceInUnknownState formatted to JSON */
nlohmann::json serviceInUnknownState();

/**
 * @brief Formats EventSubscriptionLimitExceeded message into JSON
 * Message body: "The event subscription failed due to the number of
 * simultaneous subscriptions exceeding the limit of the implementation."
 *
 *
 * @returns Message EventSubscriptionLimitExceeded formatted to JSON */
nlohmann::json eventSubscriptionLimitExceeded();

/**
 * @brief Formats ActionParameterMissing message into JSON
 * Message body: "The action <arg0> requires the parameter <arg1> to be present
 * in the request body."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ActionParameterMissing formatted to JSON */
nlohmann::json actionParameterMissing(const std::string& arg1,
                                      const std::string& arg2);

/**
 * @brief Formats StringValueTooLong message into JSON
 * Message body: "The string <arg0> exceeds the length limit <arg1>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message StringValueTooLong formatted to JSON */
nlohmann::json stringValueTooLong(const std::string& arg1, const int& arg2);

/**
 * @brief Formats PropertyValueTypeError message into JSON
 * Message body: "The value <arg0> for the property <arg1> is of a different
 * type than the property can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message PropertyValueTypeError formatted to JSON */
nlohmann::json propertyValueTypeError(const std::string& arg1,
                                      const std::string& arg2);

/**
 * @brief Formats ResourceNotFound message into JSON
 * Message body: "The requested resource of type <arg0> named <arg1> was not
 * found."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ResourceNotFound formatted to JSON */
nlohmann::json resourceNotFound(const std::string& arg1,
                                const std::string& arg2);

/**
 * @brief Formats CouldNotEstablishConnection message into JSON
 * Message body: "The service failed to establish a connection with the URI
 * <arg0>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message CouldNotEstablishConnection formatted to JSON */
nlohmann::json couldNotEstablishConnection(const std::string& arg1);

/**
 * @brief Formats PropertyNotWritable message into JSON
 * Message body: "The property <arg0> is a read only property and cannot be
 * assigned a value."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message PropertyNotWritable formatted to JSON */
nlohmann::json propertyNotWritable(const std::string& arg1);

/**
 * @brief Formats QueryParameterValueTypeError message into JSON
 * Message body: "The value <arg0> for the query parameter <arg1> is of a
 * different type than the parameter can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message QueryParameterValueTypeError formatted to JSON */
nlohmann::json queryParameterValueTypeError(const std::string& arg1,
                                            const std::string& arg2);

/**
 * @brief Formats ServiceShuttingDown message into JSON
 * Message body: "The operation failed because the service is shutting down and
 * can no longer take incoming requests."
 *
 *
 * @returns Message ServiceShuttingDown formatted to JSON */
nlohmann::json serviceShuttingDown();

/**
 * @brief Formats ActionParameterDuplicate message into JSON
 * Message body: "The action <arg0> was submitted with more than one value for
 * the parameter <arg1>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ActionParameterDuplicate formatted to JSON */
nlohmann::json actionParameterDuplicate(const std::string& arg1,
                                        const std::string& arg2);

/**
 * @brief Formats ActionParameterNotSupported message into JSON
 * Message body: "The parameter <arg0> for the action <arg1> is not supported on
 * the target resource."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message ActionParameterNotSupported formatted to JSON */
nlohmann::json actionParameterNotSupported(const std::string& arg1,
                                           const std::string& arg2);

/**
 * @brief Formats SourceDoesNotSupportProtocol message into JSON
 * Message body: "The other end of the connection at <arg0> does not support the
 * specified protocol <arg1>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message SourceDoesNotSupportProtocol formatted to JSON */
nlohmann::json sourceDoesNotSupportProtocol(const std::string& arg1,
                                            const std::string& arg2);

/**
 * @brief Formats AccountRemoved message into JSON
 * Message body: "The account was successfully removed."
 *
 *
 * @returns Message AccountRemoved formatted to JSON */
nlohmann::json accountRemoved();

/**
 * @brief Formats AccessDenied message into JSON
 * Message body: "While attempting to establish a connection to <arg0>, the
 * service denied access."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message AccessDenied formatted to JSON */
nlohmann::json accessDenied(const std::string& arg1);

/**
 * @brief Formats QueryNotSupported message into JSON
 * Message body: "Querying is not supported by the implementation."
 *
 *
 * @returns Message QueryNotSupported formatted to JSON */
nlohmann::json queryNotSupported();

/**
 * @brief Formats CreateLimitReachedForResource message into JSON
 * Message body: "The create operation failed because the resource has reached
 * the limit of possible resources."
 *
 *
 * @returns Message CreateLimitReachedForResource formatted to JSON */
nlohmann::json createLimitReachedForResource();

/**
 * @brief Formats GeneralError message into JSON
 * Message body: "A general error has occurred. See ExtendedInfo for more
 * information."
 *
 *
 * @returns Message GeneralError formatted to JSON */
nlohmann::json generalError();

/**
 * @brief Formats Success message into JSON
 * Message body: "Successfully Completed Request"
 *
 *
 * @returns Message Success formatted to JSON */
nlohmann::json success();

/**
 * @brief Formats Created message into JSON
 * Message body: "The resource has been created successfully"
 *
 *
 * @returns Message Created formatted to JSON */
nlohmann::json created();

/**
 * @brief Formats PropertyUnknown message into JSON
 * Message body: "The property <arg0> is not in the list of valid properties for
 * the resource."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message PropertyUnknown formatted to JSON */
nlohmann::json propertyUnknown(const std::string& arg1);

/**
 * @brief Formats NoValidSession message into JSON
 * Message body: "There is no valid session established with the
 * implementation."
 *
 *
 * @returns Message NoValidSession formatted to JSON */
nlohmann::json noValidSession();

/**
 * @brief Formats InvalidObject message into JSON
 * Message body: "The object at <arg0> is invalid."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message InvalidObject formatted to JSON */
nlohmann::json invalidObject(const std::string& arg1);

/**
 * @brief Formats ResourceInStandby message into JSON
 * Message body: "The request could not be performed because the resource is in
 * standby."
 *
 *
 * @returns Message ResourceInStandby formatted to JSON */
nlohmann::json resourceInStandby();

/**
 * @brief Formats ActionParameterValueTypeError message into JSON
 * Message body: "The value <arg0> for the parameter <arg1> in the action <arg2>
 * is of a different type than the parameter can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 * @param[in] arg3 Parameter of message that will replace %3 in its body.
 *
 * @returns Message ActionParameterValueTypeError formatted to JSON */
nlohmann::json actionParameterValueTypeError(const std::string& arg1,
                                             const std::string& arg2,
                                             const std::string& arg3);

/**
 * @brief Formats SessionLimitExceeded message into JSON
 * Message body: "The session establishment failed due to the number of
 * simultaneous sessions exceeding the limit of the implementation."
 *
 *
 * @returns Message SessionLimitExceeded formatted to JSON */
nlohmann::json sessionLimitExceeded();

/**
 * @brief Formats ActionNotSupported message into JSON
 * Message body: "The action <arg0> is not supported by the resource."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message ActionNotSupported formatted to JSON */
nlohmann::json actionNotSupported(const std::string& arg1);

/**
 * @brief Formats InvalidIndex message into JSON
 * Message body: "The Index <arg0> is not a valid offset into the array."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message InvalidIndex formatted to JSON */
nlohmann::json invalidIndex(const int& arg1);

/**
 * @brief Formats EmptyJSON message into JSON
 * Message body: "The request body submitted contained an empty JSON object and
 * the service is unable to process it."
 *
 *
 * @returns Message EmptyJSON formatted to JSON */
nlohmann::json emptyJSON();

/**
 * @brief Formats QueryNotSupportedOnResource message into JSON
 * Message body: "Querying is not supported on the requested resource."
 *
 *
 * @returns Message QueryNotSupportedOnResource formatted to JSON */
nlohmann::json queryNotSupportedOnResource();

/**
 * @brief Formats InsufficientPrivilege message into JSON
 * Message body: "There are insufficient privileges for the account or
 * credentials associated with the current session to perform the requested
 * operation."
 *
 *
 * @returns Message InsufficientPrivilege formatted to JSON */
nlohmann::json insufficientPrivilege();

/**
 * @brief Formats PropertyValueModified message into JSON
 * Message body: "The property <arg0> was assigned the value <arg1> due to
 * modification by the service."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message PropertyValueModified formatted to JSON */
nlohmann::json propertyValueModified(const std::string& arg1,
                                     const std::string& arg2);

/**
 * @brief Formats AccountNotModified message into JSON
 * Message body: "The account modification request failed."
 *
 *
 * @returns Message AccountNotModified formatted to JSON */
nlohmann::json accountNotModified();

/**
 * @brief Formats QueryParameterValueFormatError message into JSON
 * Message body: "The value <arg0> for the parameter <arg1> is of a different
 * format than the parameter can accept."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 *
 * @returns Message QueryParameterValueFormatError formatted to JSON */
nlohmann::json queryParameterValueFormatError(const std::string& arg1,
                                              const std::string& arg2);

/**
 * @brief Formats PropertyMissing message into JSON
 * Message body: "The property <arg0> is a required property and must be
 * included in the request."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message PropertyMissing formatted to JSON */
nlohmann::json propertyMissing(const std::string& arg1);

/**
 * @brief Formats ResourceExhaustion message into JSON
 * Message body: "The resource <arg0> was unable to satisfy the request due to
 * unavailability of resources."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 *
 * @returns Message ResourceExhaustion formatted to JSON */
nlohmann::json resourceExhaustion(const std::string& arg1);

/**
 * @brief Formats AccountModified message into JSON
 * Message body: "The account was successfully modified."
 *
 *
 * @returns Message AccountModified formatted to JSON */
nlohmann::json accountModified();

/**
 * @brief Formats QueryParameterOutOfRange message into JSON
 * Message body: "The value <arg0> for the query parameter <arg1> is out of
 * range <arg2>."
 *
 * @param[in] arg1 Parameter of message that will replace %1 in its body.
 * @param[in] arg2 Parameter of message that will replace %2 in its body.
 * @param[in] arg3 Parameter of message that will replace %3 in its body.
 *
 * @returns Message QueryParameterOutOfRange formatted to JSON */
nlohmann::json queryParameterOutOfRange(const std::string& arg1,
                                        const std::string& arg2,
                                        const std::string& arg3);

/*********************************
 * AUTOGENERATED FUNCTIONS END *
 *********************************/

}  // namespace messages

}  // namespace redfish

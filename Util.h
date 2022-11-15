#pragma once
#include <string>

namespace EthCpp {

/****
 * @brief pull a string result out of JSON
 * @param json the json string
 * @return the results from the result member
 */
std::string string_result(const std::string& json);

/****
 * @brief pull a boolean result out of JSON
 * @param json the json string
 * @return the results from the result member
 */
bool bool_result(const std::string& json);

} // namespace EthCpp

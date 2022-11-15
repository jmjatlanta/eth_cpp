#include "Util.h"
#include "rapidjson/document.h"

namespace EthCpp {

std::string string_result(const std::string& json)
{
    rapidjson::Document d;
    d.Parse(json.c_str());
    if (d.HasMember("result") && d["result"].IsString())
    {
        return d["result"].GetString();
    }
    return "";
}

bool bool_result(const std::string& json)
{
    rapidjson::Document d;
    d.Parse(json.c_str());
    if (d.HasMember("result") && d["result"].IsBool())
    {
        return d["result"].GetBool();
    }
    return "";
}

} // namespace EthCpp


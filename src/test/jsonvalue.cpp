#include <iostream>
#include <limits>
#include <string>

#include <jsonrpc/rpc.h>

void trim(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

bool isnan(double val)
{
    return val != val;
}

bool parseJsonAndGetKey(std::string str, const std::string key, double& val)
{
    Json::Reader reader;
    Json::Value value;
    if (reader.parse(str, value, false)) {
        if (value.isMember(key) && value[key].isDouble()) {
            val = value["key"].asDouble();
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    double nan = std::numeric_limits<float>::quiet_NaN();
    double inf = std::numeric_limits<float>::infinity();

    Json::FastWriter writer;
    Json::Reader reader;

    {
        Json::Value value;
        value["key"] = nan;
        std::string result = writer.write(value);
        trim(result);
        const std::string expected = "{\"key\":NaN}";
        if (result != expected) {
            std::cerr << result << " should be " << expected << std::endl;
            return -1;
        }
    }

    {
        Json::Value value;
        value["key"] = inf;
        std::string result = writer.write(value);
        trim(result);
        const std::string expected = "{\"key\":Infinity}";
        if (result != expected) {
            std::cerr << result << " should be " << expected << std::endl;
            return -2;
        }
    }

    {
        Json::Value value;
        value["key"] = -inf;
        std::string result = writer.write(value);
        trim(result);
        const std::string expected = "{\"key\":-Infinity}";
        if (result != expected) {
            std::cerr << result << " should be " << expected << std::endl;
            return -3;
        }
    }

    {
        double val;
        if (!parseJsonAndGetKey("{\"key\":NaN}", "key", val)) {
            std::cerr << "parse error" << std::endl;
            return -4;
        }
        if (!isnan(val)) {
            std::cerr << val << " should be a nan" << std::endl;
            return -4;
        }
    }

    {
        double val;
        if (!parseJsonAndGetKey("{\"key\":Infinity}", "key", val)) {
            std::cerr << "parse error" << std::endl;
            return -5;
        }
        if (val != inf) {
            std::cerr << val << " should be a inf" << std::endl;
            return -5;
        }
    }

    {
        double val;
        if (!parseJsonAndGetKey("{\"key\":-Infinity}", "key", val)) {
            std::cerr << "parse error" << std::endl;
            return -6;
        }
        if (val != -inf) {
            std::cerr << val << " should be a -inf" << std::endl;
            return -6;
        }
    }

    return 0;
}

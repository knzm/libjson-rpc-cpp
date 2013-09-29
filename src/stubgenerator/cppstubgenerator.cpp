/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    cppstubgenerator.cpp
 * @date    29.09.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "cppstubgenerator.h"
#include <sstream>

using namespace std;
using namespace jsonrpc;

string  CPPStubGenerator::toCppType                        (jsontype_t type, bool isConst, bool isReference)
{
    string result;
    switch(type)
    {
        case JSON_BOOLEAN:
            result = "bool";
            break;
        case JSON_INTEGER:
            result = "int";
            break;
        case JSON_REAL:
            result = "double";
            break;
        case JSON_STRING:
            result = "std::string";
            break;
        default:
            result = "Json::Value";
            break;
    }
    if(isConst)
    {
        result = "const " + result;
    }
    if(isReference)
    {
        result = result + "&";
    }
    return result;
}
string  CPPStubGenerator::toCppConversion                  (jsontype_t type)
{
    string result;
    switch(type)
    {
        case JSON_BOOLEAN:
            result = ".asBool()";
            break;
        case JSON_INTEGER:
            result = ".asInt()";
            break;
        case JSON_REAL:
            result = ".asDouble()";
            break;
        case JSON_STRING:
            result = ".asString()";
            break;
        default:
            result = "";
            break;
    }
    return result;
}
string  CPPStubGenerator::toString                         (jsontype_t type)
{
    string result;
    switch(type)
    {
        case JSON_BOOLEAN:
            result = "jsonrpc::JSON_BOOLEAN";
            break;
        case JSON_INTEGER:
            result = "jsonrpc::JSON_INTEGER";
            break;
        case JSON_REAL:
            result = "jsonrpc::JSON_REAL";
            break;
        case JSON_STRING:
            result = "jsonrpc::JSON_STRING";
            break;
        case JSON_OBJECT:
            result = "jsonrpc::JSON_OBJECT";
            break;
        case JSON_ARRAY:
            result = "jsonrpc::JSON_ARRAY";
            break;
        case JSON_NULL:
            result = "jsonrpc::JSON_NULL";
    }
    return result;
}
string  CPPStubGenerator::generateParameterDeclarationList (Procedure &proc)
{
    stringstream param_string;
    parameterNameList_t list = proc.GetParameters();
    for (parameterNameList_t::iterator it = list.begin(); it != list.end();)
    {
        param_string << toCppType(it->second, true, true) << " " << it->first;
        if (++it != list.end())
        {
            param_string << ", ";
        }
    }
    return param_string.str();
}
string  CPPStubGenerator::normalizeString                  (const string &text)
{
    string result = text;
    for(unsigned int i=0; i < text.length(); i++)
    {
        if (!((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')))
        {
            result[i] = '_';
        }
    }
    return result;
}

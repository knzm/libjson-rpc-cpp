/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    client.cpp
 * @date    03.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "client.h"

using namespace jsonrpc;

Client::Client(AbstractClientConnector &connector)
    : connector(connector)
{
}

void Client::CallMethod(const std::string &name, const Json::Value &paramter, Json::Value& result) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildRequest(name, paramter, request, false);
    connector.SendRPCRequest(request, response);
    protocol.HandleResponse(response, result);
}

void Client::CallProcedures(const BatchCall &calls, Json::Value &result) throw(JsonRpcException)
{
    std::string request, response;
    request = calls.toString();
    connector.SendRPCRequest(request, response);
    Json::Reader reader;
    reader.parse(response, result);
}

Json::Value Client::CallProcedures(const BatchCall &calls) throw(JsonRpcException)
{
    Json::Value result;
    this->CallProcedures(calls, result);
    return result;
}

Json::Value Client::CallMethod(const std::string& name,
                               const Json::Value& parameter) throw(JsonRpcException)
{
    Json::Value result;
    this->CallMethod(name, parameter, result);
    return result;
}

void Client::CallNotification(const std::string& name, const Json::Value& parameter) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildRequest(name, parameter, request, true);
    connector.SendRPCRequest(request, response);
}

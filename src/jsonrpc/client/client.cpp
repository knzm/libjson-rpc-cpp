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

void Client::CallMethods(const batchProcedureCall_t &calls, Json::Value &result) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildBatchRequest(calls, response, false);
    connector.SendRPCRequest(request, response);
    Json::Reader reader;
    reader.parse(response, result);
}

Json::Value Client::CallMethods(const batchProcedureCall_t &calls) throw(JsonRpcException)
{
    Json::Value result;
    this->CallMethods(calls, result);
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

void Client::CallNotifications(const batchProcedureCall_t &calls) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildBatchRequest(calls, response, true);
    connector.SendRPCRequest(request, response);
}

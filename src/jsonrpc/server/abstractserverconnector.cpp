/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    serverconnector.cpp
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "abstractserverconnector.h"
#include <jsonrpc/common/specificationwriter.h>
#include <cstdlib>

using namespace std;
using namespace jsonrpc;

AbstractServerConnector::AbstractServerConnector()
{
    this->handler = NULL;
}
AbstractServerConnector::~AbstractServerConnector()
{
}

bool AbstractServerConnector::OnRequest(const std::string& request, void* addInfo)
{
    string response;
    if (this->handler != NULL)
    {
        this->handler->HandleRequest(request, response);
        this->SendResponse(response, addInfo);
        return true;
    }
    else
    {
        return false;
    }
}
void AbstractServerConnector::SetHandler(RpcProtocolServer& handler)
{
    this->handler = &handler;
}

/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    clientconnector.h
 * @date    02.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef CLIENTCONNECTOR_H_
#define CLIENTCONNECTOR_H_

#include <string>
#include <jsonrpc/common/exception.h>

namespace jsonrpc
{
    class AbstractClientConnector
    {
        public:
            virtual ~AbstractClientConnector();

            virtual void SendRPCRequest(const std::string& message, std::string& result) throw(JsonRpcException) = 0;
    };
} /* namespace jsonrpc */
#endif /* CLIENTCONNECTOR_H_ */

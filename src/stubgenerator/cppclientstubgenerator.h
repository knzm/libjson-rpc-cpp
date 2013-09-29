/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    clientstubgenerator.h
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_CLIENTSTUBGENERATOR_H
#define JSONRPC_CPP_CLIENTSTUBGENERATOR_H

#include "stubgenerator.h"
#include "cppstubgenerator.h"

namespace jsonrpc
{
    class CPPClientStubGenerator : public StubGenerator, public CPPStubGenerator
    {
        public:
            CPPClientStubGenerator(const std::string& stubname, std::vector<Procedure> &procedures);

            virtual std::string generateStub();

        private:
            static std::string generateMethod(Procedure& proc);
    };
}
#endif // JSONRPC_CPP_CLIENTSTUBGENERATOR_H

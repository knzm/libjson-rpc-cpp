/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    serverstubgenerator.h
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_SERVERSTUBGENERATOR_H
#define JSONRPC_CPP_SERVERSTUBGENERATOR_H

#include "stubgenerator.h"
#include "cppstubgenerator.h"

namespace jsonrpc
{
    class ServerStubGenerator : public StubGenerator, public CPPStubGenerator
    {
        public:
            ServerStubGenerator(const std::string& stubname, std::vector<Procedure> &procedures);

            virtual std::string generateStub();

        private:
            std::string generateBindings();
            std::string generateProcedureDefinitions();
            std::string generateAbstractDefinitions();
            std::string generateBindingParameterlist(Procedure &proc);
            std::string generateParameterMapping(Procedure &proc);
    };
}

#endif // JSONRPC_CPP_SERVERSTUBGENERATOR_H

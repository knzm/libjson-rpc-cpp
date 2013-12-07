/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubgenerator.h
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_STUBGENERATOR_H
#define JSONRPC_CPP_STUBGENERATOR_H

#include <string>
#include <jsonrpc/common/procedure.h>

namespace jsonrpc
{
    enum connectiontype_t {CONNECTION_HTTP};

    class StubGenerator
    {
        public:
            StubGenerator(const std::string& stubname, std::vector<Procedure> &procedures);
            virtual ~StubGenerator();

            virtual std::string generateStubToFile(const std::string& outputpath);
            virtual std::string getStubName();

            virtual std::string generateStub() = 0;

            static void replaceAll(std::string& text, const std::string& fnd, const std::string& rep);

        protected:
            std::string             stubname;
            std::vector<Procedure>  &procedures;
    };
}


#endif // JSONRPC_CPP_STUBGENERATOR_H

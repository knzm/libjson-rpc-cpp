/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubgenerator.h
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef STUBGENERATOR_H
#define STUBGENERATOR_H

#include <string>
#include <jsonrpc/common/procedure.h>

namespace jsonrpc
{
    class StubGenerator
    {
        public:
            StubGenerator(const std::string& stubname, const std::string& filename);
            virtual ~StubGenerator();

            virtual std::string generateStubToFile(const std::string& outputpath);
            virtual std::string getStubName();

            virtual std::string generateStub() = 0;

            static void replaceAll(std::string& text, const std::string& fnd, const std::string& rep);

        protected:
            std::string             stubname;
            std::vector<Procedure>  procedures;

            static std::string toCppType        (jsontype_t type, bool isConst = false, bool isReference = false);
            static std::string toCppConversion  (jsontype_t);
            static std::string toString         (jsontype_t type);
            static std::string normalizeString  (const std::string &text);
            static std::string generateParameterDeclarationList(Procedure& proc);
    };
}


#endif // STUBGENERATOR_H

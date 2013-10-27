/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    phpserverstubgenerator.h
 * @date    27.10.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_PHPSERVERSTUBGENERATOR_H
#define JSONRPC_CPP_PHPSERVERSTUBGENERATOR_H

#include "stubgenerator.h"

namespace jsonrpc
{
    class PHPServerStubGenerator : public StubGenerator
    {
        public:
            PHPServerStubGenerator(const std::string& stubname, std::vector<Procedure> &procedures);
    };
}
#endif // JSONRPC_CPP_PHPSERVERSTUBGENERATOR_H

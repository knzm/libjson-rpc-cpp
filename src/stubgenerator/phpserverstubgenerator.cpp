/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    phpserverstubgenerator.cpp
 * @date    27.10.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "phpserverstubgenerator.h"

using namespace jsonrpc;
using namespace std;

PHPServerStubGenerator::PHPServerStubGenerator(const string &stubname, std::vector<Procedure> &procedures) :
    StubGenerator(stubname, procedures)
{

}

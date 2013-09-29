/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubgenerator.cpp
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include <fstream>
#include <algorithm>
#include <jsonrpc/common/specificationparser.h>

#include "stubgenerator.h"

using namespace std;
using namespace jsonrpc;

StubGenerator::StubGenerator    (const string &stubname, std::vector<Procedure> &procedures) :
    stubname                    (stubname),
    procedures                  (procedures)
{
}
StubGenerator::~StubGenerator   ()
{
}

void    StubGenerator::replaceAll                       (string &text, const string &fnd, const string &rep)
{
    size_t pos = text.find(fnd);
    while (pos != string::npos)
    {
        text.replace(pos, fnd.length(), rep);
        pos = text.find(fnd, pos + rep.length());
    }
}
string  StubGenerator::generateStubToFile               (const string &path)
{
    ofstream stream;
    stream.open(path.c_str(), ios_base::out);
    stream << this->generateStub();
    stream.close();
    return path;
}
string  StubGenerator::getStubName                      ()
{
    return this->stubname;
}

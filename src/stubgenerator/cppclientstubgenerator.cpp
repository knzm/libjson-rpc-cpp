/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    CPPClientStubGenerator.cpp
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "cppclientstubgenerator.h"
#include "cppclienttemplate.h"

#include <sstream>
#include <algorithm>

using namespace std;
using namespace jsonrpc;

CPPClientStubGenerator::CPPClientStubGenerator(const string &stubname, std::vector<Procedure> &procedures) :
    StubGenerator(stubname+"Client", procedures)
{
}

std::string CPPClientStubGenerator::generateStub()
{
    string tmp = TEMPLATE_CLIENT_STUB;
    replaceAll(tmp, "<stubname>", stubname);

    string stub_upper = stubname;
    std::transform(stub_upper.begin(), stub_upper.end(), stub_upper.begin(),
                   ::toupper);
    replaceAll(tmp, "<STUBNAME>", stub_upper);

    //generate procedures
    stringstream procedure_string;
    for (vector<Procedure>::iterator it = procedures.begin(); it != procedures.end(); it++)
    {
        procedure_string << generateMethod(*it) << endl;
    }

    replaceAll(tmp, "<methods>", procedure_string.str());
    return tmp;
}

string CPPClientStubGenerator::generateMethod(Procedure &proc)
{
    string tmp = TEMPLATE_CLIENT_METHOD;

    //set methodname
    replaceAll(tmp, "<methodname>", normalizeString(proc.GetProcedureName()));

    //build parameterlist
    stringstream assignment_string;

    parameterNameList_t list = proc.GetParameters();

    if(list.size() > 0)
    {
        for (parameterNameList_t::iterator it = list.begin(); it != list.end(); it++)
        {
            if(proc.GetParameterDeclarationType() == PARAMS_BY_NAME)
            {
                assignment_string << "p[\"" << it->first << "\"] = " << it->first
                                  << "; " << endl;
            }
            else
            {
                assignment_string << "p.append(" << it->first << ");" << endl;
            }
        }
    }
    else
    {
        assignment_string << "p = Json::nullValue;";
    }

    replaceAll(tmp, "<parameters>", generateParameterDeclarationList(proc));
    replaceAll(tmp, "<parameter_assign>", assignment_string.str());

    if (proc.GetProcedureType() == RPC_METHOD)
    {
        replaceAll(tmp, "<return_type>", toCppType(proc.GetReturnType()));
        stringstream result;
        result <<  "Json::Value result = this->CallMethod(\"" + proc.GetProcedureName() + "\",p);" << endl;
        result <<  "    if (result" << isCppConversion(proc.GetReturnType()) << ")" << endl;
        result <<  "        return result" << toCppConversion(proc.GetReturnType()) << ";" << endl;
        result << "     else " << endl;
        result << "         throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());" << endl;
        replaceAll(tmp, "<return_statement>", result.str());
    }
    else
    {
        replaceAll(tmp, "<return_type>", "void");
        replaceAll(tmp, "<return_statement>", "this->CallNotification(\"" + proc.GetProcedureName() + "\",p);");
    }

    return tmp;
}

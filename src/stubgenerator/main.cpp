/**
 * @file main.cpp
 * @date 03.01.2013
 * @author Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @brief This application generates stubs for all specified methods
 * and notifications of a given file
 */

#include <string>
#include <iostream>

#include <jsonrpc/server.h>
#include <jsonrpc/client.h>
#include <jsonrpc/common/procedure.h>

#include <argtable2.h>

#include "cppclientstubgenerator.h"
#include "serverstubgenerator.h"

using namespace std;
using namespace jsonrpc;

int main(int argc, char** argv)
{
    struct arg_lit *help        = arg_lit0("h","help", "print this help and exit");
    struct arg_file *inputfile  = arg_file0("i", "input", "<inputfile>.json", "path of input specification file");
    struct arg_str *classname   = arg_str0("c", "class", NULL, "name of the class");
    struct arg_str *server      = arg_str0("s", "server", "<filename>.h", "name of the server stubfile");
    struct arg_str *cppclient   = arg_str0(NULL, "cpp", "<filename>.h", "name of the cpp client stubfile");
    struct arg_end *end         = arg_end(20);
    void* argtable[] = {help, inputfile, classname, server, cppclient, end};

    int nerrors = arg_parse(argc,argv,argtable);
    if (nerrors > 0)
    {
        //  cerr << "Invalid arguments: try --help for more information" << endl;
        arg_print_errors(stderr, end, argv[0]);
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }

    if (help->count > 0 || argc == 1)
    {
        cout << "Usage: " << argv[0] << " "; cout.flush();
        arg_print_syntax(stdout,argtable,"\n"); cout << endl;
        arg_print_glossary_gnu(stdout, argtable);
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 0;
    }

    if (inputfile->count == 0 || classname->count == 0)
    {
        cerr << "Invalid arguments: -i|--input and -c|--class parameter must be provided" << endl;
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }

    try {

        if (server->count > 0)
        {
            ServerStubGenerator serverstub(classname->sval[0], inputfile->filename[0]);
            serverstub.generateStubToFile(server->sval[0]);
        }

        if (cppclient->count > 0)
        {
            CPPClientStubGenerator cppclientstub(classname->sval[0], inputfile->filename[0]);
            cppclientstub.generateStubToFile(server->sval[0]);
        }
    } catch (const JsonRpcException &ex)
    {
        cerr << ex.what() << endl;
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }
    return 0;
}

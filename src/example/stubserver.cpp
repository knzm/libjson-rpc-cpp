/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubserver.cpp
 * @date    02.05.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/
#include <iostream>

#include "gen/abstractsubserver.h"

using namespace jsonrpc;
using namespace std;

class MyStubServer : public AbstractStubServer
{
    public:
        MyStubServer(AbstractServerConnector &connector);

        virtual void notifyServer();
        virtual std::string sayHello(const std::string& name);
        virtual int addNumbers(const int& param1, const int& param2);
};

MyStubServer::MyStubServer(AbstractServerConnector &connector) :
    AbstractStubServer(connector)
{
}

void MyStubServer::notifyServer()
{
    cout << "Server got notified" << endl;
}

string MyStubServer::sayHello(const string &name)
{
    return "Hello " + name;
}

int MyStubServer::addNumbers(const int &param1, const int &param2)
{
    return param1 + param2;
}

int main()
{
    HttpServer httpserver(8080);
    MyStubServer s(httpserver);
    s.StartListening();

    getchar();

    s.StopListening();

    return 0;
}

/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    test_client.cpp
 * @date    28.09.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <jsonrpc/client.h>
#include "server.h"

using namespace jsonrpc;
using namespace std;

bool check_exception1(JsonRpcException const&ex)
{
    return ex.GetCode() == Errors::ERROR_CLIENT_CONNECTOR;
}

BOOST_AUTO_TEST_CASE(test_client_httpclient_error)
{
    HttpClient c("absdfasöj");
    string result;
    BOOST_CHECK_EXCEPTION(c.SendRPCRequest("foo", result), JsonRpcException, check_exception1);
}

BOOST_AUTO_TEST_CASE(test_client_httpclient_success)
{
    HttpClient c("http://www.google.at");
    string result;
    c.SendRPCRequest("foo", result);
    BOOST_CHECK_EQUAL(result.substr(0, 15), "<!DOCTYPE html>");

    c.SetUrl("http://docs.google.com");
    c.SendRPCRequest("foo", result);
    BOOST_CHECK_EQUAL(result.substr(0, 15), "<!DOCTYPE html>");
}

BOOST_AUTO_TEST_CASE(test_client_clientprotocol_batchrequest)
{
    HttpServer sconn(8383);
    HttpClient cconn("http://localhost:8383");
    TestServer server(sconn);
    Client client(cconn);



    //client.BuildBatchRequest()
}

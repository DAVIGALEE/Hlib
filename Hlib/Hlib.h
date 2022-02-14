#pragma once

#ifndef HLIB_H
#define HLIB_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <thread>
#include <vector>
#include <unordered_map>
#pragma comment(lib, "Ws2_32.lib")

#define EMPTY ""

namespace Hlib{

    enum IPv {
        IPv4,
        IPv6,
    };

    enum Methods {
        GET,
        POST,
        _DELETE,
        PUT,
        CONNECT,
        TRACE,
    };

    void * res();
    void req();

    class HTTP {

    private:
        std::string mapp;
        std::unordered_map<std::string , std::vector<std::string>> routers;
        int dataindex;
        bool run;
        void recvHTTP(int sock, char *buff, size_t len, int flag = 0);
        int recvHTTP();
        void sendHTTP(int sock, char *buff, size_t len, int flag = 0);
        int sendHTTP();
        WSADATA wsaData;
        struct sockaddr_in address;
        const char*   s_ipAddress;
        int __ip;
        int _port;
        int _result;
        SOCKET s_socket;
        SOCKET c_socket;
        int c_send;
        char recvbuf[512];
        int recvbuflen = 512;
        char *local = "127.0.0.1";
        int c_recv;
        int new_socket;
        char *HTTPdata="HTTP/1.1 , std::string stutus\nContent-Type: text/html\nContent-Length: 30\n\n<h1> Hello world! </h1>";
        const char *bdata;
        char buffer[30000] = {0};
        std::string data;
        void parseData(std::string buff);
        std::string resMaker(std::string httpv, std::string ct, std::string cl, std::string resdata);
        std::string str;
        std::string method;
        std::string router;
        bool fav;
    public:
        HTTP();
        int createServer(IPv _ipv, int type, int protocol, int port);
        void ShutDown(int c_sock, int s_sock, int exit_code = SD_SEND);
        void Listen();
        void Checker(std::string method);
        void Get(std::string path);
        void Post(std::string path, void callBack());
        void Put(std::string path, void callBack());
        void _Delete(std::string path, void callBack());
    };
}

#endif

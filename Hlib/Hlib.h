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

#pragma comment(lib, "Ws2_32.lib")

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

    class Sock {

    private:
        WSADATA wsaData;
        struct sockaddr_in address;
        const char*   s_ipAddress;
        int __ip;
        int _port;
        int _result;
        SOCKET s_socket;
        SOCKET c_socket;
        int c_result;
        char recvbuf[512];
        int recvbuflen = 512;
        std::string local = "127.0.0.1";
        int c_send;
        int new_socket;
        char hello[100] = "Hello from server";
    public:
        Sock(IPv _ipv, int service, int protocol, int port);
        int disconnect;
        void inputU();
    };
}

#endif
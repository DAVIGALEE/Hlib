#pragma once

#ifndef HLIB_H
#define HLIB_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

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
        struct addrinfo *result = NULL, *ptr = NULL, hints;
        int _ip;
        int _port;
        int _result;

	public:
		Sock(IPv _ipv, int service, int protocol, int port);
        int disconnect;

	};
}

#endif
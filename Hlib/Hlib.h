#pragma once

#ifndef HLIB_H
#define HLIB_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <fstream>
#ifdef _WIN32
    #include <winsock2.h>
    #include <iphlpapi.h>
    #include <winsock.h>
    #include <ws2tcpip.h>
    #include <WS2tcpip.h>
    #include <windows.h>
#else
    #include <string.h>	//strlen
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif
#include <vector>
#include <unordered_map>

#pragma comment(lib, "Ws2_32.lib")

#define EMPTY ""

namespace Hlib {

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

    void req();
    std::string res(std::string resdata, std::string status = "200 OK", std::string ct = "Content-Type: text/html");

    class HTTP {

    private:
        #ifdef _WIN32
            struct sockaddr_in address;
            SOCKET s_socket;
            SOCKET c_socket;
            WSADATA wsaData;
            PCSTR localhost = "127.0.0.1";
        #else 
            int s_socket;
            int c_socket;
            struct sockaddr_in address;
        #endif

        std::ifstream read;

        std::string line;
        std::string _file;
        std::string mapp;
        std::string str;
        std::string method;
        std::string router;
        std::string data;
        std::string httpVer;
        std::string ct;
        std::string cl;
        std::string hdr;

        int dataindex;
        int recvHTTP();
        int sendHTTP();
        int __ip;
        int _port;
        int _result;
        int c_send;
        int recvbuflen = 512;
        int c_recv;
        int new_socket;

        bool run;
        bool fav;

        void parsePost(std::string path);
        void recvHTTP(int sock, char *buff, size_t len, int flag = 0);
        void parseData(std::string buff);
        void sendHTTP(int sock, char const *buff, size_t len, int flag = 0);

        const char* s_ipAddress;
        const char *bdata;
               

        const char *buffHT;
        char recvbuf[512];
        char *local = "127.0.0.1";
        char *HTTPdata="HTTP/1.1 , std::string stutus\nContent-Type: text/html\nContent-Length: 30\n\n<h1> Hello world! </h1>";
        char buffer[30000] = {0};

        std::unordered_map<std::string, std::vector<std::string>> routers;
        std::unordered_map<std::string, std::vector<std::string>> resMap;
    public:
        HTTP();
        int createServer(IPv _ipv, int type, int protocol, int port);
        
        #ifdef _WIN32
            void ShutDown(int c_sock, int s_sock, int exit_code = SD_SEND);
        #else
            void ShutDown(int c_sock,  int s_sock, int exit_code);
        #endif
        void Listen();
        void Checker(std::string method);
        void Get(std::string path, std::string res);
        void Post(std::string path, std::string res);
        void Put(std::string path, std::string res);
        void _Delete(std::string path, std::string res);

        std::string File(std::string path);
    };
}

#endif

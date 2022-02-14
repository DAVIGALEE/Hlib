#include <iostream>
#include "Hlib.h"

//establish socket

//establish conncetion

//create functions GET,POST,DELETE,HEAD,PUT,CONNECT,OPTIONS,TRACE,PATCH

//HTTP REQUEST, RESPONSE

// TODO 
// Init func (Sock() constructor)
// CreateServer func (createServer(IPv, type, protocol))
// Listen func (listen(port))
// Route func (Get(path, func res, req), Put(path, func res, req), Post(path, func res, req), Delete(path, func res, req))

// create socket SOCK() func
Hlib::Sock::Sock(Hlib::IPv _ipv, int service, int protocol, int port) {
    // winsock init
    WSADATA wsadata;
    WORD ver = MAKEWORD(2,2);
    _result = WSAStartup(ver, &wsaData);
    if (_result != 0) {
        printf("WSAStartup failed: %d\n", _result);
        exit(EXIT_FAILURE);
    }

    // IP type checker
    if (_ipv == IPv4) {
        __ip = AF_INET;
    } else if (_ipv == IPv6) {
        __ip = AF_INET6;
    }

    // sock binding
    s_socket = socket(__ip,service,protocol);
    ZeroMemory(&address, sizeof (address));
    address.sin_family = __ip;
    address.sin_port = htons(port);
    inet_pton(__ip, "127.0.0.1",&address.sin_addr);
    // bind things to socket
    if(bind(s_socket,(sockaddr*)&address,sizeof(address)) == SOCKET_ERROR){
        exit(WSAGetLastError());
    }
    // listen incoming packages
    if (listen(s_socket, 20) == SOCKET_ERROR) {
        exit(WSAGetLastError());
    }
    c_socket = INVALID_SOCKET;


// establishing connection with client


// accepts packages
    do
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(s_socket, nullptr, nullptr))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        c_send = recv( new_socket , buffer, 30000, 0);
        printf("user %s\n",buffer );
        c_result = send(new_socket , hello, c_send, 0);
        if(c_result == SOCKET_ERROR){
            printf("c_result shutdown failed: %d\n", WSAGetLastError());
            closesocket(c_socket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        printf("------------------Hello message sent-------------------\n");
        // c_send = recv( new_socket , buffer, 30000, 0);
        printf("%s \n", hello);

    } while(c_send > 0);

    // shutdown socket
    c_result = shutdown(c_socket, SD_SEND);
    if(c_result == SOCKET_ERROR) {
        printf(" shutdown failed: %d\n", WSAGetLastError());
        closesocket(c_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    closesocket(new_socket);
    WSACleanup();


};
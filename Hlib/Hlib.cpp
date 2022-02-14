#include <iostream>
#include "Hlib.h"
#define EMPTY ""

int Hlib::HTTP::createServer(Hlib::IPv _ipv, int type, int protocol, int port) {
    if (_ipv == IPv4) {
        __ip = AF_INET;

    } else if (_ipv == IPv6) {
        __ip = AF_INET6;
    }

    s_socket = socket(__ip,type,protocol); // socket create
    ZeroMemory(&address, sizeof (address));
    address.sin_family = __ip; // IP version
    address.sin_port = htons(port); // Port
    inet_pton(__ip, local,&address.sin_addr); // converting IP address in bytes
    // bind stuff to socket
    if(bind(s_socket,(sockaddr*)&address,sizeof(address)) == SOCKET_ERROR){
        printf("BIND ERROR");
        return 0;
    }
    return 1;
}

void Hlib::HTTP::Get(std::string path, void callBack()) {

}

void Hlib::HTTP::Listen() {
    if (listen(s_socket, SOMAXCONN) == SOCKET_ERROR) {
        exit(WSAGetLastError());
    }
    c_socket = INVALID_SOCKET;
    // socket is ready to listen incoming connections
    run = true;

    while (run)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        //accepting client socket
        if ((new_socket = accept(s_socket, nullptr, nullptr))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        //receiving sockemake-build-debug\Hlib.et request
        recvHTTP(new_socket, buffer, 30000);
        if (c_recv > 0 ) {
            //sending response
            sendHTTP(new_socket, HTTPdata, strlen(buffer));

        }
        else if (c_recv == 0) {
            printf("connection closing...");
            run = false;
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(new_socket);
            WSACleanup();
            run = false;
            exit(EXIT_FAILURE);
        }

    }


    // shutdown socket
    ShutDown(c_socket,new_socket);
}

void Hlib::HTTP::recvHTTP(int sock, char *buff, size_t len, int flag) {
    c_recv = recv( sock , buff, len, flag);
    parseData(buff);
   // printf("%s\n",buff);
}

int Hlib::HTTP::recvHTTP() {
    return c_recv;
}

void Hlib::HTTP::sendHTTP(int sock, char *buff, size_t len, int flag) {
    c_send = send(sock , buff, len, flag);
    if(c_send == SOCKET_ERROR){
        printf("c_result shutdown failed: %d\n", WSAGetLastError());
        closesocket(c_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
  //  printf("sent -> %s\n", buff);
}

int Hlib::HTTP::sendHTTP() {
    return c_send;
}
void Hlib::HTTP::ShutDown(int c_sock,  int s_sock, int exit_code) {
    c_send = shutdown(c_sock, exit_code);
    if(c_send == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(c_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    closesocket(s_sock);
    WSACleanup();
}

void Hlib::HTTP::parseData(std::string buff) {
    for (int i = 0; i < buff[i]; i++){
        if(buff[i] == '\n') {
            break;
        }
        data = data + buff[i];
    }
    data = data + " ";
    std::string method;
    std::string fileName;
    std::vector<std::string> dataArray;
    for(int i = 0; i < data.size(); i++) {
        dataindex = data.size();
        if (data[i] != ' ') {
            method = method + data[i];
        } else if (data[i] == ' ') {
            dataArray.push_back(method);
            method = EMPTY;
        }
    }
    std::cout << dataArray[0] << " " << dataArray[1] << " " << dataArray[2] << buff <<std::endl;
    method = dataArray[0];
    fileName = dataArray[1];

    data = EMPTY;
}

// create socket SOCK() func
Hlib::HTTP::HTTP() {
    // winsock init
    WORD ver = MAKEWORD(2,2);
    _result = WSAStartup(ver, &wsaData);
    if (_result != 0) {
        printf("WSAStartup failed: %d\n", _result);
        exit(EXIT_FAILURE);
    }
}

#include <iostream>
#include "Hlib.h"

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
// Get() func
void Hlib::HTTP::Get(std::string path, std::string res) {
    routers["GET " + path].push_back("Method: GET");
    routers["GET " + path].push_back(res);
}
// Put() func
void Hlib::HTTP::Post(std::string path, std::string res) {
    routers["POST " + path].push_back("Method: POST");
    routers["POST " + path].push_back(res);
}

void Hlib::HTTP::_Delete(std::string path, std::string res) {
    routers["DELETE " + path].push_back("Method: POST");
    routers["DELETE " + path].push_back(res);
}

void Hlib::HTTP::Put(std::string path, std::string res) {
    routers["PUT " + path].push_back("Method: POST");
    routers["PUT " + path].push_back(res);
}

std::string Hlib::res(std::string resdata, std::string status, std::string ct) {
    std::string len = std::to_string(resdata.length());
    std::string resDATA;
    resDATA = "HTTP/1.1 " + status + "\n" + ct + "\n" + "Content-Length: " + len + "\n\n" + resdata;
    return resDATA;
}

void Hlib::HTTP::Listen() {
    if (listen(s_socket, SOMAXCONN) == SOCKET_ERROR) {
        exit(WSAGetLastError());
    }
    c_socket = INVALID_SOCKET;
    // socket is ready to listen incoming connections
    run = true;
    fav = false;

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
            printf("%s\n", buffer);
            Checker(router);
            printf("%s\n", router.c_str());
            if(!fav) {
                sendHTTP(new_socket, buffHT, strlen(buffer));
                std::cout << bdata << "\n";
            }
        }
        else if (c_recv == 0) {
            printf("connection closing...");
        } else {
            closesocket(new_socket);
        }
    }
    // shutdown socket
    ShutDown(c_socket,new_socket);
    run = false;
}

void Hlib::HTTP::recvHTTP(int sock, char *buff, size_t len, int flag) {
    c_recv = recv( sock , buff, len, flag);
    parseData(buff);
}

int Hlib::HTTP::recvHTTP() {
    return c_recv;
}

void Hlib::HTTP::sendHTTP(int sock, char *buff, size_t len, int flag) {
    if (router == "/favicon.ico") {
        printf("FAVICON OMITTED\n");
        bdata = EMPTY;
    }
    else {
        c_send = send(sock, buff, len, flag);
    }
    if(c_send == SOCKET_ERROR){
        printf("c_result shutdown failed: %d\n", WSAGetLastError());
        closesocket(c_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

int Hlib::HTTP::sendHTTP() {
    return c_send;
}
// shutdown socket
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
// parse buff
void Hlib::HTTP::parseData(std::string buff) {
    for (int i = 0; i < buff[i]; i++){
        if(buff[i] == '\n') {
            break;
        }
        data = data + buff[i];
    }
    data = data + " ";
    std::vector<std::string> dataArray;
    for(int i = 0; i < data.size(); i++) {
        dataindex = data.size();
        if (data[i] != ' ') {
            str = str + data[i];
        }
        else if (data[i] == ' ') {
            dataArray.push_back(str);
            str = EMPTY;
        }
    }
    method = dataArray[0];
    router = dataArray[1];
    printf("%s\n",router.c_str());
    fav = false;
    data = EMPTY;
}

void Hlib::HTTP::parsePost(std::string path) {

}

// check routers
void Hlib::HTTP::Checker(std::string router){
    if(routers.find(method + " " + router) == routers.end()){
        printf("404 NOT FOUND \n");
        buffHT = "HTTP/1.1 404 Bad Request\nContent-Type: text/html\nContent-Length: 38\n\n<center><h1>404 NOT FOUND </h1></center>";
    } else {
        if (method == "GET") {
            bdata = routers["GET " + router][1].c_str();
            buffHT = routers["GET " + router][1].data();
        } else if (method == "POST") {
            bdata = routers["POST " + router][1].c_str();
            buffHT = routers["POST " + router][1].data();
        } else if (method == "PUT") {
            bdata = routers["PUT " + router][1].c_str();
            buffHT = routers["PUT " + router][1].data();
        } else if (method == "DELETE") {
            bdata = routers["DELETE " + router][1].c_str();
            buffHT = routers["DELETE " + router][1].data();
        }
        //std::cout << " bff" <<buffHT << "\n";
    }
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

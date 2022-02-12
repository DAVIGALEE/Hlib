//
// Created by PC on 12-Feb-22.
//

#include <iostream>
#include "headers/Hlib.h"

class Niko {

public:

     void davit();
};

int main() {

    Hlib::Sock app(Hlib::IPv4, SOCK_STREAM, IPPROTO_TCP, 8080);

    return 0;
}
//
// Created by PC on 12-Feb-22.
//

#include <iostream>
#include "Hlib.h"

using namespace Hlib;

int main() {

    Sock app(Hlib::IPv4, SOCK_STREAM, IPPROTO_TCP, 8080);

    return 0;
}
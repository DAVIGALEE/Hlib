//
// Created by PC on 12-Feb-22.
//

#include <iostream>
#include "Hlib.h"
#include <string>
#include <vector>
using namespace Hlib;

int main() {
    HTTP app;

    app.createServer(IPv4, SOCK_STREAM, IPPROTO_TCP, 8080);

    // app.dir(join.dir("public"))

    app.Get("/About/profile");
    // app.Post('/users', callbacks);
    // hash map [re]

    app.Listen();

    return 0;
}
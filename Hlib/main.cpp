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

    // app.dir(join.dir("public"));

    app.Get("/", res("<h1> default / route </h1>"));
    app.Get("/home", res("<h1> /home route </h1>"));

    // app.Post('/users', callbacks);

    app.Listen();

    return 0;
}
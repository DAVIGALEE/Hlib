//
// Created by PC on 12-Feb-22.
//

#include <iostream>
#include "Hlib.h"

using namespace Hlib;

int main() {
    HTTP app;

    app.createServer(IPv4, SOCK_STREAM, IPPROTO_TCP, 80);

    // app.dir(join.dir("public"));

    app.Get("/home", res("<h1> /home route </h1>"));
    app.Put("/home", res("<h1> /home rousste </h1>"));
    app.Get("/", res("<h1> /def route </h1>"));

    // app.Post('/users', callbacks);

    app.Listen();

    return 0;
}

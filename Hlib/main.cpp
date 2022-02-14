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

    // app.get('/users', callbacks);
    // app.post('/users', callbacks);

    app.Listen();

    return 0;
}
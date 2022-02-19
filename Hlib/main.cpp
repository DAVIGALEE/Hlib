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

    app.createServer(IPv4, SOCK_STREAM, IPPROTO_TCP, 80);

    // app.dir(join.dir("public"));

    app.Get("/home", res("<form action=\"/home\" method=\"POST\">\n"
                         "  <div>\n"
                         "    <label for=\"say\">What greeting do you want to say?</label>\n"
                         "    <input name=\"say\" id=\"say\" value=\"Hi\">\n"
                         "  </div>\n"
                         "  <div>\n"
                         "    <label for=\"to\">Who do you want to say it to?</label>\n"
                         "    <input name=\"to\" id=\"to\" value=\"Mom\">\n"
                         "  </div>\n"
                         "  <div>\n"
                         "    <button>Send my greetings</button>\n"
                         "  </div>\n"
                         "</form>"));

    app.Post("/home", res("<h1> /home </h1>"));

    app.Get("/", res(app.File("D:\\GitHub\\Hlib\\example\\index.html")));

    // app.Post('/users', callbacks);

    app.Listen();

    return 0;
}

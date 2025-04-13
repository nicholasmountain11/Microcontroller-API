#include <iostream>
#include "include/httplib.h"
#include "include/json.hpp"
using json = nlohmann::json;

int main()
{
    using namespace httplib;
    Server svr;

    svr.Get("/test", [](const Request &, Response &res)
            {
        json response = {
            {"message", "Hello, World!"}
        };
         res.set_content(response.dump(), "application/json"); });

    svr.listen("0.0.0.0", 8080);
}
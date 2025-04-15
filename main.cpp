#include <iostream>
#include "include/ControllerManager.h"
// #include <ctime>
// #include <thread>
// #include <chrono>
// #include <memory>
#include "include/httplib.h"
#include "include/json.hpp"
using json = nlohmann::json;

int main()
{
    using namespace httplib;
    Server svr;
    ControllerManager manager;
    int s = manager.addSensor();

    svr.Get("/test", [](const Request &, Response &res)
            {
        json response = {
            {"message", "Hello, World!"}
        };
         res.set_content(response.dump(), "application/json"); });

    svr.Get(R"(/sensor/(\d+))", [&](const Request &req, httplib::Response &res)
            {
        int sensorId = std::stoi(req.matches[1]);
        res.set_content(manager.getSensorData(sensorId), "text/plain"); });

    svr.listen("0.0.0.0", 8080);
}
/**
 * @file main.cpp
 * @brief Entry point of the API server for controlling sensors and actuators.
 *
 * This lightweight HTTP server initializes a ControllerManager instance and provides a REST API for:
 *  - Retrieving sensor data via GET requests
 *  - Sending commands to actuators via POST requests
 *  - A basic test route for health checks
 *
 * The server is powered by `cpp-httplib` and communicates with microcontrollers using TCP sockets
 */

#include <iostream>
#include "include/ControllerManager.h" ///< Manages communication with sensors and actuators
#include "include/httplib.h"           ///< HTTP server implementation
#include "include/json.hpp"            ///< JSON serialization (nlohmann::json)

using json = nlohmann::json;

/**
 * @brief Main entry point of the application.
 *
 * Sets up an HTTP server with three API endpoints:
 *  - GET /test
 *  - GET /sensor/{id}
 *  - POST /actuator/{id}
 *
 * @return Exit code (always 0)
 */
int main()
{
    using namespace httplib;

    Server svr;                ///< HTTP server instance
    ControllerManager manager; ///< Sensor/Actuator controller

    // Add default sensor and actuator (for testing/demo purposes)
    int s = manager.addSensor();
    int a = manager.addActuator();

    /**
     * @brief GET /test
     * Simple test endpoint that returns a Hello World message in JSON format.
     */
    svr.Get("/test", [](const Request &, Response &res)
            {
         json response = {
             {"message", "Hello, World!"}
         };
         res.set_content(response.dump(), "application/json"); });

    /**
     * @brief GET /sensor/{id}
     * Fetches sensor data for the given sensor ID.
     *
     * @param id Sensor index (e.g., /sensor/0)
     * @return JSON response containing sensor readings or error
     */
    svr.Get(R"(/sensor/(\d+))", [&](const Request &req, Response &res)
            {
         int sensorId = std::stoi(req.matches[1]);
         json response = manager.getSensorData(sensorId);
         res.set_content(response, "application/json"); });

    /**
     * @brief POST /actuator/{id}
     * Sends a command string to the specified actuator.
     *
     * @param id Actuator index (e.g., /actuator/0)
     * @body Raw string command to send (e.g., "ON")
     * @return JSON response echoing the command
     */
    svr.Post(R"(/actuator/(\d+))", [&](const Request &req, Response &res)
             {
         int actuatorId = std::stoi(req.matches[1]);
         std::string message = req.body;
         manager.sendActuatorCommand(actuatorId, message);
         json response = {
             {"message", message}
         };
         res.set_content(response.dump(), "application/json"); });

    // Start server on all interfaces at port 8080
    svr.listen("0.0.0.0", 8080);

    return 0;
}

# Home Automation API

## Goals

- Communicate with microcontrollers using TCP sockets.
- Build an API that allows future applications to send and receive messages with microcontrollers
- Learn how to use microcontrollers for home automation

## Objectives

- Use an internet connected microcontroller (ESP32 NodeMCU) to send an outbound TCP socket connection to a C++ program run on a different WiFi network.
- Create an Object Oriented Programming structure to manage multiple microcontroller socket connections at the same time.
- Write API routes that send or get messages to/from microcontrollers.
- Build microcontroller circuits that get sensor data or interact with their environment.
- Convert sensor data to JSON format before sending to the API.

## How It Works

### Microcontrollers
- Using the ESP32 NodeMCU microcontroller, we can connect to a WiFi network and send messages through a TCP socket. The microcontrollers create an outgoing socket connection so that they can connect to a server that is not on the same network without needing a public IP address.
- Microcontrollers are categorized as *sensors*, which measure their environment, and *actuators*, which carry out physical actions.
- *Sensors* measure data and send it as a JSON through a TCP socket, *actuators* receive commands and act accordingly.
- Right now, there is a sensor that measure temperature/humidity and an actuator that controls and LED.

### Connecting to the Microcontrollers

- For each connection to a microcontroller, a `SensorCommunicator` or `ActuatorCommunicator` is created.
- Theses Communicator objects accept a socket connection from a microcontroller, then send or receive messages.

### Managing Microcontroller Connections

- To manage all the different connections to microcontrollers, there is one `ControllerManager` object. 
- The `ControllerManager` keeps a list of sensors and actuators, and exposes methods that allow the API to send/receive messages to/from the microcontrollers.

### API 
- The `main.cpp` file is the entry point that runs the API with a few endpoints.
- GET /sensor/{sensor index} returns a JSON object containing the sensor data from the sensor at index {sensor index} in the `ControllerManager`'s sensor list.
- POST /actuator/{actuator index} has a request body of a message string to send to the actuator at index {actuator index} in the `ControllerManager`'s actuator index.
- The API can be configured to support many sensors and actuators.



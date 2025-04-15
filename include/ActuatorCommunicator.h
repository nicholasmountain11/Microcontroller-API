/**
 * @file ActuatorCommunicator.h
 * @brief Defines the ActuatorCommunicator class for managing TCP communication with an actuator.
 */

#ifndef ACTUATOR_COMMUNICATOR_H
#define ACTUATOR_COMMUNICATOR_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

/**
 * @class ActuatorCommunicator
 * @brief Handles TCP socket communication with a remote actuator.
 *
 * This class creates a TCP connection to an actuator at a specified IP and port,
 * allowing messages to be sent to control or trigger actuator behavior.
 */
class ActuatorCommunicator
{
private:
    std::string ip; /**< IP address of the actuator */
    int port;       /**< Port number used to connect to the actuator */
    int fd;         /**< File descriptor for the socket */
    int actuator_fd;
    struct sockaddr_in actuator_addr;
    struct sockaddr_in sock_addr; /**< Struct for storing actuator address info */

public:
    /**
     * @brief Constructs a new ActuatorCommunicator instance.
     *
     * Initializes the socket and prepares the address structure for connection.
     *
     * @param ip The IP address of the actuator.
     * @param port The port number to connect to.
     */
    ActuatorCommunicator();

    /**
     * @brief Connects the socket to the actuator.
     *
     * Attempts to establish a TCP connection with the actuator.
     * Exits the program if the connection fails.
     */
    bool connectToActuator();

    /**
     * @brief Sends a string message to the actuator.
     *
     * @param message The message to be sent to the actuator.
     */
    void sendMessage(const std::string &message);

    /**
     * @brief Destroys the ActuatorCommunicator object and closes the socket.
     */
    ~ActuatorCommunicator();
};

#endif // ACTUATOR_COMMUNICATOR_H

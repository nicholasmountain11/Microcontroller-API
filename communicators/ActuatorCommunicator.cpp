#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "../include/ActuatorCommunicator.h"

#define PORT 9002
#define BUFFER_SIZE 4096

ActuatorCommunicator::ActuatorCommunicator() : fd(-1)
{
    char buffer[BUFFER_SIZE];
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("Failed to set SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

bool ActuatorCommunicator::connectToActuator()
{
    if (listen(fd, 5) < 0)
    {
        perror("Bind failed");
        return false;
    }
    std::cout << "Listening for actuator" << std::endl;

    socklen_t actuator_addr_len = sizeof(actuator_addr);
    actuator_fd = accept(fd, (struct sockaddr *)&actuator_addr, &actuator_addr_len);
    if (actuator_fd < 0)
    {
        perror("Accept failed");
        return false;
    }
    std::cout << "Connected to actuator!" << std::endl;
    return true;
}

void ActuatorCommunicator::sendMessage(const std::string &message)
{
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("Failed to send message");
    }
    else
    {
        std::cout << "Send: " << message << std::endl;
    }
}
/**
 * @file SensorCommunicator.cpp
 * @brief Implementation of the SensorCommunicator class for managing TCP communication with a sensor device.
 */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../include/SensorCommunicator.h"

SensorCommunicator::SensorCommunicator(const std::string &ip, int port) : ip(ip), port(port), fd(-1), is_running(false)
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

    if (listen(fd, 5) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening for sensor" << std::endl;

    socklen_t sensor_addr_len = sizeof(sensor_addr);
    sensor_fd = accept(fd, (struct sockaddr *)&sensor_addr, &sensor_addr_len);
    if (sensor_fd < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
}
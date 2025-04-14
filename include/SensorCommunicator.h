/**
 * @file SensorCommunicator.h
 * @brief Defines the SensorCommunicator class for handling TCP communication with a sensor.
 */

#ifndef SENSOR_COMMUNICATOR_H
#define SENSOR_COMMUNICATOR_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define PORT 9001

/**
 * @class SensorCommunicator
 * @brief Manages a TCP connection to a sensor for receiving data asynchronously.
 *
 * This class establishes a connection to a remote sensor, receives data over TCP,
 * and stores the latest message in a thread-safe buffer.
 */
class SensorCommunicator
{
private:
    std::string ip; /**< IP address of the sensor */
    int port;       /**< Port number used to connect to the sensor */
    int fd;         /**< File descriptor for the TCP socket */
    int sensor_fd;
    struct sockaddr_in sensor_addr;
    struct sockaddr_in sock_addr; /**< Address structure for the sensor */
    std::string data;             /**< Latest data received from the sensor */
    std::mutex data_mutex;        /**< Mutex to protect access to sensor data */
    std::thread listen_thread;    /**< Thread that continuously receives messages */
    bool is_running;              /**< Flag to control the listener thread loop */

public:
    /**
     * @brief Constructs a new SensorCommunicator instance.
     *
     */
    SensorCommunicator();

    /**
     * @brief Establishes a TCP connection to the sensor.
     *
     * Should be called before attempting to receive messages.
     */
    bool connectToSensor();

    /**
     * @brief Starts a background thread to receive messages from the sensor.
     *
     * Messages are received continuously and stored in a thread-safe buffer.
     */
    void receiveMessages();

    /**
     * @brief Gets the most recently received message from the sensor.
     *
     * @return Latest sensor data as a string.
     */
    std::string getData();

    /**
     * @brief Destructor that stops the listener thread and closes the socket.
     */
    ~SensorCommunicator();
};

#endif // SENSOR_COMMUNICATOR_H

/**
 * @file ControllerManager.h
 * @brief Declares the ControllerManager class for managing sensor and actuator communication.
 */

#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "SensorCommunicator.h"
#include <vector>
#include <memory>

/**
 * @class ControllerManager
 * @brief Central manager for coordinating multiple sensors and actuators.
 *
 * This class allows dynamic addition of sensors and actuators, and provides
 * access to sensor data and actuator control via simple indexed methods.
 */
class ControllerManager
{
private:
    std::vector<std::shared_ptr<SensorCommunicator>> sensors; /**< List of connected sensor communicators */

public:
    /**
     * @brief Adds a new sensor to the system and begins receiving data from it.
     *
     * @param ip The IP address of the sensor.
     * @param port The port number the sensor listens on.
     * @return The index of the sensor in the internal list.
     */
    int addSensor();

    /**
     * @brief Adds a new actuator to the system and establishes a connection.
     *
     * @param ip The IP address of the actuator.
     * @param port The port number the actuator listens on.
     * @return The index of the actuator in the internal list.
     */
    //  int addActuator(const std::string &ip, int port);

    /**
     * @brief Retrieves the latest data received from a specified sensor.
     *
     * @param sensorIdx The index of the sensor in the internal list.
     * @return The latest sensor data, or an error message if the index is invalid.
     */
    std::string getSensorData(int sensorIdx);

    /**
     * @brief Sends a command to a specified actuator.
     *
     * @param actuatorIdx The index of the actuator in the internal list.
     * @param message The command message to send.
     */
    //  void sendActuatorCommand(int actuatorIdx, const std::string &message);
};

#endif // CONTROLLER_MANAGER_H

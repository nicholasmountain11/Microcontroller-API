/**
 * @file ControllerManager.cpp
 * @brief Implementation of the ControllerManager class, which coordinates communication with sensors and actuators.
 */

#include "include/ControllerManager.h"
#include <iostream>
#include "include/json.hpp"
using json = nlohmann::json;

int ControllerManager::addSensor()
{
    std::shared_ptr<SensorCommunicator> sensor = std::make_shared<SensorCommunicator>();
    if (sensor->connectToSensor())
    {
        sensor->receiveMessages();
    }
    else
    {
        perror("Failed to connect to the sensor");
        return -1;
    }
    sensors.push_back(sensor);
    return sensors.size() - 1;
}

int ControllerManager::addActuator()
{
    std::shared_ptr<ActuatorCommunicator> actuator = std::make_shared<ActuatorCommunicator>();
    if (!actuator->connectToActuator())
    {
        perror("Failed to connect to actuator");
        return -1;
    }
    actuators.push_back(actuator);
    return actuators.size() - 1;
}

json ControllerManager::getSensorData(int sensorIdx)
{
    if (sensorIdx >= 0 && sensorIdx < sensors.size())
    {
        std::string response = sensors[sensorIdx]->getData();
        json result = json::parse(response);
        return result.dump();
    }
    return "Invalid sensor index";
}

void ControllerManager::sendActuatorCommand(int actuatorIdx, const std::string &message)
{
    if (actuatorIdx >= 0 && actuatorIdx < actuators.size())
    {
        actuators[actuatorIdx]->sendMessage(message);
    }
    else
    {
        std::cout << "Invalid sensor index" << std::endl;
    }
}
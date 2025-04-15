/**
 * @file ControllerManager.cpp
 * @brief Implementation of the ControllerManager class, which coordinates communication with sensors and actuators.
 */

#include "include/ControllerManager.h"
#include <iostream>

int ControllerManager::addSensor()
{
    std::cout << "in addSensor" << std::endl;
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

std::string ControllerManager::getSensorData(int sensorIdx)
{
    if (sensorIdx >= 0 && sensorIdx < sensors.size())
    {
        return sensors[sensorIdx]->getData();
    }
    return "Invalid sensor index";
}
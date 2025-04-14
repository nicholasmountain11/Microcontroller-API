/**
 * @file ControllerManager.cpp
 * @brief Implementation of the ControllerManager class, which coordinates communication with sensors and actuators.
 */

#include "include/ControllerManager.h"
#include <iostream>

std::string ControllerManager::getSensorData(int sensorIdx)
{
    if (sensorIdx >= 0 && sensorIdx < sensors.size())
    {
        return sensors[sensorIdx]->getData();
    }
    return "Invalid sensor index";
}
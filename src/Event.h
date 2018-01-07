// Event.h
// Created by Tommy Janna
// Description of file: Function for handling events according to ship location.
// Created on January 2, 2018
// Last modified on January 2, 2018

#ifndef EVENT_H
#define EVENT_H

#include "GameObjects/Ship.h"

class Ship;

namespace Event
{
    void StartEvent(Ship* ship);
    void ResetLocations();

    static bool visited[15];
}

#endif
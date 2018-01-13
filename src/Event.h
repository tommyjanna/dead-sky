// Event.h
// Created by Tommy Janna
// Description of file: Function for handling events according to ship location.
// Created on January 2, 2018
// Last modified on January 2, 2018

#ifndef EVENT_H
#define EVENT_H

#include "GameObjects/Ship.h"
#include "GameObjects/Enemy.h"
#include "SceneManager.h"

class Ship;
class Enemy;

namespace Event
{
    void UpdateEvent(Ship* ship, int panelNumber, int choice);
    void ResetLocations();
    void DestroyEnemy();

    static bool visited[15];
    static bool destroyEnemy;

    static Enemy* currentEnemy;
};

#endif
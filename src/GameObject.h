// GameObject.h
// Created by Tommy Janna
// Class name: GameObject
// Description of class: GameObject class which implements all necessary members for
//                       objects in the game such as position, texture 
//                       and an abstract update function.
// Created on October 24, 2017
// Last modified on October 24, 2017

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"
#include <vector>

class Texture;

class GameObject
{
public:

    GameObject();
    ~GameObject();

    void Update() {};
    void LoadTexture(std::string);

    GameObject* GetInstace() { return this; }
    bool GetToBeDestroyed() { return _toBeDestroyed; }

    Texture* _texture;

private:

    bool _toBeDestroyed;
};

#endif
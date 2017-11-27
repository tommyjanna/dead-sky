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

//#include "Game.h"
#include "Texture.h"
#include <vector>

class Texture;

class GameObject
{
public:

    GameObject();
    GameObject(SDL_Renderer*);
    virtual ~GameObject();

    virtual void Update() = 0; // (= 0) makes this a pure virtual method, so Update() must be implemented.
    void LoadTexture(std::string);

    static std::vector<GameObject*> _objects;

    GameObject* GetInstace() { return this; }
    bool _toBeDestroyed;

    Texture* _texture;

private:

};

#endif
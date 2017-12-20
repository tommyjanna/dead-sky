// GameObject.cpp
// Implementation of the GameObject class.
// Created on October 24, 2017
// Last modified on Dcember 16, 2017

#include "GameObject.h"

// Declare static members
std::vector<GameObject*> GameObject::_objects;

GameObject::GameObject(int x, int y, int width, int height, Uint8 layer, SDL_Renderer* renderer, std::string name)
{
    _toBeDestroyed = false;
    _name = name;
    _objects.push_back(this);
    _layer = layer;

    _texture = new Texture(x, y, width, height, renderer);
}

GameObject::~GameObject()
{
    delete _texture;
    _texture = NULL;
}
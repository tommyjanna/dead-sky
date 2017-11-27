// GameObject.cpp
// Implementation of the GameObject class.
// Created on October 24, 2017
// Last modified on October 24, 2017

#include "GameObject.h"

// Declare static members
std::vector<GameObject*> GameObject::_objects;

GameObject::GameObject(SDL_Renderer* renderer)
{
    _toBeDestroyed = false;
    _objects.push_back(this);

    _texture = new Texture(renderer);
}

GameObject::~GameObject()
{
    _texture->FreeTexture();
}
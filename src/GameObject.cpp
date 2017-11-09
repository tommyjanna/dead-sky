// GameObject.cpp
// Implementation of the GameObject class.
// Created on October 24, 2017
// Last modified on October 24, 2017

#include "GameObject.h"

std::vector<GameObject*> Game::_objects;

GameObject::GameObject()
{
    _toBeDestroyed = false;
    Game::_objects.push_back(this);

    _texture = new Texture();
}

GameObject::~GameObject()
{
    _texture->FreeTexture();
}
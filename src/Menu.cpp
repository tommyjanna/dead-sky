// Menu.cpp
// Implementation of the Menu class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Menu.h"

Menu::Menu()
{
    b = new Button(Game::_renderer, 0, 0, 0, 0);
    b->_texture->LoadTexture("../assets/graphics/polygonwhale.png");
}
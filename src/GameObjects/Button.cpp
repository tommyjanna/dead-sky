// Button.cpp
// Implementation of the Button class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Button.h"

Button::Button(SDL_Renderer* renderer, int width, int height, int x, int y) : GameObject(renderer, "Button")
{
    _buttonWidth = width;
    _buttonHeight = height;

    _x = x;
    _y = y;

    return;
}

Button::~Button()
{

}

void Button::Update()
{

}

void Button::Draw()
{
    _texture->Render(_x, _y);
}

void Button::Destroy()
{
    
}
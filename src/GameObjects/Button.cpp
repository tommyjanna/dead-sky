// Button.cpp
// Implementation of the Button class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Button.h"

Button::Button(SDL_Renderer* renderer, int width, int height, int x, int y, std::function<void()> const& event) : GameObject(renderer, "Button")
{
    _buttonWidth = width;
    _buttonHeight = height;

    _x = x;
    _y = y;

    _event = event;

    return;
}

Button::Button(SDL_Renderer* renderer, int width, int height, int x, int y, int fontSize, std::string text, std::function<void()> const& event) : GameObject(renderer, "Button + Text")
{
    _buttonWidth = width;
    _buttonHeight = height;

    _x = x;
    _y = y;

    _event = event;

    _texture->_font = TTF_OpenFont("../assets/fonts/lilliputsteps.ttf", fontSize);

    if(_texture->_font == NULL)
    {
        printf("Error loading fonts... Error %s\n", TTF_GetError());
    }

    else
    {
        SDL_Color colour = {0xFF, 0xFF, 0xFF};

        _texture->LoadRenderedText(text, colour);
    }

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
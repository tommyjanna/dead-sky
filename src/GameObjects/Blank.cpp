// Blank.cpp
// Implementation of the Blank class.
// Created on December 17, 2017
// Last modified on December 17, 2017

#include "Blank.h"

Blank::Blank(SDL_Renderer* renderer, int x, int y, int width, int height) : GameObject(x, y, width, height, renderer, "Blank")
{

}

Blank::Blank(SDL_Renderer* renderer, int x, int y, int width, int height, int fontSize, std::string text) : GameObject(x, y, width, height, renderer, "Blank")
{

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

Blank::~Blank()
{
}

void Blank::Update()
{
}

void Blank::Draw()
{
    _texture->Render();
}

void Blank::Destroy()
{
}
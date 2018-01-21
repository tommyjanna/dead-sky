// Blank.cpp
// Implementation of the Blank class.
// Created on December 17, 2017
// Last modified on December 17, 2017

#include "Blank.h"

Blank::Blank(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer) : GameObject(x, y, width, height, layer, renderer, "Blank")
{
    // Nothing really needs to be done.
    return;
}

Blank::Blank(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, int fontSize, std::string text) : GameObject(x, y, width, height, layer, renderer, "Blank")
{
    // Default font.
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

Blank::Blank(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, int fontSize, std::string font, std::string text) : GameObject(x, y, width, height, layer, renderer, "Blank")
{
    // Load custom font.
    _texture->_font = TTF_OpenFont(font.c_str(), fontSize);

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
    return;
}

void Blank::Update()
{
    return;
}

void Blank::Draw()
{
    if(_show)
    {
        _texture->Render();
    }
}

void Blank::Destroy()
{
    return;
}
// SplashScreen.cpp
// Implementation of the SplashScreen class.
// Created on November 8, 2017
// Last modified on November 8, 2017

#include "SplashScreen.h"

SplashScreen::SplashScreen(SDL_Renderer* renderer) : GameObject(renderer)
{
}

SplashScreen::~SplashScreen()
{
    Texture* g = new Texture();
}

void SplashScreen::Update()
{
    // Fade the texture for 3 seconds.
    if(_texture->Fade(3) == true)
    {
        _toBeDestroyed = true;
    }
}
// SplashScreen.cpp
// Implementation of the SplashScreen class.
// Created on November 8, 2017
// Last modified on November 8, 2017

#include "SplashScreen.h"

SplashScreen::SplashScreen(SDL_Renderer* renderer) : GameObject(renderer)
{
    _parentGO = GetInstace();
}

SplashScreen::~SplashScreen()
{
    
}

void SplashScreen::Update()
{
    _parentGO->_texture->Fade(3);
}
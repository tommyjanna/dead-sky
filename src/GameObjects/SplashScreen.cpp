// SplashScreen.cpp
// Implementation of the SplashScreen class.
// Created on November 8, 2017
// Last modified on November 8, 2017

#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
    //_parentGO = GameObject::GetInstace();
}

void SplashScreen::Update()
{
    _parentGO->_texture->Fade();
}
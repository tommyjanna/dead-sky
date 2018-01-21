// SplashScreen.cpp
// Implementation of the SplashScreen class.
// Created on November 8, 2017
// Last modified on November 8, 2017

#include "SplashScreen.h"

SplashScreen::SplashScreen(int x, int y, int width, int height, Uint8 layer, SDL_Renderer* renderer) : GameObject(x, y, width, height, layer, renderer, "SplashScreen")
{

}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::Update()
{
    // Fade the texture for 3 seconds.
    if(_texture->Fade(3) == true)
    {
        _toBeDestroyed = true;
    }
}

void SplashScreen::Draw()
{
    _texture->Render();
}

void SplashScreen::Destroy()
{
    // Load new menu.
    SceneManager::ChangeScene(SceneManager::MENU);
}
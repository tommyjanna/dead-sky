// SceneManager.cpp
// Implementation of SceneManager.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "SceneManager.h"

void SceneManager::ChangeScene(int scene)
{
    switch(scene)
    {
    case SceneManager::SPLASHSCREEN:
    {
        SplashScreen* s = new SplashScreen(Game::_renderer);
        s->_texture->LoadTexture("../assets/graphics/polygonwhale.png");
        break;
    }

    case SceneManager::MENU:
    {
        Menu m = Menu();
        break;
    }
    }
    

    return;
}
// Menu.cpp
// Implementation of the Menu class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Menu.h"

Menu::Menu()
{
    _play = new Button(Game::_renderer, 
                        0, 0, 
                        SCREEN_WIDTH / 2 - 85, 50,
                        60, "PLAY", NULL);
    
    _exit = new Button(Game::_renderer, 
                        0, 0, 
                        SCREEN_WIDTH / 2 - 85, 50,
                        60, "EXIT", NULL);

    _play2 = new Button(Game::_renderer, 
                        0, 0, 
                        SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
                        30, "PLAY", []() { SceneManager::ChangeScene(SceneManager::GAME); });
    
    _exit2 = new Button(Game::_renderer, 
                        0, 0, 
                        SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 60,
                        30, "EXIT", []() { SceneManager::ChangeScene(SceneManager::EXIT); });
}
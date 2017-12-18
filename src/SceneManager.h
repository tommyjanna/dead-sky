// SceneManager.h
// Created by Tommy Janna
// Class name: SceneManager
// Description of class: Static class which controls transitions between,
//                       game scenes. It will load all necessary GameObjects
//                       required in each scene.                   
// Created on November 30, 2017
// Last modified on November 30, 2017

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "GameObjects/SplashScreen.h"
#include "Menu.h"
#include "Game.h"

class SceneManager
{
public:
    enum SCENES
    {
        SPLASHSCREEN,
        MENU,
        SETUP,
        GAME,
        EXIT
    };

    static void ChangeScene(int scene);
};

#endif
// Menu.h
// Created by Tommy Janna
// Class name: Menu
// Description of class: Constructs all pieces necessary to display,
//                       the main menu.
// Created on November 30, 2017
// Last modified on November 30, 2017

#ifndef MENU_H
#define MENU_H

#include "SceneManager.h"
#include "GameObjects/Button.h"
#include "GameObjects/Blank.h"

class Button;

class Menu
{
public:
    Menu();
    static void Destroy();

private:

    static Button* _play;
    static Button* _exit;

    static Blank* _bg;
    static Blank* _title;
};

#endif
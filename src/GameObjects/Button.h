// Button.h
// Created by Tommy Janna
// Class name: Button
// Description of class: It's a button.
// Created on November 30, 2017
// Last modified on November 30, 2017

#ifndef BUTTON_H
#define BUTTON_H

#include "../GameObject.h"

class Button : public GameObject
{
public:
    Button(SDL_Renderer*, int, int, int, int);
    ~Button();

    void Update() override;
    void Draw() override;
    void Destroy() override;

private:
    int _buttonWidth, _buttonHeight;
    int _x, _y;

    enum BUTTON_STATES
    {
        BUTTON_MOUSE_OUT,
        BUTTON_MOUSE_OVER_MOTION,
        BUTTON_MOUSE_DOWN,
        BUTTON_MOUSE_UP,
        BUTTON_TOTAL
    };
};

#endif
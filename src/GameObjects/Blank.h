// Blank.h
// Created by Tommy Janna
// Class name: Blank
// Description of class: A blank GameObject without much specifics,
//                       typically used for displaying plain textures,
//                       or plain text.
// Created on December 17, 2017
// Last modified on December 17, 2017


#ifndef BLANK_H
#define BLANK_H

#include "../GameObject.h"

class Blank : public GameObject
{
public:
    Blank(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer);
    Blank(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, int fontSize, std::string);
    ~Blank();

    void Update() override;
    void Draw() override;
    void Destroy() override;
};

#endif
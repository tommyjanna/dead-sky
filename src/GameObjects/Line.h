// Line.h
// Created by Tommy Janna
// Class name: Line
// Description of class: Gameobject for rendering lines,
//                       specifically on the space map.
// Created on December 31, 2017
// Last modified on December 31, 2017

#ifndef LINE_H
#define LINE_H

#include "../GameObject.h"

class Line : public GameObject
{
public:
    Line(SDL_Renderer*, int x1, int y1, int x2, int y2);
    ~Line();

    static std::vector<Line*> _lines;

    void Update() override;
    void Draw() override;
    void Destroy() override;
private:
    SDL_Renderer* _renderer;
    int _x1, _y1, _x2, _y2;
};

#endif
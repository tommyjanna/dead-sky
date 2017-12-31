// Line.cpp
// Implementation of the Line class.
// Created on December 31, 2017
// Last modified on December 31, 2017

#include "Line.h"

// Declare static members.
std::vector<Line*> Line::_lines;

Line::Line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) : GameObject(-80, 140, 600, 300, 4, renderer, "Line")
{
    _renderer = renderer;

    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;

    _lines.push_back(this);

    return;
}

Line::~Line()
{
    return;
}

void Line::Update()
{
    return;
}

void Line::Draw()
{
    SDL_RenderDrawLine(_renderer, _x1, _y1, _x2, _y2);
    _texture->Render();
    return;
}

void Line::Destroy()
{
    return;
}
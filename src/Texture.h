// Texture.h
// Created by Tommy Janna
// Class name: Texture
// Description of class: Texture wrapper class for SDL_Textures.
//                       This class extends the functionality of SDL_Textures
//                       with methods to easily access properties,
//                       blend/fade in or out, and render.
// Created on October 20, 2017
// Last modified on October 20, 2017

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
#include <chrono>
#include <string>
#include <cmath>


class Texture
{
public:
    
    Texture();
    Texture(SDL_Renderer*);
    ~Texture();

    void LoadTexture(std::string);
    bool LoadRenderedText(std::string, SDL_Color);

    TTF_Font* _font;

    int _width, _height;
    int _opacity;

    void Render(int, int);

    void FreeTexture();

    bool Fade(int);

private:

    SDL_Texture* _texture;
    SDL_Renderer* _renderer;

    std::chrono::system_clock::time_point _beginningTime;
    std::chrono::duration<double, std::milli> _elapsedTime;
    bool _timerRunning;
};

#endif
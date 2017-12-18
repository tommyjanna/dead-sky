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
    
    Texture(int, int, int, int);
    Texture(int, int, int, int, SDL_Renderer*);
    ~Texture();

    void LoadTexture(std::string);
    bool LoadRenderedText(std::string, SDL_Color);


    TTF_Font* _font;

    int _opacity;

    void Render();
    
    void SetColor(Uint8, Uint8, Uint8);
    bool Fade(int);

    void FreeTexture();

private:

    SDL_Texture* _texture;
    SDL_Renderer* _renderer;

    int _x, _y;
    int _width, _height;

    std::chrono::system_clock::time_point _beginningTime;
    std::chrono::duration<double, std::milli> _elapsedTime;
    bool _timerRunning;
};

#endif
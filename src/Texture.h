// Texture.h
// Created by Tommy Janna
// Class name: Texture
// Description of class: Texture wrapper class for SDL_Textures.
//                       This class extends the functionality of SDL_Textures,
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
    
    Texture(int x, int y, int width, int height);
    Texture(int x, int y, int width, int height, SDL_Renderer* renderer);
    ~Texture();

    void LoadTexture(std::string path);
    bool LoadRenderedText(std::string text);
    bool LoadRenderedText(std::string text, SDL_Color colour);


    TTF_Font* _font;

    int _opacity;
    int _width, _height;

    void Render();
    
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    bool Fade(int totalTime);

    void FreeTexture();

private:

    SDL_Texture* _texture;
    SDL_Renderer* _renderer;

    int _x, _y;

    std::chrono::system_clock::time_point _beginningTime;
    std::chrono::duration<double, std::milli> _elapsedTime;
    bool _timerRunning;
};

#endif
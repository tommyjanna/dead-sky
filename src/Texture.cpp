// Texture.cpp
// Implementation of the Texture class.
// Created on October 20, 2017
// Last modified on October 20, 2017

#include "Texture.h"


Texture::Texture()
{
    _texture = NULL;
    
    _width = 0;
    _height = 0;
    _opacity = 255;
    _timerRunning = false;

    // Set texture opactiy.
    SDL_SetTextureAlphaMod(_texture, _opacity);
}

Texture::Texture(SDL_Renderer* renderer)
{
    _texture = NULL;

    _width = 0;
    _height = 0;
    _opacity = 255;

    _renderer = renderer;

    // Set texture opactiy.
    SDL_SetTextureAlphaMod(_texture, _opacity);
}

Texture::~Texture()
{
    FreeTexture();
}

void Texture::LoadTexture(std::string path)
{
    // Free old texture if one is pre-existing.
    FreeTexture();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Error loading image... Error %s\n", IMG_GetError());
    }

    else
    {
        // Create SDL_Texture using loaded surface data
        _texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);

        if (_texture == NULL)
        {
            printf("Error creating texture... Error %s\n", SDL_GetError());
        }

        else
        {
            _width = loadedSurface->w;
            _height = loadedSurface->h;
        }

        // Free temporary surface as data is now stored in an SDL_Texture.
        SDL_FreeSurface(loadedSurface);
    }
}

void Texture::FreeTexture()
{
    if(_texture != NULL)
    {
        _texture = NULL;
        _width = 0;
        _height = 0;
    }
}

void Texture::Render(int x, int y)
{
    // Target rendering rectangle.
    SDL_Rect renderRect =
    {
        x,
        y,
        _width,
        _height
    };

    SDL_RenderCopy(_renderer, _texture, NULL, &renderRect);
}

bool Texture::Fade(int totalTime)
{
    bool completed = false;

    if(!_timerRunning)
    {
        _beginningTime = std::chrono::system_clock::now();
        _timerRunning = true;
        _opacity = 0;
        SDL_SetTextureAlphaMod(_texture, _opacity);
    }
    
    else
    {
        totalTime *= 1000; // Get time in milliseconds.
        _elapsedTime = std::chrono::system_clock::now() - _beginningTime;
        
        _opacity = (-(255/2) * cos((M_PI/totalTime) * _elapsedTime.count())) + (255/2);
        SDL_SetTextureAlphaMod(_texture, _opacity);

        if(_elapsedTime.count() >= totalTime * 2)
        {
            _timerRunning = false;
            completed = true;
        }
    }

    return completed;
}
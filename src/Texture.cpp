// Texture.cpp
// Implementation of the Texture class.
// Created on October 20, 2017
// Last modified on October 20, 2017

#include "Texture.h"

Texture::Texture(int x, int y, int width, int height)
{
    _texture = NULL;
    _font = NULL;
    
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _opacity = 255;
    _timerRunning = false;

    // Set texture opactiy.
    SDL_SetTextureAlphaMod(_texture, _opacity);
}

Texture::Texture(int x, int y, int width, int height, SDL_Renderer* renderer)
{
    _texture = NULL;
    _font = NULL;

    _x = x;
    _y = y;
    _width = width;
    _height = height;
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

bool Texture::LoadRenderedText(std::string text)
{
    SDL_Color colour = { 0xFF, 0xFF, 0xFF };
    //FreeTexture();

    // Create surface with text.
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(_font, text.c_str(), colour, 575);

    if(textSurface == NULL)
    {
        printf("Error rendering text surface... Error %s\n", TTF_GetError());
    }

    else
    {
        // Convert surface to SDL_Texture.
        _texture = SDL_CreateTextureFromSurface(_renderer, textSurface);

        if(_texture == NULL)
        {
            printf("Error creating texture... Error %s\n", SDL_GetError());
        }

        else
        {
            _width = textSurface->w;
            _height = textSurface->h;
        }

        // Free surface
        SDL_FreeSurface(textSurface);
    }

    return _texture != NULL;
}

bool Texture::LoadRenderedText(std::string text, SDL_Color colour)
{
    //FreeTexture();

    // Create surface with text.
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(_font, text.c_str(), colour, 575);

    if(textSurface == NULL)
    {
        printf("Error rendering text surface... Error %s\n", TTF_GetError());
    }

    else
    {
        // Convert surface to SDL_Texture.
        _texture = SDL_CreateTextureFromSurface(_renderer, textSurface);

        if(_texture == NULL)
        {
            printf("Error creating texture... Error %s\n", SDL_GetError());
        }

        else
        {
            _width = textSurface->w;
            _height = textSurface->h;
        }

        // Free surface
        SDL_FreeSurface(textSurface);
    }

    return _texture != NULL;
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

void Texture::Render()
{
    // Target rendering rectangle.
    SDL_Rect renderRect =
    {
        _x,
        _y,
        _width,
        _height
    };

    SDL_RenderCopy(_renderer, _texture, NULL, &renderRect);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(_texture, red, green, blue);
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
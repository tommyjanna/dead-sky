// Button.cpp
// Implementation of the Button class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Button.h"

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height, std::function<void()> const& event) : GameObject(x, y, width, height, renderer, "Button")
{
    _buttonWidth = width;
    _buttonHeight = height;

    _down = false;

    _x = x;
    _y = y;

    _event = event;

    return;
}

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height, int fontSize, std::string text, std::function<void()> const& event) : GameObject(x, y, width, height, renderer, "Button + Text")
{
    _buttonWidth = width;
    _buttonHeight = height;

    _x = x;
    _y = y;

    _event = event;

    _texture->_font = TTF_OpenFont("../assets/fonts/lilliputsteps.ttf", fontSize);

    if(_texture->_font == NULL)
    {
        printf("Error loading fonts... Error %s\n", TTF_GetError());
    }

    else
    {
        SDL_Color colour = {0xFF, 0xFF, 0xFF};

        _texture->LoadRenderedText(text, colour);
    }

    return;
}

Button::~Button()
{

}

void Button::Update()
{
    bool inside = true; // Innocent until proven guilty :)

    // Get mouse pos.
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check mouse pos with button boundaries.
    if(mouseX < _x)
    {
        inside = false;
    }

    else if(mouseX > _x + _buttonWidth)
    {
        inside = false;
    }

    else if(mouseY < _y)
    {
        inside = false;
    }

    else if(mouseY > _y + _buttonHeight)
    {
        inside = false;
    }

    if(!inside)
    {
        _down = false;
        _texture->SetColor(255, 255, 255);
    }

    else
    {
        if(Game::_mouseInput[0]) // Mouse over.
        {
            _texture->SetColor(255, 0, 255);
        }

        if(Game::_mouseInput[1]) // Mouse down.
        {
            _down = true;
            _texture->SetColor(200, 100, 200);
        }

        if(Game::_mouseInput[2]) // Mouse up.
        {
            if(_down)
            {
                _down = false;

                _texture->SetColor(255, 0, 255);
                
                // Run buttons _event action.
                _event();
            }
        }
    }
}

void Button::Draw()
{
    _texture->Render();
}

void Button::Destroy()
{
    
}
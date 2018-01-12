// Button.cpp
// Implementation of the Button class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Button.h"

// Declare static members.
std::chrono::system_clock::time_point Button::_beginningTime;
std::chrono::duration<double, std::milli> Button::_elapsedTime;
bool Button::_timerRunning;

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, std::string path, std::function<void()> const& event, bool menuButton) : GameObject(x, y, width, height, layer, renderer, "Button")
{
    _texture->LoadTexture(path);

    _buttonWidth = _texture->_width;
    _buttonHeight = _texture->_height;

    _menuButton = menuButton;

    _down = false;

    _x = x;
    _y = y;

    _event = event;

    return;
}

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, int fontSize, std::string text, std::function<void()> const& event, bool menuButton) : GameObject(x, y, width, height, layer, renderer, "Button + Text")
{
    _menuButton = menuButton;

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

    _buttonWidth = _texture->_width;
    _buttonHeight = _texture->_height;

    return;
}

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 layer, int fontSize, std::string font, std::string text, std::function<void()> const& event, bool menuButton) : GameObject(x, y, width, height, layer, renderer, "Button + Text")
{
    _menuButton = menuButton;

    _x = x;
    _y = y;

    _event = event;

    _texture->_font = TTF_OpenFont(font.c_str(), fontSize);

    if(_texture->_font == NULL)
    {
        printf("Error loading fonts... Error %s\n", TTF_GetError());
    }

    else
    {
        SDL_Color colour = {0xFF, 0xFF, 0xFF};

        _texture->LoadRenderedText(text, colour);
    }

    _buttonWidth = _texture->_width;
    _buttonHeight = _texture->_height;

    return;
}

Button::~Button()
{

}

void Button::Update()
{
    bool inside = true; // Innocent until proven guilty :)
    bool timeCheck = true;

    // Get mouse pos.
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if(_timerRunning)
    {
        _elapsedTime = std::chrono::system_clock::now() - _beginningTime;
        if(_elapsedTime.count() < 200)
        {
            timeCheck = false;
        }
    }

    if(_show && timeCheck)
    {
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
                _texture->SetColor(150, 255, 0);
            }

            if(Game::_mouseInput[1]) // Mouse down.
            {
                _down = true;
                _texture->SetColor(100, 255, 0);
            }

            if(Game::_mouseInput[2]) // Mouse up.
            {
                if(_down)
                {
                    // Start timer between button presses.
                    _beginningTime = std::chrono::system_clock::now();
                    _timerRunning = true;

                    _down = false;

                    _texture->SetColor(255, 255, 0);
                    
                    if(_menuButton)
                    {
                        Menu::Destroy();
                    }

                    // Run buttons _event action.
                    _event();
                }
            }
        }
    }
}

void Button::Draw()
{
    if(_show)
    {
        _texture->Render();
    }
}

void Button::Destroy()
{
    
}
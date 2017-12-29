// Game.h
// Created by Tommy Janna
// Class name: Game
// Description of class: Game class which creates a new instance of the game.
//                       This class contains methods which initialize the SDL framework,
//                       create a new window, handle the game loop,
//                       handle input, load graphics, and draw to the screen.
// Created on October 4, 2017
// Last modified on October 20, 2017

#ifndef GAME_H
#define GAME_H

#include "SceneManager.h"
#include "GameObject.h"
#include <SDL_image.h>
#include <SDL.h>
#include <map>
#include <cstdio>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

class Game
{
public:
    
    Game();
    ~Game();

    void Run();

    static SDL_Renderer* _renderer;

    // Array for storing mouse input.
    static bool* _mouseInput;
    
    // Game loop exit flag.
    static bool _quit;

private:

    bool InitializeSDL();

    void Input();
    bool IsKeyDown(int);

    void Update();
    void Draw();
    void Cleanup();

    // Map for storing keyboard input
    std::map<int, bool> _keyDown;

    SDL_Window* _window;
};

#endif
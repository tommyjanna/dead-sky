// Game.cpp
// Implementation of the Game class.
// Created on October 4, 2017
// Last modified on October 20, 2017

#include "Game.h"

Game::Game()
{
	_window = NULL, _splashScreen = NULL, _renderer = NULL;

	InitializeSDL();
	LoadMedia();
}

Game::~Game()
{
    Cleanup();
}

void Game::Run()
{
	// Game loop.
	while(!_quit)
	{
		Input();
		Update();
		Draw();
		//SDL_Delay(10);
	}

	Cleanup();
}

bool Game::InitializeSDL()
{
    bool success = true;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error initializing SDL... Error: %s\n", SDL_GetError());
		success = false;
	}

	_window = SDL_CreateWindow("Game", 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, 
								SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);
	
	if(_window == NULL)
	{
		printf("Error creating SDL window... Error: %s\n", SDL_GetError());
		success = false;
	}

	// Create renderer for _window, this attaches _renderer to _window.
	// -1 index to setup with accelerated rendering.
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if(_renderer == NULL)
	{
		printf("Error creating SDL renderer... Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		// Init the renderers draw colour.
		// SDL_SetRenderDrawColor(renderer, red, green, blue, alpha)
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	// Initialize SDL_image subsystem.
	// This statement sets up the system for handling PNG files.
	int imgInit = IMG_INIT_PNG;
	if (!(IMG_Init(imgInit)&imgInit))
	{
		printf("Error initializing SDL_image... Error: %s\n", IMG_GetError());
		success = false;
	}

    return success;
}

bool Game::LoadMedia()
{
	bool success = true;

	_splashScreen = new Texture(_renderer);
/*
#ifdef _WIN32
	_splashScreen = LoadTexture("../Dead-Sky/assets/graphics/polygonwhale.png");
#else
	_splashScreen = LoadTexture("../assets/graphics/polygonwhale.png");
#endif

	if(_splashScreen == NULL)
	{
		printf("Error loading image... Error %s\n", SDL_GetError());
		success = false;
	}*/

	_splashScreen->LoadTexture("../assets/graphics/polygonwhale.png");

	return success;
}

void Game::Input()
{
	// Variable to hold next event in the queue.
    SDL_Event e;

	// SDL_PollEvent pulls event from the event queue and stores it in e.
	// e will be assigned NULL when the queue is empty.
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
        case SDL_QUIT: // Close button on window.
            _quit = true;
            break;

        case SDL_KEYDOWN: // Key push.
			_keyDown[e.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP: // Key release.
			_keyDown[e.key.keysym.scancode] = false;
			break;
        }
    }
}

bool Game::IsKeyDown(int key)
{
	// find() will return map.end() if there is no data stored in key location
	// meaning key has yet to be pushed.
	std::map<int, bool>::iterator i = _keyDown.find(key);

	if(i == _keyDown.end())
		return false;

	else
		return _keyDown.at(key);

}

void Game::Update()
{
	if(IsKeyDown(SDL_SCANCODE_UP))
		printf("Up\n");

	if(IsKeyDown(SDL_SCANCODE_DOWN))
		printf("Down\n");

	if(IsKeyDown(SDL_SCANCODE_LEFT))
		printf("Left\n");

	if(IsKeyDown(SDL_SCANCODE_RIGHT))
		printf("Right\n");
	
}

void Game::Draw()
{
	/*SDL_Rect stretchRect; 
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = SCREEN_WIDTH; 
	stretchRect.h = SCREEN_HEIGHT; 
	SDL_BlitScaled( _splashScreen, NULL, _screenSurface, &stretchRect );

	SDL_UpdateWindowSurface(_window);*/

	// Clear the renderer.
	SDL_RenderClear(_renderer);

	// Draw to the back buffer.
	//SDL_RenderCopy(_renderer, _splashScreen, NULL, NULL); //renderer, texture, src rect, trg rect
	_splashScreen->Render(0, 0);

	// Update the window.
	SDL_RenderPresent(_renderer);

	/*
	// Update _screenSurface with the first argument.
	SDL_BlitSurface(_splashScreen, NULL, _screenSurface, NULL);

	// Draw _screenSurface to the window.
	SDL_UpdateWindowSurface(_window);*/
}

void Game::Cleanup()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _splashScreen;
	_splashScreen = NULL, _window = NULL, _renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}
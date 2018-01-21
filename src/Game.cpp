// Game.cpp
// Implementation of the Game class.
// Created on October 4, 2017
// Last modified on October 20, 2017

#include "Game.h"

// Declare static members.
SDL_Renderer* Game::_renderer;
bool Game::_quit;
bool* Game::_mouseInput;

Game::Game()
{
	_window = NULL, _renderer = NULL, _quit = false;

	_mouseInput = new bool[4];

	// Seed random number generator.
	srand(time(NULL));

	InitializeSDL();

	SceneManager::ChangeScene(SceneManager::SPLASHSCREEN);
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
		SDL_Delay(1000/30);
	}

	Cleanup();
}

bool Game::InitializeSDL()
{
    bool success = true;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize SDL video subsystem.
	{
		printf("Error initializing SDL... Error: %s\n", SDL_GetError());
		success = false;
	}

	_window = SDL_CreateWindow("Dead Sky", 
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
	Game::_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if(Game::_renderer == NULL)
	{
		printf("Error creating SDL renderer... Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		// Init the renderers draw colour.
		// SDL_SetRenderDrawColor(renderer, red, green, blue, alpha)
		SDL_SetRenderDrawColor(Game::_renderer, 0x00, 0x00, 0x00, 0xFF);
	}

	// Initialize SDL_image subsystem.
	// This statement sets up the system for handling PNG files.
	int imgInit = IMG_INIT_PNG;
	if(!(IMG_Init(imgInit)&imgInit))
	{
		printf("Error initializing SDL_image... Error: %s\n", IMG_GetError());
		success = false;
	}

	// Initialize SDL_ttf subsystem for working with true type fonts.
	if(TTF_Init() == -1)
	{
		printf("Error initializing SDL_ttf... Error: %s\n", TTF_GetError());
		success = false;
	}

    return success;
}

void Game::Input()
{
	// Variable to hold next event in the queue.
    SDL_Event e;

	// Reset mouse input.
	for(int i = 0; i < 4; i++)
	{
		_mouseInput[i] = false;
	}

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

		case SDL_MOUSEMOTION: // Mouse movement.
			_mouseInput[0] = true;
			break;

		case SDL_MOUSEBUTTONDOWN: // Mouse click.
			_mouseInput[1] = true;
			break;

		case SDL_MOUSEBUTTONUP:  // Mouse released.
			_mouseInput[2] = true;
			break;
        }
    }

	return;
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
	// Update existing GameObjects
	for(int i = 0; i < GameObject::_objects.size(); /*conditional increment*/ )
	{
		GameObject::_objects[i]->Update();

		// If objects flag to be destroyed is true, swap it and the last
		// object in the vector, then delete it.
		// This will help avoid having an empty element in the vector,
		// and having to shift every element down.
		if(GameObject::_objects[i]->_toBeDestroyed)
		{
			GameObject::_objects[i]->Destroy();

			int lastObject = GameObject::_objects.size() - 1;
			std::swap(GameObject::_objects[i], GameObject::_objects[lastObject]);
			
			delete GameObject::_objects[lastObject];
			GameObject::_objects[lastObject] = NULL;
			GameObject::_objects.pop_back(); // Removes the last element from the vector.

			// Don't increment i here to update the swapped object,
			// unless vector is empty, in which we want to exit the loop.
			if(!GameObject::_objects.empty())
				i++;
		}
		else
		{
			i++;
		}
	}

	return;
}

void Game::Draw()
{
	// Clear the renderer.
	SDL_RenderClear(Game::_renderer);

	for(int i = 1; i < 5; i++)
	{
		for(int j = 0; j < GameObject::_objects.size(); j++)
		{
			if(GameObject::_objects[j]->_layer == i)
			{
				// Draw to the back buffer.
				GameObject::_objects[j]->Draw();
			}
		}
	}

	// Update the window.
	SDL_RenderPresent(Game::_renderer);
}

void Game::Cleanup()
{
	SDL_DestroyWindow(_window);

	SDL_DestroyRenderer(Game::_renderer);
	
	_window = NULL, Game::_renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
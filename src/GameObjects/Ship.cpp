// Ship.cpp
// Implementation of the Ship class.
// Created on December 18, 2017
// Last modified on December 18, 2017

#include "Ship.h"

Ship::Ship(int layer, SDL_Renderer* renderer) : GameObject(-80, 140, 600, 300, layer, renderer, "Ship")
{
    si = ShipInterface(renderer);

    _health = 100;
    _shield = 0;

    si.DisplayPanel("You and your marauder crew are carrying vital information on the Janerian Empire's "
                "mothership. Your payment from the rebel camp will be wired once you return the intel "
                "to Earth-5. The Janerian's tagged your ship with a tracker and have a probe in pursuit!\n\n"
                "Your shields were damaged while escaping the Janerian space station and the enemies are "
                "hot on your trail.");
}

Ship::~Ship()
{
    return;
}

void Ship::Update()
{
    si.Update(_health, _shield);
    return;
}

void Ship::Draw()
{
    _texture->Render();
    return;
}

void Ship::Destroy()
{
    return;
}

Ship::ShipInterface::ShipInterface()
{
    _renderer = NULL;
}

Ship::ShipInterface::ShipInterface(SDL_Renderer* renderer)
{
    _renderer = renderer;

    _panel = new Blank(_renderer, 200, 80, 640, 420, 3);
    _panel->_texture->LoadTexture("../assets/graphics/panel.png");

    _panelText = new Blank(_renderer, 240, 120, 1, 1, 4, 16, " ");
    _healthText = new Blank(_renderer, 51, 25, 1, 1, 4, 40, " ");
    _shieldText = new Blank(_renderer, 51, 500, 1, 1, 4, 40, " ");

    _healthDisplay = new Blank(_renderer, 0, 20, 144, 60, 3);
    _shieldDisplay = new Blank(_renderer, 0, 496, 144, 60, 3);

    _healthDisplay->_texture->LoadTexture("../assets/graphics/hp.png");
    _shieldDisplay->_texture->LoadTexture("../assets/graphics/sh.png");
}

void Ship::ShipInterface::DisplayPanel(std::string message)
{
    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText(message, textColour);
    _continueButton = new Button(_renderer, 
                                500, 400, 
                                88, 37,
                                4,
                                18, "Continue...",
                                [this]() { _panel->_show = false;
                                                        _panelText->_show = false;
                                                        _continueButton->_show = false;
                                                        _continueButton->_toBeDestroyed = true; }, 
                                false);
}

void Ship::ShipInterface::Update(int health, int shield)
{
    _healthText->_texture->LoadRenderedText(std::to_string(health), SDL_Color { 0x00, 0x00, 0x00 });
    _shieldText->_texture->LoadRenderedText(std::to_string(shield), SDL_Color { 0x00, 0x00, 0x00 });
    return;
}
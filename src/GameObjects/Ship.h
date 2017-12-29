// Ship.h
// Created by Tommy Janna
// Class name: Ship
// Description of class: Space ship which contains,
//                       all information about the player's,
//                       crew members and resources. This,
//                       also displays the ship and interacts in space,
//                       combat.
// Created on December 18, 2017
// Last modified on December 18, 2017

#ifndef SHIP_H
#define SHIP_H

#include "Button.h"
#include "Blank.h"
#include "../GameObject.h"
#include <ctime>

class Button;

class Ship : public GameObject
{
public:
    Ship(int layer, SDL_Renderer* renderer);
    ~Ship();

    void Update() override;
    void Draw() override;
    void Destroy() override;

private:
    int _health, _shield;

    class ShipInterface
    {
    public:
        ShipInterface(); // Default constructor cuz this damn compiler wants one. DONT DELETE
        ShipInterface(SDL_Renderer* renderer);

        void Update(int health, int shield);

        void DisplayPanel(std::string);

    private:
        SDL_Renderer* _renderer;
        Blank* _panel;
        Blank* _panelText;


        Blank* _healthDisplay;
        Blank* _shieldDisplay;

        Blank* _healthText;
        Blank* _shieldText;

        Button* _continueButton;
    };

    ShipInterface si;
};

#endif
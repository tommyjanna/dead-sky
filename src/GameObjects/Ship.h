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

#include "Line.h"
#include "Button.h"
#include "Blank.h"
#include "../Event.h"
#include "../GameObject.h"
#include <functional>
#include <ctime>
#include <cmath>

class Button;
class ShipInterface;

class Ship : public GameObject
{
public:
    Ship(int layer, SDL_Renderer* renderer);
    ~Ship();

    void Update() override;
    void Draw() override;
    void Destroy() override;

    class ShipInterface
    {
    public:
        ShipInterface(); // Default constructor cuz this damn compiler wants one. DONT DELETE
        ShipInterface(SDL_Renderer* renderer, Ship* parentShip);

        void Update();

        void DisplayPanel(std::string text); // Single text panel.
        int DisplayPanel(std::string text, std::vector<std::string> answers, int panelNum); // A panel with multiple answers.
        void CombatPanel();
        void CreateMap();

        void DrawMapLines();
        void DeleteMapLines();
        void DeleteButtons(std::vector<Button*> buttonVector);

        int LocateShip();
        int _location;

    private:

        int Distance(int x1, int y1, int x2, int y2);

        Ship* _parentShip;

        SDL_Renderer* _renderer;
        Blank* _panel;
        Blank* _panelText;

        Blank* _mapPanel;
        Blank* _locationNode;

        Blank* _healthDisplay;
        Blank* _shieldDisplay;
        Blank* _statusBar;

        Blank* _healthText;
        Blank* _shieldText;
        Blank* _damageText;
        Blank* _membersText;
        Blank* _creditsText;

        Button* _continueButton;
        
        Button* _spaceMap;
        Button* _closeMap;

        int _mapNodes[15][2];
        int _mapPosX, _mapPosY;

        std::vector<Button*> _mapButtons;
        std::vector<Button*> _answers;

        Line* _lines;
    };

    ShipInterface si;

    int _health, _shield;
    int _credits, _damage, _members;

private:
};

#endif
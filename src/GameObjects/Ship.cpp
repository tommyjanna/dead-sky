// Ship.cpp
// Implementation of the Ship class.
// Created on December 18, 2017
// Last modified on December 18, 2017

#include "Ship.h"

Ship::Ship(int layer, SDL_Renderer* renderer) : GameObject(-80, 140, 600, 300, layer, renderer, "Ship")
{
    si = ShipInterface(renderer, this);

    _health = 100;
    _shield = 0;

    _damage = 25;
    _members = 3;
    _credits = 40;
    
    si.CreateMap();

    si._location = si.LocateShip();
    Event::UpdateEvent(this, 1, 0);
}

Ship::~Ship()
{
    return;
}

void Ship::Update()
{
    si.Update();
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

Ship::ShipInterface::ShipInterface(SDL_Renderer* renderer, Ship* parentShip)
{
    _renderer = renderer;
    _parentShip = parentShip;

    _panel = new Blank(_renderer, 200, 80, 640, 420, 3);
    _panel->_texture->LoadTexture("../assets/graphics/panel.png");

    _panelText = new Blank(_renderer, 240, 120, 1, 1, 4, 16, "../assets/fonts/nasalization-rg.ttf", " ");
    _healthText = new Blank(_renderer, 51, 25, 1, 1, 4, 40, " ");
    _shieldText = new Blank(_renderer, 51, 500, 1, 1, 4, 40, " ");
    _damageText = new Blank(_renderer, 265, 17, 1, 1, 4, 24, " ");
    _membersText = new Blank(_renderer, 505, 17, 1, 1, 4, 24, " ");
    _creditsText = new Blank(_renderer, 718, 17, 1, 1, 4, 24, " ");

    _healthDisplay = new Blank(_renderer, 0, 20, 144, 60, 3);
    _shieldDisplay = new Blank(_renderer, 0, 496, 144, 60, 3);
    _statusBar = new Blank(_renderer, 212, 0, 600, 300, 3);

    _healthDisplay->_texture->LoadTexture("../assets/graphics/hp.png");
    _shieldDisplay->_texture->LoadTexture("../assets/graphics/sh.png");
    _statusBar->_texture->LoadTexture("../assets/graphics/statusbar.png");

    _mapPanel = new Blank(_renderer, 200, 80, 640, 420, 3);
    _mapPanel->_texture->LoadTexture("../assets/graphics/spacemap.png");
    _mapPanel->_show = false;
}

void Ship::ShipInterface::DisplayPanel(std::string message)
{
    _panel->_show = true;
    _panelText->_show = true;
    _spaceMap->_show = false;

    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText(message, textColour);
    _continueButton = new Button(_renderer, 
                                455, 430, 
                                88, 37,
                                4,
                                18, "../assets/fonts/nasalization-rg.ttf", "Continue...",
                                [this]() { _panel->_show = false;
                                                        _panelText->_show = false;
                                                        _continueButton->_show = false;
                                                        _spaceMap->_show = true;
                                                        _continueButton->_toBeDestroyed = true; }, 
                                false);
                    
}

int Ship::ShipInterface::DisplayPanel(std::string message, std::vector<std::string> answers, int panelNum)
{
    _panel->_show = true;
    _panelText->_show = true;
    _spaceMap->_show = false;

    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText(message, textColour);

    for(int i = 0; i < answers.size(); i++)
    {
        Button* b = new Button(_renderer,
                                240, 350 + (25 * i),
                                200, 37,
                                4,
                                18, "../assets/fonts/nasalization-rg.ttf", answers[i],
                                [this, panelNum, i]() {
                                    DeleteButtons(_answers);
                                    _panel->_show = false;
                                    _panelText->_show = false;
                                    _spaceMap->_show = true;
                                    Event::UpdateEvent(_parentShip, panelNum, i);
                                },
                                false);
        
        _answers.push_back(b);
    }

    return 0;
}

void Ship::ShipInterface::Update()
{
    _healthText->_texture->LoadRenderedText(std::to_string(_parentShip->_health), SDL_Color { 0x00, 0x00, 0x00 });
    _shieldText->_texture->LoadRenderedText(std::to_string(_parentShip->_shield), SDL_Color { 0x00, 0x00, 0x00 });
    _damageText->_texture->LoadRenderedText(std::to_string(_parentShip->_damage), SDL_Color { 0xFF, 0xFF, 0xFF });
    _membersText->_texture->LoadRenderedText(std::to_string(_parentShip->_members), SDL_Color { 0xFF, 0xFF, 0xFF });
    _creditsText->_texture->LoadRenderedText(std::to_string(_parentShip->_credits), SDL_Color { 0xFF, 0xFF, 0xFF });

    return;
}

void Ship::ShipInterface::CreateMap()
{
    int mapNodes[15][2] = { {263, 434},
                            {323, 385},
                            {390, 373},
                            {387, 341},
                            {311, 321},
                            {378, 266},
                            {445, 283},
                            {521, 254},
                            {526, 193},
                            {591, 247},
                            {642, 207},
                            {630, 180},
                            {701, 156},
                            {738, 136},
                            {741, 201} };

    std::copy(&mapNodes[0][0], &mapNodes[15][2], &_mapNodes[0][0]);

    _mapPosX = _mapNodes[0][0];
    _mapPosY = _mapNodes[0][1];

    _spaceMap = new Button(_renderer,
                            450, 500,
                            88, 37,
                            2,
                            24, "Space Map",
                            [this]() { _mapPanel->_show = true;
                                        _closeMap->_show = true; 
                                        _locationNode = new Blank(_renderer, 
                                                                    _mapPosX - 10, _mapPosY - 10,
                                                                    40, 40, 4);
                                        _locationNode->_texture->LoadTexture("../assets/graphics/shipicon.png");
                                        DrawMapLines(); }, false);
    
    _closeMap = new Button(_renderer,
                            230, 107,
                            1, 1,
                            4,
                            "../assets/graphics/close.png",
                            [this]() { _mapPanel->_show = false;
                                        _closeMap->_show = false;
                                        _locationNode->_show = false;
                                        _locationNode->_toBeDestroyed = true;
                                        DeleteMapLines();
                                        DeleteButtons(_mapButtons); }, false);
    _closeMap->_show = false;

    return;
}

int Ship::ShipInterface::LocateShip()
{
    for(int i = 0; i < 15; i++)
    {
        if(_mapPosX == _mapNodes[i][0])
        {
            return i;
        }
    }

    return 0;
}

void Ship::ShipInterface::DrawMapLines()
{
    _location = LocateShip();

    for(int i = _location - 3; i < _location + 3; i++)
    {
        if(i >= 0 && i != _location)
        {
            if(Distance(_mapNodes[_location][0], _mapNodes[_location][1],
                        _mapNodes[i][0], _mapNodes[i][1]) < 100)
            {
                new Line(_renderer, _mapNodes[_location][0] + 5, _mapNodes[_location][1] + 5, _mapNodes[i][0] + 5, _mapNodes[i][1] + 5);

                Button* b = new Button(_renderer,
                            _mapNodes[i][0] - 5, _mapNodes[i][1] - 5,
                            25, 25,
                            4,
                            "../assets/graphics/mapnode.png",
                            [this, i](){ 
                                _mapPosX = _mapNodes[i][0];
                                _mapPosY = _mapNodes[i][1];
                                _mapPanel->_show = false;
                                _closeMap->_show = false;
                                _locationNode->_show = false;
                                _locationNode->_toBeDestroyed = true;
                                _location = LocateShip();
                                Event::UpdateEvent(_parentShip, 1, 0);
                                DeleteMapLines();
                                DeleteButtons(_mapButtons);
                            }, false);
                _mapButtons.push_back(b);
            }
        }
    }
}

int Ship::ShipInterface::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}

void Ship::ShipInterface::DeleteMapLines()
{
    for(int i = 0; i < Line::_lines.size(); i++)
    {
        Line::_lines[i]->_toBeDestroyed = true;
    }
}

void Ship::ShipInterface::DeleteButtons(std::vector<Button*> buttonVector)
{
    for(int i = 0; i < buttonVector.size(); i++)
    {
        if(buttonVector[i] != NULL)
            buttonVector[i]->_toBeDestroyed = true;
    }
}

void Ship::ShipInterface::CombatPanel()
{
    _spaceMap->_show = false;


}
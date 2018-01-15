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
    _shieldRegen = 5;

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
    si.Destroy();
    return;
}

void Ship::Attack(Enemy* enemy)
{
    int damage = _damage * _blasterPts;
    int shieldDamage = _damage * _shieldPenPts;
    int shieldRegen = _shieldRegen * _shieldPts;

    int spilloverDamage;

    // String for storing history of attacks
    std::string battleLog = "Your turn:\n";

    if(shieldDamage > 0)
    {
        if(enemy->_shield > 0)
        {
            shieldDamage *= 2;

            battleLog.append("You dealt " + std::to_string(shieldDamage / 2) + " damage, but it was DOUBLED to " +
                        std::to_string(shieldDamage) + " because you hit the shield with your shield penetration missiles!\n\n");

            if(enemy->_shield < shieldDamage)
            {
                enemy->_shield = 0;
            }

            else
            {
                enemy->_shield -= shieldDamage;
            }
        }

        else
        {
            shieldDamage /= 2;
            
            battleLog.append("You dealt " + std::to_string(shieldDamage * 2) + " damage, but it was HALVED to " +
                        std::to_string(shieldDamage) + " because you didn't hit any shield with your shield penetration missiles!\n\n");
            
            if(enemy->_health < shieldDamage)
            {
                enemy->_health = 0;
            }

            else
            {
                enemy->_health -= shieldDamage;
            }
        }
    }

    if(damage > 0)
    {
        if(enemy->_shield > 0)
        {
            damage /= 2;
            
            battleLog.append("You dealt " + std::to_string(damage * 2) + " damage, but it was HALVED to " +
                            std::to_string(damage) + " because you hit the shield with your regular blasters!\n\n");

            if(enemy->_shield < damage) // If damage should do more damage than the enemy's shield.
            {
                spilloverDamage = damage - enemy->_shield;

                enemy->_shield = 0;
                
                enemy->_health -= spilloverDamage;
            }

            else
            {
                enemy->_shield -= damage;
            }
        }

        else
        {
            if(enemy->_health < damage)
            {
                enemy->_health = 0;
            }

            else
            {
                enemy->_health -= damage;
            }

            battleLog.append("You dealt " + std::to_string(damage) + " damage with your regular blasters!\n\n");
        }
    }

    if(shieldRegen > 0)
    {
        _shield += shieldRegen;

        battleLog.append("You recovered " + std::to_string(shieldRegen) + " shield points!\n\n");
    }

    si.BattleLog(battleLog, false, this, enemy);

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

    _combatPanel = new Blank(_renderer, 300, 70, 420, 420, 3);
    _combatPanel->_texture->LoadTexture("../assets/graphics/combatpanel.png");
    _combatPanel->_show = false;

    _loseOptions.push_back("Exit Game.");

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
                                                        _continueButton->_toBeDestroyed = true; 
                                                        DeleteButtons(_shopButtons);
                                                        DeleteButtons(_continueButtons); }, 
                                false);
    _continueButtons.push_back(_continueButton);                   
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

void Ship::ShipInterface::Destroy()
{
    _parentShip->_toBeDestroyed = true;
    _panel->_toBeDestroyed = true;
    _panelText->_toBeDestroyed = true;

    _combatPanel->_toBeDestroyed = true;
    _energyText->_toBeDestroyed = true;
    _blasterPoints->_toBeDestroyed = true;
    _shieldPenPoints->_toBeDestroyed = true;
    _shieldPoints->_toBeDestroyed = true;

    _fire->_toBeDestroyed = true;

    _mapPanel->_toBeDestroyed = true;
    _locationNode->_toBeDestroyed = true;

    _healthDisplay->_toBeDestroyed = true;
    _shieldDisplay->_toBeDestroyed = true;
    _statusBar->_toBeDestroyed = true;

    _healthText->_toBeDestroyed = true;
    _shieldText->_toBeDestroyed = true;
    _damageText->_toBeDestroyed = true;
    _membersText->_toBeDestroyed = true;
    _creditsText->_toBeDestroyed = true;

    _continueButton->_toBeDestroyed = true;
    
    _spaceMap->_toBeDestroyed = true;
    _closeMap->_toBeDestroyed = true;

    DeleteButtons(_mapButtons);
    DeleteButtons(_answers);
    DeleteButtons(_combatButtons);
    DeleteButtons(_shopButtons);

    _lines->_toBeDestroyed = true;

    return;
}

void Ship::ShipInterface::CreateMap()
{
    int mapNodes[13][2] = { {263, 434},
                            {323, 385},
                            {390, 373},
                            {387, 341},
                            {311, 321},
                            {378, 266},
                            {445, 283},
                            {521, 254},
                            {591, 247},
                            {642, 207},
                            {630, 180},
                            {701, 156},
                            {738, 136} };

    std::copy(&mapNodes[0][0], &mapNodes[13][2], &_mapNodes[0][0]);

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
    for(int i = 0; i < 13; i++)
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

void Ship::ShipInterface::CombatPanel(Enemy* enemy)
{
    _parentShip->_blasterPts = 0;
    _parentShip->_shieldPenPts = 0;
    _parentShip->_shieldPts = 0;

    if(_parentShip->_health <= 0)
    {
        _parentShip->_health = 0;
        DisplayPanel("You have been defeated. All hope for the Galaxy has been lost.", _loseOptions, 69);
    }

    else
    {
        _energyText = new Blank(_renderer, 340, 120, 1, 1, 4, 16, "../assets/fonts/nasalization-rg.ttf", " ");
        _blasterPoints = new Blank(_renderer, 505, 231, 1, 1, 4, 20, "../assets/fonts/nasalization-rg.ttf", "0");
        _shieldPenPoints = new Blank(_renderer, 505, 304, 1, 1, 4, 20, "../assets/fonts/nasalization-rg.ttf", "0");
        _shieldPoints = new Blank(_renderer, 505, 379, 1, 1, 4, 20, "../assets/fonts/nasalization-rg.ttf", "0");

        Blank* _blasterWord = new Blank(_renderer, 478, 200, 1, 1, 4, 16, "../assets/fonts/nasalization-rg.ttf", "Blasters");
        Blank* _shieldPenWord = new Blank(_renderer, 405, 273, 1, 1, 4, 16, "../assets/fonts/nasalization-rg.ttf", "Shield Penetrating Missiles");
        Blank* _shieldWord = new Blank(_renderer, 462, 348, 1, 1, 4, 16, "../assets/fonts/nasalization-rg.ttf", "Shield Regen");

        _spaceMap->_show = false;
        _combatPanel->_show = true;

        _parentShip->_energy = _parentShip->_members;

        _energyText->_texture->LoadRenderedText("You have " + std::to_string(_parentShip->_energy) + " energy points to spend.");

        // Must initilize each member outside of a loob because otherwise lambda will not work?
        // Yes, this is a terrible solution, but I don't have time right now man.
        // If you find yourself here, don't mark the following code. Close your eyes.
        Button* minus1 = new Button(_renderer, 380, 228, 32, 32, 4, "../assets/graphics/minus.png",
                                [this]() { ModPoints(_combatButtons[0]); }, false);

        Button* plus1 = new Button(_renderer, 630, 228, 32, 32, 4, "../assets/graphics/plus.png",
                                [this]() { ModPoints(_combatButtons[1]); }, false);

        Button* minus2 = new Button(_renderer, 380, 301, 32, 32, 4, "../assets/graphics/minus.png",
                                [this]() { ModPoints(_combatButtons[2]); }, false);

        Button* plus2 = new Button(_renderer, 630, 301, 32, 32, 4, "../assets/graphics/plus.png",
                                [this]() { ModPoints(_combatButtons[3]); }, false);

        Button* minus3 = new Button(_renderer, 380, 375, 32, 32, 4, "../assets/graphics/minus.png",
                                [this]() { ModPoints(_combatButtons[4]); }, false);

        Button* plus3 = new Button(_renderer, 630, 375, 32, 32, 4, "../assets/graphics/plus.png",
                                [this]() { ModPoints(_combatButtons[5]); }, false);

        _combatButtons.push_back(minus1);
        _combatButtons.push_back(plus1);
        _combatButtons.push_back(minus2);
        _combatButtons.push_back(plus2);
        _combatButtons.push_back(minus3);
        _combatButtons.push_back(plus3);
        // Ok, the bad code is over, open your eyes.

        _fire = new Button(_renderer, 
                            490, 430, 
                            88, 37,
                            4,
                            18, "../assets/fonts/nasalization-rg.ttf", "FIRE!",
                            [this, enemy, _blasterWord, _shieldPenWord, _shieldWord]() { _energyText->_toBeDestroyed = true;
                                        _combatPanel->_show = false;
                                        _blasterPoints->_toBeDestroyed = true;
                                        _shieldPenPoints->_toBeDestroyed = true;
                                        _shieldPoints->_toBeDestroyed = true;
                                        _fire->_toBeDestroyed = true;
                                        _blasterWord->_toBeDestroyed = true;
                                        _shieldPenWord->_toBeDestroyed = true;
                                        _shieldWord->_toBeDestroyed = true;
                                        DeleteButtons(_combatButtons);
                                        _parentShip->Attack(enemy); }, 
                            false);
    }
}

void Ship::ShipInterface::ModPoints(Button* b)
{
    int buttonId;

    for(int i = 0; i < 6; i++)
    {
        if(b == _combatButtons[i])
        {
            buttonId = i;
        }
    }

    switch(buttonId)
    {
    case 0: // Minus blasters
        if(_parentShip->_blasterPts > 0)
        {
            _parentShip->_blasterPts--;
            _parentShip->_energy++;

            _blasterPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_blasterPts));
        }
        break;
    case 1: // Plus blasters
        if(_parentShip->_energy > 0)
        {
            _parentShip->_blasterPts++;
            _parentShip->_energy--;

            _blasterPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_blasterPts));
        }
        break;
    case 2: // Minus shield pen
        if(_parentShip->_shieldPenPts > 0)
        {
            _parentShip->_shieldPenPts--;
            _parentShip->_energy++;

            _shieldPenPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_shieldPenPts));
        }
        break;
    case 3: // Plus shield pen
        if(_parentShip->_energy > 0)
        {
            _parentShip->_shieldPenPts++;
            _parentShip->_energy--;

            _shieldPenPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_shieldPenPts));
        }
        break;
    case 4: // Minus shield
        if(_parentShip->_shieldPts > 0)
        {
            _parentShip->_shieldPts--;
            _parentShip->_energy++;

            _shieldPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_shieldPts));
        }
        break;
    case 5: // Plus shield
        if(_parentShip->_energy > 0)
        {
            _parentShip->_shieldPts++;
            _parentShip->_energy--;
            
            _shieldPoints->_texture->LoadRenderedText(std::to_string(_parentShip->_shieldPts));
        }
        break;
    }

    _energyText->_texture->LoadRenderedText("You have " + std::to_string(_parentShip->_energy) + " energy points to spend.");
}

void Ship::ShipInterface::Shop()
{
    std::string shopItems[4] = {"Repair Hull [100 HP] (35 GTC)",
                            "Repair Shields [100 SH] (20 GTC)",
                            "Upgrade Weapon Systems [+10 damage] (35 GTC)",
                            "Upgrade Shield Regen Systems [+5 shield per turn] (30 GTC)"};

    for(int i = 0; i < 4; i++)
    {
        _shopOwned[i] = false;
    }

    _shopPrices[0] = 35;
    _shopPrices[1] = 20;
    _shopPrices[2] = 35;
    _shopPrices[3] = 30;

    _panel->_show = true;
    _panelText->_show = true;
    _spaceMap->_show = false;

    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText("Welcome to the Galactic Trade Market, hope you find what you're lookin' for.\n\n", textColour);
    DisplayPanel("");
    for(int i = 0; i < 4; i++)
    {
        Button* b = new Button(_renderer,
                                240, 250 + (25 * i),
                                200, 37,
                                4,
                                18, "../assets/fonts/nasalization-rg.ttf", shopItems[i],
                                [this, i, shopItems]() {
                                    if(_shopOwned[i])
                                    {
                                        DisplayPanel("You already own this.");
                                    }

                                    else
                                    {
                                        if(_parentShip->_credits >= _shopPrices[i])
                                        {
                                            _parentShip->_credits -= _shopPrices[i];
                                            DisplayPanel("You bought " + shopItems[i] + "!!");
                                            _shopOwned[i] = true;

                                            switch(i)
                                            {
                                            case 0:
                                                _parentShip->_health = 100;
                                                break;
                                            case 1:
                                                _parentShip->_shield = 100;
                                                break;
                                            case 2:
                                                _parentShip->_damage += 10;
                                                break;
                                            case 3:
                                                _parentShip->_shieldRegen += 5;
                                                break;
                                            }
                                        }

                                        else
                                        {
                                            DisplayPanel("You don't have enought credits!");
                                        }
                                    }

                                },
                                false);
        
        _shopButtons.push_back(b);
    }
}

void Ship::ShipInterface::BattleLog(std::string message, bool myTurn, Ship* ship, Enemy* enemy)
{
    _panel->_show = true;
    _panelText->_show = true;
    _spaceMap->_show = false;

    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText(message, textColour);

    if(myTurn)
    {
        _continueButton = new Button(_renderer, 
                                    455, 430, 
                                    88, 37,
                                    4,
                                    18, "../assets/fonts/nasalization-rg.ttf", "My turn!",
                                    [this, enemy]() { _panel->_show = false;
                                                _panelText->_show = false;
                                                _continueButton->_show = false;
                                                _spaceMap->_show = true;
                                                _continueButton->_toBeDestroyed = true;
                                                CombatPanel(enemy); }, 
                                    false);
    }

    else
    {
        _continueButton = new Button(_renderer, 
                                    455, 430, 
                                    88, 37,
                                    4,
                                    18, "../assets/fonts/nasalization-rg.ttf", "Enemy turn...",
                                    [this, enemy]() { _panel->_show = false;
                                                _panelText->_show = false;
                                                _continueButton->_show = false;
                                                _spaceMap->_show = true;
                                                _continueButton->_toBeDestroyed = true;
                                                enemy->Attack(_parentShip); }, 
                                    false);
    }        
}
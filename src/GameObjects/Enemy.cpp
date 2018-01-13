// Enemy.cpp
// Implementation of the Enemy class.
// Created on January 11, 2018
// Last modified on January 11, 2018

#include "Enemy.h"

Enemy::Enemy(int layer, SDL_Renderer* renderer) : GameObject(492, 140, 600, 300, layer, renderer, "Enemy")
{
    _health = 100;
    _shield = 0;

    _healthText = new Blank(renderer, 885, 25, 1, 1, 4, 40, " ");
    _shieldText = new Blank(renderer, 885, 500, 1, 1, 4, 40, " ");

    _healthDisplay = new Blank(renderer, 880, 20, 144, 60, 3);
    _shieldDisplay = new Blank(renderer, 880, 496, 144, 60, 3);

    _healthDisplay->_texture->LoadTexture("../assets/graphics/hpenemy.png");
    _shieldDisplay->_texture->LoadTexture("../assets/graphics/shenemy.png");
}

Enemy::~Enemy()
{
    return;
}

void Enemy::Update()
{
    _healthText->_texture->LoadRenderedText(std::to_string(_health), SDL_Color { 0x00, 0x00, 0x00 });
    _shieldText->_texture->LoadRenderedText(std::to_string(_shield), SDL_Color { 0x00, 0x00, 0x00 });
    return;
}

void Enemy::Draw()
{
    _texture->Render();
    return;
}

void Enemy::Destroy()
{
    return;
}
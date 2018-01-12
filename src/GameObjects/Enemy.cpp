// Enemy.cpp
// Implementation of the Enemy class.
// Created on January 11, 2018
// Last modified on January 11, 2018

#include "Enemy.h"

Enemy::Enemy(int layer, SDL_Renderer* renderer) : GameObject(492, 140, 600, 300, layer, renderer, "Enemy")
{
    _health = 100;
    _shield = 0;
}

Enemy::~Enemy()
{
    return;
}

void Enemy::Update()
{
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
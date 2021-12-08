#include "Player.h"
#include <iostream>

Player::Player(std::string playerName, std::string charName, std::string race,
               std::string playerClass, std::string alignment, 
               int maxHealth, int armorClass, int moveSpeed)
{
    this->maxHealth       = maxHealth;
    this->moveSpeed       = moveSpeed;
    this->abilities       = abilities;
    this->armorClass      = armorClass;
    this->creatureName    = charName;
    this->playerName      = playerName;
    this->race            = race;
    this->alignment       = alignment;
    this->playerClass     = playerClass;
    this->healthRemaining = maxHealth;

    this->natureOfTheBeast = KillableType::PLAYER; 
}

Player::Player()
{
    
}

void Player::attack()
{
    std::cout << "Prompt player for their actions, and continue to deal damage etc" << std::endl;
}

int Player::takeDamage(int amount)
{
    this->healthRemaining -= amount;
    return this->healthRemaining;
}
#include "NPC.h"
#include <iostream>

NPC::NPC(std::string charName, std::string race, std::string playerClass, 
         std::string alignment, int maxHealth, int armorClass, 
         int moveSpeed, Abilities abilities)
{
    this->maxHealth    = maxHealth;
    this->playerClass  = playerClass;
    this->moveSpeed    = moveSpeed;
    this->abilities    = abilities;
    this->armorClass   = armorClass;
    this->creatureName = charName;
    this->race         = race;
    this->alignment    = alignment;

    this->natureOfTheBeast = KillableType::NPC; 
}

NPC::NPC()
{
    // placeholder
}

void NPC::attack()
{
    std::cout << "Function not ready yet; your move DM!" << std::endl;
}

int NPC::takeDamage(int amount)
{
    this->healthRemaining -= amount;
    return this->healthRemaining;
}
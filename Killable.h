#ifndef KILLABLE_H
#define KILLABLE_H

#include <string>
#include <vector>
#include "DiceRoll.h"

// killable entities are either players, monsters, or NPCs (NPCs not yet implemented)
typedef enum KillableType {PLAYER, MONSTER, NPC} KillableType;

// string for abilities a killable entity may possess, that aren't directly an attack
typedef std::string Ability;

// collection of abilities the monster possesses
typedef std::vector<Ability> Abilities;

// for initialization of Monsters
static  Abilities BASE_ABILITIES;

class Killable
{
    public:
        int maxHealth;                 // maximum health the entity may possess
        int armorClass;                // attack roll to beat to hit the target
        int moveSpeed;                 // not used in combat; for reference to party only
        int healthRemaining;           // fluid value for when the entity is harmed
        DiceRoller itsDiceRoller;      // interface to roll dice for various reasons
        Abilities abilities;           // the abilities the killable entity has
        KillableType natureOfTheBeast; // is it a player? monster? or NPC?
        std::string creatureName;      // the entity's in-game name
    protected:
        void setNature(KillableType);
        virtual int attackRoll();
        virtual int attack(Killable&);
};


#endif

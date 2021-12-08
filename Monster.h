#ifndef MONSTER_H
#define MONSTER_H

#include "Killable.h"

// where the monster can reasonably exist
typedef enum  Environment {NOWHERE, FOREST, WATER, DESERT, TOWN} Environment;

// types of attack saves the monster may have to make
typedef enum  AttackSave {NONE, STR, DEX, CON, INT, WIS, CHA} AttackSave;

// for initialization of Monster constructor
static vector<Environment> DEFAULT_ENVIRONMENT = {Environment::NOWHERE};

typedef string Attack;
typedef vector<Attack> AttackList;
typedef vector<string> Consequence;

// 6 elements, number of d4, d6, d8, d10, d12, d20 respectively
typedef vector<int> DamageDice;

// one element for each of the above structures per attack
typedef vector<DamageDice> DamageList;

class Monster : public Killable {
    public:
        int itsLibraryIndex; // not directly used, but a reminder to set value in library list
        int itsStrMod = 0;   // modifier for strength saves
        int itsDexMod = 0;   // modifier for dexterity saves
        int itsConMod = 0;   // modifier for constitution saves
        int itsIntMod = 0;   // modifier for intelligence saves
        int itsWisMod = 0;   // modifier for wisdom saves
        int itsChaMod = 0;   // modifier for charisma saves
        double challengeRating = 0.0;        // also not directly used
        vector<int> itsAttackModifiers;      // additional bonus to attack rolls per attack
        vector<AttackSave> itsAttackSaves;   // saving throws which might be needed for an attack
        AttackList itsAttacks;               // string of attack names the monster can use
        Consequence itsConsequences;         // string for consequences of a failed save against a monster's attack
        vector<int> itsDifficulty;           // the difficulty rating of an attack save
        DamageDice itsDamageDice;            // damage dice needed for each attack the monster has
        DamageList itsDamageList;            // see above
        vector<Environment> itsEnvironment;  // settings the monster can reside

    public: 
        Monster() {};
        Monster(std::string,          // creatureName
                int,                  // maxHealth
                int,                  // armorClass
                int,                  // moveSpeed
                Abilities,            // abilities
                vector<Environment>&, // environment
                int,                  // libraryIndex
                int,                  // strMod
                int,                  // dexMod
                int,                  // conMod
                int,                  // intMod
                int,                  // wisMod
                int);                 // chaMod
        virtual int attack(int);
        virtual int attackRoll(int&);
        int  takeDamage(int);
        int makeSavingThrow(int);
        vector<Environment> getEnvironment();
        Abilities getAbilities();
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "Killable.h"

class Player : public Killable {
    public:
        std::string race;
        std::string playerClass;
        std::string alignment;
        std::string playerName;
        int playerID = 0;
        int deathSavesPassed = 0;
        int deathSavesFailed = 0;
    public:
        Player(std::string, //playerName
               std::string, // characterName
               std::string, // race
               std::string, // playerClass
               std::string, // alignment
               int,         // maxHealth
               int,         // armorClass
               int          // moveSpeed
        );
        Player();
        // included for their turn in attack
        void attack();
        int  takeDamage(int); // not direclty used
};

// heavily used in main thread and encounters
typedef std::vector<Player> PlayerList; 

#endif
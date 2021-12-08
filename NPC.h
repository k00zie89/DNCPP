#ifndef NPC_H
#define NPC_H

#include "Killable.h"

class NPC : public Killable {
    private:
        std::string race;
        std::string playerClass;
        std::string alignment;
    public:
        NPC(std::string, // characterName
            std::string, // race
            std::string, // characterClass
            std::string, // alignment
            int,         // maxHealth
            int,         // armorClass
            int,         // moveSpeed
            Abilities);
        NPC();
               
        std::string getPlayerName();
        void attack();
        int  takeDamage(int);
        Abilities getAbilities() {return this->abilities;};
};

#endif
#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <iostream>
#include "MonsterLibrary.h"
#include "Player.h"
#include "NPC.h"

using namespace std;

// to pair a killable entity with its initiative for sorting
class Participant
{
    public:
        int itsInitiative  = 0;
        Killable* itsEntity = 0;
        Participant();
        Participant(Participant*);
        void attack();
};

typedef vector<Participant> ParticipantList;

class Encounter
{
    public:
        bool ended;                         // has the encounter ended?
        Environment   environment;          // where the encounter takes place
        ParticipantList itsParticipants;    // the entities involved in the fight
        ParticipantList* tempParticipants;  // used for sorting participants for combat order
        ParticipantList sortedParticipants; // holds the sorted results of the above
        MonsterLibrary itsLibrary;          // interface for monster creation
        DiceRoller itsDiceRoller;           // for needed dice rolls

        Encounter(Environment);
        void startEncounter(ParticipantList&, PlayerList&, Environment, int); // begins and runs the encounter
        void getMonsterInitiative(ParticipantList&);                          // takes participant list and assigns initiative to monsters
        int displayCombatMenu();                                              // prints the display for the interface
        Monster* getRandomMonster();                                          // generates a random value and creates a monster corresponding to it
        Monster* getMonsterFromLibrary();                                     // brings up the monster list and allows a choice to be made
    private:
        void sortParticipants(ParticipantList&);                              // when a new participant is added, this resorts participants to include them
};

#endif
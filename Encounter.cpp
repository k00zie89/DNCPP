#include "Encounter.h"

Encounter::Encounter(Environment theEnvironment)
{
    try 
    {
        // make sure there's room for icoming participants
        this->environment = theEnvironment;
        this->itsParticipants.reserve(20);
        cout << " participants vector can hold: " << this->itsParticipants.capacity() << endl;
    } 
    catch (...) 
    {
        cout << "Something went wrong while creating encounter..." << endl;
    }
}

void Encounter::startEncounter(ParticipantList& theParticipants, PlayerList& players,Environment env, int globalPlayerNum)
{
    // mucho del initializers
    int choiceAsNum = 0;
    int innerChoiceAsNum = 0;
    bool validChoice = false;
    bool validInnerChoice = false;
    string yesOrNo;
    string choiceAsString;
    string innerChoiceAsString;
    vector<Environment> theEnvironment;
    theEnvironment.reserve(5);

    // for primary loop
    bool stillInCombat = true;

    sortedParticipants.reserve(20);

    // create concrete instance
    itsLibrary = MonsterLibrary();

    cout << "Party consists of " << theParticipants.size() << " players." << endl;

    // prepare to sort without influencing primary participant list
    tempParticipants = new ParticipantList();
    tempParticipants->reserve(20);
    for (int s = 0; s < theParticipants.size(); s++)
    {
        tempParticipants->push_back(theParticipants.at(s));
    }

    // add monsters to encounter
    while (!validChoice) 
    {
        cout << "Let's add some monsters..." << endl;
        cout << "1.) Randomly add monsters:" << endl;
        cout << "2.) Pick from library:    " << endl;
        cin >> choiceAsString;
        try
        {
            choiceAsNum = stoi(choiceAsString);
        }
        catch(...)
        {
            cout << "Try again dumbass..." << endl;
        }
        if (choiceAsNum != 0)
        {
            switch (choiceAsNum) 
            {
                case 1:
                {
                    // create random monsters
                    validChoice = true;
                    while (!validInnerChoice) 
                    {
                        cout << "How many monsters to add?" << endl;
                        cin  >> innerChoiceAsString;
                        try
                        {
                            innerChoiceAsNum = stoi(innerChoiceAsString);
                        } 
                        catch (...) 
                        {
                            cout << "Give me an integer, buddy..." << endl;
                            break;
                        }
                        // make sure we stay in bounds
                        if (!(innerChoiceAsNum <= 0) && tempParticipants->size()+innerChoiceAsNum < 20)
                        {
                            validInnerChoice = true;
                            cout << "creating " << innerChoiceAsNum << " new monsters." << endl;
                            
                            for (int i = 0; i < innerChoiceAsNum; i++)
                            {
                                bool validMonster = false;
                                while (!validMonster) 
                                {
                                    Participant newParticipant = new Participant();
                                    Monster* newMonster = 0;
                                    while (newMonster == 0)
                                    {
                                        newMonster = getRandomMonster();
                                    }
                                    // make sure encounter environment is compatible with monster
                                    for (int e = 0; e < newMonster->itsEnvironment.size(); e++)
                                    {
                                        if (newMonster->itsEnvironment.at(e) == env)
                                        {
                                            validMonster = true;
                                        }
                                        else 
                                        {
                                            cout << "Monster environment " << newMonster->itsEnvironment.at(e)
                                                 << " does not match environment " << env << endl;    
                                        }
                                    }
                                    if (!validMonster)
                                    {
                                        cout << "No monster environment matches the one chosen; trying again." << endl;
                                    } 
                                    else
                                    {
                                        // if successful and compatible, add it to participant list
                                        newParticipant.itsEntity = newMonster;
                                        tempParticipants->push_back(newParticipant);
                                        cout << "Added " << newMonster->creatureName << " to list." << endl;
                                    }
                                    
                                }
                            }
                        }
                        else 
                        {
                            cout << "That makes too many participants. Let's try again." << endl;
                        }
                    }
                    break;
                }
                case 2:
                {
                    // manually choose monsters to add
                    validChoice = true;
                    while (!validInnerChoice) 
                    {
                        cout << "How many monsters to add?" << endl;
                        cin  >> innerChoiceAsString;
                        try
                        {
                            innerChoiceAsNum = stoi(innerChoiceAsString);
                        } catch (...) 
                        {
                            cout << "Give me an integer, buddy..." << endl;
                            break;
                        }
                        // make sure we stay in bounds
                        if (!(innerChoiceAsNum <= 0) && tempParticipants->size()+innerChoiceAsNum < 20)
                        {
                            validInnerChoice = true;
                            for (int i = 0; i < innerChoiceAsNum; i++)
                            {
                                bool validMonster = false;
                                while (!validMonster)
                                {
                                    Participant newParticipant;
                                    Monster* newMonster = 0;
                                    while (newMonster == 0)
                                    {
                                        newMonster = getMonsterFromLibrary();
                                    }
                                    // make sure encounter environment is compatible with monster
                                    for (int e = 0; e < newMonster->itsEnvironment.size(); e++)
                                    {
                                        if (newMonster->itsEnvironment.at(e) == env) 
                                        {
                                            validMonster = true;
                                        }
                                        else 
                                        {
                                            cout << "Monster environment " << newMonster->itsEnvironment.at(e)
                                                 << " does not match environment " << env << endl;
                                        }
                                    }
                                    if (!validMonster)
                                    {
                                        cout << "Monster not valid for environment; trying again." << endl;
                                    }
                                    else
                                    {
                                        // if successful and compatible, add to participant list
                                        newParticipant.itsEntity = newMonster;
                                        tempParticipants->push_back(newParticipant);
                                        cout << "Added " << newMonster->creatureName << " to list." << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << "That makes too many participants; let's try again." << endl;
                        }
                        
                    }

                    break;
                }
                default:
                    // shouldn't get here
                    break;
            }
        }
    } // done adding monsters

    // set monster initiative; players are already dealth with
    this->getMonsterInitiative(*tempParticipants);

    // sort participants
    sortParticipants(*tempParticipants);
    // store for later use
    sortedParticipants = *tempParticipants;

    int numMonstersConscious = 0;
    for (int p = 0; p < sortedParticipants.size(); p++)
    {
        if (sortedParticipants.at(p).itsEntity->natureOfTheBeast ==
            KillableType::MONSTER) 
        {
            // if this number drops to later during the encounter, end combat
            numMonstersConscious++;
        }
    } 

    cout << numMonstersConscious << " monsters conscious" << endl;
    
    // real thing starts NOW
    while (stillInCombat) 
    {
        // do combat until over

        // find out what we're doing
        int thingToDo = displayCombatMenu();
        // display at the start of every main menu choice (start of turn)
        cout << numMonstersConscious << " monsters conscious" << endl;

        switch (thingToDo)
        {
            case 1:
            {
                // display participant Type index, name, AC, remaining health, 
                // speed, and abilities if applicable
                cout << endl << "***** PARTICIPANT INFO ****** " << endl << endl;
                for (int p = 0; p < sortedParticipants.size(); p++)
                {
                    cout << "***** ";
                    cout << sortedParticipants.at(p).itsEntity->creatureName << " - ";
                    cout << " Armor Class: ";
                    cout << sortedParticipants.at(p).itsEntity->armorClass;
                    cout << " HP: ";
                    cout << sortedParticipants.at(p).itsEntity->healthRemaining;
                    cout << " Speed: ";
                    cout << sortedParticipants.at(p).itsEntity->moveSpeed 
                         << " ***** " << endl;
                    for (int a = 0; a < sortedParticipants.at(p).itsEntity->abilities.size();
                         a++)
                    {
                        cout << "  -> " << sortedParticipants.at(p).itsEntity->abilities.at(a) << " " << endl;
                    }
                    cout << "  Has initiative: ";
                    cout << sortedParticipants.at(p).itsInitiative << endl;
                }
                break;
            }
            case 2:
            {
                bool needSorting = false;
                // cycle through list of remaining participants once
                // allowing them to ...do...their thing?
                cout << "Initiating the round..." << endl;
                // seperate players from enemies since this changes round-to-round sometimes
                ParticipantList* currentMonsters = new ParticipantList();
                ParticipantList* currentPlayers  = new ParticipantList();
                ParticipantList* currentNPCs     = new ParticipantList();

                // allow for all participants to be players...unlikely, but...
                 currentPlayers->reserve(sortedParticipants.capacity());
                currentMonsters->reserve(sortedParticipants.capacity());
                    currentNPCs->reserve(sortedParticipants.capacity());

                // only add to current list if health > 0
                for (int v = 0; v < sortedParticipants.size(); v++)
                {
                    if (sortedParticipants.at(v).itsEntity->natureOfTheBeast == 
                        KillableType::PLAYER && (sortedParticipants.at(v).itsEntity->healthRemaining > 0))
                    {
                        currentPlayers->push_back(sortedParticipants.at(v));
                    }
                    else if (sortedParticipants.at(v).itsEntity->natureOfTheBeast ==
                             KillableType::MONSTER && (sortedParticipants.at(v).itsEntity->healthRemaining > 0))
                    {
                        currentMonsters->push_back(sortedParticipants.at(v));
                    }
                    else if ((sortedParticipants.at(v).itsEntity->healthRemaining > 0))
                    {
                        // TODO NPCs not yet supported
                        currentNPCs->push_back(sortedParticipants.at(v));
                    }
                }
                cout << "There are " << currentPlayers->size() << " players" << endl;
                cout << " and " << currentMonsters->size() << " monsters" << endl;

                // for random target selections
                Dice* participantChooser = new Dice(100);
                string pauseString;
                
                // starting the actual round
                for (int t = 0; t < sortedParticipants.size(); t++)
                {
                    if (stillInCombat)
                    {
                        if (sortedParticipants.at(t).itsEntity->natureOfTheBeast ==
                            KillableType::MONSTER)
                        {
                            // Monster's turn...if it's conscious.
                            if (sortedParticipants.at(t).itsEntity->healthRemaining > 0
                                && stillInCombat)
                            {
                                cout << "*** Monster - " << sortedParticipants.at(t).itsEntity->creatureName
                                    << "'s turn ***" << endl;

                                int monsterChoice = 0;
                                string monsterChoiceString;

                                bool monsterFinished = false;
                                while (!monsterFinished)
                                {
                                    // display choices of action
                                    cout << "What shall the monster do?"                       << endl;
                                    cout << "1.) Attack Participant"                           << endl;
                                    cout << "2.) Finish turn"                                  << endl;
                                    cout << "3.) DM CONTROL - Print Monsters w/ Health and AC" << endl;
                                    cout << "4.) DM CONTROL - Heal Participant"                << endl;
                                    cout << "5.) DM CONTROL - Harm Participant"                << endl;
                                    cout << "6.) DM CONTROL - Add New Monster From Library"    << endl;
                                    cout << "7.) DM CONTROL - Initiate 3rd Party Attack"       << endl;

                                    cin  >> monsterChoiceString;
                                    try
                                    {
                                        monsterChoice = stoi(monsterChoiceString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Invalid selection." << endl;
                                    }
                                    switch (monsterChoice)
                                    {
                                        case 1:
                                        {
                                            // attacking - determine the target
                                            cout << "Who shall he attack? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;
                                            while (validChoiceReceived == false) 
                                            {
                                                    // print players currently in combat
                                                    for (int z = 0; z < sortedParticipants.size(); z++)
                                                    {
                                                        if (z != t) 
                                                        {
                                                            cout << z+1 << ".) " << sortedParticipants.at(z).itsEntity->creatureName 
                                                                << " - " << sortedParticipants.at(z).itsEntity->healthRemaining << endl;
                                                        }

                                                    }
                                                    // allow random attack
                                                    cout << sortedParticipants.size() + 1 << ".) Random Participant" << endl;
                                                    cin  >> theChoiceReceived;
                                                    try
                                                    {
                                                        theChoice = stoi(theChoiceReceived);
                                                    }
                                                    catch(...)
                                                    {
                                                        cout << "Try again fucknuts..." << endl;
                                                    }
                                                    // check validity
                                                    if ((0 < theChoice) && (theChoice <= sortedParticipants.size()+1) && (theChoice != t+1))
                                                    {
                                                        validChoiceReceived = true;
                                                    }   
                                            }
                                            int beingAttacked = 0;
                                            if ((0 < theChoice) && (theChoice <= sortedParticipants.size()))
                                            {
                                                // if valid choice
                                                cout << "Setting value directly from choice." << endl;
                                                beingAttacked = theChoice;
                                            } 
                                            else if (theChoice == sortedParticipants.size()+1)
                                            {
                                                // generate random target choice
                                                cout << "Getting random value." << endl;
                                                beingAttacked = participantChooser->roll() % sortedParticipants.size() + 1;
                                            }
                                            else 
                                            {
                                                // if something goes wrong, default to first in list
                                                cout << "Invalid choice. Attacking first player in list." << endl;
                                                beingAttacked = 1;
                                            }
                                            // decrement to stay in vector's bounds
                                            beingAttacked -= 1;
                                            cout << "Monster attacks participant " << 
                                                sortedParticipants.at(beingAttacked).itsEntity->creatureName << endl;

                                            // generate attack roll and choose attack...
                                            // these are done at the same time since attack modifiers depend on the attack
                                            int attackRoll = 0;
                                            int chosenAttack = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->attackRoll(attackRoll);
                                            
                                            cout << "Attack roll result was a " << attackRoll << endl;

                                            if (attackRoll == 0)
                                            {
                                                // critical failure - no damage dealt by attack; deal with accordingly
                                                cout << "Critical Failure" << endl;
                                            }
                                            else if (attackRoll == 100)
                                            {
                                                // damage calculated, doubled, and dealt
                                                cout << "Critical Hit!" << endl;
                                                int damage = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->
                                                                                        attack(chosenAttack);
                                                cout << "Participant takes " << 2*damage << " damage." << endl;

                                                sortedParticipants.at(beingAttacked).itsEntity->healthRemaining -= 2*damage;
                                                // check for death
                                                if (sortedParticipants.at(beingAttacked).itsEntity->healthRemaining <= 0)
                                                {
                                                    cout << "Participant has been killed." << endl;
                                                    if (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::MONSTER)
                                                    {
                                                        numMonstersConscious -= 1;
                                                    }                                                
                                                }
                                            }
                                            else if (attackRoll > sortedParticipants.at(beingAttacked).itsEntity->armorClass)
                                            {
                                                // damage calculated and dealt
                                                int damage = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->
                                                                                        attack(chosenAttack);
                                                cout << "Player takes " << damage << " damage." << endl;
                                                sortedParticipants.at(beingAttacked).itsEntity->healthRemaining -= damage;

                                                // check for death
                                                if (sortedParticipants.at(beingAttacked).itsEntity->healthRemaining <= 0)
                                                {
                                                    cout << "Participant has been killed." << endl;
                                                    if (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::MONSTER)
                                                    {
                                                        numMonstersConscious -= 1;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                {
                                                    cout << "Monster's attack missed!" << endl;
                                                }
                                            }
                                            break;
                                        }
                                        case 2:
                                        {
                                            // ending the monster's turn...
                                            monsterFinished = true;
                                            cout << "Moving on..." << endl;
                                            break;
                                        }
                                        case 3:
                                        {
                                            // display monster data
                                            cout << "Monsters remaining: " << endl;
                                            for (int m = 0; m < currentMonsters->size(); m++)
                                            {
                                                cout << m+1 << ".) "     << currentMonsters->at(m).itsEntity->creatureName
                                                            << " - HP: " << currentMonsters->at(m).itsEntity->healthRemaining
                                                            << " - AC: " << currentMonsters->at(m).itsEntity->armorClass
                                                            << endl;
                                                for (int a = 0; a < currentMonsters->at(m).itsEntity->abilities.size(); a++)
                                                {
                                                    cout << "  -> " << currentMonsters->at(m).itsEntity->abilities.at(a) << " " << endl;
                                                }
                                            }
                                            break;
                                        }
                                        case 4:
                                        {
                                            // heal participant

                                            // initialize
                                            int thePlayer = -1;
                                            bool validPlayer = false;
                                            string thePlayerString;

                                            while (validPlayer == false)
                                            {
                                                // who are we healing?
                                                cout << "Which participant to heal?" << endl;
                                                for (int p = 0; p < sortedParticipants.size(); p++)
                                                {
                                                    cout << p+1 << ".) " << sortedParticipants.at(p).itsEntity->creatureName 
                                                                << " - " << sortedParticipants.at(p).itsEntity->healthRemaining 
                                                                << endl;
                                                }
                                                cin >> thePlayerString;
                                                try
                                                {
                                                    thePlayer = stoi(thePlayerString);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Invalid input. Try again." << endl;
                                                }
                                                // if valid choice...
                                                if ((0 < thePlayer) && (thePlayer <= sortedParticipants.size()))
                                                {
                                                    validPlayer = true;
                                                    // decrement for vector index
                                                    thePlayer--;
                                                    cout << "Healing participant " << sortedParticipants.at(thePlayer).itsEntity->creatureName << endl;

                                                    int healValue = 0;
                                                    bool validValue = false;
                                                    bool monsterRevived = false;
                                                    string healValueString;
                                                    while (!validValue) 
                                                    {
                                                        cout << "By how much" << endl;
                                                        cin  >> healValueString;
                                                        try
                                                        {
                                                            healValue = stoi(healValueString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Invalid number." << endl;
                                                        }
                                                        // don't harm the player by healing them...
                                                        if (0 < healValue)
                                                        {
                                                            validValue = true;

                                                            // count if monster was below zero health
                                                            if ((sortedParticipants.at(thePlayer).itsEntity->natureOfTheBeast == KillableType::MONSTER) &&
                                                                (sortedParticipants.at(thePlayer).itsEntity->healthRemaining <= 0))
                                                            {
                                                                monsterRevived = true;
                                                            }
                                                            // apply health change
                                                            sortedParticipants.at(thePlayer).itsEntity->healthRemaining += healValue;
                                                            if (monsterRevived)
                                                            {
                                                                cout << "Monster revived...returning it to the pool." << endl;
                                                                sortedParticipants.at(thePlayer).itsEntity->healthRemaining = healValue;
                                                                currentMonsters->push_back(sortedParticipants.at(thePlayer));
                                                                numMonstersConscious++;
                                                            }
                                                        }
                                                        else 
                                                        {
                                                            cout << "Cannot heal participant by negative amount." << endl;
                                                        }
                                                    }
                                                    cout << "Participant health is now " << sortedParticipants.at(thePlayer).itsEntity->healthRemaining << endl;
                                                }
                                                
                                            }
                                            break;
                                        }
                                        case 5:
                                        {
                                            // harm
                                            cout << "Which participant to harm? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;

                                            while (validChoiceReceived == false) 
                                            {
                                                // print participants and current health remaining
                                                for (int z = 0; z < sortedParticipants.size(); z++)
                                                {
                                                    cout << z+1 << ".) " << sortedParticipants.at(z).itsEntity->creatureName 
                                                        << " - HP: " << sortedParticipants.at(z).itsEntity->healthRemaining << endl;
                                                }
                                                // allow random damage e.g. "Lightning shall smithe....you!"
                                                cout << sortedParticipants.size() + 1 << ".) Random participant" << endl;
                                                cin  >> theChoiceReceived;
                                                try
                                                {
                                                    theChoice = stoi(theChoiceReceived);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Try again fucknuts..." << endl;
                                                }
                                                // validity check
                                                if (!(theChoice <= 0) && theChoice <= sortedParticipants.size()+1)
                                                {
                                                    validChoiceReceived = true;
                                                }   
                                            }
                                            int beingHarmed = -1;
                                            if (theChoice <= sortedParticipants.size())
                                            {
                                                beingHarmed = theChoice;
                                            } 
                                            else if (theChoice == sortedParticipants.size()+1)
                                            {
                                                beingHarmed = (participantChooser->roll()) % sortedParticipants.size() + 1;
                                            }
                                            beingHarmed--;
                                            cout << "Harming participant " << sortedParticipants.at(beingHarmed).itsEntity->creatureName << endl;
                                            int damageDealt = 0;
                                            bool validDamage = false;
                                            string damageAsString;
                                            while (!validDamage)
                                            {
                                                cout << "How much damage is being dealt?" << endl;
                                                cin  >> damageAsString;
                                                try
                                                {
                                                    damageDealt = stoi(damageAsString);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Valid integer please!" << endl;
                                                }
                                                // don't heal the participant by harming them
                                                if (damageDealt > 0)
                                                {
                                                    validDamage = true;
                                                    cout << "Dealing " << damageDealt << " damage to participant." << endl;

                                                    // apply damage
                                                    sortedParticipants.at(beingHarmed).itsEntity->healthRemaining -= damageDealt;

                                                    // check for death of monster
                                                    if ((sortedParticipants.at(beingHarmed).itsEntity->healthRemaining <= 0) &&
                                                         (sortedParticipants.at(beingHarmed).itsEntity->natureOfTheBeast == KillableType::MONSTER))
                                                    {
                                                        cout << "Monster has been killed." << endl;
                                                        numMonstersConscious--;
                                                        cout << numMonstersConscious << " monsters conscious" << endl;
                                                        if (numMonstersConscious <= 0) 
                                                        {
                                                            stillInCombat = false;
                                                            break;
                                                        }
                                                    }
                                                    // check for death of player
                                                    if ((sortedParticipants.at(beingHarmed).itsEntity->healthRemaining <= 0) &&
                                                         (sortedParticipants.at(beingHarmed).itsEntity->natureOfTheBeast == KillableType::PLAYER))
                                                    {
                                                        cout << "Player has been killed." << endl;
                                                    }
                                                }
                                            }
                                            break;
                                        }
                                        case 6:
                                        {
                                            // adding new monster
                                            bool validMonster = false;
                                            while (!validMonster)
                                            {
                                                Participant newParticipant;
                                                Monster* newMonster = 0;
                                                while (newMonster == 0)
                                                {
                                                    newMonster = getMonsterFromLibrary();
                                                }
                                                
                                                // check monster environment compatibility
                                                for (int e = 0; e < newMonster->itsEnvironment.size(); e++)
                                                {
                                                    if (newMonster->itsEnvironment.at(e) == env) 
                                                    {
                                                        validMonster = true;
                                                    }
                                                    else 
                                                    {
                                                        cout << "Monster environment " << newMonster->itsEnvironment.at(e)
                                                             << " does not match environment " << env << endl;
                                                    }
                                                }
                                                if (!validMonster)
                                                {
                                                    cout << "Monster not valid for environment; trying again." << endl;
                                                }
                                                else
                                                {
                                                    // assign new monster to participant list, with newly rolled initiative
                                                    newParticipant.itsEntity = newMonster;
                                                    newParticipant.itsInitiative = itsDiceRoller.rollDice(20);
                                                    sortedParticipants.push_back(newParticipant);
                                                    currentMonsters->push_back(newParticipant);
                                                    cout << "Added " << newMonster->creatureName << " to list." << endl;
                                                    // update monsters remaining
                                                    numMonstersConscious++;
                                                    needSorting = true;
                                                }
                                            }
                                            break;
                                        }
                                        case 7:
                                        {
                                            // have one participant attack a second one
                                            // get Attacker
                                            cout << "Who is attacking?" << endl;
                                            for (int s=0; s < sortedParticipants.size(); s++)
                                            {
                                                cout << s+1 << ".) ";
                                                cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                                            }
                                            bool validAttacker = false;
                                            string attackerString;
                                            int attackerIndex = 0;
                                            Killable* theAttacker;
                                            Player* playerAttacker = 0;
                                            Monster* monsterAttacker = 0;

                                            while (!validAttacker)
                                            {
                                                cin >> attackerString;
                                                try 
                                                {
                                                    attackerIndex = stoi(attackerString);
                                                }
                                                catch (...)
                                                {
                                                    cout << "Valid integer please." << endl;
                                                }
                                                if ((0 < attackerIndex) && (attackerIndex <= sortedParticipants.size()))
                                                {
                                                    validAttacker = true;
                                                    attackerIndex--;
                                                }
                                                else if (attackerIndex < 0) 
                                                {
                                                    cout << "Positive integer is needed." << endl;
                                                }
                                                else if (sortedParticipants.size() < attackerIndex) 
                                                {
                                                    cout << "Index out of bounds. Try again." << endl;
                                                }
                                            }
                                            theAttacker = sortedParticipants.at(attackerIndex).itsEntity;
                                            cout << "Valid attacker " << theAttacker->creatureName << " chosen." << endl;

                                            if (theAttacker->natureOfTheBeast == KillableType::PLAYER)
                                            {
                                                playerAttacker = reinterpret_cast<Player*>(sortedParticipants.at(attackerIndex).itsEntity);
                                            }
                                            else if (theAttacker->natureOfTheBeast == KillableType::MONSTER)
                                            {
                                                monsterAttacker = reinterpret_cast<Monster*>(sortedParticipants.at(attackerIndex).itsEntity);
                                            }

                                            // get Defender
                                            cout << "Who is being attacked?" << endl;
                                            for (int s=0; s < sortedParticipants.size(); s++)
                                            {
                                                cout << s+1 << ".) ";
                                                cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                                            }
                                            bool validDefender = false;
                                            string defenderString;
                                            int defenderIndex = 0;
                                            Killable* theDefender;
                                            Player* playerDefender = 0;
                                            Monster* monsterDefender = 0;

                                            while (!validDefender)
                                            {
                                                cin >> defenderString;
                                                try 
                                                {
                                                    defenderIndex = stoi(defenderString);
                                                }
                                                catch (...)
                                                {
                                                    cout << "Valid integer please." << endl;
                                                }
                                                if ((0 < defenderIndex) && (defenderIndex <= sortedParticipants.size()))
                                                {
                                                    validDefender = true;
                                                    defenderIndex--;
                                                }
                                                else if (defenderIndex < 0) 
                                                {
                                                    cout << "Positive integer is needed." << endl;
                                                }
                                                else if (sortedParticipants.size() < defenderIndex) 
                                                {
                                                    cout << "Index out of bounds. Try again." << endl;
                                                }
                                            }

                                            theDefender = sortedParticipants.at(defenderIndex).itsEntity;
                                            cout << "Valid defender " << theDefender->creatureName << " chosen." << endl;

                                            // determine KillableType of attacker and defender
                                            KillableType attackerType = theAttacker->natureOfTheBeast;
                                            KillableType defenderType = theDefender->natureOfTheBeast;

                                            // perform attack

                                            // for monsters...
                                            if (attackerType == KillableType::MONSTER)
                                            {
                                                if (monsterAttacker != 0) 
                                                {
                                                    int attackRoll = 0;
                                                    int chosenAttack = monsterAttacker->attackRoll(attackRoll);
                                                                    
                                                    cout << "Attack roll result was a " << attackRoll << endl;

                                                    if (attackRoll == 0)
                                                    {
                                                        // critical failure - no damage dealt by attack; deal with accordingly
                                                        cout << "Critical Failure" << endl;
                                                    }
                                                    else if (attackRoll == 100)
                                                    {
                                                        // damage calculated, doubled, and dealt
                                                        cout << "Critical Hit!" << endl;
                                                        int damage = monsterAttacker->attack(chosenAttack);
                                                        cout << "Participant takes " << 2*damage << " damage." << endl;

                                                        theDefender->healthRemaining -= 2*damage;
                                                        // check for death
                                                        if (theDefender->healthRemaining <= 0)
                                                        {
                                                            cout << "Participant has been killed." << endl;
                                                            if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                            {
                                                                numMonstersConscious -= 1;
                                                            }                                                
                                                        }
                                                    }
                                                    else if (attackRoll > theDefender->armorClass)
                                                    {
                                                        // damage calculated and dealt
                                                        int damage = reinterpret_cast<Monster*>(theAttacker)->attack(chosenAttack);
                                                        cout << "Player takes " << damage << " damage." << endl;
                                                        theDefender->healthRemaining -= damage;

                                                        // check for death
                                                        if (theDefender->healthRemaining <= 0)
                                                        {
                                                            cout << "Participant has been killed." << endl;
                                                            if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                            {
                                                                numMonstersConscious -= 1;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << "Monster's attack missed!" << endl;
                                                    }
                                                }
                                                else 
                                                {
                                                    cout << "Unable to cast attacker as MONSTER type." << endl;
                                                }
                                            } 
                                            else if (attackerType == KillableType::PLAYER)
                                            {
                                                if (playerAttacker != 0)
                                                {
                                                    int playerAttackRoll = 0;
                                                    bool validAttackRoll = false;
                                                    string attackRollString;

                                                    // get player attack roll
                                                    while (!validAttackRoll)
                                                    { 
                                                        cout << "What is " << theAttacker->creatureName << "'s attack roll?" << endl;
                                                        cin  >> attackRollString;
                                                        try
                                                        {
                                                            playerAttackRoll = stoi(attackRollString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Valid integer please!" << endl;
                                                        }
                                                        if (playerAttackRoll > 0)
                                                        {
                                                            // can't be negative
                                                            validAttackRoll = true;
                                                        }
                                                    }
                                                    // see if the attack hits
                                                    if (playerAttackRoll > theDefender->armorClass)
                                                    {   
                                                        int savingThrowNeeded;
                                                        bool validSaveThrowNeededCheck = false;
                                                        string savingThrowNeededString;

                                                        // see if monster needs to make a saving throw
                                                        while (!validSaveThrowNeededCheck)
                                                        {
                                                            cout << "Is a saving throw needed? (enter 0 for no, 1 for yes)" << endl;
                                                            cin  >> savingThrowNeededString;
                                                            try
                                                            {
                                                                savingThrowNeeded = stoi(savingThrowNeededString);
                                                            }
                                                            catch(...)
                                                            {
                                                                cout << "Enter a '0', or a '1'" << endl;
                                                            }
                                                            if (savingThrowNeeded == 0) 
                                                            {
                                                                validSaveThrowNeededCheck = true;
                                                                cout << "No saving throw needed" << endl;
                                                            } 
                                                            else if (savingThrowNeeded == 1) 
                                                            {
                                                                validSaveThrowNeededCheck = true;
                                                                // if a saving throw is necessary, find out which kind

                                                                int saveType = 0;
                                                                bool validSaveType = false;
                                                                string saveTypeString;
                                                                int monsterSaveThrow = 0;
                                                                while (!validSaveType)
                                                                {
                                                                    cout << "Which type of save is needed? " << endl;
                                                                    cout << "1.) Strength"     << endl;
                                                                    cout << "2.) Dexterity"    << endl;
                                                                    cout << "3.) Constitution" << endl; 
                                                                    cout << "4.) Intelligence" << endl;
                                                                    cout << "5.) Wisdom"       << endl;
                                                                    cout << "6.) Charisma"     << endl;
                                                                    cin >> saveTypeString;
                                                                    try
                                                                    {
                                                                        saveType = stoi(saveTypeString);
                                                                    }
                                                                    catch(...)
                                                                    {
                                                                        cout << "Please select a valid option." << endl;
                                                                    }
                                                                    // validity check
                                                                    if ((0 < saveType) && (saveType <= 6) &&
                                                                        (theDefender->natureOfTheBeast == KillableType::MONSTER))
                                                                    {
                                                                        // have the monster make the save
                                                                        Monster* theMonster = 0;
                                                                        theMonster = reinterpret_cast<Monster*>(theDefender);
                                                                        if (theMonster != 0)
                                                                        {
                                                                            monsterSaveThrow = theMonster->makeSavingThrow(saveType);
                                                                            validSaveType = true;
                                                                            cout << "Monster rolled " << monsterSaveThrow << " as its save." << endl;
                                                                        }
                                                                        else 
                                                                        {
                                                                            validSaveType = true;
                                                                            cout << "Failed to cast target as Monster." << endl;
                                                                        }
                                                                    }
                                                                    else if ((0 < saveType) && (saveType <= 6))
                                                                    {
                                                                        validSaveType = true;
                                                                        cout << "Determine effect of saving throw between players..." << endl;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                cout << "Invalid input detected. Moving on to attack roll." << endl;
                                                            }  
                                                        }
                                                        cout << "Find out how they're attacking, and HOW MUCH DAMAGE?" << endl;

                                                        int damageDealt = 0;
                                                        bool validDamage = false;
                                                        string damageAsString;
                                                        while (!validDamage)
                                                            {   
                                                                cout << "How much damage is being dealt?" << endl;
                                                                cin  >> damageAsString;
                                                                try
                                                                {
                                                                    damageDealt = stoi(damageAsString);
                                                                }
                                                                catch(...)
                                                                {
                                                                    cout << "Valid integer please!" << endl;
                                                                }
                                                                if (damageDealt > 0)
                                                                {
                                                                    validDamage = true;
                                                                    cout << "Dealing " << damageDealt << " damage to participant." << endl;

                                                                    // deal the damage
                                                                    theDefender->healthRemaining -= damageDealt;
                                                                    // check for death
                                                                    if (theDefender->healthRemaining <= 0)
                                                                    {
                                                                        cout << "Participant has been killed." << endl;
                                                                        if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                                        {
                                                                            numMonstersConscious--;
                                                                            cout << numMonstersConscious << " monsters conscious" << endl;
                                                                            if (numMonstersConscious <= 0) 
                                                                            {
                                                                                stillInCombat = false;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            cout << "Player attack missed." << endl;
                                                        } 
                                                }
                                                else 
                                                {
                                                    cout << "Unable to cast attacker to PLAYER type." << endl;
                                                }
                                            }
                                            break;
                                        }
                                        default:
                                        {
                                            cout << "Invalid choice." << endl;
                                            
                                        }
                                    }
                                }
                            }
                            else if (stillInCombat)
                            {
                                // monster is dead; no further action necessary
                                cout << "Monster is unconscious..." << endl;
                            }
                            else
                            {
                                break;
                            }    
                        }
                        else if (sortedParticipants.at(t).itsEntity->natureOfTheBeast ==
                             KillableType::PLAYER) 
                        {
                            // Player's turn, if conscious
                            if (sortedParticipants.at(t).itsEntity->healthRemaining > 0
                                && stillInCombat)
                            {
                                // get player choice, do the thing
                                cout << "Player " << sortedParticipants.at(t).itsEntity->creatureName 
                                    << "'s turn..." << endl;

                                int playerChoice = 0;
                                string playerChoiceString;

                                bool playerFinished = false;

                                // provide choices
                                while (!playerFinished)
                                {
                                    cout << "What shall the player do?"                        << endl;
                                    cout << "1.) Attack Participant"                           << endl;
                                    cout << "2.) Finish Turn"                                  << endl;
                                    cout << "3.) DM CONTROL - Print Monsters w/ Health and AC" << endl;
                                    cout << "4.) DM CONTROL - Heal Participant"                << endl;
                                    cout << "5.) DM CONTROL - Harm Participant"                << endl;
                                    cout << "6.) DM CONTROL - Add New Monster From Library"    << endl;
                                    cout << "7.) DM CONTROL - Initiate 3rd Party Attack"       << endl;

                                    cin  >> playerChoiceString;
                                    try
                                    {
                                        playerChoice = stoi(playerChoiceString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Invalid selection." << endl;
                                    }
                                    switch (playerChoice)
                                    {
                                        case 1:
                                        {
                                            // attacking. but who?
                                            cout << "Who shall the player attack? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;
                                            while (validChoiceReceived == false) 
                                            {
                                                // print monsters available to attack
                                                for (int z = 0; z < sortedParticipants.size(); z++)
                                                {
                                                    cout << z+1 << ".) " << sortedParticipants.at(z).itsEntity->creatureName 
                                                        << " - HP: " << sortedParticipants.at(z).itsEntity->healthRemaining << endl;
                                                }
                                                // allow random choice
                                                cout << sortedParticipants.size() + 1 << ".) Random participant" << endl;
                                                cin  >> theChoiceReceived;
                                                try
                                                {
                                                    theChoice = stoi(theChoiceReceived);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Try again fucknuts..." << endl;
                                                }
                                                if ((0 < theChoice) && (theChoice <= sortedParticipants.size()+1))
                                                {
                                                    validChoiceReceived = true;
                                                }   
                                            }
                                            int beingAttacked = 0;
                                            // check validity
                                            if ((0 < theChoice) && (theChoice <= sortedParticipants.size()))
                                            {
                                                // valid choice received
                                                cout << "Setting the choice directly." << endl;
                                                beingAttacked = theChoice;
                                            } 
                                            else if (theChoice == sortedParticipants.size()+1)
                                            {
                                                // choose random value and monster
                                                cout << "Choosing random participant." << endl;
                                                beingAttacked = participantChooser->roll() % sortedParticipants.size() + 1;
                                            }
                                            else
                                            {
                                                // something went wrong; use first item on list
                                                cout << "Invalid selection detected. Choosing first available participant." << endl;
                                                beingAttacked = 1;
                                            }
                                            // decrement for vector index
                                            beingAttacked--;
                                            if (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::MONSTER)
                                            {
                                                cout << "Participant chosen is MONSTER " << beingAttacked+1 << endl;
                                            } 
                                            else if (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::PLAYER)
                                            {
                                                cout << "Participant chosen is PLAYER " << beingAttacked+1 << endl;
                                            }

                                            int playerAttackRoll = 0;
                                            bool validAttackRoll = false;
                                            string attackRollString;

                                            // get player attack roll
                                            while (!validAttackRoll)
                                            {
                                                cout << "What is " << sortedParticipants.at(t).itsEntity->creatureName << "'s attack roll?" << endl;
                                                cin  >> attackRollString;
                                                try
                                                {
                                                    playerAttackRoll = stoi(attackRollString);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Valid integer please!" << endl;
                                                }
                                                if (playerAttackRoll > 0)
                                                {
                                                    // can't be negative
                                                    validAttackRoll = true;
                                                }
                                                // see if the attack hits
                                                if (playerAttackRoll > sortedParticipants.at(beingAttacked).itsEntity->armorClass)
                                                {   
                                                    int savingThrowNeeded;
                                                    bool validSaveThrowNeededCheck = false;
                                                    string savingThrowNeededString;

                                                    // see if monster needs to make a saving throw
                                                    while (!validSaveThrowNeededCheck)
                                                    {
                                                        cout << "Is a saving throw needed? (enter 0 for no, 1 for yes)" << endl;
                                                        cin  >> savingThrowNeededString;
                                                        try
                                                        {
                                                            savingThrowNeeded = stoi(savingThrowNeededString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Enter a '0', or a '1'" << endl;
                                                        }
                                                        if (savingThrowNeeded == 0) 
                                                        {
                                                            validSaveThrowNeededCheck = true;
                                                            cout << "No saving throw needed" << endl;
                                                        } 
                                                        else if (savingThrowNeeded == 1) 
                                                        {
                                                            validSaveThrowNeededCheck = true;
                                                            // if a saving throw is necessary, find out which kind

                                                            int saveType = 0;
                                                            bool validSaveType = false;
                                                            string saveTypeString;
                                                            int monsterSaveThrow = 0;
                                                            while (!validSaveType)
                                                            {
                                                                cout << "Which type of save is needed? " << endl;
                                                                cout << "1.) Strength"     << endl;
                                                                cout << "2.) Dexterity"    << endl;
                                                                cout << "3.) Constitution" << endl; 
                                                                cout << "4.) Intelligence" << endl;
                                                                cout << "5.) Wisdom"       << endl;
                                                                cout << "6.) Charisma"     << endl;
                                                                cin >> saveTypeString;
                                                                try
                                                                {
                                                                    saveType = stoi(saveTypeString);
                                                                }
                                                                catch(...)
                                                                {
                                                                    cout << "Please select a valid option." << endl;
                                                                }
                                                                // validity check
                                                                if ((0 < saveType) && (saveType <= 6) &&
                                                                    (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::MONSTER))
                                                                {
                                                                    // have the monster make the save
                                                                    Monster* theMonster = 0;
                                                                    theMonster = reinterpret_cast<Monster*>(sortedParticipants.at(beingAttacked).itsEntity);
                                                                    if (theMonster != 0)
                                                                    {
                                                                        monsterSaveThrow = theMonster->makeSavingThrow(saveType);
                                                                        validSaveType = true;
                                                                        cout << "Monster rolled " << monsterSaveThrow << " as its save." << endl;
                                                                    }
                                                                    else
                                                                    {
                                                                        validSaveType = true;
                                                                        cout << "Failed to cast target as Monster." << endl;
                                                                    }
                                                                }
                                                                else if ((0 < saveType) && (saveType <= 6))
                                                                {
                                                                    validSaveType = true;
                                                                    cout << "Determine effect of saving throw between players..." << endl;
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            cout << "Invalid input detected. Moving on to attack roll." << endl;
                                                        }  
                                                    }
                                                    cout << "Find out how they're attacking, and HOW MUCH DAMAGE?" << endl;

                                                    int damageDealt = 0;
                                                    bool validDamage = false;
                                                    string damageAsString;
                                                    while (!validDamage)
                                                    {
                                                        cout << "How much damage is being dealt?" << endl;
                                                        cin  >> damageAsString;
                                                        try
                                                        {
                                                            damageDealt = stoi(damageAsString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Valid integer please!" << endl;
                                                        }
                                                        if (damageDealt > 0)
                                                        {
                                                            validDamage = true;
                                                            cout << "Dealing " << damageDealt << " damage to participant." << endl;

                                                            // deal the damage
                                                            sortedParticipants.at(beingAttacked).itsEntity->healthRemaining -= damageDealt;
                                                            // check for death
                                                            if (sortedParticipants.at(beingAttacked).itsEntity->healthRemaining <= 0)
                                                            {
                                                                cout << "Participant has been killed." << endl;
                                                                if (sortedParticipants.at(beingAttacked).itsEntity->natureOfTheBeast == KillableType::MONSTER)
                                                                {
                                                                    numMonstersConscious--;
                                                                    cout << numMonstersConscious << " monsters conscious" << endl;
                                                                    if (numMonstersConscious <= 0) 
                                                                    {
                                                                        stillInCombat = false;
                                                                        break;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    cout << "Player attack missed." << endl;
                                                } 
                                            }
                                            break;
                                        }
                                        case 2:
                                        {
                                            // player done
                                            playerFinished = true;
                                            cout << "Moving on..." << endl;
                                            break;
                                        }
                                        case 3:
                                        {
                                            // monsters left in combat
                                            cout << "Monsters remaining: " << endl;
                                            for (int m = 0; m < currentMonsters->size(); m++)
                                            {
                                                cout << m+1 << ".) "     << currentMonsters->at(m).itsEntity->creatureName
                                                            << " - HP: " << currentMonsters->at(m).itsEntity->healthRemaining
                                                            << " - AC: " << currentMonsters->at(m).itsEntity->armorClass
                                                            << endl;
                                                for (int a = 0; a < currentMonsters->at(m).itsEntity->abilities.size(); a++)
                                                {
                                                    cout << "  -> " << currentMonsters->at(m).itsEntity->abilities.at(a) << " " << endl;
                                                }
                                            }
                                            break;
                                        }
                                        case 4:
                                        {
                                            // heal participant
                                            int thePlayer = -1;
                                            bool validPlayer = false;
                                            string thePlayerString;
                                            while (validPlayer == false)
                                            {
                                                cout << "Which participant to heal?" << endl;
                                                for (int p = 0; p < sortedParticipants.size(); p++)
                                                {
                                                    cout << p+1 << ".) " << sortedParticipants.at(p).itsEntity->creatureName 
                                                                << " - " << sortedParticipants.at(p).itsEntity->healthRemaining 
                                                                << endl;
                                                }
                                                cin >> thePlayerString;
                                                try
                                                {
                                                    thePlayer = stoi(thePlayerString);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Invalid input. Try again." << endl;
                                                }
                                                if ((0 < thePlayer) && (thePlayer <= sortedParticipants.size()))
                                                {
                                                    validPlayer = true;
                                                    thePlayer--;
                                                    cout << "Healing participant " << sortedParticipants.at(thePlayer).itsEntity->creatureName << endl;
                                                    int healValue = 0;
                                                    bool validValue = false;
                                                    bool monsterRevived = false;
                                                    string healValueString;
                                                    while (!validValue) 
                                                    {
                                                        cout << "By how much" << endl;
                                                        cin  >> healValueString;
                                                        try
                                                        {
                                                            healValue = stoi(healValueString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Invalid number." << endl;
                                                        }
                                                        if (0 < healValue)
                                                        {
                                                            validValue = true;
                                                            if ((sortedParticipants.at(thePlayer).itsEntity->natureOfTheBeast == KillableType::MONSTER) &&
                                                                (sortedParticipants.at(thePlayer). itsEntity->healthRemaining <= 0))
                                                            {
                                                                monsterRevived = true;
                                                            }
                                                            sortedParticipants.at(thePlayer).itsEntity->healthRemaining += healValue;
                                                            if (monsterRevived)
                                                            {
                                                                cout << "Monster revived. Returning monster to pool." << endl;
                                                                sortedParticipants.at(thePlayer).itsEntity->healthRemaining = healValue;
                                                                currentMonsters->push_back(sortedParticipants.at(thePlayer));
                                                                numMonstersConscious++;
                                                            }
                                                        }
                                                        else 
                                                        {
                                                            cout << "Cannot heal participant by negative amount." << endl;
                                                        }
                                                    }
                                                    cout << "Participant health is now " << sortedParticipants.at(thePlayer).itsEntity->healthRemaining << endl;
                                                }
                                                
                                            }
                                            
                                                
                                            break;
                                        }
                                        case 5:
                                        {
                                            // hurt someone
                                            cout << "Which participant to harm? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;
                                            while (validChoiceReceived == false) 
                                            {
                                                for (int z = 0; z < sortedParticipants.size(); z++)
                                                {
                                                    cout << z+1 << ".) " << sortedParticipants.at(z).itsEntity->creatureName 
                                                        << " - HP: " << sortedParticipants.at(z).itsEntity->healthRemaining << endl;
                                                }
                                                cout << sortedParticipants.size() + 1 << ".) Random participant" << endl;
                                                cin  >> theChoiceReceived;
                                                try
                                                {
                                                    theChoice = stoi(theChoiceReceived);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Try again fucknuts..." << endl;
                                                }
                                                if (!(theChoice <= 0) && theChoice <= sortedParticipants.size()+1)
                                                {
                                                    validChoiceReceived = true;
                                                }   
                                            }
                                            int beingHarmed = -1;
                                            if (theChoice <= sortedParticipants.size())
                                            {
                                                beingHarmed = theChoice;
                                            } 
                                            else if (theChoice == sortedParticipants.size()+1)
                                            {
                                                beingHarmed = (participantChooser->roll()) % sortedParticipants.size() + 1;
                                            }
                                            beingHarmed--;
                                            cout << "Participant " << sortedParticipants.at(beingHarmed).itsEntity->creatureName << " chosen." << endl;
                                            int damageDealt = 0;
                                            bool validDamage = false;
                                            string damageAsString;
                                            while (!validDamage)
                                            {
                                                cout << "How much damage is being dealt?" << endl;
                                                cin  >> damageAsString;
                                                try
                                                {
                                                    damageDealt = stoi(damageAsString);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Valid integer please!" << endl;
                                                }
                                                if (damageDealt > 0)
                                                {
                                                    validDamage = true;
                                                    cout << "Dealing " << damageDealt << " damage to participant." << endl;
                                                    sortedParticipants.at(beingHarmed).itsEntity->healthRemaining -= damageDealt;
                                                    if ((sortedParticipants.at(beingHarmed).itsEntity->healthRemaining <= 0) &&
                                                         (sortedParticipants.at(beingHarmed).itsEntity->natureOfTheBeast == KillableType::MONSTER))
                                                    {
                                                        cout << "Monster has been killed." << endl;
                                                        numMonstersConscious--;
                                                        cout << numMonstersConscious << " monsters conscious" << endl;
                                                        if (numMonstersConscious <= 0) 
                                                        {
                                                            stillInCombat = false;
                                                            break;
                                                        }
                                                    }
                                                    if ((sortedParticipants.at(beingHarmed).itsEntity->healthRemaining <= 0) &&
                                                         (sortedParticipants.at(beingHarmed).itsEntity->natureOfTheBeast == KillableType::PLAYER))
                                                    {
                                                        cout << "Player has been killed." << endl;
                                                    }
                                                }
                                            }
                                            break;
                                        }
                                        case 6:
                                        {
                                            bool validMonster = false;
                                            while (!validMonster)
                                            {
                                                Participant newParticipant;
                                                Monster* newMonster = 0;
                                                while (newMonster == 0)
                                                {
                                                    newMonster = getMonsterFromLibrary();
                                                }
                                                for (int e = 0; e < newMonster->itsEnvironment.size(); e++)
                                                {
                                                    if (newMonster->itsEnvironment.at(e) == env) 
                                                    {
                                                        validMonster = true;
                                                    }
                                                    else 
                                                    {
                                                        cout << "Monster environment " << newMonster->itsEnvironment.at(e)
                                                             << " does not match environment " << env << endl;
                                                    }
                                                }
                                                if (!validMonster)
                                                {
                                                    cout << "Monster not valid for environment; trying again." << endl;
                                                }
                                                else
                                                {
                                                    newParticipant.itsEntity = newMonster;
                                                    newParticipant.itsInitiative = itsDiceRoller.rollDice(20);
                                                    sortedParticipants.push_back(newParticipant);
                                                    currentMonsters->push_back(newParticipant);
                                                    cout << "Added " << newMonster->creatureName << " to list." << endl;
                                                    // increment monsters conscious for turn
                                                    numMonstersConscious++;
                                                    needSorting = true;
                                                }
                                            }
                                            break;
                                        }
                                        case 7:
                                        {
                                            // have one participant attack a second one
                                            // get Attacker
                                            cout << "Who is attacking?" << endl;
                                            for (int s=0; s < sortedParticipants.size(); s++)
                                            {
                                                cout << s+1 << ".) ";
                                                cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                                            }
                                            bool validAttacker = false;
                                            string attackerString;
                                            int attackerIndex = 0;
                                            Killable* theAttacker;
                                            Player* playerAttacker = 0;
                                            Monster* monsterAttacker = 0;

                                            while (!validAttacker)
                                            {
                                                cin >> attackerString;
                                                try 
                                                {
                                                    attackerIndex = stoi(attackerString);
                                                }
                                                catch (...)
                                                {
                                                    cout << "Valid integer please." << endl;
                                                }
                                                if ((0 < attackerIndex) && (attackerIndex <= sortedParticipants.size()))
                                                {
                                                    validAttacker = true;
                                                    attackerIndex--;
                                                }
                                                else if (attackerIndex < 0) 
                                                {
                                                    cout << "Positive integer is needed." << endl;
                                                }
                                                else if (sortedParticipants.size() < attackerIndex) 
                                                {
                                                    cout << "Index out of bounds. Try again." << endl;
                                                }
                                            }
                                            theAttacker = sortedParticipants.at(attackerIndex).itsEntity;
                                            cout << "Valid attacker " << theAttacker->creatureName << " chosen." << endl;

                                            if (theAttacker->natureOfTheBeast == KillableType::PLAYER)
                                            {
                                                playerAttacker = reinterpret_cast<Player*>(sortedParticipants.at(attackerIndex).itsEntity);
                                            }
                                            else if (theAttacker->natureOfTheBeast == KillableType::MONSTER)
                                            {
                                                monsterAttacker = reinterpret_cast<Monster*>(sortedParticipants.at(attackerIndex).itsEntity);
                                            }

                                            // get Defender
                                            cout << "Who is being attacked?" << endl;
                                            for (int s=0; s < sortedParticipants.size(); s++)
                                            {
                                                cout << s+1 << ".) ";
                                                cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                                            }
                                            bool validDefender = false;
                                            string defenderString;
                                            int defenderIndex = 0;
                                            Killable* theDefender;
                                            Player* playerDefender = 0;
                                            Monster* monsterDefender = 0;

                                            while (!validDefender)
                                            {
                                                cin >> defenderString;
                                                try 
                                                {
                                                    defenderIndex = stoi(defenderString);
                                                }
                                                catch (...)
                                                {
                                                    cout << "Valid integer please." << endl;
                                                }
                                                if ((0 < defenderIndex) && (defenderIndex <= sortedParticipants.size()))
                                                {
                                                    validDefender = true;
                                                    defenderIndex--;
                                                }
                                                else if (defenderIndex < 0) 
                                                {
                                                    cout << "Positive integer is needed." << endl;
                                                }
                                                else if (sortedParticipants.size() < defenderIndex) 
                                                {
                                                    cout << "Index out of bounds. Try again." << endl;
                                                }
                                            }

                                            theDefender = sortedParticipants.at(defenderIndex).itsEntity;
                                            cout << "Valid defender " << theDefender->creatureName << " chosen." << endl;

                                            // determine KillableType of attacker and defender
                                            KillableType attackerType = theAttacker->natureOfTheBeast;
                                            KillableType defenderType = theDefender->natureOfTheBeast;

                                            // perform attack

                                            // for monsters...
                                            if (attackerType == KillableType::MONSTER)
                                            {
                                                if (monsterAttacker != 0) 
                                                {
                                                    int attackRoll = 0;
                                                    int chosenAttack = monsterAttacker->attackRoll(attackRoll);
                                                                    
                                                    cout << "Attack roll result was a " << attackRoll << endl;

                                                    if (attackRoll == 0)
                                                    {
                                                        // critical failure - no damage dealt by attack; deal with accordingly
                                                        cout << "Critical Failure" << endl;
                                                    }
                                                    else if (attackRoll == 100)
                                                    {
                                                        // damage calculated, doubled, and dealt
                                                        cout << "Critical Hit!" << endl;
                                                        int damage = monsterAttacker->attack(chosenAttack);
                                                        cout << "Participant takes " << 2*damage << " damage." << endl;

                                                        theDefender->healthRemaining -= 2*damage;
                                                        // check for death
                                                        if (theDefender->healthRemaining <= 0)
                                                        {
                                                            cout << "Participant has been killed." << endl;
                                                            if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                            {
                                                                numMonstersConscious -= 1;
                                                            }                                                
                                                        }
                                                    }
                                                    else if (attackRoll > theDefender->armorClass)
                                                    {
                                                        // damage calculated and dealt
                                                        int damage = reinterpret_cast<Monster*>(theAttacker)->attack(chosenAttack);
                                                        cout << "Player takes " << damage << " damage." << endl;
                                                        theDefender->healthRemaining -= damage;

                                                        // check for death
                                                        if (theDefender->healthRemaining <= 0)
                                                        {
                                                            cout << "Participant has been killed." << endl;
                                                            if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                            {
                                                                numMonstersConscious -= 1;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << "Monster's attack missed!" << endl;
                                                    }
                                                }
                                                else 
                                                {
                                                    cout << "Unable to cast attacker as MONSTER type." << endl;
                                                }
                                            }    
                                            else if (attackerType == KillableType::PLAYER)
                                            {
                                                if (playerAttacker != 0)
                                                {
                                                    int playerAttackRoll = 0;
                                                    bool validAttackRoll = false;
                                                    string attackRollString;

                                                    // get player attack roll
                                                    while (!validAttackRoll)
                                                    {
                                                        cout << "What is " << theAttacker->creatureName << "'s attack roll?" << endl;
                                                        cin  >> attackRollString;
                                                        try
                                                        {
                                                            playerAttackRoll = stoi(attackRollString);
                                                        }
                                                        catch(...)
                                                        {
                                                            cout << "Valid integer please!" << endl;
                                                        }
                                                        if (playerAttackRoll > 0)
                                                        {
                                                            // can't be negative
                                                            validAttackRoll = true;
                                                        }
                                                    }
                                                    // see if the attack hits
                                                    if (playerAttackRoll > theDefender->armorClass)
                                                    {   
                                                        int savingThrowNeeded;
                                                        bool validSaveThrowNeededCheck = false;
                                                        string savingThrowNeededString;

                                                        // see if monster needs to make a saving throw
                                                        while (!validSaveThrowNeededCheck)
                                                        {
                                                            cout << "Is a saving throw needed? (enter 0 for no, 1 for yes)" << endl;
                                                            cin  >> savingThrowNeededString;
                                                            try
                                                            {
                                                                savingThrowNeeded = stoi(savingThrowNeededString);
                                                            }
                                                            catch(...)
                                                            {
                                                                cout << "Enter a '0', or a '1'" << endl;
                                                            }
                                                            if (savingThrowNeeded == 0) 
                                                            {
                                                                validSaveThrowNeededCheck = true;
                                                                cout << "No saving throw needed" << endl;
                                                            } 
                                                            else if (savingThrowNeeded == 1) 
                                                            {
                                                                validSaveThrowNeededCheck = true;
                                                                // if a saving throw is necessary, find out which kind

                                                                int saveType = 0;
                                                                bool validSaveType = false;
                                                                string saveTypeString;
                                                                int monsterSaveThrow = 0;
                                                                while (!validSaveType)
                                                                {
                                                                    cout << "Which type of save is needed? " << endl;
                                                                    cout << "1.) Strength"     << endl;
                                                                    cout << "2.) Dexterity"    << endl;
                                                                    cout << "3.) Constitution" << endl; 
                                                                    cout << "4.) Intelligence" << endl;
                                                                    cout << "5.) Wisdom"       << endl;
                                                                    cout << "6.) Charisma"     << endl;
                                                                    cin >> saveTypeString;
                                                                    try
                                                                    {
                                                                        saveType = stoi(saveTypeString);
                                                                    }
                                                                    catch(...)
                                                                    {
                                                                        cout << "Please select a valid option." << endl;
                                                                    }
                                                                    // validity check
                                                                    if ((0 < saveType) && (saveType <= 6) &&
                                                                        (theDefender->natureOfTheBeast == KillableType::MONSTER))
                                                                    {
                                                                        // have the monster make the save
                                                                        Monster* theMonster = 0;
                                                                        theMonster = reinterpret_cast<Monster*>(theDefender);
                                                                        if (theMonster != 0)
                                                                        {
                                                                            monsterSaveThrow = theMonster->makeSavingThrow(saveType);
                                                                            validSaveType = true;
                                                                            cout << "Monster rolled " << monsterSaveThrow << " as its save." << endl;
                                                                        }
                                                                        else 
                                                                        {
                                                                            validSaveType = true;
                                                                            cout << "Failed to cast target as Monster." << endl;
                                                                        }
                                                                    }
                                                                    else if ((0 < saveType) && (saveType <= 6))
                                                                    {
                                                                        validSaveType = true;
                                                                        cout << "Determine effect of saving throw between players..." << endl;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                cout << "Invalid input detected. Moving on to attack roll." << endl;
                                                            }  
                                                        }
                                                        cout << "Find out how they're attacking, and HOW MUCH DAMAGE?" << endl;

                                                        int damageDealt = 0;
                                                        bool validDamage = false;
                                                        string damageAsString;
                                                        while (!validDamage)
                                                        {
                                                            cout << "How much damage is being dealt?" << endl;
                                                            cin  >> damageAsString;
                                                            try
                                                            {
                                                                damageDealt = stoi(damageAsString);
                                                            }
                                                            catch(...)
                                                            {
                                                                cout << "Valid integer please!" << endl;
                                                            }
                                                            if (damageDealt > 0)
                                                            {
                                                                validDamage = true;
                                                                cout << "Dealing " << damageDealt << " damage to participant." << endl;

                                                                // deal the damage
                                                                theDefender->healthRemaining -= damageDealt;
                                                                // check for death
                                                                if (theDefender->healthRemaining <= 0)
                                                                {
                                                                    cout << "Participant has been killed." << endl;
                                                                    if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                                                    {
                                                                        numMonstersConscious--;
                                                                        cout << numMonstersConscious << " monsters conscious" << endl;
                                                                        if (numMonstersConscious <= 0) 
                                                                        {
                                                                            stillInCombat = false;
                                                                            break;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << "Player attack missed." << endl;
                                                    } 
                                                }
                                                else 
                                                {
                                                    cout << "Unable to cast attacker to PLAYER type." << endl;
                                                }
                                            }
                                            break;
                                        }
                                        default:
                                        {
                                            cout << "***** unexpected condition *****" << endl;
                                            break;
                                        }
                                    }
                                }                                    
                            } 
                            // player has zero or less health
                            else if (stillInCombat)
                            {
                                cout << "Player is unconscious; make a saving throw!" << endl;
                                bool validSaveResponse = false;
                                int  saveResponse = -1;
                                string saveResponseString;
                                while (!validSaveResponse)
                                {
                                    cout << "Did player pass the save? 0 for no, 1 for yes..." << endl;
                                    cin  >> saveResponseString;
                                    try
                                    {
                                        saveResponse = stoi(saveResponseString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Invalid response. Try again..." << endl;
                                    }
                                    if (saveResponse == 0)
                                    {
                                        // death save failure
                                        cout << "Registering player death save failure...";
                                        // increment failures
                                        reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesFailed += 1;
                                        cout << "DONE." << endl;
                                        validSaveResponse = true;
                                        // if third failure, declare player to be DEAD
                                        if (reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesFailed == 3)
                                        {
                                            // make death save successes impossible to overcome
                                            reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed = -1000;
                                            cout << "Player is DEAD. Dearest condolences to you departed comrade's real-life representative." << endl;
                                        }
                                    }
                                    else if (saveResponse == 1)
                                    {
                                        // death save success
                                        cout << "Registering player death save success...";
                                        // increment success counter
                                        reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed += 1;
                                        cout << "DONE." << endl;
                                        validSaveResponse = true;
                                        // if this is the third success before third failure, stabilize character
                                        if (reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed == 3)
                                        {
                                            cout << "Player has been stabilized. Recovering health..." << endl;
                                            // auto-assign 1d6 health back to player
                                            sortedParticipants.at(t).itsEntity->healthRemaining = 
                                            sortedParticipants.at(t).itsEntity->itsDiceRoller.rollDice(6);
                                            cout << "Player now has  " << sortedParticipants.at(t).itsEntity->healthRemaining << " HP." << endl;
                                            // reset death save counters
                                            reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed = 0;
                                            reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesFailed = 0;
                                            cout << "Reset saving throw numbers. Moving on." << endl;
                                        }
                                    }
                                    
                                }
                            }
                            else 
                            {
                                break;
                            }
                        }                         
                        else if (sortedParticipants.at(t).itsEntity->natureOfTheBeast ==
                                KillableType::NPC)
                        {
                            cout << "NPC - " << sortedParticipants.at(t).itsEntity->creatureName
                                << "'s turn..." << endl;
                            // TODO --- WHY CAN'T NPC BE USED AS A REINTERPRET CAST?!!!?
                        }
                        else 
                        {
                            cout << "Invalid participant in list. " << endl;
                        }
                        cin >> pauseString;
                    }
                }
                if (needSorting)
                {
                    // if new player or monster added, sort by initiative
                    sortParticipants(sortedParticipants);
                }
                break;
            }
            case 3:
            {
                // display remaining participants, then kill one!
                int choice = 0;
                bool validChoice = false;
                while (validChoice == false) 
                {
                    string choiceString;
                    cout << "Which participant to kill? " << endl;
                    // print participants remaining
                    for (int k = 0; k < sortedParticipants.size(); k++)
                    {
                        cout << k + 1 << ".) " << sortedParticipants.at(k).itsEntity->creatureName << " - " << 
                                                  sortedParticipants.at(k).itsEntity->healthRemaining <<  endl;
                    }
                    cin  >> choiceString;
                    try
                    {
                        choice = stoi(choiceString);
                    }
                    catch(...)
                    {
                        cout << "Enter a number, please..." << endl;
                    }
                    if (!(choice <= 0) && choice <= sortedParticipants.size()) 
                    {
                        validChoice = true;
                    }
                }
                choice--;
                cout << "Killing Participant " << sortedParticipants.at(choice).itsEntity->creatureName << ". " << endl;
                    sortedParticipants.at(choice).itsEntity->healthRemaining = -1;
                if (sortedParticipants.at(choice).itsEntity->natureOfTheBeast ==
                    KillableType::MONSTER)
                {
                    // account for monster killed outside combat
                    numMonstersConscious--;
                    cout << numMonstersConscious << " monsters conscious" << endl;
                    if (numMonstersConscious <= 0) 
                    {
                        stillInCombat = false;
                    }
                }
                break;
            }
            case 4:
            {
                // restore health
                cout << "Which participant to heal? " << endl;
                // print list of participants one could heal
                for (int p = 0; p < sortedParticipants.size(); p++)
                {
                    cout << p+1 << ".) " << sortedParticipants.at(p).itsEntity->creatureName
                         <<      " - "   << sortedParticipants.at(p).itsEntity->healthRemaining << endl;
                }
                int healChoice = 0;
                bool validChoice = false;
                string healChoiceString;
                while (!validChoice)
                {
                    cin >> healChoiceString;
                    try
                    {
                        healChoice = stoi(healChoiceString);
                    } catch (...) 
                    {
                        cout << "Invalid choice, try again..." << endl;
                    }
                    if ((0 < healChoice) && (healChoice < sortedParticipants.size()))
                    {
                        validChoice = true;
                    }
                }
                healChoice--;
                cout << "Healing participant " << sortedParticipants.at(healChoice).itsEntity->creatureName << ". " << endl;

                int healValue = 0;
                bool validValue = false;
                string healValueString;
                while (!validValue) 
                {
                    cout << "By how much" << endl;
                    cin  >> healValueString;
                    try
                    {
                        healValue = stoi(healValueString);
                    }
                    catch(...)
                    {
                        cout << "Invalid number." << endl;
                    }
                    // validity check
                    if ((0 < healValue) && (healValue <= sortedParticipants.at(healChoice).itsEntity->maxHealth))
                    {
                        validValue = true;
                        // assign up to max health
                        sortedParticipants.at(healChoice).itsEntity->healthRemaining += healValue;
                        cout << "Participant health is now " << sortedParticipants.at(healChoice).itsEntity->healthRemaining << endl;
                    }
                    else 
                    {
                        cout << "Cannot heal participant by that amount." << endl;
                    }
                
                }
                break;
            }
            case 5:
            {
                // add player logic
                int numPlayersInCombat = 0;
                vector<Player*> playersInCombat;
                playersInCombat.reserve(10);
                
                // count and keep track of players already in combat
                for (int t = 0; t < sortedParticipants.size(); t++)
                {
                    if (sortedParticipants.at(t).itsEntity->natureOfTheBeast == KillableType::PLAYER)
                    {
                        numPlayersInCombat += 1;
                        playersInCombat.push_back(reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity));
                        cout << "Found player " << reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->playerName << endl;
                    }
                }
                if (numPlayersInCombat == globalPlayerNum)
                {
                    // no players left to enter combat
                    cout << "All available players are in combat." << endl;
                }
                else
                {
                    cout << "Which player to add?" << endl;
                    for (int p1 = 0; p1 < globalPlayerNum; p1++)
                    {
                        // check for players in global list - are they in current participant list?
                        bool playerFound = false;
                        int theIndex = players.at(p1).playerID; // playerID to check for presence
                        for (int p2 = 0; p2 < numPlayersInCombat; p2++)
                        {
                            // check global index against those in combat already
                            if (theIndex == playersInCombat.at(p2)->playerID)
                            {
                                playerFound = true;
                            }
                        }
                        // if the global player is not found in current participants, display them as a choice
                        if ((!playerFound) && (players.at(theIndex-1).playerID != 0))
                        {
                            cout << theIndex << ".) " << players.at(theIndex-1).creatureName << endl;
                        }
                    }
                    int playerChoice = 0;
                    bool validChoice = false;
                    string theChoice;
                    while (!validChoice)
                    {
                        cin >> theChoice;
                        try
                        {
                            playerChoice = stoi(theChoice);
                        }
                        catch(...)
                        {
                            cout << "Invalid entry; try again." << endl;
                        }
                        // validity check
                        if ((playerChoice > 0) && (playerChoice < players.size()+1))
                        {
                            bool playerAlreadyInCombat = false;
                            for (int p3 = 0; p3 < sortedParticipants.size(); p3++)
                            {
                                if (sortedParticipants.at(p3).itsEntity->natureOfTheBeast == KillableType::PLAYER)
                                {
                                    if (reinterpret_cast<Player*>(sortedParticipants.at(p3).itsEntity)->playerID == playerChoice)
                                    {
                                        // user entered index for player already in combat
                                        playerAlreadyInCombat = true;
                                    }
                                }
                            }
                            if (!playerAlreadyInCombat)
                            {
                                validChoice = true;
                                Participant incomingParticipant = new Participant();
                                // copy global player for participant entity
                                incomingParticipant.itsEntity = &players.at(playerChoice-1);
                                // auto assign initiative
                                // *** TODO *** input player initiative // 
                                incomingParticipant.itsInitiative = itsDiceRoller.rollDice(20);
                                // add participant
                                sortedParticipants.push_back(incomingParticipant);
                                // confirm
                                cout << "Added player " << players.at(playerChoice-1).playerName << endl;
                                cout << "Re-sorting participants with new addition..." << endl;
                                // re-arrange for new participant since not mid-turn
                                sortParticipants(sortedParticipants);
                                cout << "Assumed success." << endl;
                            }
                        }
                        
                    }
                }
                
                break;
            }
            case 6:
            {
                // have one participant attack a second one
                // get Attacker
                cout << "Who is attacking?" << endl;
                for (int s=0; s < sortedParticipants.size(); s++)
                {
                    cout << s+1 << ".) ";
                    cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                }
                bool validAttacker = false;
                string attackerString;
                int attackerIndex = 0;
                Killable* theAttacker;
                Player* playerAttacker = 0;
                Monster* monsterAttacker = 0;

                while (!validAttacker)
                {
                    cin >> attackerString;
                    try 
                    {
                        attackerIndex = stoi(attackerString);
                    }
                    catch (...)
                    {
                        cout << "Valid integer please." << endl;
                    }
                    if ((0 < attackerIndex) && (attackerIndex <= sortedParticipants.size()))
                    {
                        validAttacker = true;
                        attackerIndex--;
                    }
                    else if (attackerIndex < 0) 
                    {
                        cout << "Positive integer is needed." << endl;
                    }
                    else if (sortedParticipants.size() < attackerIndex) 
                    {
                        cout << "Index out of bounds. Try again." << endl;
                    }
                }
                theAttacker = sortedParticipants.at(attackerIndex).itsEntity;
                cout << "Valid attacker " << theAttacker->creatureName << " chosen." << endl;

                if (theAttacker->natureOfTheBeast == KillableType::PLAYER)
                {
                    playerAttacker = reinterpret_cast<Player*>(sortedParticipants.at(attackerIndex).itsEntity);
                }
                else if (theAttacker->natureOfTheBeast == KillableType::MONSTER)
                {
                    monsterAttacker = reinterpret_cast<Monster*>(sortedParticipants.at(attackerIndex).itsEntity);
                }

                // get Defender
                cout << "Who is being attacked?" << endl;
                for (int s=0; s < sortedParticipants.size(); s++)
                {
                    cout << s+1 << ".) ";
                    cout << sortedParticipants.at(s).itsEntity->creatureName << endl;
                }
                bool validDefender = false;
                string defenderString;
                int defenderIndex = 0;
                Killable* theDefender;
                Player* playerDefender = 0;
                Monster* monsterDefender = 0;

                while (!validDefender)
                {
                    cin >> defenderString;
                    try 
                    {
                        defenderIndex = stoi(defenderString);
                    }
                    catch (...)
                    {
                        cout << "Valid integer please." << endl;
                    }
                    if ((0 < defenderIndex) && (defenderIndex <= sortedParticipants.size()))
                    {
                        validDefender = true;
                        defenderIndex--;
                    }
                    else if (defenderIndex < 0) 
                    {
                        cout << "Positive integer is needed." << endl;
                    }
                    else if (sortedParticipants.size() < defenderIndex) 
                    {
                        cout << "Index out of bounds. Try again." << endl;
                    }
                }

                theDefender = sortedParticipants.at(defenderIndex).itsEntity;
                cout << "Valid defender " << theDefender->creatureName << " chosen." << endl;

                // determine KillableType of attacker and defender
                KillableType attackerType = theAttacker->natureOfTheBeast;
                KillableType defenderType = theDefender->natureOfTheBeast;

                // perform attack

                // for monsters...
                if (attackerType == KillableType::MONSTER)
                {
                    if (monsterAttacker != 0) 
                    {
                        int attackRoll = 0;
                        int chosenAttack = monsterAttacker->attackRoll(attackRoll);
                                            
                        cout << "Attack roll result was a " << attackRoll << endl;

                        if (attackRoll == 0)
                        {
                            // critical failure - no damage dealt by attack; deal with accordingly
                            cout << "Critical Failure" << endl;
                        }
                        else if (attackRoll == 100)
                        {
                            // damage calculated, doubled, and dealt
                            cout << "Critical Hit!" << endl;
                            int damage = monsterAttacker->attack(chosenAttack);
                            cout << "Participant takes " << 2*damage << " damage." << endl;

                            theDefender->healthRemaining -= 2*damage;
                            // check for death
                            if (theDefender->healthRemaining <= 0)
                            {
                                cout << "Participant has been killed." << endl;
                                if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                {
                                    numMonstersConscious -= 1;
                                }                                                
                            }
                        }
                        else if (attackRoll > theDefender->armorClass)
                        {
                            // damage calculated and dealt
                            int damage = reinterpret_cast<Monster*>(theAttacker)->attack(chosenAttack);
                            cout << "Player takes " << damage << " damage." << endl;
                            theDefender->healthRemaining -= damage;

                            // check for death
                            if (theDefender->healthRemaining <= 0)
                            {
                                cout << "Participant has been killed." << endl;
                                if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                {
                                    numMonstersConscious -= 1;
                                }
                            }
                        }
                        else
                        {
                            cout << "Monster's attack missed!" << endl;
                        }
                    }
                    else 
                    {
                        cout << "Unable to cast attacker as MONSTER type." << endl;
                    }
                } 
                else if (attackerType == KillableType::PLAYER)
                {
                    if (playerAttacker != 0)
                    {
                        int playerAttackRoll = 0;
                        bool validAttackRoll = false;
                        string attackRollString;

                        // get player attack roll
                        while (!validAttackRoll)
                        {
                            cout << "What is " << theAttacker->creatureName << "'s attack roll?" << endl;
                            cin  >> attackRollString;
                            try
                            {
                                playerAttackRoll = stoi(attackRollString);
                            }
                            catch(...)
                            {
                                cout << "Valid integer please!" << endl;
                            }
                            if (playerAttackRoll > 0)
                            {
                                // can't be negative
                                validAttackRoll = true;
                            }
                        }
                            // see if the attack hits
                            if (playerAttackRoll > theDefender->armorClass)
                            {   
                                int savingThrowNeeded;
                                bool validSaveThrowNeededCheck = false;
                                string savingThrowNeededString;

                                // see if monster needs to make a saving throw
                                while (!validSaveThrowNeededCheck)
                                {
                                    cout << "Is a saving throw needed? (enter 0 for no, 1 for yes)" << endl;
                                    cin  >> savingThrowNeededString;
                                    try
                                    {
                                        savingThrowNeeded = stoi(savingThrowNeededString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Enter a '0', or a '1'" << endl;
                                    }
                                    if (savingThrowNeeded == 0) 
                                    {
                                        validSaveThrowNeededCheck = true;
                                        cout << "No saving throw needed" << endl;
                                    } 
                                    else if (savingThrowNeeded == 1) 
                                    {
                                        validSaveThrowNeededCheck = true;
                                        // if a saving throw is necessary, find out which kind

                                        int saveType = 0;
                                        bool validSaveType = false;
                                        string saveTypeString;
                                        int monsterSaveThrow = 0;
                                        while (!validSaveType)
                                        {
                                            cout << "Which type of save is needed? " << endl;
                                            cout << "1.) Strength"     << endl;
                                            cout << "2.) Dexterity"    << endl;
                                            cout << "3.) Constitution" << endl; 
                                            cout << "4.) Intelligence" << endl;
                                            cout << "5.) Wisdom"       << endl;
                                            cout << "6.) Charisma"     << endl;
                                            cin >> saveTypeString;
                                            try
                                            {
                                                saveType = stoi(saveTypeString);
                                            }
                                            catch(...)
                                            {
                                                cout << "Please select a valid option." << endl;
                                            }
                                            // validity check
                                            if ((0 < saveType) && (saveType <= 6) &&
                                                (theDefender->natureOfTheBeast == KillableType::MONSTER))
                                            {
                                                // have the monster make the save
                                                Monster* theMonster = 0;
                                                theMonster = reinterpret_cast<Monster*>(theDefender);
                                                if (theMonster != 0)
                                                {
                                                    monsterSaveThrow = theMonster->makeSavingThrow(saveType);
                                                    validSaveType = true;
                                                    cout << "Monster rolled " << monsterSaveThrow << " as its save." << endl;
                                                }
                                                else 
                                                {
                                                    validSaveType = true;
                                                    cout << "Failed to cast target as Monster." << endl;
                                                }
                                            }
                                            else if ((0 < saveType) && (saveType <= 6))
                                            {
                                                validSaveType = true;
                                                cout << "Determine effect of saving throw between players..." << endl;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        cout << "Invalid input detected. Moving on to attack roll." << endl;
                                    }  
                                }
                                cout << "Find out how they're attacking, and HOW MUCH DAMAGE?" << endl;

                                int damageDealt = 0;
                                bool validDamage = false;
                                string damageAsString;
                                while (!validDamage)
                                {
                                    cout << "How much damage is being dealt?" << endl;
                                    cin  >> damageAsString;
                                    try
                                    {
                                        damageDealt = stoi(damageAsString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Valid integer please!" << endl;
                                    }
                                    if (damageDealt > 0)
                                    {
                                        validDamage = true;
                                        cout << "Dealing " << damageDealt << " damage to participant." << endl;

                                        // deal the damage
                                        theDefender->healthRemaining -= damageDealt;
                                        // check for death
                                        if (theDefender->healthRemaining <= 0)
                                        {
                                            cout << "Participant has been killed." << endl;
                                            if (theDefender->natureOfTheBeast == KillableType::MONSTER)
                                            {
                                                numMonstersConscious--;
                                                cout << numMonstersConscious << " monsters conscious" << endl;
                                                if (numMonstersConscious <= 0) 
                                                {
                                                    stillInCombat = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cout << "Player attack missed." << endl;
                            } 
                    }
                    else 
                    {
                        cout << "Unable to cast attacker to PLAYER type." << endl;
                    }
                }
                break;
            }
            case 7:
            {
                // end encounter spontaneously
                cout << "Ending combat... " << endl;
                stillInCombat = false;
                break;
            }
            default:
            {
                cout << "Invalid choice detected. Let's try again..." << endl;
                break;
            }
        }
    }
}

void Encounter::getMonsterInitiative(ParticipantList& participants)
{
    // cycle through participants
    for (int i = 0; i < participants.size(); i++)
    {
        if (participants.at(i).itsEntity->natureOfTheBeast == KillableType::MONSTER)
        {
            // player initiative is entered manually. if monster, roll for it.
            participants.at(i).itsInitiative = participants.at(i).itsEntity->itsDiceRoller.rollDice(20);
            if (participants.at(i).itsInitiative == 20)
            {
                // crit success (to overrule modifiers of players)
                participants.at(i).itsInitiative = 100;
            }
            if (participants.at(i).itsInitiative == 1)
            {
                // guarantee lowest placement
                participants.at(i).itsInitiative = 0;
            }
        }
    }   
}

Monster* Encounter::getRandomMonster()
{
    Monster* theMonster = 0;
    int theRandomIndex = 0;
    int theRandomIndexStart = itsDiceRoller.rollDice(100);
    // random int between zero and representative last value; all monsters possible
    theRandomIndex = static_cast<int>(theRandomIndexStart % (MonstersAvailable::LAST_VALUE));
    cout << "Rolled monster index " << theRandomIndex << endl;
    // get monster
    theMonster = itsLibrary.createMonster(theRandomIndex);
    if (theMonster != 0)
    {
        cout << "Successfully created monster." << endl;
    }

    return theMonster;
}

Monster* Encounter::getMonsterFromLibrary()
{
    Monster* theMonster = 0;
    int  index = 0;
    bool validIndex = false;
    string indexString;
    // display to the user all monsters available
    itsLibrary.printMonsterList();
    while (!validIndex)
    {
        cin >> indexString;
        try
        {
            index = stoi(indexString);
        }
        catch(...)
        {
            cout << "Invalid index; try again..." << endl;
        }
        if ((0 <= index) && (index <= MonstersAvailable::LAST_VALUE))
        {
            // if valid input, try to create monster
            validIndex = true;
            cout << "Creating monster..." << endl;
            theMonster = itsLibrary.createMonster(index);
            if (theMonster == 0)
            {
                cout << "Failed to create monster." << endl;
            }
        } 
        else 
        {
            cout << "Unable to validate index" << endl;
        }
        
    }

    return theMonster;
}

void Encounter::sortParticipants(ParticipantList& participants)
{
    int numParticipants = participants.size();
    int positionsSorted = 0;

    // newly sorted participant array
    ParticipantList* sortedParticipants = new ParticipantList();
    sortedParticipants->reserve(participants.size());
    // clone incoming participants for ease of notation and to prevent errors erasing elements
    ParticipantList  oldParticipantList(participants);

    // be sure to sort ALL current participants
    while (positionsSorted < numParticipants)
    {
        int highestInitiative = 0;
        int positionHighest = 0;
        for (int i = 0; i < oldParticipantList.size(); i++) 
        {
            if (oldParticipantList.at(i).itsInitiative >
                highestInitiative)
            {
                // store incrementally highest initiative participants
                highestInitiative = oldParticipantList.at(i).itsInitiative;
                positionHighest = i;
            }
        }
        positionsSorted += 1;
        // add highest participant
        sortedParticipants->push_back(oldParticipantList.at(positionHighest)); 
        cout << "Added participant " << oldParticipantList.at(positionHighest).itsEntity->creatureName
             << " to sorted list."   << endl;
        // remove sorted participant from list of consideration
        oldParticipantList.erase(oldParticipantList.begin()+positionHighest);
    }

    // reassign participant list to the newly sorted one
    participants = *sortedParticipants;

}

int Encounter::displayCombatMenu()
{
    int choice = 0;
    bool validChoice = false;
    string choiceAsString;

    while (!validChoice) 
    {
        cout << "What to do now?"                 << endl;
        cout << "1.) Display Participant Info: "  << endl;
        cout << "2.) Start Turn: "                << endl;
        cout << "3.) God Kill Participant: "      << endl;
        cout << "4.) Heal Participant: "          << endl;
        cout << "5.) Add Player to encounter:"    << endl;
        cout << "6.) Initiate 3rd party attack: " << endl;
        cout << "7.) Disengage Combat: "          << endl;

        cin >> choiceAsString;
        try 
        {
            choice = stoi(choiceAsString);
        }
        catch (...) 
        {
            cout << "Try again." << endl;
        }
        if ((0 < choice) && (choice < 8))
        {
            validChoice = true;
        }
    }
    return choice;
}

Participant::Participant()
{
    // placeholder
}

Participant::Participant(Participant* original)
{
    itsEntity = original->itsEntity;
    itsInitiative = original->itsInitiative;
}

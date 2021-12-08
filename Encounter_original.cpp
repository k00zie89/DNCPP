#include "Encounter.h"

Encounter::Encounter(Environment theEnvironment)
{
    try 
    {
        
        this->environment = theEnvironment;
        this->itsParticipants.reserve(20);
        cout << " participants vector can hold: " << this->itsParticipants.capacity() << endl;
    } 
    catch (...) 
    {
        cout << "Something went wrong while creating encounter..." << endl;
        throw;
    }
}

void Encounter::startEncounter(ParticipantList& theParticipants, PlayerList& players,Environment env, int globalPlayerNum)
{
    int choiceAsNum = 0;
    int innerChoiceAsNum = 0;
    bool validChoice = false;
    bool validInnerChoice = false;
    string yesOrNo;
    string choiceAsString;
    string innerChoiceAsString;
    vector<Environment> theEnvironment;
    theEnvironment.reserve(5);

     bool stillInCombat = true;

    sortedParticipants.reserve(20);

    itsLibrary = MonsterLibrary();

    cout << "Party consists of " << theParticipants.size() << " players." << endl;

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
            throw;
        }
        if (choiceAsNum != 0)
        {
            switch (choiceAsNum) 
            {
                case 1:
                {
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
                            throw;
                            break;
                        }
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
                                        newParticipant.itsEntity = newMonster;
                                        tempParticipants->push_back(newParticipant);
                                        cout << "Added " << newMonster->creatureName << " to list." << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                break;
                }
                case 2:
                {
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
                            throw;
                            break;
                        }
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
                                        tempParticipants->push_back(newParticipant);
                                        cout << "Added " << newMonster->creatureName << " to list." << endl;
                                    }
                                }
                            }
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

    int numParticipants = tempParticipants->size();
    int positionsSorted = 0;
    
    cout << "There are " << numParticipants << " after adding monsters" << endl;

    this->getMonsterInitiative(*tempParticipants);

    while (positionsSorted < numParticipants)
    {
        int highestInitiative = 0;
        int positionHighest = 0;
        for (int i = 0; i < tempParticipants->size(); i++) 
        {
            if (tempParticipants->at(i).itsInitiative >
                highestInitiative)
            {
                highestInitiative = tempParticipants->at(i).itsInitiative;
                positionHighest = i;
            }
        }
        positionsSorted += 1;
        sortedParticipants.push_back(tempParticipants->at(positionHighest)); 
        tempParticipants->erase(tempParticipants->begin()+positionHighest);
        cout << "added participant to sorted list" << endl;
    }

    int numMonstersConscious = 0;
    for (int p = 0; p < sortedParticipants.size(); p++)
    {
        if (sortedParticipants.at(p).itsEntity->natureOfTheBeast ==
            KillableType::MONSTER) 
        {
            numMonstersConscious++;
        }
    } 

    cout << numMonstersConscious << " monsters conscious" << endl;
    
    while (stillInCombat) 
    {
        // do combat until over
        int thingToDo = displayCombatMenu();
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
                    cout << " ----- ";
                    cout << sortedParticipants.at(p).itsEntity->creatureName << " - ";
                    cout << " Armor Class: ";
                    cout << sortedParticipants.at(p).itsEntity->armorClass;
                    cout << " HP: ";
                    cout << sortedParticipants.at(p).itsEntity->healthRemaining;
                    cout << " Speed: ";
                    cout << sortedParticipants.at(p).itsEntity->moveSpeed 
                         << " ----- " << endl;
                    for (int a = 0; a < sortedParticipants.at(p).itsEntity->abilities.size();
                         a++)
                    {
                        cout << sortedParticipants.at(p).itsEntity->abilities.at(a) << " " << endl;
                    }
                    cout << "Has initiative: ";
                    cout << sortedParticipants.at(p).itsInitiative << endl;
                }
                break;
            }
            case 2:
            {
                // cycle through list of remaining participants once
                // allowing them to ...do...their thing?
                cout << "Initiating the round..." << endl;
                // seperate players from enemies
                ParticipantList* currentMonsters = new ParticipantList();
                ParticipantList* currentPlayers  = new ParticipantList();
                ParticipantList* currentNPCs     = new ParticipantList();

                 currentPlayers->reserve(sortedParticipants.capacity());
                currentMonsters->reserve(sortedParticipants.capacity());
                    currentNPCs->reserve(sortedParticipants.capacity());

                for (int v = 0; v < sortedParticipants.size(); v++)
                {
                    if (sortedParticipants.at(v).itsEntity->natureOfTheBeast == 
                        KillableType::PLAYER)
                    {
                        currentPlayers->push_back(sortedParticipants.at(v));
                    }
                    else if (sortedParticipants.at(v).itsEntity->natureOfTheBeast ==
                             KillableType::MONSTER)
                    {
                        currentMonsters->push_back(sortedParticipants.at(v));
                    }
                    else
                    {
                        // TODO NPCs not yet supported
                        currentNPCs->push_back(sortedParticipants.at(v));
                    }
                }
                cout << "There are " << currentPlayers->size() << " players" << endl;
                cout << " and " << currentMonsters->size() << " monsters" << endl;

                Dice* participantChooser = new Dice(100);
                string pauseString;

                for (int t = 0; t < sortedParticipants.size(); t++)
                {
                    if (stillInCombat)
                    {
                        if (sortedParticipants.at(t).itsEntity->natureOfTheBeast ==
                            KillableType::MONSTER)
                        {
                            if (sortedParticipants.at(t).itsEntity->healthRemaining > 0
                                && stillInCombat)
                            {
                                cout << "Monster - " << sortedParticipants.at(t).itsEntity->creatureName
                                    << "'s turn..." << endl;

                                int monsterChoice = 0;
                                string monsterChoiceString;

                                bool monsterFinished = false;
                                while (!monsterFinished)
                                {
                                    cout << "What shall the monster do?" << endl;
                                    cout << "1.) Attack player" << endl;
                                    cout << "2.) Finish turn" << endl;
                                    cout << "3.) DM CONTROL - Print Monsters w/ Health and AC" << endl;
                                    cout << "4.) DM CONTROL - Heal Player" << endl;
                                    cout << "5.) DM CONTROL - Harm Participant" << endl;
                                    cout << "6.) DM CONTROL - Add New Monster From Library" << endl;

                                    cin  >> monsterChoiceString;
                                    try
                                    {
                                        monsterChoice = stoi(monsterChoiceString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Invalid selection." << endl;
                                        throw;
                                    }
                                    switch (monsterChoice)
                                    {
                                        case 1:
                                        {
                                            cout << "Who shall he attack? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;
                                            while (validChoiceReceived == false) 
                                            {
                                                    for (int z = 0; z < currentPlayers->size(); z++)
                                                    {
                                                        cout << z+1 << ".) " << currentPlayers->at(z).itsEntity->creatureName 
                                                            << " - " << currentPlayers->at(z).itsEntity->healthRemaining << endl;

                                                    }
                                                    cout << currentPlayers->size() + 1 << ".) Random player" << endl;
                                                    cin  >> theChoiceReceived;
                                                    try
                                                    {
                                                        theChoice = stoi(theChoiceReceived);
                                                    }
                                                    catch(...)
                                                    {
                                                        cout << "Try again fucknuts..." << endl;
                                                        throw;
                                                    }
                                                    if ((0 < theChoice) && (theChoice <= currentPlayers->size()+1))
                                                    {
                                                        validChoiceReceived = true;
                                                    }   
                                            }
                                            int beingAttacked = 0;
                                            if ((0 < theChoice) && (theChoice <= currentPlayers->size()))
                                            {
                                                cout << "Setting value directly from choice." << endl;
                                                beingAttacked = theChoice;
                                            } 
                                            else if (theChoice == currentPlayers->size()+1)
                                            {
                                                cout << "Getting random value." << endl;
                                                beingAttacked = participantChooser->roll() % currentPlayers->size() + 1;
                                            }
                                            else 
                                            {
                                                cout << "Invalid choice. Attacking first player in list." << endl;
                                                beingAttacked = 1;
                                            }
                                            beingAttacked -= 1;
                                            cout << "Player number " << beingAttacked << " has been selected." << endl;
                                            cout << "Monster attacks player " << 
                                                currentPlayers->at(beingAttacked).itsEntity->creatureName << endl;
                                            int attackRoll = 0;
                                            int chosenAttack = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->attackRoll(attackRoll);
                                            cout << "Attack roll result was a " << attackRoll << endl;
                                            if (attackRoll == 0)
                                            {
                                                cout << "Critical Failure" << endl;
                                            }
                                            else if (attackRoll == 100)
                                            {
                                                cout << "Critical Hit!" << endl;
                                                int damage = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->
                                                                                        attack(chosenAttack);
                                                cout << "Player takes " << 2*damage << " damage." << endl;
                                                currentPlayers->at(beingAttacked).itsEntity->healthRemaining -= 2*damage;
                                                if (currentPlayers->at(beingAttacked).itsEntity->healthRemaining <= 0)
                                                {
                                                    cout << "Player has been killed." << endl;
                                                }
                                            }
                                            else if (attackRoll > currentPlayers->at(beingAttacked).itsEntity->armorClass)
                                            {
                                                int damage = reinterpret_cast<Monster*>(sortedParticipants.at(t).itsEntity)->
                                                                                        attack(chosenAttack);
                                                cout << "Player takes " << damage << " damage." << endl;
                                                currentPlayers->at(beingAttacked).itsEntity->healthRemaining -= damage;
                                                if (currentPlayers->at(beingAttacked).itsEntity->healthRemaining <= 0)
                                                {
                                                    cout << "Player has been killed." << endl;
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
                                            monsterFinished = true;
                                            cout << "Moving on..." << endl;
                                            break;
                                        }
                                        case 3:
                                        {
                                            cout << "Monsters remaining: " << endl;
                                            for (int m = 0; m < currentMonsters->size(); m++)
                                            {
                                                cout << m+1 << ".) "     << currentMonsters->at(m).itsEntity->creatureName
                                                            << " - HP: " << currentMonsters->at(m).itsEntity->healthRemaining
                                                            << " - AC: " << currentMonsters->at(m).itsEntity->armorClass
                                                            << endl;
                                            }
                                            break;
                                        }
                                        case 4:
                                        {
                                            int thePlayer = -1;
                                            bool validPlayer = false;
                                            string thePlayerString;
                                            while (validPlayer == false)
                                            {
                                                cout << "Which player to heal?" << endl;
                                                for (int p = 0; p < currentPlayers->size(); p++)
                                                {
                                                    cout << p+1 << ".) " << currentPlayers->at(p).itsEntity->creatureName 
                                                                << " - " << currentPlayers->at(p).itsEntity->healthRemaining 
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
                                                    throw;
                                                }
                                                if ((0 < thePlayer) && (thePlayer <= currentPlayers->size()))
                                                {
                                                    validPlayer = true;
                                                    thePlayer--;
                                                    cout << "Healing player " << currentPlayers->at(thePlayer).itsEntity->creatureName << endl;
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
                                                            throw;
                                                        }
                                                        if (0 < healValue)
                                                        {
                                                            validValue = true;
                                                            currentPlayers->at(thePlayer).itsEntity->healthRemaining += healValue;
                                                            if (currentPlayers->at(thePlayer).itsEntity->healthRemaining >
                                                                currentPlayers->at(thePlayer).itsEntity->maxHealth)
                                                            {
                                                                currentPlayers->at(thePlayer).itsEntity->healthRemaining =
                                                                currentPlayers->at(thePlayer).itsEntity->maxHealth;
                                                            }
                                                        }
                                                        else 
                                                        {
                                                            cout << "Cannot heal player by negative amount." << endl;
                                                        }
                                                    }
                                                    cout << "Player health is now " << currentPlayers->at(thePlayer).itsEntity->healthRemaining << endl;
                                                }
                                                
                                            }
                                            
                                                
                                            break;
                                        }
                                        case 5:
                                        {
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
                                                    throw;
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
                                                    throw;
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
                                                    newParticipant.itsInitiative = 10;
                                                    sortedParticipants.push_back(newParticipant);
                                                    currentMonsters->push_back(newParticipant);
                                                    cout << "Added " << newMonster->creatureName << " to list." << endl;
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
                            if (sortedParticipants.at(t).itsEntity->healthRemaining > 0
                                && stillInCombat)
                            {
                                // get player choice, do the thing
                                cout << "Player " << sortedParticipants.at(t).itsEntity->creatureName 
                                    << "'s turn..." << endl;

                                int playerChoice = 0;
                                string playerChoiceString;

                                bool playerFinished = false;
                                while (!playerFinished)
                                {
                                    cout << "What shall the player do?" << endl;
                                    cout << "1.) Attack monster" << endl;
                                    cout << "2.) Finish turn" << endl;
                                    cout << "3.) DM CONTROL - Print Monsters w/ Health and AC" << endl;
                                    cout << "4.) DM CONTROL - Heal Player" << endl;
                                    cout << "5.) DM CONTROL - Harm Participant" << endl;
                                    cout << "6.) DM CONTROL - Add New Monster From Library" << endl;

                                    cin  >> playerChoiceString;
                                    try
                                    {
                                        playerChoice = stoi(playerChoiceString);
                                    }
                                    catch(...)
                                    {
                                        cout << "Invalid selection." << endl;
                                        throw;
                                    }
                                    switch (playerChoice)
                                    {
                                        case 1:
                                        {
                                            cout << "Who shall the player attack? " << endl;
                                            bool validChoiceReceived = false;
                                            int  theChoice = 0;
                                            string theChoiceReceived;
                                            while (validChoiceReceived == false) 
                                            {
                                                for (int z = 0; z < currentMonsters->size(); z++)
                                                {
                                                    cout << z+1 << ".) " << currentMonsters->at(z).itsEntity->creatureName 
                                                        << " - HP: " << currentMonsters->at(z).itsEntity->healthRemaining << endl;
                                                }
                                                cout << currentMonsters->size() + 1 << ".) Random monster" << endl;
                                                cin  >> theChoiceReceived;
                                                try
                                                {
                                                    theChoice = stoi(theChoiceReceived);
                                                }
                                                catch(...)
                                                {
                                                    cout << "Try again fucknuts..." << endl;
                                                    throw;
                                                }
                                                if ((0 < theChoice) && (theChoice <= currentMonsters->size()+1))
                                                {
                                                    validChoiceReceived = true;
                                                }   
                                            }
                                            int beingAttacked = 0;
                                            if ((0 < theChoice) && (theChoice <= currentMonsters->size()))
                                            {
                                                cout << "Setting the choice directly." << endl;
                                                beingAttacked = theChoice;
                                            } 
                                            else if (theChoice == currentMonsters->size()+1)
                                            {
                                                cout << "Choosing random monster." << endl;
                                                beingAttacked = participantChooser->roll() % currentMonsters->size() + 1;
                                            }
                                            else
                                            {
                                                cout << "Invalid selection detected. Choosing first available monster." << endl;
                                                beingAttacked = 1;
                                            }
                                            beingAttacked--;
                                            cout << "Monster chosen is number " << beingAttacked << endl;

                                            int playerAttackRoll = 0;
                                            bool validAttackRoll = false;
                                            string attackRollString;
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
                                                    throw;
                                                }
                                                if (playerAttackRoll > 0)
                                                {
                                                    validAttackRoll = true;
                                                }
                                                if (playerAttackRoll > currentMonsters->at(beingAttacked).itsEntity->armorClass)
                                                {   
                                                    int savingThrowNeeded;
                                                    bool validSaveThrowNeededCheck = false;
                                                    string savingThrowNeededString;
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
                                                            throw;
                                                        }
                                                        if (savingThrowNeeded == 0) 
                                                        {
                                                            validSaveThrowNeededCheck = true;
                                                            cout << "No saving throw needed" << endl;
                                                        } 
                                                        else if (savingThrowNeeded == 1) 
                                                        {
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
                                                                    throw;
                                                                }
                                                                if ((0 < saveType) && (saveType <= 6))
                                                                {
                                                                    monsterSaveThrow = reinterpret_cast<Monster*>(currentMonsters->at(beingAttacked).itsEntity)->
                                                                    makeSavingThrow(saveType);
                                                                    validSaveType = true;
                                                                }
                                                            }
                                                            cout << "Monster rolled " << monsterSaveThrow << " as its save." << endl;
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
                                                            throw;
                                                        }
                                                        if (damageDealt > 0)
                                                        {
                                                            validDamage = true;
                                                            cout << "Dealing " << damageDealt << " damage to monster." << endl;
                                                            currentMonsters->at(beingAttacked).itsEntity->healthRemaining -= damageDealt;
                                                            if (currentMonsters->at(beingAttacked).itsEntity->healthRemaining <= 0)
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
                                            playerFinished = true;
                                            cout << "Moving on..." << endl;
                                            break;
                                        }
                                        case 3:
                                        {
                                            cout << "Monsters remaining: " << endl;
                                            for (int m = 0; m < currentMonsters->size(); m++)
                                            {
                                                cout << m+1 << ".) "     << currentMonsters->at(m).itsEntity->creatureName
                                                            << " - HP: " << currentMonsters->at(m).itsEntity->healthRemaining
                                                            << " - AC: " << currentMonsters->at(m).itsEntity->armorClass
                                                            << endl;
                                            }
                                            break;
                                        }
                                        case 4:
                                        {
                                            int thePlayer = -1;
                                            bool validPlayer = false;
                                            string thePlayerString;
                                            while (validPlayer == false)
                                            {
                                                cout << "Which player to heal?" << endl;
                                                for (int p = 0; p < currentPlayers->size(); p++)
                                                {
                                                    cout << p+1 << ".) " << currentPlayers->at(p).itsEntity->creatureName 
                                                                << " - " << currentPlayers->at(p).itsEntity->healthRemaining 
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
                                                    throw;
                                                }
                                                if ((0 < thePlayer) && (thePlayer <= currentPlayers->size()))
                                                {
                                                    validPlayer = true;
                                                    thePlayer--;
                                                    cout << "Healing player " << currentPlayers->at(thePlayer).itsEntity->creatureName << endl;
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
                                                            throw;
                                                        }
                                                        if (0 < healValue)
                                                        {
                                                            validValue = true;
                                                            currentPlayers->at(thePlayer).itsEntity->healthRemaining += healValue;
                                                            if (currentPlayers->at(thePlayer).itsEntity->healthRemaining >
                                                                currentPlayers->at(thePlayer).itsEntity->maxHealth)
                                                            {
                                                                currentPlayers->at(thePlayer).itsEntity->healthRemaining =
                                                                currentPlayers->at(thePlayer).itsEntity->maxHealth;
                                                            }
                                                        }
                                                        else 
                                                        {
                                                            cout << "Cannot heal player by negative amount." << endl;
                                                        }
                                                    }
                                                    cout << "Player health is now " << currentPlayers->at(thePlayer).itsEntity->healthRemaining << endl;
                                                }
                                                
                                            }
                                            
                                                
                                            break;
                                        }
                                        case 5:
                                        {
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
                                                    throw;
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
                                                    throw;
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
                                                    newParticipant.itsInitiative = 10;
                                                    sortedParticipants.push_back(newParticipant);
                                                    currentMonsters->push_back(newParticipant);
                                                    cout << "Added " << newMonster->creatureName << " to list." << endl;
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
                                        throw;
                                    }
                                    if (saveResponse == 0)
                                    {
                                        cout << "Registering player death save failure...";
                                        reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesFailed += 1;
                                        cout << "DONE." << endl;
                                        validSaveResponse = true;
                                        if (reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesFailed == 3)
                                        {
                                            cout << "Player is DEAD. Dearest condolences to you departed comrade's real-life representative." << endl;
                                        }
                                    }
                                    else if (saveResponse == 1)
                                    {
                                        cout << "Registering player death save success...";
                                        reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed += 1;
                                        cout << "DONE." << endl;
                                        validSaveResponse = true;
                                        if (reinterpret_cast<Player*>(sortedParticipants.at(t).itsEntity)->deathSavesPassed == 3)
                                        {
                                            cout << "Player has been stabilized. Recovering health..." << endl;
                                            sortedParticipants.at(t).itsEntity->healthRemaining = 
                                            sortedParticipants.at(t).itsEntity->itsDiceRoller.rollDice(6);
                                            cout << "Player now has  " << sortedParticipants.at(t).itsEntity->healthRemaining << " HP." << endl;
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
                        throw;
                    }
                    if (!(choice <= 0) && choice <= sortedParticipants.size()) 
                    {
                        validChoice = true;
                    }
                }
                cout << "Killing Participant " << choice << ". " << endl;
                    sortedParticipants.at(choice-1).itsEntity->healthRemaining = -1;
                if (sortedParticipants.at(choice-1).itsEntity->natureOfTheBeast ==
                    KillableType::MONSTER)
                {
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
                cout << "Which participant to heal? " << endl;
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
                        throw;
                    }
                    if ((0 < healChoice) && (healChoice < sortedParticipants.size()))
                    {
                        validChoice = true;
                    }
                }
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
                        throw;
                    }
                    if ((0 < healValue) && (healValue <= sortedParticipants.at(healChoice-1).itsEntity->maxHealth))
                    {
                        validValue = true;
                        sortedParticipants.at(healChoice-1).itsEntity->healthRemaining += healValue;
                        if (sortedParticipants.at(healChoice-1).itsEntity->healthRemaining >
                            sortedParticipants.at(healChoice-1).itsEntity->maxHealth)
                            {
                                sortedParticipants.at(healChoice-1).itsEntity->healthRemaining =
                                sortedParticipants.at(healChoice-1).itsEntity->maxHealth;
                            }
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
                int numPlayersInCombat = 0;
                vector<Player*> playersInCombat;
                playersInCombat.reserve(10);
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
                    cout << "All available players are in combat." << endl;
                }
                else
                {
                    cout << "Which player to add?" << endl;
                    for (int p1 = 0; p1 < globalPlayerNum; p1++)
                    {
                        bool playerFound = false;
                        int theIndex = players.at(p1).playerID;
                        for (int p2 = 0; p2 < numPlayersInCombat; p2++)
                        {
                            if (theIndex == playersInCombat.at(p2)->playerID)
                            {
                                playerFound = true;
                            }
                        }
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
                            throw;
                        }
                        if ((playerChoice > 0) && (playerChoice < players.size()+1))
                        {
                            bool playerAlreadyInCombat = false;
                            for (int p3 = 0; p3 < sortedParticipants.size(); p3++)
                            {
                                if (sortedParticipants.at(p3).itsEntity->natureOfTheBeast == KillableType::PLAYER)
                                {
                                    if (reinterpret_cast<Player*>(sortedParticipants.at(p3).itsEntity)->playerID == playerChoice)
                                    {
                                        playerAlreadyInCombat = true;
                                    }
                                }
                            }
                            if (!playerAlreadyInCombat)
                            {
                                validChoice = true;
                                Participant incomingParticipant = new Participant();
                                incomingParticipant.itsEntity = &players.at(playerChoice-1);
                                incomingParticipant.itsInitiative = 100;
                                sortedParticipants.push_back(incomingParticipant);
                                cout << "Added player " << players.at(playerChoice-1).playerName << endl;
                            }
                        }
                        
                    }
                }
                
                break;
            }
            case 6:
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
    for (int i = 0; i < participants.size(); i++)
    {
        if (participants.at(i).itsEntity->natureOfTheBeast == KillableType::MONSTER)
        {
            participants.at(i).itsInitiative = participants.at(i).itsEntity->itsDiceRoller.rollDice(20);
            if (participants.at(i).itsInitiative == 20)
            {
                participants.at(i).itsInitiative = 100;
            }
            if (participants.at(i).itsInitiative == 1)
            {
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
    theRandomIndex = static_cast<int>(theRandomIndexStart % (MonstersAvailable::LAST_VALUE));
    cout << "Rolled monster index " << theRandomIndex << endl;
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
            throw;
        }
        if ((0 <= index) && (index <= MonstersAvailable::LAST_VALUE))
        {
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

int Encounter::displayCombatMenu()
{
    int choice = 0;
    bool validChoice = false;
    string choiceAsString;

    while (!validChoice) 
    {
        cout << "What to do now?"                << endl;
        cout << "1.) Display Participant Info: " << endl;
        cout << "2.) Start Turn: "               << endl;
        cout << "3.) God Kill Participant: "     << endl;
        cout << "4.) Heal Participant: "         << endl;
        cout << "5.) Add Player to encounter:"   << endl;
        cout << "6.) Disengage Combat: "         << endl;

        cin >> choiceAsString;
        try 
        {
            choice = stoi(choiceAsString);
        }
        catch (...) 
        {
            cout << "Try again." << endl;
            throw;
        }
        if ((0 < choice) && (choice < 7))
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

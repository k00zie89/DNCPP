#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "Player.h"
#include "DiceRoll.h"
#include "Encounter.h"
#include "MonsterLibrary.h"

using namespace std;

PlayerList players;

int globalNumPlayers = 0;
bool stillPlaying = true;

DiceRoller itsDiceRoller;
MonsterLibrary theMonsterLibrary;

bool displayMenu();
PlayerList getActivePlayersFromFile();
PlayerList getActivePlayersManually();
ParticipantList getParticipants(PlayerList&);

int main () 
{
    // players = getActivePlayersManually(); // backup to enter player information manually
    players = getActivePlayersFromFile();    // reads player file and creates players as needed
    while (stillPlaying) 
    {
        // main loop
        stillPlaying = displayMenu();
    }
    return 0;
}

bool displayMenu() 
{
    bool validTopChoice = false;
    string choice = " ";
    int diceType = 0;
    int choiceAsInt = 0;

    cout << endl;
    cout << "(1.) to print Player(s) info \n";
    cout << "(2.) to generate encounter \n";
    cout << "(3.) to roll a DXX \n";
    cout << "(4.) to get a long rest (HEAL ALL PLAYERS) \n";
    cout << "(5.) to heal individual player \n";
    cout << "(6.) to end the session. \n";

    while (!validTopChoice) // until valid entry registered
    {   
        cin >> choice; // get player's choice
        try
        {
            choiceAsInt = stoi(choice); // store as int
        }
        catch (...)
        {
            cout << "That's not a fucking number." << endl;
        }
        switch (choiceAsInt) 
        {
            case 1:
            {
                cout << "Printing player info:" << endl;
                
                validTopChoice = true;
                for (int i = 0; i < globalNumPlayers; i++) 
                {
                    cout <<                                                                                           endl;
                    cout << "Player "         << players.at(i).playerID        << ": " << players.at(i).playerName << endl;
                    cout << "Character: "     << players.at(i).creatureName                                        << endl;
                    cout << "Race: "          << players.at(i).race                                                << endl;
                    cout << "Class: "         << players.at(i).playerClass                                         << endl;
                    cout << "Alignment: "     << players.at(i).alignment                                           << endl;
                    cout << "MaxHealth: "     << players.at(i).maxHealth                                           << endl;
                    cout << "CurrentHealth: " << players.at(i).healthRemaining                                     << endl;
                    cout << "AC: "            << players.at(i).armorClass                                          << endl;
                    cout << "Speed: "         << players.at(i).moveSpeed                                           << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Starting a new encounter..." << endl;
                validTopChoice = true;
                // operation finds which players are involved, and what their initiative is
                // then pairs it to a Participant structure.
                ParticipantList thoseInvolved = getParticipants(players);
                if (thoseInvolved.size() != 0) // there must be at least one participant
                {
                    cout << "There are " << thoseInvolved.size() << " players." << endl;
                    int environmentResponse;
                    bool validEnvironment = false;
                    string environmentString;
                    Environment environment;
                    Encounter* thisEncounter = 0;
                    while (!validEnvironment) // until valid environment chosen...
                    {
                        cout << "Select the type of terrain: " << endl;
                        cout << "1.) for FOREST " << endl;
                        cout << "2.) for WATER  " << endl;
                        cout << "3.) for DESERT " << endl;
                        cout << "4.) for TOWN   " << endl;
                        cin >> environmentString; // get the player choice
                        try
                        {
                            environmentResponse = stoi(environmentString); // store as int
                        }
                        catch (...)
                        {
                            cout << "Invalid selection, try again..." << endl;
                        }
                        switch(environmentResponse) // register success if valid option is chosen
                        {
                            case 1:
                                environment = Environment::FOREST;
                                validEnvironment = true;
                                break;
                            case 2: 
                                environment = Environment::WATER;
                                validEnvironment = true;
                                break;
                            case 3:
                                environment = Environment::DESERT;
                                validEnvironment = true;
                                break;
                            case 4: 
                                environment = Environment::TOWN;
                                validEnvironment = true;
                                break;
                            default:
                                // shouldn't arrive here with check above...
                                break;
                        }
                    }
                        thisEncounter = new Encounter(environment);
                        if (thisEncounter != 0) 
                        {
                            // see Encounter.cpp 
                            thisEncounter->startEncounter(thoseInvolved, players, environment, globalNumPlayers);
                        }
                } 
                else 
                {
                    cout << "Invalid participant list generated, try again." << endl;
                }
                break;
            }
            case 3:
            {
                cout << "What would you like to roll, a dXX?" << endl;
                validTopChoice = true;
                string diceChoice;
                cin >> diceChoice; // get player choice
                try 
                {
                    diceType = stoi(diceChoice); // try storing as int
                    cout << "Rolling.....:     " << itsDiceRoller.rollDice(diceType) << endl; // see DiceRoll.cpp
                }
                catch (...) 
                {
                    break;
                }
                break;
            }
            case 4:
            {
                for (int i = 0; i < globalNumPlayers; i++) 
                {
                    players.at(i).healthRemaining = players.at(i).maxHealth;
                    cout << "Player " << players.at(i).creatureName << " fully recovered." << endl;
                }
                validTopChoice = true;
                break;
            }
            case 5:
            {
                cout << "Which player to heal?" << endl;
                for (int p=0; p < globalNumPlayers; p++)
                {
                    cout << "Player " << p+1 << ".) " << players.at(p).creatureName << endl;
                }
                string playerToHeal;
                cin >> playerToHeal;
                for (int i=0; i < globalNumPlayers; i++)
                {
                    if (playerToHeal.compare(to_string(players.at(i).playerID)) == 0)
                    {
                        cout << "By how much?" << endl;
                        bool validNumber = false;
                        string numberInput;
                        int amountToHeal = 0;

                        while (!validNumber)
                        {
                            cin >> numberInput;
                            try 
                            {
                                amountToHeal = stoi(numberInput);
                            } 
                            catch (...)
                            {
                                cout << "Enter a valid integer" << endl;
                            }
                            if (amountToHeal > 0) 
                            {
                                cout << "Healing " << players.at(i).creatureName << " by " << amountToHeal << endl;
                                players.at(i).healthRemaining += amountToHeal;
                                validNumber = true;
                            } 
                            else if (amountToHeal == 0) 
                            {
                                cout << "Probable invalid entry..." << endl;
                            }
                            else
                            {
                                cout << "Please enter a positive integer." << endl;
                            }
                        }
                    }
                }


                validTopChoice = true;
                break;
            }
            case 6:
            {
                cout << "Ending session...goodbye!" << endl;
                stillPlaying = false;
                validTopChoice = true;
                break;
            }
            default:
            {
                cout << "Invalid menu choice, try again, lil BIIITCH" << endl;
                break;
            }
            // at end of expected switch cases...
            if (validTopChoice == false) 
            {
                cout << "Invalid choice detected, try again" << endl;
            }
        }
    }
    return stillPlaying;
}

PlayerList getActivePlayersFromFile()
{
    PlayerList activePlayers;
    activePlayers.reserve(20);

    int maxHealth;
    int armorClass;
    int moveSpeed;

    // inputs to be read per line from file specified
    string playerName;
    string charName;
    string race;
    string playerClass;
    string alignment;

    ifstream data;
    try{
        // open sesame!
        data.open("Players.txt"); // change this file name if needed
        if (data) // make sure it's open
        {
            int numPlayers = 0;
            int playerID = 0;
            // read in fields per line -> new player per line
            while (data >> playerName >> charName >> race >> playerClass >> alignment >> maxHealth >> armorClass >> moveSpeed
            && (numPlayers <= activePlayers.capacity()))
            {
                playerID += 1;
                Player* tempPlayer = new Player(playerName,
                                                charName,
                                                race,
                                                playerClass,
                                                alignment,
                                                maxHealth,
                                                armorClass,
                                                moveSpeed);
                tempPlayer->playerID = playerID; // for adding players to encounters after they start
                activePlayers.push_back(*tempPlayer);
                numPlayers += 1;
            }
        }
        else 
        {
            data.close();
            cout << "Failed to open file; abort" << endl;
            exit(1);
        }
    // when done, close the file stream
    data.close();
    } catch(...)
    {
        cout << "This is where it fucks up..." << endl;
    }
    // number of players added; for use later where reference copies create too large of a vector
    globalNumPlayers = activePlayers.size();

    // fill in available space to avoid invalid indices
    for (int p = globalNumPlayers; p < 20; p++) 
    {
        Player* dummyPlayer = new Player();
        activePlayers.push_back(*dummyPlayer);
    }
    return activePlayers;
}

PlayerList getActivePlayersManually() 
{
    PlayerList thePlayers;
    thePlayers.reserve(10);

    bool validNumberPlayers = false;
    string numberPlayersAsString;
    int numberPlayersAsInt = 0;
    while (!validNumberPlayers) 
    {
        cout << "How many players are we with today?" << endl;
        cin  >> numberPlayersAsString; // get user answer
        try
        {
            numberPlayersAsInt = stoi(numberPlayersAsString); // store as int
        } catch (...)
        {
            cout << "Enter a fucking integer..." << endl;
        }
        // make sure answer will fit in vector allocated
        if (numberPlayersAsInt != 0 && numberPlayersAsInt < 10) 
        {
            validNumberPlayers = true;
        }
    }
    for (int i = 0; i < numberPlayersAsInt; i++)
    {
        // per player
        bool validMaxHealth  = false;
        bool validArmorClass = false;
        bool validMoveSpeed  = false;
        string playerName;
        string characterName;
        string race;
        string playerClass;
        string alignment;
        string maxHealthString;
        string armorClassString;
        string moveSpeedString;
        int maxHealth  = 0;
        int armorClass = 0;
        int moveSpeed  = 0;

        cout << "Enter player name: " << endl;
        cin  >> playerName;

        cout << "Enter character name: " << endl;
        cin  >> characterName;

        cout << "Enter character race: " << endl;
        cin  >> race;
        
        cout << "Enter player class: " << endl;
        cin  >> playerClass;

        cout << "Enter player alignment: " << endl;
        cin  >> alignment;

        while (!validMaxHealth)
        {
            cout << "Enter player max health:" << endl;
            cin  >> maxHealthString;
            try
            {
                maxHealth = stoi(maxHealthString);
            }
            catch (...) 
            {
                cout << "Integer please, fucker" << endl;
            }
            if (!(maxHealth <= 0)) 
            {
                validMaxHealth = true;
            }
        }
        while (!validArmorClass)
        {
            cout << "Enter player armor class:" << endl;
            cin  >> armorClassString;
            try
            {
                armorClass = stoi(armorClassString);
            }
            catch (...) 
            {
                cout << "Integer please, fucker" << endl;
            }
            if (!(armorClass <= 0)) 
            {
                validArmorClass = true;
            }
        }
        while (!validMoveSpeed)
        {
            cout << "Enter player move speed:" << endl;
            cin  >> moveSpeedString;
            try
            {
                moveSpeed = stoi(moveSpeedString);
            }
            catch (...) 
            {
                cout << "Integer please, fucker" << endl;
            }
            if (!(moveSpeed <= 0)) 
            {
                validMoveSpeed = true;
            }
        }
        Player* newPlayer = new Player(playerName,
                                       characterName,
                                       race,
                                       playerClass,
                                       alignment,
                                       maxHealth,
                                       armorClass,
                                       moveSpeed);
        cout << newPlayer->playerName << newPlayer->creatureName << newPlayer->race << endl;
        newPlayer->playerID = i+1;
        thePlayers.push_back(*newPlayer);
        cout << "Player added." << endl;
    }
    return thePlayers;
}

// Determine which players are to participate in the encounter
ParticipantList getParticipants(PlayerList& thePlayers)
{
    ParticipantList* theParticipants = new ParticipantList();
    bool validInput = false;
    bool stillAddingParticipants = true;
    string input;

    while (!validInput)
    {
        cout << "Are all players participating? Enter 'y' or 'n': " << endl;
        cin >> input;
        if (input.compare("y")   == 0 || 
            input.compare("Y")   == 0 || 
            input.compare("yes") == 0)
        {
            Participant tempParticipant;
            int numberParticipants = 0;
            for (int i = 0; i < globalNumPlayers; i++) 
            {
                string input;
                int initiative = 0;
                bool validInitiative = false;
                tempParticipant = new Participant();
                while (!validInitiative)
                {
                    cout << "What is " << players.at(i).playerName << "'s initiative?" << endl;
                    cin  >> input;
                    try
                    {
                        initiative = stoi(input);
                    }
                    catch (...)
                    {
                        cout << "That's not a number, dipshit." << endl;
                    }
                    if (!(initiative <= 0)) // if valid initiative
                    {
                        validInitiative = true;
                        // populate Participant values
                        tempParticipant.itsEntity = &thePlayers.at(i);
                        tempParticipant.itsInitiative = initiative;
                    }
                }
                if (tempParticipant.itsInitiative != 0) 
                {
                    // add participant to list
                    theParticipants->push_back(tempParticipant);
                    numberParticipants += 1; 
                }
            } 
            validInput = true;
        } 
        else if (input.compare("n") == 0 || 
                 input.compare("N") == 0 || 
                 input.compare("no") == 0)
        {
            cout << "Build the current party for the encounter..." << endl;
            PlayerList* tempPlayerList = new PlayerList();
            tempPlayerList->reserve(globalNumPlayers);

            for (int p = 0; p < globalNumPlayers; p++)
            {
                tempPlayerList->push_back(players.at(p));
            }

            PlayerList* participatingPlayers = new PlayerList();
            participatingPlayers->reserve(tempPlayerList->size());

            cout << "Able to add " << participatingPlayers->capacity() << " players." << endl;
            int thePlayerAdded = 0;
            bool stillAddingPlayers = true;
            string playerAddedString;
            while (stillAddingPlayers)
            {
                cout << "Which player to add?" << endl;

                // print players available (by character name)
                for (int t = 0; t < tempPlayerList->size(); t++)
                {
                    cout << t+1 << ".) " << tempPlayerList->at(t).creatureName << endl;
                }
                // option to stop adding players
                cout << tempPlayerList->size()+1 << ".) Done adding players." << endl;
                
                cin >> playerAddedString; // get input
                try
                {
                    thePlayerAdded = stoi(playerAddedString); // store as int
                }
                catch(...)
                {
                    cout << "Invalid player indicated." << endl;
                    break;
                }
                if ((0 < thePlayerAdded) && (thePlayerAdded <= tempPlayerList->size())) // validity check
                {
                    thePlayerAdded--; // make user's choice of player match indices in vector
                    string alreadyPicked("ALREADY PICKED");
                    // make sure the player hasn't already been added. We don't need clones.
                    if (alreadyPicked.compare(tempPlayerList->at(thePlayerAdded).creatureName) == 0)
                    {
                        cout << "Player has already been added to list." << endl;
                    } 
                    else
                    {
                        participatingPlayers->push_back(tempPlayerList->at(thePlayerAdded));
                        cout << "Added player " << tempPlayerList->at(thePlayerAdded).creatureName 
                             << "..."           << endl;

                        // register player as already chosen
                        (tempPlayerList->begin()+thePlayerAdded)->creatureName = "ALREADY PICKED";
                    }
                }
                else if (thePlayerAdded == tempPlayerList->size()+1) // done adding players check
                {
                    if (tempPlayerList->size() < 1)
                    {
                        cout << "Must add at least one player!" << endl;
                    }
                    else 
                    {
                        stillAddingPlayers = false;
                    }
                }
                else
                {
                    cout << "Invalid choice." << endl;
                    break;
                }
            }
            Participant tempParticipant;
            for (int i = 0; i < participatingPlayers->size(); i++) 
            {
                string input;
                int initiative = 0;
                bool validInitiative = false;
                tempParticipant = new Participant();

                // get valid initiative for each player
                while (!validInitiative)
                {
                    cout << "What is " << participatingPlayers->at(i).playerName << "'s initiative?" << endl;
                    cin  >> input;
                    try
                    {
                        initiative = stoi(input);                        
                    }
                    catch (...)
                    {
                        cout << "That's not a number, dipshit." << endl;
                    }
                    if (!(initiative <= 0))
                    {
                        validInitiative = true;
                        // construct participant
                        tempParticipant.itsEntity = &participatingPlayers->at(i);
                        tempParticipant.itsInitiative = initiative;                        
                    }
                }
                if (tempParticipant.itsInitiative != 0) 
                {
                    theParticipants->push_back(tempParticipant);                    
                }
            }            
            validInput = true;        
        } 
        else 
        {
            cout << "Try again..." << endl;        
        }
    }
    return *theParticipants;
}

#include "Monster.h"

Monster::Monster(std::string creatureName, int maxHealth, int armorClass, int moveSpeed,
                 Abilities abilities, vector<Environment>& environment, int libraryIndex,
                 int str, int dex, int con, int intel, int wis, int cha)
{
    this->maxHealth       = maxHealth;
    this->healthRemaining = maxHealth;
    this->moveSpeed       = moveSpeed;
    this->abilities       = abilities;
    this->armorClass      = armorClass;
    this->creatureName    = creatureName;
    this->itsEnvironment  = environment;

    this->itsStrMod = str;
    this->itsDexMod = dex;
    this->itsConMod = con;
    this->itsIntMod = intel;
    this->itsWisMod = wis;
    this->itsChaMod = cha;

    this->natureOfTheBeast = KillableType::MONSTER;

    this->itsLibraryIndex = libraryIndex;

    itsAttacks.reserve(20);
    itsAttackSaves.reserve(20);
    itsAttackModifiers.reserve(20);
    itsConsequences.reserve(20);
    itsDifficulty.reserve(20);
    itsDamageDice.reserve(20);
    itsDamageList.reserve(20);
    itsEnvironment.reserve(5);
}

vector<Environment> Monster::getEnvironment()
{
    return this->itsEnvironment;
}

int Monster::attack(int whichAttack)
{
    // initialize damage results for the monster's attack
    int diceRolls[6];
    for (int r = 0; r < 6; r++) 
    {
        diceRolls[r] = 0;
    }

    bool validSave = false;
    int  theSave = 0;
    string theSaveString;
    try 
    {
        if ((0 <= whichAttack) && (whichAttack < itsAttacks.size())) // ensure valid attack referenced
        {
            bool takesConsequence = false;
            switch (itsAttackSaves.at(whichAttack)) // check enumeration
            {
                case AttackSave::NONE:
                {
                    cout << "No saving throw necessary." << endl;
                    break;
                }
                case AttackSave::STR:
                {
                    cout << "Make a strength save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                case AttackSave::DEX:
                {
                    cout << "Make a dexterity save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                case AttackSave::CON:
                {
                    cout << "Make a constitution save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                case AttackSave::INT:
                {
                    cout << "Make an intelligence save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                case AttackSave::WIS:
                {
                    cout << "Make a wisdom save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                case AttackSave::CHA:
                {
                    cout << "Make a charisma save!" << endl;
                    while (!validSave) 
                    {
                        cout << "Save value: ";
                        cin  >> theSaveString;
                        try
                        {
                            theSave = stoi(theSaveString);
                        }
                        catch(...)
                        {
                            cout << "Valid integer please." << endl;
                        }
                        if (theSave > 0) 
                        {
                            validSave = true;

                            // if save failed, suffer the consequences (action might be needed)
                            if (theSave < itsDifficulty.at(whichAttack))
                            {
                                cout << itsConsequences.at(whichAttack) << endl;
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    cout << "Invalid save indicated." << endl;
                    break;
                }
            }
        } 
        else
        {
            cout << "Unexpected condition! Invalid attack indicated. Returning 0 damage." << endl;
            return 0;
        }

        // roll damage for the attack, going by dice type positions in the DamageDice structure
        for (int d = 0; d < itsDamageList.at(whichAttack).at(0); d++)
        {
            diceRolls[0] += itsDiceRoller.rollDice(4);
        }
        for (int d = 0; d < itsDamageList.at(whichAttack).at(1); d++)
        {
            diceRolls[1] += itsDiceRoller.rollDice(6);
        }
        for (int d = 0; d < itsDamageList.at(whichAttack).at(2); d++)
        {
            diceRolls[2] += itsDiceRoller.rollDice(8);
        }
        for (int d = 0; d < itsDamageList.at(whichAttack).at(3); d++)
        {
            diceRolls[3] += itsDiceRoller.rollDice(10);
        }
        for (int d = 0; d < itsDamageList.at(whichAttack).at(4); d++)
        {
            diceRolls[4] += itsDiceRoller.rollDice(12);
        }
        for (int d = 0; d < itsDamageList.at(whichAttack).at(5); d++)
        {
            diceRolls[5] += itsDiceRoller.rollDice(20);
        }
        int totalDamage = 0;
        for (int i=0; i < 6; i++) 
        {
            totalDamage += diceRolls[i];
        }
        return totalDamage;
    }
    catch (...)
    {
        cout << "*** UNEXPECTED ATTACK *** " << endl;
        return 0;
    }
}

int Monster::attackRoll(int& attackRoll)
{
    cout << "Monster - " << this->creatureName << " attacking!" << endl;
    int itsAttackRoll = -1;
    bool validAttackRoll = false;

    // ensure valid attack roll
    while (!validAttackRoll)
    {
        itsAttackRoll = itsDiceRoller.rollDice(20);
        if (1 <= itsAttackRoll <= 20)
        {
            validAttackRoll = true;
        }
    }

    int theAttack = 0;
    bool validAttack = false;
    string theAttackString;

    while (!validAttack)
    {
        cout << "Which attack shall it use? " << endl;
        
        // display attacks available for the monster to use
        for (int a = 0; a < itsAttacks.size(); a++)
        {
            cout << a+1 << ".) " << itsAttacks.at(a) << endl;
        }
        cin >> theAttackString;
        try
        {
            theAttack = stoi(theAttackString); // try storing choice as int
        }
        catch(...)
        {
            cout << "Please select a valid option." << endl;
        }

        // guarantee valid choice
        if (!(theAttack < 0) && theAttack <= itsAttacks.size())
        {
            theAttack--;
            cout << "Monster will use " << itsAttacks.at(theAttack) << "..." << endl;
            validAttack = true;
        }
    }
    
    // critical failure
    if (itsAttackRoll == 1) 
    {
        return (itsAttackRoll = 0);
    }
    // critical hit
    else if (itsAttackRoll == 20)
    {
        return (itsAttackRoll = 100);
    } 
    
    // literally anything else with the corresponding modifier added
    else 
    {
        itsAttackRoll += itsAttackModifiers.at(theAttack);
    }
    // set attack roll in reference input
    attackRoll = itsAttackRoll;

    // attack chosen by user
    return theAttack;
}

int Monster::takeDamage(int amount) 
{
    this->healthRemaining -= amount;
    return this->healthRemaining;
}

Abilities Monster::getAbilities()
{
    return this->abilities;
}

int Monster::makeSavingThrow(int type)
{
    int theSave = itsDiceRoller.rollDice(20);
    switch (type)
    {
        // check type of save from menu (which calls this) and add modifier
        case 1:
            theSave += itsStrMod;
            break;
        case 2:
            theSave += itsDexMod;
            break;
        case 3:
            theSave += itsConMod;
            break;
        case 4:
            theSave += itsIntMod;
            break;
        case 5:
            theSave += itsWisMod;
            break;
        case 6:
            theSave += itsChaMod;
            break;
        default:
            std::cout << "Invalid input type. Skipping modifier." << endl;
            break;
    }
    return theSave;
}

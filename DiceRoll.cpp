#include "DiceRoll.h"

    Dice::Dice(int value) 
    {
        itsFaces = value;
        srand(time(0));
    }

    int Dice::roll() 
    {
        return static_cast<int>((rand() % (itsFaces-2)) + 3);
    }

    Dice::~Dice() 
    {
        delete this;
    }

    int DiceRoller::rollDice(int whatKind)
    {
        int result = 0; // this should only remain the result if it doesn't work...
        switch (whatKind) 
        {
            case 4:
                result = itsD4.roll();
                break;
            case 6:
                result = itsD6.roll();
                break;
            case 8:
                result = itsD8.roll();
                break;
            case 10:
                result = itsD10.roll();
                break;
            case 12:
                result = itsD12.roll();
                break;
            case 20:
                result = itsD20.roll();
                break;
            case 100: 
                result = itsD100.roll();
                break;
            default:
                cout << "Unnaccepted polyhedral die designator!" << endl;
                break;
        }
        return result;

    }
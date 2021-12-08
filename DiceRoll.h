#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

class Dice
{
    private:
        int itsFaces;

    public: 
         Dice(int);
        ~Dice();

        int roll();
};

class DiceRoller
{
    private:
        Dice itsD4   = Dice(4);
        Dice itsD6   = Dice(6);
        Dice itsD8   = Dice(8);
        Dice itsD10  = Dice(10);
        Dice itsD12  = Dice(12);
        Dice itsD20  = Dice(20);
        Dice itsD100 = Dice(100);


    public:
        int rollDice(int);
};

#endif
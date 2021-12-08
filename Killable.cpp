#include "Killable.h"

void Killable::setNature(KillableType type)
{
    this->natureOfTheBeast = type;
}

int Killable::attackRoll()
{
    return 0;
}

int Killable::attack(Killable& target)
{
    return 0;
}
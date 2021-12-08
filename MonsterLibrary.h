#ifndef MONSTER_LIBRARY_H
#define MONSTER_LIBRARY_H

#include "Monster.h"


// Words don't matter...but last value is used to determine random monster modulus
typedef enum MonstersAvailable 
        {
            TEST_MONSTER,
            ANIMATED_ARMOR,
            RUG_OF_SMOTHERING,
            BANSHEE,
            SPECTATOR,
            CARRION_CRAWLER,
            IMP,
            SPINED_DEVIL,
            BLACK_DRAGON_WYRMLING,
            ETTERCAP,
            INTELLECT_DEVOURER,
            MIMIC,
            NOTHIC,
            DARK_GUARD,
            BILWIS,
            PISHACHA_DEMON,
            LIVING_SHADE,
            SHADOW_OOZE,
            SHADOW_SKELETON,
            WEIRDING_SCROLL,
            ZOOG,
            CENTAUR,
            SHAMBLING_MOUND,
            WILL_O_WISP,
            NEOPHRON,
            EXPLODING_TOAD,
            DOOM_GOLEM,
            GOLIATH_LONG_LEGS,
            JINMENJU,
            BONE_DEVIL,
            CHAIN_DEVIL,
            LITCH_LORD,
            LAST_VALUE
        } MonstersAvailable;

class MonsterLibrary
{
    public:
        MonsterLibrary() {};
        void printMonsterList(); 
        Monster* createMonster(int);
};


// Each monster implemented will need a class of this format

class TestMonster : public Monster
{
    public: 
        TestMonster();
        TestMonster(std::string, int, int, int, 
                    Abilities, 
                    Environment,
                    int);
        // 0.) Test Monster
};

class AnimatedArmor : public Monster
{
    public: 
        AnimatedArmor();
        AnimatedArmor(std::string, int, int, int, 
                    Abilities, 
                    Environment,
                    int);
        // 1.) Animated Armor
};

class RugOfSmothering : public Monster
{
    public: 
        RugOfSmothering();
        RugOfSmothering(std::string, int, int, int, 
                    Abilities, 
                    Environment,
                    int);
        // 2.) Rug of Smothering
};

class Banshee : public Monster
{
    public: 
        Banshee();
        Banshee(std::string, int, int, int, 
                    Abilities, 
                    Environment,
                    int);
        // 3.) Banshee
};

class Spectator : public Monster
{
    public:
        Spectator();
        Spectator(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 4.) Spectator
};

class CarrionCrawler : public Monster
{
    public:
        CarrionCrawler();
        CarrionCrawler(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 5.) Carrion Crawler
};

class Imp : public Monster
{
    public:
        Imp();
        Imp(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 6.) Imp
};

class SpinedDevil : public Monster
{
    public:
        SpinedDevil();
        SpinedDevil(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 7.) Spined Devil
};

class BlackDragonWyrmling : public Monster 
{
    public:
        BlackDragonWyrmling();
        BlackDragonWyrmling(std::string, int, int, int,
                            Abilities,
                            Environment,
                            int);
        // 8.) Black Dragon Wyrmling
};

class Ettercap : public Monster
{
    public:
        Ettercap();
        Ettercap(std::string, int, int, int,
                 Abilities,
                 Environment,
                 int);
        // 9.) Ettercap
};

class IntellectDevourer : public Monster
{
    public:
        IntellectDevourer();
        IntellectDevourer(std::string, int, int, int,
                          Abilities,
                          Environment,
                          int);
        // 10.) Intellect Devourer
};

class Mimic : public Monster
{
    public:
        Mimic();
        Mimic(std::string, int, int, int,
              Abilities,
              Environment,
              int);
        // 11.) Mimic
};

class Nothic : public Monster
{
    public:
        Nothic();
        Nothic(std::string, int, int, int,
               Abilities,
               Environment,
               int);
        // 12.) Nothic
};

class DarkGuard : public Monster
{
    public:
        DarkGuard();
        DarkGuard(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 13.) Dark Guard
};

class Bilwis : public Monster
{
    public:
        Bilwis();
        Bilwis(std::string, int, int, int,
                  Abilities,
                  Environment,
                  int);
        // 14.) Bilwis 
};

class PishachaDemon : public Monster
{
    public:
        PishachaDemon();
        PishachaDemon(std::string, int, int, int,
                      Abilities,
                      Environment,
                      int);
        // 15.) Pishacha Demon 
};

class LivingShade : public Monster
{
    public:
        LivingShade();
        LivingShade(std::string, int, int, int,
                    Abilities,
                    Environment,
                    int);
        // 16.) Living Shade
};

class ShadowOoze : public Monster
{
    public:
        ShadowOoze();
        ShadowOoze(std::string, int, int, int,
                    Abilities,
                    Environment,
                    int);
        // 17.) Shadow Ooze
};

class ShadowSkeleton : public Monster
{
    public:
        ShadowSkeleton();
        ShadowSkeleton(std::string, int, int, int,
                       Abilities,
                       Environment,
                       int);
        // 18.) Shadow Skeleton
};

class WeirdingScroll : public Monster
{
    public:
        WeirdingScroll();
        WeirdingScroll(std::string, int, int, int,
                       Abilities,
                       Environment,
                       int);
        // 19.) Weirding Scroll
};

class Zoog : public Monster
{
    public:
        Zoog();
        Zoog(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 20.) Zoog
};

class Centaur : public Monster
{
    public:
        Centaur();
        Centaur(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 21.) Centaur
};

class ShamblingMound : public Monster
{
    public:
        ShamblingMound();
        ShamblingMound(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 22.) ShamblingMound
};

class Will_o_Wisp : public Monster
{
    public:
        Will_o_Wisp();
        Will_o_Wisp(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 23.) Will_o_Wisp
};

class Neophron : public Monster
{
    public:
        Neophron();
        Neophron(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 24.) Neophron
};

class ExplodingToad : public Monster
{
    public:
        ExplodingToad();
        ExplodingToad(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 25.) ExplodingToad
};

class DoomGolem : public Monster
{
    public:
        DoomGolem();
        DoomGolem(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 26.) DoomGolem
};

class GoliathLongLegs : public Monster
{
    public:
        GoliathLongLegs();
        GoliathLongLegs(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 27.) GoliathLongLegs
};

class Jinmenju : public Monster
{
    public:
        Jinmenju();
        Jinmenju(std::string, int, int, int,
             Abilities, 
             Environment,
             int);
        // 28.) Jinmenju
};

class BoneDevil : public Monster
{
    public:
        BoneDevil();
        BoneDevil(std::string, int, int, int,
            Abilities,
            Environment,
            int);
        // 29.) BoneDevil
};

class ChainDevil : public Monster
{
    public:
        ChainDevil();
        ChainDevil(std::string, int, int, int,
            Abilities,
            Environment,
            int);
        // 30.) ChainDevil
};

class LitchLord : public Monster
{
    public:
        LitchLord();
        LitchLord(std::string, int, int, int,
            Abilities,
            Environment,
            int);
        // 31.) LitchLord
};

#endif
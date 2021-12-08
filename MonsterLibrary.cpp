#include "MonsterLibrary.h"

void MonsterLibrary::printMonsterList()
{
    // menu of options to select
    cout << "0.)  Test Monster          CR: 1/2"  << endl;
    cout << "1.)  Animated Armor        CR: 1"    << endl;
    cout << "2.)  Rug of Smothering     CR: 2"    << endl;
    cout << "3.)  Banshee               CR: 4"    << endl;
    cout << "4.)  Spectator             CR: 3"    << endl;
    cout << "5.)  Carrion Crawler       CR: 2"    << endl;
    cout << "6.)  Imp                   CR: 1"    << endl;
    cout << "7.)  Spined Devil          CR: 2"    << endl;
    cout << "8.)  Black Dragon Wyrmling CR: 2"    << endl;
    cout << "9.)  Ettercap              CR: 2"    << endl;
    cout << "10.) Intellect Devourer    CR: 2"    << endl;
    cout << "11.) Mimic                 CR: 2"    << endl;
    cout << "12.) Nothic                CR: 2"    << endl;
    cout << "13.) Dark Guard            CR: 3"    << endl;
    cout << "14.) Bilwis                CR: 1"    << endl;
    cout << "15.) Pishacha Demon        CR: 3"    << endl;
    cout << "16.) Living Shade          CR: 1/4"  << endl;
    cout << "17.) Shadow Ooze           CR: 3"    << endl;
    cout << "18.) Shadow Skeleton       CR: 2"    << endl;
    cout << "19.) Weirding Scroll       CR: 1/2"  << endl;
    cout << "20.) Zoog                  CR: 0"    << endl;
    cout << "21.) Centaur               CR: 2"    << endl;
    cout << "22.) Shambling Mound       CR: 5"    << endl;
    cout << "23.) Will'O Wisp           CR: 2"    << endl;
    cout << "24.) Neophron              CR: 8"    << endl;
    cout << "25.) Exploding Toad        CR: 1/4"  << endl;
    cout << "26.) Doom Golem            CR: 10"   << endl;
    cout << "27.) Goliath LongLegs      CR: 7"    << endl;
    cout << "28.) Jinmenju              CR: 9"    << endl;
    cout << "29.) Bone Devil            CR: 9"    << endl;
    cout << "30.) Chain Devil           CR: 8"    << endl;
    cout << "31.) Litch Lord            CR: 9"    << endl;
}

Monster* MonsterLibrary::createMonster(int libraryIndex) 
{
    Monster* newMonster = 0;
    switch (libraryIndex) 
    {
        // create the chosen monster and return a pointer to it
        case 0:
            newMonster = new TestMonster();
            break;
        case 1:
            newMonster = new AnimatedArmor();
            break;
        case 2:
            newMonster = new RugOfSmothering();
            break;
        case 3:
            newMonster = new Banshee();
            break;
        case 4:
            newMonster = new Spectator();
            break;
        case 5:
            newMonster = new CarrionCrawler();
            break;
        case 6:
            newMonster = new Imp();
            break;
        case 7:
            newMonster = new SpinedDevil();
            break;
        case 8:
            newMonster = new BlackDragonWyrmling();
            break;
        case 9:
            newMonster = new Ettercap();
            break;
        case 10:
            newMonster = new IntellectDevourer();
            break;
        case 11:
            newMonster = new Mimic();
            break;
        case 12:
            newMonster = new Nothic();
            break;
        case 13:
            newMonster = new DarkGuard();
            break;
        case 14:
            newMonster = new Bilwis();
            break;
        case 15:
            newMonster = new PishachaDemon();
            break;
        case 16:
            newMonster = new LivingShade();
            break;
        case 17:
            newMonster = new ShadowOoze();
            break;
        case 18:
            newMonster = new ShadowSkeleton();
            break;
        case 19:
            newMonster = new WeirdingScroll();
            break;
        case 20:
            newMonster = new Zoog();
            break;
        case 21:
            newMonster = new Centaur();
            break;
        case 22:
            newMonster = new ShamblingMound();
            break;
        case 23:
            newMonster = new Will_o_Wisp();
            break;
        case 24:
            newMonster = new Neophron();
            break;
        case 25:
            newMonster = new ExplodingToad();
            break;
        case 26:
            newMonster = new DoomGolem();
            break;
        case 27:
            newMonster = new GoliathLongLegs();
            break;
        case 28:
            newMonster = new Jinmenju();
            break;
        case 29:
            newMonster = new BoneDevil();
            break;
        case 30:
            newMonster = new ChainDevil();
            break;
        case 31:
            newMonster = new LitchLord();
            break;
        default:
            cout << "Monster not found, try again" << endl;   
            break;
    }
    return newMonster;
}

// Test Monster Constructor
TestMonster::TestMonster() : Monster(std::string("Test Monster"),
                                     20, // health
                                     10, // armor class
                                     25, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     0, // library index
                                     0, 0, 0, 0, 0, 0) // modifiers
{
    challengeRating = 0.5;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;
    
    Abilities TestMonsterAbilities;
    // declare abilities sequentially
    Ability TestMonsterAbility1("Being a punk ass lil bitch.");
    // push abilities back in order above
    TestMonsterAbilities.push_back(TestMonsterAbility1);
    this->abilities = TestMonsterAbilities;

    // holders for attack details
    AttackList         TestMonsterAttackList;
    vector<AttackSave> TestMonsterAttackSaves;
    DamageList         TestMonsterDamageList;
    vector<int>        TestMonsterAttackModifiers;
    vector<int>        TestMonsterDifficulty;
    Consequence        TestMonsterConsequences;

    // all attack details
    Attack TestMonsterAttack1("Claw");
    int TestMonsterAttackMod1 = 3;
    DamageDice TestMonsterAttackDamage1 = {1, 0, 0, 0, 0, 0};
    AttackSave TestMonsterAttackSave1 = AttackSave::NONE;
    int TestMonsterSaveDifficulty1 = 0;
    string TestMonsterConsequence1("Nothing");

    TestMonsterAttackList.push_back(TestMonsterAttack1);
    TestMonsterAttackModifiers.push_back(TestMonsterAttackMod1);
    TestMonsterDamageList.push_back(TestMonsterAttackDamage1);
    TestMonsterAttackSaves.push_back(TestMonsterAttackSave1);
    TestMonsterDifficulty.push_back(TestMonsterSaveDifficulty1);
    TestMonsterConsequences.push_back(TestMonsterConsequence1);

    this->itsAttacks         = TestMonsterAttackList;
    this->itsAttackSaves     = TestMonsterAttackSaves;
    this->itsDamageList      = TestMonsterDamageList;
    this->itsAttackModifiers = TestMonsterAttackModifiers;
    this->itsDifficulty      = TestMonsterDifficulty;
    this->itsConsequences    = TestMonsterConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// AnimatedArmor Constructor
AnimatedArmor::AnimatedArmor() : Monster(std::string("Animated Armor"),
                                     33, // health
                                     18, // armor class
                                     25, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     1, // library index
                                     2, 0, 1, -5, -4, -5) // modifiers
{
    challengeRating = 1;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;
    
    Abilities AnimatedArmorAbilities;
    AnimatedArmorAbilities.reserve(10);
    // declare abilities sequentially
    Ability AnimatedArmorAbility1("MultiAttack");
    Ability AnimatedArmorAbility2("AntiMagic Susceptibility");
    Ability AnimatedArmorAbility3("False Appearance");
    Ability AnimatedArmorAbility4("Immune:PoisonPsychicBlindCharmDeafnessFearParalz");
    // push abilities back in order above
    AnimatedArmorAbilities.push_back(AnimatedArmorAbility1);
    AnimatedArmorAbilities.push_back(AnimatedArmorAbility2);
    AnimatedArmorAbilities.push_back(AnimatedArmorAbility3);
    AnimatedArmorAbilities.push_back(AnimatedArmorAbility4);
    this->abilities = AnimatedArmorAbilities;

    // holders for attack details
    AttackList         AnimatedArmorAttackList; AnimatedArmorAttackList.reserve(10);
    vector<AttackSave> AnimatedArmorAttackSaves; AnimatedArmorAttackSaves.reserve(10);
    DamageList         AnimatedArmorDamageList; AnimatedArmorDamageList.reserve(10);
    vector<int>        AnimatedArmorAttackModifiers; AnimatedArmorAttackModifiers.reserve(10);
    vector<int>        AnimatedArmorDifficulty; AnimatedArmorDifficulty.reserve(10);
    Consequence        AnimatedArmorConsequences; AnimatedArmorConsequences.reserve(10);

    // all attack details
    Attack AnimatedArmorAttack1("Slam");
    int AnimatedArmorAttackMod1 = 4;
    DamageDice AnimatedArmorAttackDamage1 = {0, 1, 0, 0, 0, 0};
    AttackSave AnimatedArmorAttackSave1 = AttackSave::NONE;
    int AnimatedArmorSaveDifficulty1 = 0;
    string AnimatedArmorConsequence1("Nothing");

    AnimatedArmorAttackList.push_back(AnimatedArmorAttack1);
    AnimatedArmorAttackModifiers.push_back(AnimatedArmorAttackMod1);
    AnimatedArmorDamageList.push_back(AnimatedArmorAttackDamage1);
    AnimatedArmorAttackSaves.push_back(AnimatedArmorAttackSave1);
    AnimatedArmorDifficulty.push_back(AnimatedArmorSaveDifficulty1);
    AnimatedArmorConsequences.push_back(AnimatedArmorConsequence1);

    this->itsAttacks         = AnimatedArmorAttackList;
    this->itsAttackSaves     = AnimatedArmorAttackSaves;
    this->itsDamageList      = AnimatedArmorDamageList;
    this->itsAttackModifiers = AnimatedArmorAttackModifiers;
    this->itsDifficulty      = AnimatedArmorDifficulty;
    this->itsConsequences    = AnimatedArmorConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Rug of Smothering Constructor
RugOfSmothering::RugOfSmothering() : Monster(std::string("Rug of Smothering"),
                                     33, // health
                                     18, // armor class
                                     25, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     2, // library index
                                     3, 2, 0, -5, -4, -5) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;
    
    Abilities RugOfSmotheringAbilities;
              RugOfSmotheringAbilities.reserve(10);

    // declare abilities sequentially
    Ability RugOfSmotheringAbility1("AntiMagic Susceptibility");
    Ability RugOfSmotheringAbility2("FalseAppearance");
    Ability RugOfSmotheringAbility3("DamageTransfer(half)");
    Ability RugOfSmotheringAbility4("Immune:PoisonPsychicBlindCharmDeafnessFearParalz");

    // push abilities back in order above
    RugOfSmotheringAbilities.push_back(RugOfSmotheringAbility1);
    RugOfSmotheringAbilities.push_back(RugOfSmotheringAbility2);
    RugOfSmotheringAbilities.push_back(RugOfSmotheringAbility3);
    RugOfSmotheringAbilities.push_back(RugOfSmotheringAbility4);
                     this->abilities = RugOfSmotheringAbilities;

    // holders for attack details
    AttackList         RugOfSmotheringAttackList; RugOfSmotheringAttackList.reserve(10);
    vector<AttackSave> RugOfSmotheringAttackSaves; RugOfSmotheringAttackSaves.reserve(10);
    DamageList         RugOfSmotheringDamageList; RugOfSmotheringDamageList.reserve(10);
    vector<int>        RugOfSmotheringAttackModifiers; RugOfSmotheringAttackModifiers.reserve(10);
    vector<int>        RugOfSmotheringDifficulty; RugOfSmotheringDifficulty.reserve(10);
    Consequence        RugOfSmotheringConsequences; RugOfSmotheringConsequences.reserve(10);

    // all attack details
    Attack     RugOfSmotheringAttack1("Smother");
    int        RugOfSmotheringAttackMod1 = 100;
    DamageDice RugOfSmotheringAttackDamage1 = {0, 0, 0, 0, 0, 0};
    AttackSave RugOfSmotheringAttackSave1 = AttackSave::STR;
    int        RugOfSmotheringSaveDifficulty1 = 13;
    string     RugOfSmotheringConsequence1("Stuck until DC 13 is passed; takes same damage at start of each turn (1d4, 2d6)");

    RugOfSmotheringAttackList.push_back     (RugOfSmotheringAttack1);
    RugOfSmotheringAttackModifiers.push_back(RugOfSmotheringAttackMod1);
    RugOfSmotheringDamageList.push_back     (RugOfSmotheringAttackDamage1);
    RugOfSmotheringAttackSaves.push_back    (RugOfSmotheringAttackSave1);
    RugOfSmotheringDifficulty.push_back     (RugOfSmotheringSaveDifficulty1);
    RugOfSmotheringConsequences.push_back   (RugOfSmotheringConsequence1);

    this->itsAttacks         = RugOfSmotheringAttackList;
    this->itsAttackSaves     = RugOfSmotheringAttackSaves;
    this->itsDamageList      = RugOfSmotheringDamageList;
    this->itsAttackModifiers = RugOfSmotheringAttackModifiers;
    this->itsDifficulty      = RugOfSmotheringDifficulty;
    this->itsConsequences    = RugOfSmotheringConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Banshee Constructor
Banshee::Banshee() : Monster(std::string("Banshee"),
                                     58, // health
                                     12, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     3, // library index
                                     -5, 2, 0, 1, 0, 3) // modifiers
{
    challengeRating = 4;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::WATER);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities BansheeAbilities;
              BansheeAbilities.reserve(10);

    // declare abilities sequentially
    Ability BansheeAbility1("DarkVision");
    Ability BansheeAbility2("DetectLife");
    Ability BansheeAbility3("IncorporealMovement");
    Ability BansheeAbility4("Immune:ColdNecroticPoisonCharmGraplParlzProne");
    Ability BansheeAbility5("Resistant:AcidFireLightngBldgPrcSlsh");

    // push abilities back in order above
    BansheeAbilities.push_back(BansheeAbility1);
    BansheeAbilities.push_back(BansheeAbility2);
    BansheeAbilities.push_back(BansheeAbility3);
    BansheeAbilities.push_back(BansheeAbility4);
    BansheeAbilities.push_back(BansheeAbility5);
    this->abilities = BansheeAbilities;

    // holders for attack details
    AttackList         BansheeAttackList; BansheeAttackList.reserve(10);
    vector<AttackSave> BansheeAttackSaves; BansheeAttackSaves.reserve(10);
    DamageList         BansheeDamageList; BansheeDamageList.reserve(10);
    vector<int>        BansheeAttackModifiers; BansheeAttackModifiers.reserve(10);
    vector<int>        BansheeDifficulty; BansheeDifficulty.reserve(10);
    Consequence        BansheeConsequences; BansheeConsequences.reserve(10);

    // all attack details
    Attack     BansheeAttack1("CorruptingTouch");
    int        BansheeAttackMod1 = 4;
    DamageDice BansheeAttackDamage1 = {0, 3, 0, 0, 0, 0};
    AttackSave BansheeAttackSave1 = AttackSave::NONE;
    int        BansheeSaveDifficulty1 = 0;
    string     BansheeConsequence1("NONE");

    Attack     BansheeAttack2("HorrifyingVisage");
    int        BansheeAttackMod2 = 100;
    DamageDice BansheeAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave BansheeAttackSave2 = AttackSave::WIS;
    int        BansheeSaveDifficulty2 = 13;
    string     BansheeConsequence2("Frightened for 1 minute or until pass save (DC 13)");

    Attack     BansheeAttack3("Wail (once daily)");
    int        BansheeAttackMod3 = 100;
    DamageDice BansheeAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave BansheeAttackSave3 = AttackSave::CON;
    int        BansheeSaveDifficulty3 = 100;
    string     BansheeConsequence3("Drop to zero or take 3d6 if DC 13 passed");

    BansheeAttackList.push_back     (BansheeAttack1);
    BansheeAttackList.push_back     (BansheeAttack2);
    BansheeAttackList.push_back     (BansheeAttack3);
    BansheeAttackModifiers.push_back(BansheeAttackMod1);
    BansheeAttackModifiers.push_back(BansheeAttackMod2);
    BansheeAttackModifiers.push_back(BansheeAttackMod3);
    BansheeDamageList.push_back     (BansheeAttackDamage1);
    BansheeDamageList.push_back     (BansheeAttackDamage2);
    BansheeDamageList.push_back     (BansheeAttackDamage3);
    BansheeAttackSaves.push_back    (BansheeAttackSave1);
    BansheeAttackSaves.push_back    (BansheeAttackSave2);
    BansheeAttackSaves.push_back    (BansheeAttackSave3);
    BansheeDifficulty.push_back     (BansheeSaveDifficulty1);
    BansheeDifficulty.push_back     (BansheeSaveDifficulty2);
    BansheeDifficulty.push_back     (BansheeSaveDifficulty3);
    BansheeConsequences.push_back   (BansheeConsequence1);
    BansheeConsequences.push_back   (BansheeConsequence2);
    BansheeConsequences.push_back   (BansheeConsequence3);

    this->itsAttacks         = BansheeAttackList;
    this->itsAttackSaves     = BansheeAttackSaves;
    this->itsDamageList      = BansheeDamageList;
    this->itsAttackModifiers = BansheeAttackModifiers;
    this->itsDifficulty      = BansheeDifficulty;
    this->itsConsequences    = BansheeConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Spectator Constructor
Spectator::Spectator() : Monster(std::string("Spectator"),
                                     39, // health
                                     14, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     4, // library index
                                     -1, 2, 2, 1, 2, 0) // modifiers
{
    challengeRating = 3;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities SpectatorAbilities;
              SpectatorAbilities.reserve(10);

    // declare abilities sequentially
    Ability SpectatorAbility1("DarkVision");
    Ability SpectatorAbility2("SpellReflection - target other creature when 'not hit'");

    // push abilities back in order above
    SpectatorAbilities.push_back(SpectatorAbility1);
    SpectatorAbilities.push_back(SpectatorAbility2);
    this->abilities = SpectatorAbilities;

    // holders for attack details
    AttackList         SpectatorAttackList; SpectatorAttackList.reserve(10);
    vector<AttackSave> SpectatorAttackSaves; SpectatorAttackSaves.reserve(10);
    DamageList         SpectatorDamageList; SpectatorDamageList.reserve(10);
    vector<int>        SpectatorAttackModifiers; SpectatorAttackModifiers.reserve(10);
    vector<int>        SpectatorDifficulty; SpectatorDifficulty.reserve(10);
    Consequence        SpectatorConsequences; SpectatorConsequences.reserve(10);

    // all attack details
    Attack     SpectatorAttack1("Bite");
    int        SpectatorAttackMod1 = 1;
    DamageDice SpectatorAttackDamage1 = {0, 1, 0, 0, 0, 0};
    AttackSave SpectatorAttackSave1 = AttackSave::NONE;
    int        SpectatorSaveDifficulty1 = 0;
    string     SpectatorConsequence1("NONE");

    Attack     SpectatorAttack2("EyeRay - Confusion");
    int        SpectatorAttackMod2 = 1;
    DamageDice SpectatorAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave SpectatorAttackSave2 = AttackSave::WIS;
    int        SpectatorSaveDifficulty2 = 13;
    string     SpectatorConsequence2("Confused until end of next turn");

    Attack     SpectatorAttack3("EyeRay - Paralyze");
    int        SpectatorAttackMod3 = 1;
    DamageDice SpectatorAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave SpectatorAttackSave3 = AttackSave::CON;
    int        SpectatorSaveDifficulty3 = 13;
    string     SpectatorConsequence3("Paralyzed for 1 minute or until DC 13 beat");

    Attack     SpectatorAttack4("EyeRay - Fear");
    int        SpectatorAttackMod4 = 1;
    DamageDice SpectatorAttackDamage4 = {0, 0, 0, 0, 0, 0};
    AttackSave SpectatorAttackSave4 = AttackSave::WIS;
    int        SpectatorSaveDifficulty4 = 13;
    string     SpectatorConsequence4("Frightened for 1 minute or until DC 13 beat");

    Attack     SpectatorAttack5("EyeRay - Wound!");
    int        SpectatorAttackMod5 = 1;
    DamageDice SpectatorAttackDamage5 = {0, 0, 0, 0, 0, 0};
    AttackSave SpectatorAttackSave5 = AttackSave::CON;
    int        SpectatorSaveDifficulty5 = 100;
    string     SpectatorConsequence5("3d10 or Half Damage if DC 13 passed");

    SpectatorAttackList.push_back     (SpectatorAttack1);
    SpectatorAttackList.push_back     (SpectatorAttack2);
    SpectatorAttackList.push_back     (SpectatorAttack3);
    SpectatorAttackList.push_back     (SpectatorAttack4);
    SpectatorAttackList.push_back     (SpectatorAttack5);
    SpectatorAttackModifiers.push_back(SpectatorAttackMod1);
    SpectatorAttackModifiers.push_back(SpectatorAttackMod2);
    SpectatorAttackModifiers.push_back(SpectatorAttackMod3);
    SpectatorAttackModifiers.push_back(SpectatorAttackMod4);
    SpectatorAttackModifiers.push_back(SpectatorAttackMod5);
    SpectatorDamageList.push_back     (SpectatorAttackDamage1);
    SpectatorDamageList.push_back     (SpectatorAttackDamage2);
    SpectatorDamageList.push_back     (SpectatorAttackDamage3);
    SpectatorDamageList.push_back     (SpectatorAttackDamage4);
    SpectatorDamageList.push_back     (SpectatorAttackDamage5);
    SpectatorAttackSaves.push_back    (SpectatorAttackSave1);
    SpectatorAttackSaves.push_back    (SpectatorAttackSave2);
    SpectatorAttackSaves.push_back    (SpectatorAttackSave3);
    SpectatorAttackSaves.push_back    (SpectatorAttackSave4);
    SpectatorAttackSaves.push_back    (SpectatorAttackSave5);
    SpectatorDifficulty.push_back     (SpectatorSaveDifficulty1);
    SpectatorDifficulty.push_back     (SpectatorSaveDifficulty2);
    SpectatorDifficulty.push_back     (SpectatorSaveDifficulty3);
    SpectatorDifficulty.push_back     (SpectatorSaveDifficulty4);
    SpectatorDifficulty.push_back     (SpectatorSaveDifficulty5);
    SpectatorConsequences.push_back   (SpectatorConsequence1);
    SpectatorConsequences.push_back   (SpectatorConsequence2);
    SpectatorConsequences.push_back   (SpectatorConsequence3);
    SpectatorConsequences.push_back   (SpectatorConsequence4);
    SpectatorConsequences.push_back   (SpectatorConsequence5);

    this->itsAttacks         = SpectatorAttackList;
    this->itsAttackSaves     = SpectatorAttackSaves;
    this->itsDamageList      = SpectatorDamageList;
    this->itsAttackModifiers = SpectatorAttackModifiers;
    this->itsDifficulty      = SpectatorDifficulty;
    this->itsConsequences    = SpectatorConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Carrion Crawler Constructor
CarrionCrawler::CarrionCrawler() : Monster(std::string("Carrion Crawler"),
                                     51, // health
                                     13, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     5, // library index
                                     2, 1, 3, -5, 1, -3) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;


    // insert names before all instance names
    Abilities CarrionCrawlerAbilities;
              CarrionCrawlerAbilities.reserve(10);

    // declare abilities sequentially
    Ability CarrionCrawlerAbility1("KeenSmell(AdvantageOnWisdomChecks");
    Ability CarrionCrawlerAbility2("SpiderClimb");
    Ability CarrionCrawlerAbility3("MultiAttack(OnceWithEachAttack)");
    Ability CarrionCrawlerAbility4("DarkVision");

    // push abilities back in order above
    CarrionCrawlerAbilities.push_back(CarrionCrawlerAbility1);
    CarrionCrawlerAbilities.push_back(CarrionCrawlerAbility2);
    CarrionCrawlerAbilities.push_back(CarrionCrawlerAbility3);
    CarrionCrawlerAbilities.push_back(CarrionCrawlerAbility4);
    this->abilities = CarrionCrawlerAbilities;

    // holders for attack details
    AttackList         CarrionCrawlerAttackList; CarrionCrawlerAttackList.reserve(10);
    vector<AttackSave> CarrionCrawlerAttackSaves; CarrionCrawlerAttackSaves.reserve(10);
    DamageList         CarrionCrawlerDamageList; CarrionCrawlerDamageList.reserve(10);
    vector<int>        CarrionCrawlerAttackModifiers; CarrionCrawlerAttackModifiers.reserve(10);
    vector<int>        CarrionCrawlerDifficulty; CarrionCrawlerDifficulty.reserve(10);
    Consequence        CarrionCrawlerConsequences; CarrionCrawlerConsequences.reserve(10);

    // all attack details
    Attack     CarrionCrawlerAttack1("Bite");
    int        CarrionCrawlerAttackMod1 = 4;
    DamageDice CarrionCrawlerAttackDamage1 = {2, 0, 0, 0, 0, 0};
    AttackSave CarrionCrawlerAttackSave1 = AttackSave::NONE;
    int        CarrionCrawlerSaveDifficulty1 = 0;
    string     CarrionCrawlerConsequence1("NONE");

    Attack     CarrionCrawlerAttack2("Tentacles");
    int        CarrionCrawlerAttackMod2 = 8;
    DamageDice CarrionCrawlerAttackDamage2 = {2, 0, 0, 0, 0, 0};
    AttackSave CarrionCrawlerAttackSave2 = AttackSave::CON;
    int        CarrionCrawlerSaveDifficulty2 = 13;
    string     CarrionCrawlerConsequence2("Poisoned / Paralyzed for 1 minute or until DC 13 passed.");

    CarrionCrawlerAttackList.push_back     (CarrionCrawlerAttack1);
    CarrionCrawlerAttackModifiers.push_back(CarrionCrawlerAttackMod1);
    CarrionCrawlerDamageList.push_back     (CarrionCrawlerAttackDamage1);
    CarrionCrawlerAttackSaves.push_back    (CarrionCrawlerAttackSave1);
    CarrionCrawlerDifficulty.push_back     (CarrionCrawlerSaveDifficulty1);
    CarrionCrawlerConsequences.push_back   (CarrionCrawlerConsequence1);

    CarrionCrawlerAttackList.push_back     (CarrionCrawlerAttack2);
    CarrionCrawlerAttackModifiers.push_back(CarrionCrawlerAttackMod2);
    CarrionCrawlerDamageList.push_back     (CarrionCrawlerAttackDamage2);
    CarrionCrawlerAttackSaves.push_back    (CarrionCrawlerAttackSave2);
    CarrionCrawlerDifficulty.push_back     (CarrionCrawlerSaveDifficulty2);
    CarrionCrawlerConsequences.push_back   (CarrionCrawlerConsequence2);

    this->itsAttacks         = CarrionCrawlerAttackList;
    this->itsAttackSaves     = CarrionCrawlerAttackSaves;
    this->itsDamageList      = CarrionCrawlerDamageList;
    this->itsAttackModifiers = CarrionCrawlerAttackModifiers;
    this->itsDifficulty      = CarrionCrawlerDifficulty;
    this->itsConsequences    = CarrionCrawlerConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Imp Constructor
Imp::Imp() : Monster(std::string("Imp"),
                                     10, // health
                                     13, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     6, // library index
                                     -2, 3, 1, 0, 1, 2) // modifiers
{
    challengeRating = 1;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::WATER);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ImpAbilities;
              ImpAbilities.reserve(10);

    // declare abilities sequentially
    Ability ImpAbility1("DarkVision");
    Ability ImpAbility2("ShapeChanger(Rat,Raven,Spider,Beast)");
    Ability ImpAbility3("Devil's Sight");
    Ability ImpAbility4("MagicResistance(advantageOnSavesAgainstMagic");
    Ability ImpAbility5("Resistant:ColdBldgPrcSlshNonMagicWpnFirePsn");

    // push abilities back in order above
    ImpAbilities.push_back(ImpAbility1);
    ImpAbilities.push_back(ImpAbility2);
    ImpAbilities.push_back(ImpAbility3);
    ImpAbilities.push_back(ImpAbility4);
    ImpAbilities.push_back(ImpAbility5);
    this->abilities = ImpAbilities;

    // holders for attack details
    AttackList         ImpAttackList; ImpAttackList.reserve(10);
    vector<AttackSave> ImpAttackSaves; ImpAttackSaves.reserve(10);
    DamageList         ImpDamageList; ImpDamageList.reserve(10);
    vector<int>        ImpAttackModifiers; ImpAttackModifiers.reserve(10);
    vector<int>        ImpDifficulty; ImpDifficulty.reserve(10);
    Consequence        ImpConsequences; ImpConsequences.reserve(10);

    // all attack details
    Attack     ImpAttack1("Sting/Bite");
    int        ImpAttackMod1 = 5;
    DamageDice ImpAttackDamage1 = {2, 0, 0, 0, 0, 0};
    AttackSave ImpAttackSave1 = AttackSave::CON;
    int        ImpSaveDifficulty1 = 100;
    string     ImpConsequence1("Take 3d10 poison or half if DC 11 or better");

    Attack     ImpAttack2("Invisibility");
    int        ImpAttackMod2 = 100;
    DamageDice ImpAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave ImpAttackSave2 = AttackSave::INT;
    int        ImpSaveDifficulty2 = 100;
    string     ImpConsequence2("Magically turns invisible until concentration broken");

    ImpAttackList.push_back     (ImpAttack1);
    ImpAttackModifiers.push_back(ImpAttackMod1);
    ImpDamageList.push_back     (ImpAttackDamage1);
    ImpAttackSaves.push_back    (ImpAttackSave1);
    ImpDifficulty.push_back     (ImpSaveDifficulty1);
    ImpConsequences.push_back   (ImpConsequence1);

    ImpAttackList.push_back     (ImpAttack2);
    ImpAttackModifiers.push_back(ImpAttackMod2);
    ImpDamageList.push_back     (ImpAttackDamage2);
    ImpAttackSaves.push_back    (ImpAttackSave2);
    ImpDifficulty.push_back     (ImpSaveDifficulty2);
    ImpConsequences.push_back   (ImpConsequence2);

    this->itsAttacks         = ImpAttackList;
    this->itsAttackSaves     = ImpAttackSaves;
    this->itsDamageList      = ImpDamageList;
    this->itsAttackModifiers = ImpAttackModifiers;
    this->itsDifficulty      = ImpDifficulty;
    this->itsConsequences    = ImpConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Spined Devil Constructor
SpinedDevil::SpinedDevil() : Monster(std::string("Spined Devil"),
                                     22, // health
                                     13, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     7, // library index
                                     0, 2, 1, 0, 2, -1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::WATER);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities SpinedDevilAbilities;
              SpinedDevilAbilities.reserve(10);

    // declare abilities sequentially
    Ability SpinedDevilAbility1("Devil'sSight");
    Ability SpinedDevilAbility2("Flyby(noAttackOfOpp)");
    Ability SpinedDevilAbility3("LimitedSpines(12)");
    Ability SpinedDevilAbility4("MultiAttack");
    Ability SpinedDevilAbility5("MagicResistance(AdvOnSavesAgainstMagic)");

    // push abilities back in order above
    SpinedDevilAbilities.push_back(SpinedDevilAbility1);
    SpinedDevilAbilities.push_back(SpinedDevilAbility2);
    SpinedDevilAbilities.push_back(SpinedDevilAbility3);
    SpinedDevilAbilities.push_back(SpinedDevilAbility4);
    SpinedDevilAbilities.push_back(SpinedDevilAbility5);
    this->abilities = SpinedDevilAbilities;

    // holders for attack details
    AttackList         SpinedDevilAttackList; SpinedDevilAttackList.reserve(10);
    vector<AttackSave> SpinedDevilAttackSaves; SpinedDevilAttackSaves.reserve(10);
    DamageList         SpinedDevilDamageList; SpinedDevilDamageList.reserve(10);
    vector<int>        SpinedDevilAttackModifiers; SpinedDevilAttackModifiers.reserve(10);
    vector<int>        SpinedDevilDifficulty; SpinedDevilDifficulty.reserve(10);
    Consequence        SpinedDevilConsequences; SpinedDevilConsequences.reserve(10);

    // all attack details
    Attack     SpinedDevilAttack1("Bite");
    int        SpinedDevilAttackMod1 = 2;
    DamageDice SpinedDevilAttackDamage1 = {2, 0, 0, 0, 0, 0};
    AttackSave SpinedDevilAttackSave1 = AttackSave::NONE;
    int        SpinedDevilSaveDifficulty1 = 0;
    string     SpinedDevilConsequence1("NONE");

    Attack     SpinedDevilAttack2("Fork");
    int        SpinedDevilAttackMod2 = 2;
    DamageDice SpinedDevilAttackDamage2 = {0, 1, 0, 0, 0, 0};
    AttackSave SpinedDevilAttackSave2 = AttackSave::NONE;
    int        SpinedDevilSaveDifficulty2 = 0;
    string     SpinedDevilConsequence2("NONE");

    Attack     SpinedDevilAttack3("Tail Spine");
    int        SpinedDevilAttackMod3 = 4;
    DamageDice SpinedDevilAttackDamage3 = {1, 1, 0, 0, 0, 0};
    AttackSave SpinedDevilAttackSave3 = AttackSave::NONE;
    int        SpinedDevilSaveDifficulty3 = 0;
    string     SpinedDevilConsequence3("NONE");

    SpinedDevilAttackList.push_back     (SpinedDevilAttack1);
    SpinedDevilAttackModifiers.push_back(SpinedDevilAttackMod1);
    SpinedDevilDamageList.push_back     (SpinedDevilAttackDamage1);
    SpinedDevilAttackSaves.push_back    (SpinedDevilAttackSave1);
    SpinedDevilDifficulty.push_back     (SpinedDevilSaveDifficulty1);
    SpinedDevilConsequences.push_back   (SpinedDevilConsequence1);

    SpinedDevilAttackList.push_back     (SpinedDevilAttack2);
    SpinedDevilAttackModifiers.push_back(SpinedDevilAttackMod2);
    SpinedDevilDamageList.push_back     (SpinedDevilAttackDamage2);
    SpinedDevilAttackSaves.push_back    (SpinedDevilAttackSave2);
    SpinedDevilDifficulty.push_back     (SpinedDevilSaveDifficulty2);
    SpinedDevilConsequences.push_back   (SpinedDevilConsequence2);

    SpinedDevilAttackList.push_back     (SpinedDevilAttack3);
    SpinedDevilAttackModifiers.push_back(SpinedDevilAttackMod3);
    SpinedDevilDamageList.push_back     (SpinedDevilAttackDamage3);
    SpinedDevilAttackSaves.push_back    (SpinedDevilAttackSave3);
    SpinedDevilDifficulty.push_back     (SpinedDevilSaveDifficulty3);
    SpinedDevilConsequences.push_back   (SpinedDevilConsequence3);

    this->itsAttacks         = SpinedDevilAttackList;
    this->itsAttackSaves     = SpinedDevilAttackSaves;
    this->itsDamageList      = SpinedDevilDamageList;
    this->itsAttackModifiers = SpinedDevilAttackModifiers;
    this->itsDifficulty      = SpinedDevilDifficulty;
    this->itsConsequences    = SpinedDevilConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Black Dragon Wyrmling Constructor 
BlackDragonWyrmling::BlackDragonWyrmling() : Monster(std::string("Black Dragon Wyrmling"),
                                                     33, // health
                                                     17, // armor class
                                                     30, // speed
                                                     BASE_ABILITIES,
                                                     DEFAULT_ENVIRONMENT,
                                                     8, // library index
                                                     2, 2, 1, 0, 0, 1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::WATER);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities BlackDragonWyrmlingAbilities;
              BlackDragonWyrmlingAbilities.reserve(5);

    // declare abilities sequentially
    Ability BlackDragonWyrmlingAbility1("DarkVisionAndBlindSight");
    Ability BlackDragonWyrmlingAbility2("Amphibious");
    Ability BlackDragonWyrmlingAbility3("ImmuneToAcid");

    // push abilities back in order above
    BlackDragonWyrmlingAbilities.push_back(BlackDragonWyrmlingAbility1);
    BlackDragonWyrmlingAbilities.push_back(BlackDragonWyrmlingAbility2);
    BlackDragonWyrmlingAbilities.push_back(BlackDragonWyrmlingAbility3);
    this->abilities = BlackDragonWyrmlingAbilities;

    // holders for attack details
    AttackList         BlackDragonWyrmlingAttackList;
    vector<AttackSave> BlackDragonWyrmlingAttackSaves;
    DamageList         BlackDragonWyrmlingDamageList;
    vector<int>        BlackDragonWyrmlingAttackModifiers;
    vector<int>        BlackDragonWyrmlingDifficulty;
    Consequence        BlackDragonWyrmlingConsequences;

    // all attack details
    Attack     BlackDragonWyrmlingAttack1("Bite");
    int        BlackDragonWyrmlingAttackMod1 = 4;
    DamageDice BlackDragonWyrmlingAttackDamage1 = {1, 0, 0, 1, 0, 0};
    AttackSave BlackDragonWyrmlingAttackSave1 = AttackSave::NONE;
    int        BlackDragonWyrmlingSaveDifficulty1 = 0;
    string     BlackDragonWyrmlingConsequence1("None");

    Attack     BlackDragonWyrmlingAttack2("Acid Breath");
    int        BlackDragonWyrmlingAttackMod2 = 100;
    DamageDice BlackDragonWyrmlingAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave BlackDragonWyrmlingAttackSave2 = AttackSave::DEX;
    int        BlackDragonWyrmlingSaveDifficulty2 = 100;
    string     BlackDragonWyrmlingConsequence2("All in a 15 foot line take 5d8 or half if DC 11 passed.");

    BlackDragonWyrmlingAttackList.push_back     (BlackDragonWyrmlingAttack1);
    BlackDragonWyrmlingAttackModifiers.push_back(BlackDragonWyrmlingAttackMod1);
    BlackDragonWyrmlingDamageList.push_back     (BlackDragonWyrmlingAttackDamage1);
    BlackDragonWyrmlingAttackSaves.push_back    (BlackDragonWyrmlingAttackSave1);
    BlackDragonWyrmlingDifficulty.push_back     (BlackDragonWyrmlingSaveDifficulty1);
    BlackDragonWyrmlingConsequences.push_back   (BlackDragonWyrmlingConsequence1);

    BlackDragonWyrmlingAttackList.push_back     (BlackDragonWyrmlingAttack2);
    BlackDragonWyrmlingAttackModifiers.push_back(BlackDragonWyrmlingAttackMod2);
    BlackDragonWyrmlingDamageList.push_back     (BlackDragonWyrmlingAttackDamage2);
    BlackDragonWyrmlingAttackSaves.push_back    (BlackDragonWyrmlingAttackSave2);
    BlackDragonWyrmlingDifficulty.push_back     (BlackDragonWyrmlingSaveDifficulty2);
    BlackDragonWyrmlingConsequences.push_back   (BlackDragonWyrmlingConsequence2);

    this->itsAttacks         = BlackDragonWyrmlingAttackList;
    this->itsAttackSaves     = BlackDragonWyrmlingAttackSaves;
    this->itsDamageList      = BlackDragonWyrmlingDamageList;
    this->itsAttackModifiers = BlackDragonWyrmlingAttackModifiers;
    this->itsDifficulty      = BlackDragonWyrmlingDifficulty;
    this->itsConsequences    = BlackDragonWyrmlingConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Ettercap (spider shepard) Constructor
Ettercap::Ettercap() : Monster(std::string("Ettercap"),
                               44, // health
                               13, // armor class
                               30, // speed
                               BASE_ABILITIES,
                               DEFAULT_ENVIRONMENT,
                               9, // library index
                               2, 2, 1, -2, 1, -1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities EttercapAbilities;
              EttercapAbilities.reserve(5);

    // declare abilities sequentially
    Ability EttercapAbility1("Darkvision");
    Ability EttercapAbility2("SpiderClimb");
    Ability EttercapAbility3("WebSense");
    Ability EttercapAbility4("WebWalker");
    Ability EttercapAbility5("MultiAttack");

    // push abilities back in order above
    EttercapAbilities.push_back(EttercapAbility1);
    EttercapAbilities.push_back(EttercapAbility2);
    EttercapAbilities.push_back(EttercapAbility3);
    EttercapAbilities.push_back(EttercapAbility4);
    EttercapAbilities.push_back(EttercapAbility5);
    this->abilities = EttercapAbilities;

    // holders for attack details
    AttackList         EttercapAttackList;
    vector<AttackSave> EttercapAttackSaves;
    DamageList         EttercapDamageList;
    vector<int>        EttercapAttackModifiers;
    vector<int>        EttercapDifficulty;
    Consequence        EttercapConsequences;

    // all attack details
    Attack     EttercapAttack1("Bite");
    int        EttercapAttackMod1 = 4;
    DamageDice EttercapAttackDamage1 = {0, 1, 1, 0, 0, 0};
    AttackSave EttercapAttackSave1 = AttackSave::NONE;
    int        EttercapSaveDifficulty1 = 13;
    string     EttercapConsequence1("consequence");

    Attack     EttercapAttack2("Claw");
    int        EttercapAttackMod2 = 4;
    DamageDice EttercapAttackDamage2 = {3, 0, 0, 0, 0, 0};
    AttackSave EttercapAttackSave2 = AttackSave::NONE;
    int        EttercapSaveDifficulty2 = 13;
    string     EttercapConsequence2("consequence");

    Attack     EttercapAttack3("Web");
    int        EttercapAttackMod3 = 4;
    DamageDice EttercapAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave EttercapAttackSave3 = AttackSave::STR;
    int        EttercapSaveDifficulty3 = 11;
    string     EttercapConsequence3("Restrained in thick spider-webbing until DC 11 passed.");

    EttercapAttackList.push_back     (EttercapAttack1);
    EttercapAttackModifiers.push_back(EttercapAttackMod1);
    EttercapDamageList.push_back     (EttercapAttackDamage1);
    EttercapAttackSaves.push_back    (EttercapAttackSave1);
    EttercapDifficulty.push_back     (EttercapSaveDifficulty1);
    EttercapConsequences.push_back   (EttercapConsequence1);

    EttercapAttackList.push_back     (EttercapAttack2);
    EttercapAttackModifiers.push_back(EttercapAttackMod2);
    EttercapDamageList.push_back     (EttercapAttackDamage2);
    EttercapAttackSaves.push_back    (EttercapAttackSave2);
    EttercapDifficulty.push_back     (EttercapSaveDifficulty2);
    EttercapConsequences.push_back   (EttercapConsequence2);

    EttercapAttackList.push_back     (EttercapAttack3);
    EttercapAttackModifiers.push_back(EttercapAttackMod3);
    EttercapDamageList.push_back     (EttercapAttackDamage3);
    EttercapAttackSaves.push_back    (EttercapAttackSave3);
    EttercapDifficulty.push_back     (EttercapSaveDifficulty3);
    EttercapConsequences.push_back   (EttercapConsequence3);

    this->itsAttacks         = EttercapAttackList;
    this->itsAttackSaves     = EttercapAttackSaves;
    this->itsDamageList      = EttercapDamageList;
    this->itsAttackModifiers = EttercapAttackModifiers;
    this->itsDifficulty      = EttercapDifficulty;
    this->itsConsequences    = EttercapConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Intellect Devourer Constructor
IntellectDevourer::IntellectDevourer() : Monster(std::string("Intellect Devourer"),
                                                             21, // health
                                                             12, // armor class
                                                             40, // speed
                                                             BASE_ABILITIES,
                                                             DEFAULT_ENVIRONMENT,
                                                             10, // library index
                                                             -2, 2, 1, 1, 0, 0) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities IntellectDevourerAbilities;
              IntellectDevourerAbilities.reserve(5);

    // declare abilities sequentially
    Ability IntellectDevourerAbility1("BlindSight");
    Ability IntellectDevourerAbility2("Telepathy");
    Ability IntellectDevourerAbility3("DetectSentience");
    Ability IntellectDevourerAbility4("MultiAttack");

    // push abilities back in order above
    IntellectDevourerAbilities.push_back(IntellectDevourerAbility1);
    IntellectDevourerAbilities.push_back(IntellectDevourerAbility2);
    IntellectDevourerAbilities.push_back(IntellectDevourerAbility3);
    IntellectDevourerAbilities.push_back(IntellectDevourerAbility4);
    this->abilities = IntellectDevourerAbilities;

    // holders for attack details
    AttackList         IntellectDevourerAttackList;
    vector<AttackSave> IntellectDevourerAttackSaves;
    DamageList         IntellectDevourerDamageList;
    vector<int>        IntellectDevourerAttackModifiers;
    vector<int>        IntellectDevourerDifficulty;
    Consequence        IntellectDevourerConsequences;

    // all attack details
    Attack     IntellectDevourerAttack1("Claws");
    int        IntellectDevourerAttackMod1 = 4;
    DamageDice IntellectDevourerAttackDamage1 = {3, 0, 0, 0, 0, 0};
    AttackSave IntellectDevourerAttackSave1 = AttackSave::NONE;
    int        IntellectDevourerSaveDifficulty1 = 0;
    string     IntellectDevourerConsequence1("NONE");

    Attack     IntellectDevourerAttack2("Devour Intellect");
    int        IntellectDevourerAttackMod2 = 100;
    DamageDice IntellectDevourerAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave IntellectDevourerAttackSave2 = AttackSave::INT;
    int        IntellectDevourerSaveDifficulty2 = 12;
    string     IntellectDevourerConsequence2("Take 2d10 psychic damage; roll 3d6 - if higher than INT score, incapacitated");

    Attack     IntellectDevourerAttack3("Body Thief");
    int        IntellectDevourerAttackMod3 = 100;
    DamageDice IntellectDevourerAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave IntellectDevourerAttackSave3 = AttackSave::INT;
    int        IntellectDevourerSaveDifficulty3 = 100;
    string     IntellectDevourerConsequence3("Incapacitated creature is under control until HP == 0.");

    IntellectDevourerAttackList.push_back     (IntellectDevourerAttack1);
    IntellectDevourerAttackModifiers.push_back(IntellectDevourerAttackMod1);
    IntellectDevourerDamageList.push_back     (IntellectDevourerAttackDamage1);
    IntellectDevourerAttackSaves.push_back    (IntellectDevourerAttackSave1);
    IntellectDevourerDifficulty.push_back     (IntellectDevourerSaveDifficulty1);
    IntellectDevourerConsequences.push_back   (IntellectDevourerConsequence1);

    IntellectDevourerAttackList.push_back     (IntellectDevourerAttack2);
    IntellectDevourerAttackModifiers.push_back(IntellectDevourerAttackMod2);
    IntellectDevourerDamageList.push_back     (IntellectDevourerAttackDamage2);
    IntellectDevourerAttackSaves.push_back    (IntellectDevourerAttackSave2);
    IntellectDevourerDifficulty.push_back     (IntellectDevourerSaveDifficulty2);
    IntellectDevourerConsequences.push_back   (IntellectDevourerConsequence2);

    IntellectDevourerAttackList.push_back     (IntellectDevourerAttack3);
    IntellectDevourerAttackModifiers.push_back(IntellectDevourerAttackMod3);
    IntellectDevourerDamageList.push_back     (IntellectDevourerAttackDamage3);
    IntellectDevourerAttackSaves.push_back    (IntellectDevourerAttackSave3);
    IntellectDevourerDifficulty.push_back     (IntellectDevourerSaveDifficulty3);
    IntellectDevourerConsequences.push_back   (IntellectDevourerConsequence3);

    this->itsAttacks         = IntellectDevourerAttackList;
    this->itsAttackSaves     = IntellectDevourerAttackSaves;
    this->itsDamageList      = IntellectDevourerDamageList;
    this->itsAttackModifiers = IntellectDevourerAttackModifiers;
    this->itsDifficulty      = IntellectDevourerDifficulty;
    this->itsConsequences    = IntellectDevourerConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Mimic Constructor
Mimic::Mimic() : Monster(std::string("Mimic"),
                                     58, // health
                                     12, // armor class
                                     15, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     11, // library index
                                     3, 1, 2, -3, 1, -1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities MimicAbilities;
              MimicAbilities.reserve(5);

    // declare abilities sequentially
    Ability MimicAbility1("ShapeChanger");
    Ability MimicAbility2("Adhesive(DC13orGrappledWithDisAdv)");
    Ability MimicAbility3("FalseAppearance");
    Ability MimicAbility4("Grappler(AdvOnCreaturesAdhered");

    // push abilities back in order above
    MimicAbilities.push_back(MimicAbility1);
    MimicAbilities.push_back(MimicAbility2);
    MimicAbilities.push_back(MimicAbility3);
    MimicAbilities.push_back(MimicAbility4);
    this->abilities = MimicAbilities;

    // holders for attack details
    AttackList         MimicAttackList;
    vector<AttackSave> MimicAttackSaves;
    DamageList         MimicDamageList;
    vector<int>        MimicAttackModifiers;
    vector<int>        MimicDifficulty;
    Consequence        MimicConsequences;

    // all attack details
    Attack     MimicAttack1("Bite");
    int        MimicAttackMod1 = 5;
    DamageDice MimicAttackDamage1 = {1, 0, 2, 0, 0, 0};
    AttackSave MimicAttackSave1 = AttackSave::NONE;
    int        MimicSaveDifficulty1 = 0;
    string     MimicConsequence1("NONE");

    Attack     MimicAttack2("Pseudopod");
    int        MimicAttackMod2 = 5;
    DamageDice MimicAttackDamage2 = {1, 0, 1, 0, 0, 0};
    AttackSave MimicAttackSave2 = AttackSave::STR;
    int        MimicSaveDifficulty2 = 100;
    string     MimicConsequence2("Victim is subject to 'adhesive' Ability");

    MimicAttackList.push_back     (MimicAttack1);
    MimicAttackModifiers.push_back(MimicAttackMod1);
    MimicDamageList.push_back     (MimicAttackDamage1);
    MimicAttackSaves.push_back    (MimicAttackSave1);
    MimicDifficulty.push_back     (MimicSaveDifficulty1);
    MimicConsequences.push_back   (MimicConsequence1);

    MimicAttackList.push_back     (MimicAttack2);
    MimicAttackModifiers.push_back(MimicAttackMod2);
    MimicDamageList.push_back     (MimicAttackDamage2);
    MimicAttackSaves.push_back    (MimicAttackSave2);
    MimicDifficulty.push_back     (MimicSaveDifficulty2);
    MimicConsequences.push_back   (MimicConsequence2);

    this->itsAttacks         = MimicAttackList;
    this->itsAttackSaves     = MimicAttackSaves;
    this->itsDamageList      = MimicDamageList;
    this->itsAttackModifiers = MimicAttackModifiers;
    this->itsDifficulty      = MimicDifficulty;
    this->itsConsequences    = MimicConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Nothic Constructor
Nothic::Nothic() : Monster(std::string("Nothic"),
                                     45, // health
                                     15, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     12, // library index
                                     2, 3, 3, 1, 0, -1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities NothicAbilities;
              NothicAbilities.reserve(5);

    // declare abilities sequentially
    Ability NothicAbility1("KeenSight(AdvOnWisomChecks)");
    Ability NothicAbility2("MultiAttack");
    Ability NothicAbility3("TrueSight");

    // push abilities back in order above
    NothicAbilities.push_back(NothicAbility1);
    NothicAbilities.push_back(NothicAbility2);
    NothicAbilities.push_back(NothicAbility3);
    this->abilities = NothicAbilities;

    // holders for attack details
    AttackList         NothicAttackList;
    vector<AttackSave> NothicAttackSaves;
    DamageList         NothicDamageList;
    vector<int>        NothicAttackModifiers;
    vector<int>        NothicDifficulty;
    Consequence        NothicConsequences;

    // all attack details
    Attack     NothicAttack1("Claw");
    int        NothicAttackMod1 = 4;
    DamageDice NothicAttackDamage1 = {1, 1, 0, 0, 0, 0};
    AttackSave NothicAttackSave1 = AttackSave::NONE;
    int        NothicSaveDifficulty1 = 0;
    string     NothicConsequence1("NONE");

    Attack     NothicAttack2("Rotting Gaze");
    int        NothicAttackMod2 = 100;
    DamageDice NothicAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave NothicAttackSave2 = AttackSave::CON;
    int        NothicSaveDifficulty2 = 12;
    string     NothicConsequence2("Victim takes 3d10 necrotic damage");

    Attack     NothicAttack3("Weird Insight");
    int        NothicAttackMod3 = 100;
    DamageDice NothicAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave NothicAttackSave3 = AttackSave::CHA;
    int        NothicSaveDifficulty3 = 100;
    string     NothicConsequence3("If fails against Nothic's WIS check, 1 secret is immediately learned.");

    NothicAttackList.push_back     (NothicAttack1);
    NothicAttackModifiers.push_back(NothicAttackMod1);
    NothicDamageList.push_back     (NothicAttackDamage1);
    NothicAttackSaves.push_back    (NothicAttackSave1);
    NothicDifficulty.push_back     (NothicSaveDifficulty1);
    NothicConsequences.push_back   (NothicConsequence1);

    NothicAttackList.push_back     (NothicAttack2);
    NothicAttackModifiers.push_back(NothicAttackMod2);
    NothicDamageList.push_back     (NothicAttackDamage2);
    NothicAttackSaves.push_back    (NothicAttackSave2);
    NothicDifficulty.push_back     (NothicSaveDifficulty2);
    NothicConsequences.push_back   (NothicConsequence2);

    NothicAttackList.push_back     (NothicAttack3);
    NothicAttackModifiers.push_back(NothicAttackMod3);
    NothicDamageList.push_back     (NothicAttackDamage3);
    NothicAttackSaves.push_back    (NothicAttackSave3);
    NothicDifficulty.push_back     (NothicSaveDifficulty3);
    NothicConsequences.push_back   (NothicConsequence3);

    this->itsAttacks         = NothicAttackList;
    this->itsAttackSaves     = NothicAttackSaves;
    this->itsDamageList      = NothicDamageList;
    this->itsAttackModifiers = NothicAttackModifiers;
    this->itsDifficulty      = NothicDifficulty;
    this->itsConsequences    = NothicConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Dark Guard Constructor
DarkGuard::DarkGuard() : Monster(std::string("Dark Guard"),
                                 35, // health
                                 13, // armor class
                                 25, // speed
                                 BASE_ABILITIES,
                                 DEFAULT_ENVIRONMENT,
                                 13, // library index
                                 3, 1, 3, -1, 4, 3) // modifiers
{
    challengeRating = 3;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities DarkGuardAbilities;
              DarkGuardAbilities.reserve(5);

    // declare abilities sequentially
    Ability DarkGuardAbility1("Devil'sSight");
    Ability DarkGuardAbility2("Telepathy");
    Ability DarkGuardAbility3("Amorphous");
    Ability DarkGuardAbility4("ShadowStealth");

    // push abilities back in order above
    DarkGuardAbilities.push_back(DarkGuardAbility1);
    DarkGuardAbilities.push_back(DarkGuardAbility2);
    DarkGuardAbilities.push_back(DarkGuardAbility3);
    DarkGuardAbilities.push_back(DarkGuardAbility4);
    this->abilities = DarkGuardAbilities;

    // holders for attack details
    AttackList         DarkGuardAttackList;
    vector<AttackSave> DarkGuardAttackSaves;
    DamageList         DarkGuardDamageList;
    vector<int>        DarkGuardAttackModifiers;
    vector<int>        DarkGuardDifficulty;
    Consequence        DarkGuardConsequences;

    // all attack details
    Attack     DarkGuardAttack1("GreatSword");
    int        DarkGuardAttackMod1 = 5;
    DamageDice DarkGuardAttackDamage1 = {0, 2, 0, 0, 0, 0};
    AttackSave DarkGuardAttackSave1 = AttackSave::NONE;
    int        DarkGuardSaveDifficulty1 = 0;
    string     DarkGuardConsequence1("NONE");

    Attack     DarkGuardAttack2("EldritchBlast");
    int        DarkGuardAttackMod2 = 5;
    DamageDice DarkGuardAttackDamage2 = {0, 0, 0, 1, 0, 0};
    AttackSave DarkGuardAttackSave2 = AttackSave::NONE;
    int        DarkGuardSaveDifficulty2 = 0;
    string     DarkGuardConsequence2("NONE");

    Attack     DarkGuardAttack3("ShieldBash");
    int        DarkGuardAttackMod3 = 5;
    DamageDice DarkGuardAttackDamage3 = {1, 1, 0, 0, 0, 0};
    AttackSave DarkGuardAttackSave3 = AttackSave::CON;
    int        DarkGuardSaveDifficulty3 = 15;
    string     DarkGuardConsequence3("Victim knocked prone");

    Attack     DarkGuardAttack4("StrengthDrain");
    int        DarkGuardAttackMod4 = 4;
    DamageDice DarkGuardAttackDamage4 = {1, 2, 0, 0, 0, 0};
    AttackSave DarkGuardAttackSave4 = AttackSave::STR;
    int        DarkGuardSaveDifficulty4 = 100;
    string     DarkGuardConsequence4("Victim Strength reduced by 1d4; if this falls to zero, DEATH. Otherwise, until rested.");


    DarkGuardAttackList.push_back     (DarkGuardAttack1);
    DarkGuardAttackModifiers.push_back(DarkGuardAttackMod1);
    DarkGuardDamageList.push_back     (DarkGuardAttackDamage1);
    DarkGuardAttackSaves.push_back    (DarkGuardAttackSave1);
    DarkGuardDifficulty.push_back     (DarkGuardSaveDifficulty1);
    DarkGuardConsequences.push_back   (DarkGuardConsequence1);

    DarkGuardAttackList.push_back     (DarkGuardAttack2);
    DarkGuardAttackModifiers.push_back(DarkGuardAttackMod2);
    DarkGuardDamageList.push_back     (DarkGuardAttackDamage2);
    DarkGuardAttackSaves.push_back    (DarkGuardAttackSave2);
    DarkGuardDifficulty.push_back     (DarkGuardSaveDifficulty2);
    DarkGuardConsequences.push_back   (DarkGuardConsequence2);

    DarkGuardAttackList.push_back     (DarkGuardAttack3);
    DarkGuardAttackModifiers.push_back(DarkGuardAttackMod3);
    DarkGuardDamageList.push_back     (DarkGuardAttackDamage3);
    DarkGuardAttackSaves.push_back    (DarkGuardAttackSave3);
    DarkGuardDifficulty.push_back     (DarkGuardSaveDifficulty3);
    DarkGuardConsequences.push_back   (DarkGuardConsequence3);

    DarkGuardAttackList.push_back     (DarkGuardAttack4);
    DarkGuardAttackModifiers.push_back(DarkGuardAttackMod4);
    DarkGuardDamageList.push_back     (DarkGuardAttackDamage4);
    DarkGuardAttackSaves.push_back    (DarkGuardAttackSave4);
    DarkGuardDifficulty.push_back     (DarkGuardSaveDifficulty4);
    DarkGuardConsequences.push_back   (DarkGuardConsequence4);

    this->itsAttacks         = DarkGuardAttackList;
    this->itsAttackSaves     = DarkGuardAttackSaves;
    this->itsDamageList      = DarkGuardDamageList;
    this->itsAttackModifiers = DarkGuardAttackModifiers;
    this->itsDifficulty      = DarkGuardDifficulty;
    this->itsConsequences    = DarkGuardConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Bilwis Constructor
Bilwis::Bilwis() : Monster(std::string("Bilwis"),
                                     49, // health
                                     13, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     14, // library index
                                     1, 3, 0, 0, 1, 3) // modifiers
{
    challengeRating = 1;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities BilwisAbilities;
              BilwisAbilities.reserve(5);

    // declare abilities sequentially
    Ability BilwisAbility1("AirForm");
    Ability BilwisAbility2("DarkVision");

    // push abilities back in order above
    BilwisAbilities.push_back(BilwisAbility1);
    BilwisAbilities.push_back(BilwisAbility2);

    this->abilities = BilwisAbilities;

    // holders for attack details
    AttackList         BilwisAttackList;
    vector<AttackSave> BilwisAttackSaves;
    DamageList         BilwisDamageList;
    vector<int>        BilwisAttackModifiers;
    vector<int>        BilwisDifficulty;
    Consequence        BilwisConsequences;

    // all attack details
    Attack     BilwisAttack1("Slam");
    int        BilwisAttackMod1 = 5;
    DamageDice BilwisAttackDamage1 = {1, 0, 2, 0, 0, 0};
    AttackSave BilwisAttackSave1 = AttackSave::NONE;
    int        BilwisSaveDifficulty1 = 0;
    string     BilwisConsequence1("NONE");

    Attack     BilwisAttack2("WhirlWind");
    int        BilwisAttackMod2 = 100;
    DamageDice BilwisAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave BilwisAttackSave2 = AttackSave::STR;
    int        BilwisSaveDifficulty2 = 100;
    string     BilwisConsequence2("Within 5ft takes 4d6 and prone or half and not on DC12");

    BilwisAttackList.push_back     (BilwisAttack1);
    BilwisAttackModifiers.push_back(BilwisAttackMod1);
    BilwisDamageList.push_back     (BilwisAttackDamage1);
    BilwisAttackSaves.push_back    (BilwisAttackSave1);
    BilwisDifficulty.push_back     (BilwisSaveDifficulty1);
    BilwisConsequences.push_back   (BilwisConsequence1);

    BilwisAttackList.push_back     (BilwisAttack2);
    BilwisAttackModifiers.push_back(BilwisAttackMod2);
    BilwisDamageList.push_back     (BilwisAttackDamage2);
    BilwisAttackSaves.push_back    (BilwisAttackSave2);
    BilwisDifficulty.push_back     (BilwisSaveDifficulty2);
    BilwisConsequences.push_back   (BilwisConsequence2);

    this->itsAttacks         = BilwisAttackList;
    this->itsAttackSaves     = BilwisAttackSaves;
    this->itsDamageList      = BilwisDamageList;
    this->itsAttackModifiers = BilwisAttackModifiers;
    this->itsDifficulty      = BilwisDifficulty;
    this->itsConsequences    = BilwisConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Pishacha Demon Constructor
PishachaDemon::PishachaDemon() : Monster(std::string("Pishacha Demon"),
                                         55, // health
                                         13, // armor class
                                         30, // speed
                                         BASE_ABILITIES,
                                         DEFAULT_ENVIRONMENT,
                                         15, // library index
                                         3, 2, 1, 0, 3, -2) // modifiers
{
    challengeRating = 3;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities PishachaDemonAbilities;
              PishachaDemonAbilities.reserve(5);

    // declare abilities sequentially
    Ability PishachaDemonAbility1("DarkVision");
    Ability PishachaDemonAbility2("Telepathy");
    Ability PishachaDemonAbility3("Shapechanger(wolfOrTiger)");
    Ability PishachaDemonAbility4("MultiAttack");

    // push abilities back in order above
    PishachaDemonAbilities.push_back(PishachaDemonAbility1);
    PishachaDemonAbilities.push_back(PishachaDemonAbility2);
    PishachaDemonAbilities.push_back(PishachaDemonAbility3);
    PishachaDemonAbilities.push_back(PishachaDemonAbility4);
    this->abilities = PishachaDemonAbilities;

    // holders for attack details
    AttackList         PishachaDemonAttackList;
    vector<AttackSave> PishachaDemonAttackSaves;
    DamageList         PishachaDemonDamageList;
    vector<int>        PishachaDemonAttackModifiers;
    vector<int>        PishachaDemonDifficulty;
    Consequence        PishachaDemonConsequences;

    // all attack details
    Attack     PishachaDemonAttack1("Bite");
    int        PishachaDemonAttackMod1 = 5;
    DamageDice PishachaDemonAttackDamage1 = {1, 0, 2, 0, 0, 0};
    AttackSave PishachaDemonAttackSave1 = AttackSave::NONE;
    int        PishachaDemonSaveDifficulty1 = 0;
    string     PishachaDemonConsequence1("NONE");

    Attack     PishachaDemonAttack2("Claws");
    int        PishachaDemonAttackMod2 = 5;
    DamageDice PishachaDemonAttackDamage2 = {1, 2, 0, 0, 0, 0};
    AttackSave PishachaDemonAttackSave2 = AttackSave::NONE;
    int        PishachaDemonSaveDifficulty2 = 0;
    string     PishachaDemonConsequence2("NONE");

    Attack     PishachaDemonAttack3("Demonic Possession");
    int        PishachaDemonAttackMod3 = 100;
    DamageDice PishachaDemonAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave PishachaDemonAttackSave3 = AttackSave::WIS;
    int        PishachaDemonSaveDifficulty3 = 13;
    string     PishachaDemonConsequence3("Victim posessed by Pishacha. 3d6 rounds of sporratic movements then dormant. \n Wait 1d4 hours then repeat  DC 13 save. If still possessed after long rest, permanent madness.");

    PishachaDemonAttackList.push_back     (PishachaDemonAttack1);
    PishachaDemonAttackModifiers.push_back(PishachaDemonAttackMod1);
    PishachaDemonDamageList.push_back     (PishachaDemonAttackDamage1);
    PishachaDemonAttackSaves.push_back    (PishachaDemonAttackSave1);
    PishachaDemonDifficulty.push_back     (PishachaDemonSaveDifficulty1);
    PishachaDemonConsequences.push_back   (PishachaDemonConsequence1);

    PishachaDemonAttackList.push_back     (PishachaDemonAttack2);
    PishachaDemonAttackModifiers.push_back(PishachaDemonAttackMod2);
    PishachaDemonDamageList.push_back     (PishachaDemonAttackDamage2);
    PishachaDemonAttackSaves.push_back    (PishachaDemonAttackSave2);
    PishachaDemonDifficulty.push_back     (PishachaDemonSaveDifficulty2);
    PishachaDemonConsequences.push_back   (PishachaDemonConsequence2);

    PishachaDemonAttackList.push_back     (PishachaDemonAttack3);
    PishachaDemonAttackModifiers.push_back(PishachaDemonAttackMod3);
    PishachaDemonDamageList.push_back     (PishachaDemonAttackDamage3);
    PishachaDemonAttackSaves.push_back    (PishachaDemonAttackSave3);
    PishachaDemonDifficulty.push_back     (PishachaDemonSaveDifficulty3);
    PishachaDemonConsequences.push_back   (PishachaDemonConsequence3);

    this->itsAttacks         = PishachaDemonAttackList;
    this->itsAttackSaves     = PishachaDemonAttackSaves;
    this->itsDamageList      = PishachaDemonDamageList;
    this->itsAttackModifiers = PishachaDemonAttackModifiers;
    this->itsDifficulty      = PishachaDemonDifficulty;
    this->itsConsequences    = PishachaDemonConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Living Shade Constructor
LivingShade::LivingShade() : Monster(std::string("Living Shade"),
                                     18, // health
                                     12, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     16, // library index
                                     -2, 2, 0, -1, 0, 1) // modifiers
{
    challengeRating = 0;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities LivingShadeAbilities;
              LivingShadeAbilities.reserve(5);

    // declare abilities sequentially
    Ability LivingShadeAbility1("Amorphous");
    Ability LivingShadeAbility2("DarkVision");
    Ability LivingShadeAbility3("ShadowStealth");
    Ability LivingShadeAbility4("SunlightSensitivity");

    // push abilities back in order above
    LivingShadeAbilities.push_back(LivingShadeAbility1);
    LivingShadeAbilities.push_back(LivingShadeAbility2);
    LivingShadeAbilities.push_back(LivingShadeAbility3);
    LivingShadeAbilities.push_back(LivingShadeAbility4);
    this->abilities = LivingShadeAbilities;

    // holders for attack details
    AttackList         LivingShadeAttackList;
    vector<AttackSave> LivingShadeAttackSaves;
    DamageList         LivingShadeDamageList;
    vector<int>        LivingShadeAttackModifiers;
    vector<int>        LivingShadeDifficulty;
    Consequence        LivingShadeConsequences;

    // all attack details
    Attack     LivingShadeAttack1("Shadow Touch");
    int        LivingShadeAttackMod1 = 4;
    DamageDice LivingShadeAttackDamage1 = {2, 0, 0, 0, 0, 0};
    AttackSave LivingShadeAttackSave1 = AttackSave::NONE;
    int        LivingShadeSaveDifficulty1 = 0;
    string     LivingShadeConsequence1("NONE");

    LivingShadeAttackList.push_back     (LivingShadeAttack1);
    LivingShadeAttackModifiers.push_back(LivingShadeAttackMod1);
    LivingShadeDamageList.push_back     (LivingShadeAttackDamage1);
    LivingShadeAttackSaves.push_back    (LivingShadeAttackSave1);
    LivingShadeDifficulty.push_back     (LivingShadeSaveDifficulty1);
    LivingShadeConsequences.push_back   (LivingShadeConsequence1);

    this->itsAttacks         = LivingShadeAttackList;
    this->itsAttackSaves     = LivingShadeAttackSaves;
    this->itsDamageList      = LivingShadeDamageList;
    this->itsAttackModifiers = LivingShadeAttackModifiers;
    this->itsDifficulty      = LivingShadeDifficulty;
    this->itsConsequences    = LivingShadeConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Shadow Ooze Constructor
ShadowOoze::ShadowOoze() : Monster(std::string("Shadow Ooze"),
                                   76, // health
                                   8, // armor class
                                   20, // speed
                                   BASE_ABILITIES,
                                   DEFAULT_ENVIRONMENT,
                                   17, // library index
                                   3, -2, 4, -4, -2, -4) // modifiers
{
    challengeRating = 3;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ShadowOozeAbilities;
              ShadowOozeAbilities.reserve(5);

    // declare abilities sequentially
    Ability ShadowOozeAbility1("Amorphous");
    Ability ShadowOozeAbility2("SpiderClimb");
    Ability ShadowOozeAbility3("BlindSight");
    Ability ShadowOozeAbility4("AuraOfDarkness(Destroys all light 30ft)");
    Ability ShadowOozeAbility5("MultiAttack");

    // push abilities back in order above
    ShadowOozeAbilities.push_back(ShadowOozeAbility1);
    ShadowOozeAbilities.push_back(ShadowOozeAbility2);
    ShadowOozeAbilities.push_back(ShadowOozeAbility3);
    ShadowOozeAbilities.push_back(ShadowOozeAbility4);
    ShadowOozeAbilities.push_back(ShadowOozeAbility5);
    this->abilities = ShadowOozeAbilities;

    // holders for attack details
    AttackList         ShadowOozeAttackList;
    vector<AttackSave> ShadowOozeAttackSaves;
    DamageList         ShadowOozeDamageList;
    vector<int>        ShadowOozeAttackModifiers;
    vector<int>        ShadowOozeDifficulty;
    Consequence        ShadowOozeConsequences;

    // all attack details
    Attack     ShadowOozeAttack1("Pseuopod");
    int        ShadowOozeAttackMod1 = 5;
    DamageDice ShadowOozeAttackDamage1 = {2, 3, 0, 0, 0, 0};
    AttackSave ShadowOozeAttackSave1 = AttackSave::NONE;
    int        ShadowOozeSaveDifficulty1 = 0;
    string     ShadowOozeConsequence1("NONE");

    Attack     ShadowOozeAttack2("SnuffOut");
    int        ShadowOozeAttackMod2 = 100;
    DamageDice ShadowOozeAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave ShadowOozeAttackSave2 = AttackSave::CON;
    int        ShadowOozeSaveDifficulty2 = 100;
    string     ShadowOozeConsequence2("Extinguishes any targeted light within 60ft");

    ShadowOozeAttackList.push_back     (ShadowOozeAttack1);
    ShadowOozeAttackModifiers.push_back(ShadowOozeAttackMod1);
    ShadowOozeDamageList.push_back     (ShadowOozeAttackDamage1);
    ShadowOozeAttackSaves.push_back    (ShadowOozeAttackSave1);
    ShadowOozeDifficulty.push_back     (ShadowOozeSaveDifficulty1);
    ShadowOozeConsequences.push_back   (ShadowOozeConsequence1);

    this->itsAttacks         = ShadowOozeAttackList;
    this->itsAttackSaves     = ShadowOozeAttackSaves;
    this->itsDamageList      = ShadowOozeDamageList;
    this->itsAttackModifiers = ShadowOozeAttackModifiers;
    this->itsDifficulty      = ShadowOozeDifficulty;
    this->itsConsequences    = ShadowOozeConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Shadow Skeleton Constructor
ShadowSkeleton::ShadowSkeleton() : Monster(std::string("ShadowSkeleton"),
                                           52, // health
                                           13, // armor class
                                           30, // speed
                                           BASE_ABILITIES,
                                           DEFAULT_ENVIRONMENT,
                                           18, // library index
                                           0, 3, 2, -1, 0, -1) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::WATER);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ShadowSkeletonAbilities;
              ShadowSkeletonAbilities.reserve(5);

    // declare abilities sequentially
    Ability ShadowSkeletonAbility1("DarkVision");
    Ability ShadowSkeletonAbility2("MultiAttack");
    Ability ShadowSkeletonAbility3("OmniLingual");

    // push abilities back in order above
    ShadowSkeletonAbilities.push_back(ShadowSkeletonAbility1);
    ShadowSkeletonAbilities.push_back(ShadowSkeletonAbility2);
    ShadowSkeletonAbilities.push_back(ShadowSkeletonAbility3);
    this->abilities = ShadowSkeletonAbilities;

    // holders for attack details
    AttackList         ShadowSkeletonAttackList;
    vector<AttackSave> ShadowSkeletonAttackSaves;
    DamageList         ShadowSkeletonDamageList;
    vector<int>        ShadowSkeletonAttackModifiers;
    vector<int>        ShadowSkeletonDifficulty;
    Consequence        ShadowSkeletonConsequences;

    // all attack details
    Attack     ShadowSkeletonAttack1("Scimitar");
    int        ShadowSkeletonAttackMod1 = 5;
    DamageDice ShadowSkeletonAttackDamage1 = {0, 1, 1, 0, 0, 0};
    AttackSave ShadowSkeletonAttackSave1 = AttackSave::NONE;
    int        ShadowSkeletonSaveDifficulty1 = 0;
    string     ShadowSkeletonConsequence1("NONE");

    Attack     ShadowSkeletonAttack2("Finger Darts");
    int        ShadowSkeletonAttackMod2 = 5;
    DamageDice ShadowSkeletonAttackDamage2 = {1, 1, 0, 0, 0, 0};
    AttackSave ShadowSkeletonAttackSave2 = AttackSave::CON;
    int        ShadowSkeletonSaveDifficulty2 = 12;
    string     ShadowSkeletonConsequence2("Surrounded by shadowy aura; until extinguished by a DC12 (by any player), scimitar deals extra 2d6");

    ShadowSkeletonAttackList.push_back     (ShadowSkeletonAttack1);
    ShadowSkeletonAttackModifiers.push_back(ShadowSkeletonAttackMod1);
    ShadowSkeletonDamageList.push_back     (ShadowSkeletonAttackDamage1);
    ShadowSkeletonAttackSaves.push_back    (ShadowSkeletonAttackSave1);
    ShadowSkeletonDifficulty.push_back     (ShadowSkeletonSaveDifficulty1);
    ShadowSkeletonConsequences.push_back   (ShadowSkeletonConsequence1);

    ShadowSkeletonAttackList.push_back     (ShadowSkeletonAttack2);
    ShadowSkeletonAttackModifiers.push_back(ShadowSkeletonAttackMod2);
    ShadowSkeletonDamageList.push_back     (ShadowSkeletonAttackDamage2);
    ShadowSkeletonAttackSaves.push_back    (ShadowSkeletonAttackSave2);
    ShadowSkeletonDifficulty.push_back     (ShadowSkeletonSaveDifficulty2);
    ShadowSkeletonConsequences.push_back   (ShadowSkeletonConsequence2);

    this->itsAttacks         = ShadowSkeletonAttackList;
    this->itsAttackSaves     = ShadowSkeletonAttackSaves;
    this->itsDamageList      = ShadowSkeletonDamageList;
    this->itsAttackModifiers = ShadowSkeletonAttackModifiers;
    this->itsDifficulty      = ShadowSkeletonDifficulty;
    this->itsConsequences    = ShadowSkeletonConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Weirding Scroll Constructor
WeirdingScroll::WeirdingScroll() : Monster(std::string("Weirding Scroll"),
                                           27, // health
                                           10, // armor class
                                           10, // speed
                                           BASE_ABILITIES,
                                           DEFAULT_ENVIRONMENT,
                                           19, // library index
                                           -5, 0, 2, 3, 0, -1) // modifiers
{
    challengeRating = 1;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities WeirdingScrollAbilities;
              WeirdingScrollAbilities.reserve(5);

    // declare abilities sequentially
    Ability WeirdingScrollAbility1("BlindSight");
    Ability WeirdingScrollAbility2("OmniLingual");
    Ability WeirdingScrollAbility3("AntiMagicSusceptibility");
    Ability WeirdingScrollAbility4("FalseAppearance");

    // push abilities back in order above
    WeirdingScrollAbilities.push_back(WeirdingScrollAbility1);
    WeirdingScrollAbilities.push_back(WeirdingScrollAbility2);
    WeirdingScrollAbilities.push_back(WeirdingScrollAbility3);
    WeirdingScrollAbilities.push_back(WeirdingScrollAbility4);
    this->abilities = WeirdingScrollAbilities;

    // holders for attack details
    AttackList         WeirdingScrollAttackList;
    vector<AttackSave> WeirdingScrollAttackSaves;
    DamageList         WeirdingScrollDamageList;
    vector<int>        WeirdingScrollAttackModifiers;
    vector<int>        WeirdingScrollDifficulty;
    Consequence        WeirdingScrollConsequences;

    // all attack details
    Attack     WeirdingScrollAttack1("Tendril of Light");
    int        WeirdingScrollAttackMod1 = 5;
    DamageDice WeirdingScrollAttackDamage1 = {0, 2, 0, 0, 0, 0};
    AttackSave WeirdingScrollAttackSave1 = AttackSave::NONE;
    int        WeirdingScrollSaveDifficulty1 = 0;
    string     WeirdingScrollConsequence1("NONE");

    Attack     WeirdingScrollAttack2("Dominate");
    int        WeirdingScrollAttackMod2 = 100;
    DamageDice WeirdingScrollAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave WeirdingScrollAttackSave2 = AttackSave::WIS;
    int        WeirdingScrollSaveDifficulty2 = 13;
    string     WeirdingScrollConsequence2("Charmed for 1 hour. Obeys Scroll's command to the best of their ability. New save DC13 when damage taken.");

    WeirdingScrollAttackList.push_back     (WeirdingScrollAttack1);
    WeirdingScrollAttackModifiers.push_back(WeirdingScrollAttackMod1);
    WeirdingScrollDamageList.push_back     (WeirdingScrollAttackDamage1);
    WeirdingScrollAttackSaves.push_back    (WeirdingScrollAttackSave1);
    WeirdingScrollDifficulty.push_back     (WeirdingScrollSaveDifficulty1);
    WeirdingScrollConsequences.push_back   (WeirdingScrollConsequence1);

    WeirdingScrollAttackList.push_back     (WeirdingScrollAttack2);
    WeirdingScrollAttackModifiers.push_back(WeirdingScrollAttackMod2);
    WeirdingScrollDamageList.push_back     (WeirdingScrollAttackDamage2);
    WeirdingScrollAttackSaves.push_back    (WeirdingScrollAttackSave2);
    WeirdingScrollDifficulty.push_back     (WeirdingScrollSaveDifficulty2);
    WeirdingScrollConsequences.push_back   (WeirdingScrollConsequence2);

    this->itsAttacks         = WeirdingScrollAttackList;
    this->itsAttackSaves     = WeirdingScrollAttackSaves;
    this->itsDamageList      = WeirdingScrollDamageList;
    this->itsAttackModifiers = WeirdingScrollAttackModifiers;
    this->itsDifficulty      = WeirdingScrollDifficulty;
    this->itsConsequences    = WeirdingScrollConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Zoog Constructor
Zoog::Zoog() : Monster(std::string("Zoog"),
                                     5, // health
                                     13, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     20, // library index
                                     -4, 3, 1, 0, 0, -1) // modifiers
{
    challengeRating = 0;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ZoogAbilities;
              ZoogAbilities.reserve(5);

    // declare abilities sequentially
    Ability ZoogAbility1("DarkVision");

    // push abilities back in order above
    ZoogAbilities.push_back(ZoogAbility1);
    this->abilities = ZoogAbilities;

    // holders for attack details
    AttackList         ZoogAttackList;
    vector<AttackSave> ZoogAttackSaves;
    DamageList         ZoogDamageList;
    vector<int>        ZoogAttackModifiers;
    vector<int>        ZoogDifficulty;
    Consequence        ZoogConsequences;

    // all attack details
    Attack     ZoogAttack1("Bite");
    int        ZoogAttackMod1 = 5;
    DamageDice ZoogAttackDamage1 = {1, 0, 0, 0, 0, 0};
    AttackSave ZoogAttackSave1 = AttackSave::NONE;
    int        ZoogSaveDifficulty1 = 0;
    string     ZoogConsequence1("NONE");

    ZoogAttackList.push_back     (ZoogAttack1);
    ZoogAttackModifiers.push_back(ZoogAttackMod1);
    ZoogDamageList.push_back     (ZoogAttackDamage1);
    ZoogAttackSaves.push_back    (ZoogAttackSave1);
    ZoogDifficulty.push_back     (ZoogSaveDifficulty1);
    ZoogConsequences.push_back   (ZoogConsequence1);

    this->itsAttacks         = ZoogAttackList;
    this->itsAttackSaves     = ZoogAttackSaves;
    this->itsDamageList      = ZoogDamageList;
    this->itsAttackModifiers = ZoogAttackModifiers;
    this->itsDifficulty      = ZoogDifficulty;
    this->itsConsequences    = ZoogConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Centaur Constructor
Centaur::Centaur() : Monster(std::string("Centaur"),
                                     45, // health
                                     12, // armor class
                                     50, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     21, // library index
                                     4, 2, 2, -1, 1, 0) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities CentaurAbilities;
              CentaurAbilities.reserve(5);

    // declare abilities sequentially
    Ability CentaurAbility1("ifChargingOpponentUsingPikeExtra3d6");
    Ability CentaurAbility2("MultiAttack");
    Ability CentaurAbility3("PikeAndHooves");
    Ability CentaurAbility4("or2LongBow");

    // push abilities back in order above
    CentaurAbilities.push_back(CentaurAbility1);
    CentaurAbilities.push_back(CentaurAbility2);
    CentaurAbilities.push_back(CentaurAbility3);
    CentaurAbilities.push_back(CentaurAbility4);
    this->abilities = CentaurAbilities;

    // holders for attack details
    AttackList         CentaurAttackList;
    vector<AttackSave> CentaurAttackSaves;
    DamageList         CentaurDamageList;
    vector<int>        CentaurAttackModifiers;
    vector<int>        CentaurDifficulty;
    Consequence        CentaurConsequences;

    // all attack details
    Attack     CentaurAttack1("Pike");
    int        CentaurAttackMod1 = 6;
    DamageDice CentaurAttackDamage1 = {0, 1, 0, 1, 0, 0};
    AttackSave CentaurAttackSave1 = AttackSave::NONE;
    int        CentaurSaveDifficulty1 = 0;
    string     CentaurConsequence1("none");

    Attack     CentaurAttack2("Hooves");
    int        CentaurAttackMod2 = 6;
    DamageDice CentaurAttackDamage2 = {1, 2, 0, 0, 0, 0};
    AttackSave CentaurAttackSave2 = AttackSave::NONE;
    int        CentaurSaveDifficulty2 = 0;
    string     CentaurConsequence2("none");

    Attack     CentaurAttack3("Longbow");
    int        CentaurAttackMod3 = 4;
    DamageDice CentaurAttackDamage3 = {1, 0, 1, 0, 0, 0};
    AttackSave CentaurAttackSave3 = AttackSave::NONE;
    int        CentaurSaveDifficulty3 = 0;
    string     CentaurConsequence3("none");

    CentaurAttackList.push_back     (CentaurAttack1);
    CentaurAttackModifiers.push_back(CentaurAttackMod1);
    CentaurDamageList.push_back     (CentaurAttackDamage1);
    CentaurAttackSaves.push_back    (CentaurAttackSave1);
    CentaurDifficulty.push_back     (CentaurSaveDifficulty1);
    CentaurConsequences.push_back   (CentaurConsequence1);

    CentaurAttackList.push_back     (CentaurAttack2);
    CentaurAttackModifiers.push_back(CentaurAttackMod2);
    CentaurDamageList.push_back     (CentaurAttackDamage2);
    CentaurAttackSaves.push_back    (CentaurAttackSave2);
    CentaurDifficulty.push_back     (CentaurSaveDifficulty2);
    CentaurConsequences.push_back   (CentaurConsequence2);

    CentaurAttackList.push_back     (CentaurAttack3);
    CentaurAttackModifiers.push_back(CentaurAttackMod3);
    CentaurDamageList.push_back     (CentaurAttackDamage3);
    CentaurAttackSaves.push_back    (CentaurAttackSave3);
    CentaurDifficulty.push_back     (CentaurSaveDifficulty3);
    CentaurConsequences.push_back   (CentaurConsequence3);

    this->itsAttacks         = CentaurAttackList;
    this->itsAttackSaves     = CentaurAttackSaves;
    this->itsDamageList      = CentaurDamageList;
    this->itsAttackModifiers = CentaurAttackModifiers;
    this->itsDifficulty      = CentaurDifficulty;
    this->itsConsequences    = CentaurConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// ShamblingMound Constructor
ShamblingMound::ShamblingMound() : Monster(std::string("ShamblingMound"),
                                     136, // health
                                     15, // armor class
                                     20, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     22, // library index
                                     4, -1, 3, -3, 0, -3) // modifiers
{
    challengeRating = 5;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::WATER);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ShamblingMoundAbilities;
              ShamblingMoundAbilities.reserve(5);

    // declare abilities sequentially
    Ability ShamblingMoundAbility1("Restistant to ColdFire");
    Ability ShamblingMoundAbility2("ImmuneTo LtngBlndDfnExh");
    Ability ShamblingMoundAbility3("Blindsight");
    Ability ShamblingMoundAbility4("AbsorbsLightningDamage");
    Ability ShamblingMoundAbility5("MultiAttack 2 slams grappled and uses engulf if hit");

    // push abilities back in order above
    ShamblingMoundAbilities.push_back(ShamblingMoundAbility1);
    ShamblingMoundAbilities.push_back(ShamblingMoundAbility2);
    ShamblingMoundAbilities.push_back(ShamblingMoundAbility3);
    ShamblingMoundAbilities.push_back(ShamblingMoundAbility4);
    ShamblingMoundAbilities.push_back(ShamblingMoundAbility5);
    this->abilities = ShamblingMoundAbilities;

    // holders for attack details
    AttackList         ShamblingMoundAttackList;
    vector<AttackSave> ShamblingMoundAttackSaves;
    DamageList         ShamblingMoundDamageList;
    vector<int>        ShamblingMoundAttackModifiers;
    vector<int>        ShamblingMoundDifficulty;
    Consequence        ShamblingMoundConsequences;

    // all attack details
    Attack     ShamblingMoundAttack1("Slam");
    int        ShamblingMoundAttackMod1 = 7;
    DamageDice ShamblingMoundAttackDamage1 = {1, 0, 2, 0, 0, 0};
    AttackSave ShamblingMoundAttackSave1 = AttackSave::NONE;
    int        ShamblingMoundSaveDifficulty1 = 0;
    string     ShamblingMoundConsequence1("none");

    Attack     ShamblingMoundAttack2("Engulf (only on grappled, one at a time)");
    int        ShamblingMoundAttackMod2 = 100;
    DamageDice ShamblingMoundAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave ShamblingMoundAttackSave2 = AttackSave::CON;
    int        ShamblingMoundSaveDifficulty2 = 100;
    string     ShamblingMoundConsequence2("BeginningOfMoundsTurn, if Fail DC 14 take 2d8+4");

    ShamblingMoundAttackList.push_back     (ShamblingMoundAttack1);
    ShamblingMoundAttackModifiers.push_back(ShamblingMoundAttackMod1);
    ShamblingMoundDamageList.push_back     (ShamblingMoundAttackDamage1);
    ShamblingMoundAttackSaves.push_back    (ShamblingMoundAttackSave1);
    ShamblingMoundDifficulty.push_back     (ShamblingMoundSaveDifficulty1);
    ShamblingMoundConsequences.push_back   (ShamblingMoundConsequence1);

    ShamblingMoundAttackList.push_back     (ShamblingMoundAttack2);
    ShamblingMoundAttackModifiers.push_back(ShamblingMoundAttackMod2);
    ShamblingMoundDamageList.push_back     (ShamblingMoundAttackDamage2);
    ShamblingMoundAttackSaves.push_back    (ShamblingMoundAttackSave2);
    ShamblingMoundDifficulty.push_back     (ShamblingMoundSaveDifficulty2);
    ShamblingMoundConsequences.push_back   (ShamblingMoundConsequence2);

    this->itsAttacks         = ShamblingMoundAttackList;
    this->itsAttackSaves     = ShamblingMoundAttackSaves;
    this->itsDamageList      = ShamblingMoundDamageList;
    this->itsAttackModifiers = ShamblingMoundAttackModifiers;
    this->itsDifficulty      = ShamblingMoundDifficulty;
    this->itsConsequences    = ShamblingMoundConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Will_o_Wisp Constructor
Will_o_Wisp::Will_o_Wisp() : Monster(std::string("Will_o_Wisp"),
                                     22, // health
                                     19, // armor class
                                     50, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     23, // library index
                                     -5, 9, 0, 1, 2, 0) // modifiers
{
    challengeRating = 2;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities Will_o_WispAbilities;
              Will_o_WispAbilities.reserve(5);

    // declare abilities sequentially
    Ability Will_o_WispAbility1("Resistant to AcidColdFireNecThndrBldgPrcSlsh");
    Ability Will_o_WispAbility2("Immune LtngExhGrplPrzPsnProneRestrUncon");
    Ability Will_o_WispAbility3("DarkVision");
    Ability Will_o_WispAbility4("VariableIllumination (5-20ft)");

    // push abilities back in order above
    Will_o_WispAbilities.push_back(Will_o_WispAbility1);
    Will_o_WispAbilities.push_back(Will_o_WispAbility2);
    Will_o_WispAbilities.push_back(Will_o_WispAbility3);
    Will_o_WispAbilities.push_back(Will_o_WispAbility4);
    this->abilities = Will_o_WispAbilities;

    // holders for attack details
    AttackList         Will_o_WispAttackList;
    vector<AttackSave> Will_o_WispAttackSaves;
    DamageList         Will_o_WispDamageList;
    vector<int>        Will_o_WispAttackModifiers;
    vector<int>        Will_o_WispDifficulty;
    Consequence        Will_o_WispConsequences;

    // all attack details
    Attack     Will_o_WispAttack1("Shock");
    int        Will_o_WispAttackMod1 = 4;
    DamageDice Will_o_WispAttackDamage1 = {0, 0, 2, 0, 0, 0};
    AttackSave Will_o_WispAttackSave1 = AttackSave::NONE;
    int        Will_o_WispSaveDifficulty1 = 0;
    string     Will_o_WispConsequence1("none");

    Attack     Will_o_WispAttack2("Consume Life (on targets w zero health)");
    int        Will_o_WispAttackMod2 = 100;
    DamageDice Will_o_WispAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave Will_o_WispAttackSave2 = AttackSave::CON;
    int        Will_o_WispSaveDifficulty2 = 10;
    string     Will_o_WispConsequence2("Target is DEAD, and wisp regains 10hp");

    Attack     Will_o_WispAttack3("Invisibility");
    int        Will_o_WispAttackMod3 = 100;
    DamageDice Will_o_WispAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave Will_o_WispAttackSave3 = AttackSave::NONE;
    int        Will_o_WispSaveDifficulty3 = 100;
    string     Will_o_WispConsequence3("Becomes Invisible until attacks or consumes life");

    Will_o_WispAttackList.push_back     (Will_o_WispAttack1);
    Will_o_WispAttackModifiers.push_back(Will_o_WispAttackMod1);
    Will_o_WispDamageList.push_back     (Will_o_WispAttackDamage1);
    Will_o_WispAttackSaves.push_back    (Will_o_WispAttackSave1);
    Will_o_WispDifficulty.push_back     (Will_o_WispSaveDifficulty1);
    Will_o_WispConsequences.push_back   (Will_o_WispConsequence1);

    Will_o_WispAttackList.push_back     (Will_o_WispAttack2);
    Will_o_WispAttackModifiers.push_back(Will_o_WispAttackMod2);
    Will_o_WispDamageList.push_back     (Will_o_WispAttackDamage2);
    Will_o_WispAttackSaves.push_back    (Will_o_WispAttackSave2);
    Will_o_WispDifficulty.push_back     (Will_o_WispSaveDifficulty2);
    Will_o_WispConsequences.push_back   (Will_o_WispConsequence2);

    Will_o_WispAttackList.push_back     (Will_o_WispAttack3);
    Will_o_WispAttackModifiers.push_back(Will_o_WispAttackMod3);
    Will_o_WispDamageList.push_back     (Will_o_WispAttackDamage3);
    Will_o_WispAttackSaves.push_back    (Will_o_WispAttackSave3);
    Will_o_WispDifficulty.push_back     (Will_o_WispSaveDifficulty3);
    Will_o_WispConsequences.push_back   (Will_o_WispConsequence3);

    this->itsAttacks         = Will_o_WispAttackList;
    this->itsAttackSaves     = Will_o_WispAttackSaves;
    this->itsDamageList      = Will_o_WispDamageList;
    this->itsAttackModifiers = Will_o_WispAttackModifiers;
    this->itsDifficulty      = Will_o_WispDifficulty;
    this->itsConsequences    = Will_o_WispConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Neophron Constructor
Neophron::Neophron() : Monster(std::string("Neophron"),
                                     114, // health
                                     16, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     24, // library index
                                     4, 3, 5, -1, 3, 2) // modifiers
{
    challengeRating = 8;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities NeophronAbilities;
              NeophronAbilities.reserve(5);

    // declare abilities sequentially
    Ability NeophronAbility1("ResistantTo ColdFireLtngBldgPrcSlsh");
    Ability NeophronAbility2("ImmuneTo Psn");
    Ability NeophronAbility3("DarkVision and MultiAttack");
    Ability NeophronAbility4("ShapeChanger (Giant Vulture)");
    Ability NeophronAbility5("MagicResistance");

    // push abilities back in order above
    NeophronAbilities.push_back(NeophronAbility1);
    NeophronAbilities.push_back(NeophronAbility2);
    NeophronAbilities.push_back(NeophronAbility3);
    NeophronAbilities.push_back(NeophronAbility4);
    this->abilities = NeophronAbilities;

    // holders for attack details
    AttackList         NeophronAttackList;
    vector<AttackSave> NeophronAttackSaves;
    DamageList         NeophronDamageList;
    vector<int>        NeophronAttackModifiers;
    vector<int>        NeophronDifficulty;
    Consequence        NeophronConsequences;

    // all attack details
    Attack     NeophronAttack1("Bite");
    int        NeophronAttackMod1 = 7;
    DamageDice NeophronAttackDamage1 = {1, 0, 0, 2, 0, 0};
    AttackSave NeophronAttackSave1 = AttackSave::DEX;
    int        NeophronSaveDifficulty1 = 16;
    string     NeophronConsequence1("SWALLOWED - 4d6eachTurn - ifDiesBecomesGhast - 20dmgOneTurn Regurgitates");

    Attack     NeophronAttack2("Claw");
    int        NeophronAttackMod2 = 7;
    DamageDice NeophronAttackDamage2 = {1, 2, 0, 0, 0, 0};
    AttackSave NeophronAttackSave2 = AttackSave::CON;
    int        NeophronSaveDifficulty2 = 16;
    string     NeophronConsequence2("Poisoned until end of next turn");

    NeophronAttackList.push_back     (NeophronAttack1);
    NeophronAttackModifiers.push_back(NeophronAttackMod1);
    NeophronDamageList.push_back     (NeophronAttackDamage1);
    NeophronAttackSaves.push_back    (NeophronAttackSave1);
    NeophronDifficulty.push_back     (NeophronSaveDifficulty1);
    NeophronConsequences.push_back   (NeophronConsequence1);

    NeophronAttackList.push_back     (NeophronAttack2);
    NeophronAttackModifiers.push_back(NeophronAttackMod2);
    NeophronDamageList.push_back     (NeophronAttackDamage2);
    NeophronAttackSaves.push_back    (NeophronAttackSave2);
    NeophronDifficulty.push_back     (NeophronSaveDifficulty2);
    NeophronConsequences.push_back   (NeophronConsequence2);

    this->itsAttacks         = NeophronAttackList;
    this->itsAttackSaves     = NeophronAttackSaves;
    this->itsDamageList      = NeophronDamageList;
    this->itsAttackModifiers = NeophronAttackModifiers;
    this->itsDifficulty      = NeophronDifficulty;
    this->itsConsequences    = NeophronConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// ExplodingToad Constructor
ExplodingToad::ExplodingToad() : Monster(std::string("ExplodingToad"),
                                     2, // health
                                     12, // armor class
                                     20, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     25, // library index
                                     -5, 1, 0, -3, -1, -4) // modifiers
{
    challengeRating = 1/4;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::WATER);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ExplodingToadAbilities;
              ExplodingToadAbilities.reserve(5);

    // declare abilities sequentially
    Ability ExplodingToadAbility1("Amphibious");
    Ability ExplodingToadAbility2("RangedAttacksHaveDisadvantage");
    Ability ExplodingToadAbility3("CanChooseToTakeFireDamage, otherwise immune");
    Ability ExplodingToadAbility4("WhenKilled, Explodes - all in 10ft rad make DC11 Dex or take 3d6 fire");

    // push abilities back in order above
    ExplodingToadAbilities.push_back(ExplodingToadAbility1);
    ExplodingToadAbilities.push_back(ExplodingToadAbility2);
    ExplodingToadAbilities.push_back(ExplodingToadAbility3);
    ExplodingToadAbilities.push_back(ExplodingToadAbility4);
    this->abilities = ExplodingToadAbilities;

    // holders for attack details
    AttackList         ExplodingToadAttackList;
    vector<AttackSave> ExplodingToadAttackSaves;
    DamageList         ExplodingToadDamageList;
    vector<int>        ExplodingToadAttackModifiers;
    vector<int>        ExplodingToadDifficulty;
    Consequence        ExplodingToadConsequences;

    // all attack details
    Attack     ExplodingToadAttack1("Bite");
    int        ExplodingToadAttackMod1 = 3;
    DamageDice ExplodingToadAttackDamage1 = {2, 0, 0, 0, 0, 0};
    AttackSave ExplodingToadAttackSave1 = AttackSave::NONE;
    int        ExplodingToadSaveDifficulty1 = 0;
    string     ExplodingToadConsequence1("none");

    ExplodingToadAttackList.push_back     (ExplodingToadAttack1);
    ExplodingToadAttackModifiers.push_back(ExplodingToadAttackMod1);
    ExplodingToadDamageList.push_back     (ExplodingToadAttackDamage1);
    ExplodingToadAttackSaves.push_back    (ExplodingToadAttackSave1);
    ExplodingToadDifficulty.push_back     (ExplodingToadSaveDifficulty1);
    ExplodingToadConsequences.push_back   (ExplodingToadConsequence1);

    this->itsAttacks         = ExplodingToadAttackList;
    this->itsAttackSaves     = ExplodingToadAttackSaves;
    this->itsDamageList      = ExplodingToadDamageList;
    this->itsAttackModifiers = ExplodingToadAttackModifiers;
    this->itsDifficulty      = ExplodingToadDifficulty;
    this->itsConsequences    = ExplodingToadConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// DoomGolem Constructor
DoomGolem::DoomGolem() : Monster(std::string("DoomGolem"),
                                     153, // health
                                     17, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     26, // library index
                                     7, 1, 3, -4, 0, -5) // modifiers
{
    challengeRating = 10;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities DoomGolemAbilities;
              DoomGolemAbilities.reserve(5);

    // declare abilities sequentially
    Ability DoomGolemAbility1("Immune to ColdPoisonPsychic - DarkVision");
    Ability DoomGolemAbility2("Immutable Form + Magic Resistance");
    Ability DoomGolemAbility3("MagicWeapons");
    Ability DoomGolemAbility4("MultiAttack");

    // push abilities back in order above
    DoomGolemAbilities.push_back(DoomGolemAbility1);
    DoomGolemAbilities.push_back(DoomGolemAbility2);
    DoomGolemAbilities.push_back(DoomGolemAbility3);
    DoomGolemAbilities.push_back(DoomGolemAbility4);
    this->abilities = DoomGolemAbilities;

    // holders for attack details
    AttackList         DoomGolemAttackList;
    vector<AttackSave> DoomGolemAttackSaves;
    DamageList         DoomGolemDamageList;
    vector<int>        DoomGolemAttackModifiers;
    vector<int>        DoomGolemDifficulty;
    Consequence        DoomGolemConsequences;

    // all attack details
    Attack     DoomGolemAttack1("Bite");
    int        DoomGolemAttackMod1 = 11;
    DamageDice DoomGolemAttackDamage1 = {0, 0, 1, 3, 0, 0};
    AttackSave DoomGolemAttackSave1 = AttackSave::NONE;
    int        DoomGolemSaveDifficulty1 = 0;
    string     DoomGolemConsequence1("none");

    Attack     DoomGolemAttack2("Doom Claw");
    int        DoomGolemAttackMod2 = 11;
    DamageDice DoomGolemAttackDamage2 = {0, 4, 1, 0, 0, 0};
    AttackSave DoomGolemAttackSave2 = AttackSave::NONE;
    int        DoomGolemSaveDifficulty2 = 0;
    string     DoomGolemConsequence2("none");

    Attack     DoomGolemAttack3("Wind of Boreas");
    int        DoomGolemAttackMod3 = 100;
    DamageDice DoomGolemAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave DoomGolemAttackSave3 = AttackSave::CON;
    int        DoomGolemSaveDifficulty3 = 100;
    string     DoomGolemConsequence3("DC 16 - 11d6 cold or half if successful");

    Attack     DoomGolemAttack4("Fear Aura");
    int        DoomGolemAttackMod4 = 100;
    DamageDice DoomGolemAttackDamage4 = {0, 0, 0, 0, 0, 0};
    AttackSave DoomGolemAttackSave4 = AttackSave::WIS;
    int        DoomGolemSaveDifficulty4 = 15;
    string     DoomGolemConsequence4("FrightenedUntilNextTurn");

    DoomGolemAttackList.push_back     (DoomGolemAttack1);
    DoomGolemAttackModifiers.push_back(DoomGolemAttackMod1);
    DoomGolemDamageList.push_back     (DoomGolemAttackDamage1);
    DoomGolemAttackSaves.push_back    (DoomGolemAttackSave1);
    DoomGolemDifficulty.push_back     (DoomGolemSaveDifficulty1);
    DoomGolemConsequences.push_back   (DoomGolemConsequence1);

    DoomGolemAttackList.push_back     (DoomGolemAttack2);
    DoomGolemAttackModifiers.push_back(DoomGolemAttackMod2);
    DoomGolemDamageList.push_back     (DoomGolemAttackDamage2);
    DoomGolemAttackSaves.push_back    (DoomGolemAttackSave2);
    DoomGolemDifficulty.push_back     (DoomGolemSaveDifficulty2);
    DoomGolemConsequences.push_back   (DoomGolemConsequence2);

    DoomGolemAttackList.push_back     (DoomGolemAttack3);
    DoomGolemAttackModifiers.push_back(DoomGolemAttackMod3);
    DoomGolemDamageList.push_back     (DoomGolemAttackDamage3);
    DoomGolemAttackSaves.push_back    (DoomGolemAttackSave3);
    DoomGolemDifficulty.push_back     (DoomGolemSaveDifficulty3);
    DoomGolemConsequences.push_back   (DoomGolemConsequence3);

    DoomGolemAttackList.push_back     (DoomGolemAttack4);
    DoomGolemAttackModifiers.push_back(DoomGolemAttackMod4);
    DoomGolemDamageList.push_back     (DoomGolemAttackDamage4);
    DoomGolemAttackSaves.push_back    (DoomGolemAttackSave4);
    DoomGolemDifficulty.push_back     (DoomGolemSaveDifficulty4);
    DoomGolemConsequences.push_back   (DoomGolemConsequence4);

    this->itsAttacks         = DoomGolemAttackList;
    this->itsAttackSaves     = DoomGolemAttackSaves;
    this->itsDamageList      = DoomGolemDamageList;
    this->itsAttackModifiers = DoomGolemAttackModifiers;
    this->itsDifficulty      = DoomGolemDifficulty;
    this->itsConsequences    = DoomGolemConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// GoliathLongLegs Constructor
GoliathLongLegs::GoliathLongLegs() : Monster(std::string("GoliathLongLegs"),
                                     162, // health
                                     16, // armor class
                                     20, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     27, // library index
                                     4, 2, 3, -3, 1, -4) // modifiers
{
    challengeRating = 7;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities GoliathLongLegsAbilities;
              GoliathLongLegsAbilities.reserve(5);

    // declare abilities sequentially
    Ability GoliathLongLegsAbility1("Immune to PoisonCharmFright + DarkVision + MultiAttack");
    Ability GoliathLongLegsAbility2("Expansive - smaller creatures can travel through safely");
    Ability GoliathLongLegsAbility3("FalseAppearance + ForestCamo (adv on stealth checks in forests)");
    Ability GoliathLongLegsAbility4("VulnerableLegs: 20+ /turn loses leg; if <4 legs, DC13 CON or prone");

    // push abilities back in order above
    GoliathLongLegsAbilities.push_back(GoliathLongLegsAbility1);
    GoliathLongLegsAbilities.push_back(GoliathLongLegsAbility2);
    GoliathLongLegsAbilities.push_back(GoliathLongLegsAbility3);
    GoliathLongLegsAbilities.push_back(GoliathLongLegsAbility4);
    this->abilities = GoliathLongLegsAbilities;

    // holders for attack details
    AttackList         GoliathLongLegsAttackList;
    vector<AttackSave> GoliathLongLegsAttackSaves;
    DamageList         GoliathLongLegsDamageList;
    vector<int>        GoliathLongLegsAttackModifiers;
    vector<int>        GoliathLongLegsDifficulty;
    Consequence        GoliathLongLegsConsequences;

    // all attack details
    Attack     GoliathLongLegsAttack1("Bite");
    int        GoliathLongLegsAttackMod1 = 7;
    DamageDice GoliathLongLegsAttackDamage1 = {1, 0, 1, 0, 0, 0};
    AttackSave GoliathLongLegsAttackSave1 = AttackSave::CON;
    int        GoliathLongLegsSaveDifficulty1 = 15;
    string     GoliathLongLegsConsequence1("2d8 poison or half; if 'killed', paralyzed 1 hour after stabilized");

    Attack     GoliathLongLegsAttack2("Leg");
    int        GoliathLongLegsAttackMod2 = 7;
    DamageDice GoliathLongLegsAttackDamage2 = {1, 1, 0, 0, 0, 0};
    AttackSave GoliathLongLegsAttackSave2 = AttackSave::NONE;
    int        GoliathLongLegsSaveDifficulty2 = 0;
    string     GoliathLongLegsConsequence2("none");

    Attack     GoliathLongLegsAttack3("Paralytic Web");
    int        GoliathLongLegsAttackMod3 = 5;
    DamageDice GoliathLongLegsAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave GoliathLongLegsAttackSave3 = AttackSave::CON;
    int        GoliathLongLegsSaveDifficulty3 = 15;
    string     GoliathLongLegsConsequence3("Prlz and webbed; action DC15 STR to break free; webbing can be attacked");

    Attack     GoliathLongLegsAttack4("Reel (when creature in Web)");
    int        GoliathLongLegsAttackMod4 = 100;
    DamageDice GoliathLongLegsAttackDamage4 = {0, 0, 0, 0, 0, 0};
    AttackSave GoliathLongLegsAttackSave4 = AttackSave::CON;
    int        GoliathLongLegsSaveDifficulty4 = 100;
    string     GoliathLongLegsConsequence4("Pulled 30 feet to Goliath LL; if w/in 10ft, bonus action BITE");

    GoliathLongLegsAttackList.push_back     (GoliathLongLegsAttack1);
    GoliathLongLegsAttackModifiers.push_back(GoliathLongLegsAttackMod1);
    GoliathLongLegsDamageList.push_back     (GoliathLongLegsAttackDamage1);
    GoliathLongLegsAttackSaves.push_back    (GoliathLongLegsAttackSave1);
    GoliathLongLegsDifficulty.push_back     (GoliathLongLegsSaveDifficulty1);
    GoliathLongLegsConsequences.push_back   (GoliathLongLegsConsequence1);

    GoliathLongLegsAttackList.push_back     (GoliathLongLegsAttack2);
    GoliathLongLegsAttackModifiers.push_back(GoliathLongLegsAttackMod2);
    GoliathLongLegsDamageList.push_back     (GoliathLongLegsAttackDamage2);
    GoliathLongLegsAttackSaves.push_back    (GoliathLongLegsAttackSave2);
    GoliathLongLegsDifficulty.push_back     (GoliathLongLegsSaveDifficulty2);
    GoliathLongLegsConsequences.push_back   (GoliathLongLegsConsequence2);

    GoliathLongLegsAttackList.push_back     (GoliathLongLegsAttack3);
    GoliathLongLegsAttackModifiers.push_back(GoliathLongLegsAttackMod3);
    GoliathLongLegsDamageList.push_back     (GoliathLongLegsAttackDamage3);
    GoliathLongLegsAttackSaves.push_back    (GoliathLongLegsAttackSave3);
    GoliathLongLegsDifficulty.push_back     (GoliathLongLegsSaveDifficulty3);
    GoliathLongLegsConsequences.push_back   (GoliathLongLegsConsequence3);

    GoliathLongLegsAttackList.push_back     (GoliathLongLegsAttack4);
    GoliathLongLegsAttackModifiers.push_back(GoliathLongLegsAttackMod4);
    GoliathLongLegsDamageList.push_back     (GoliathLongLegsAttackDamage4);
    GoliathLongLegsAttackSaves.push_back    (GoliathLongLegsAttackSave4);
    GoliathLongLegsDifficulty.push_back     (GoliathLongLegsSaveDifficulty4);
    GoliathLongLegsConsequences.push_back   (GoliathLongLegsConsequence4);

    this->itsAttacks         = GoliathLongLegsAttackList;
    this->itsAttackSaves     = GoliathLongLegsAttackSaves;
    this->itsDamageList      = GoliathLongLegsDamageList;
    this->itsAttackModifiers = GoliathLongLegsAttackModifiers;
    this->itsDifficulty      = GoliathLongLegsDifficulty;
    this->itsConsequences    = GoliathLongLegsConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// Jinmenju Constructor
Jinmenju::Jinmenju() : Monster(std::string("Jinmenju"),
                                     126, // health
                                     14, // armor class
                                     0, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     28, // library index
                                     3, -5, 4, 3, -1, 6) // modifiers
{
    challengeRating = 9;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::TOWN);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities JinmenjuAbilities;
              JinmenjuAbilities.reserve(5);

    // declare abilities sequentially
    Ability JinmenjuAbility1("Immune to BldgPrcSlsh(nonMagic) ExhProne");
    Ability JinmenjuAbility2("Roots Can Burrow 120ft and attack as though the tree was there");
    Ability JinmenjuAbility3("LaughingFruit - DC16 WIS or fall prone (laughter)");
    Ability JinmenjuAbility4("MultiAttack");

    // push abilities back in order above
    JinmenjuAbilities.push_back(JinmenjuAbility1);
    JinmenjuAbilities.push_back(JinmenjuAbility2);
    JinmenjuAbilities.push_back(JinmenjuAbility3);
    JinmenjuAbilities.push_back(JinmenjuAbility4);
    this->abilities = JinmenjuAbilities;

    // holders for attack details
    AttackList         JinmenjuAttackList;
    vector<AttackSave> JinmenjuAttackSaves;
    DamageList         JinmenjuDamageList;
    vector<int>        JinmenjuAttackModifiers;
    vector<int>        JinmenjuDifficulty;
    Consequence        JinmenjuConsequences;

    // all attack details
    Attack     JinmenjuAttack1("Root");
    int        JinmenjuAttackMod1 = 7;
    DamageDice JinmenjuAttackDamage1 = {1, 4, 0, 2, 0, 0};
    AttackSave JinmenjuAttackSave1 = AttackSave::NONE;
    int        JinmenjuSaveDifficulty1 = 0;
    string     JinmenjuConsequence1("none");

    Attack     JinmenjuAttack2("Mirthful Miasma (cost 2 actions)");
    int        JinmenjuAttackMod2 = 100;
    DamageDice JinmenjuAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave JinmenjuAttackSave2 = AttackSave::CON;
    int        JinmenjuSaveDifficulty2 = 100;
    string     JinmenjuConsequence2("PUFF OF PURPLE GAS - DC16 else incapacitated with laughter for 1 minute");

    JinmenjuAttackList.push_back     (JinmenjuAttack1);
    JinmenjuAttackModifiers.push_back(JinmenjuAttackMod1);
    JinmenjuDamageList.push_back     (JinmenjuAttackDamage1);
    JinmenjuAttackSaves.push_back    (JinmenjuAttackSave1);
    JinmenjuDifficulty.push_back     (JinmenjuSaveDifficulty1);
    JinmenjuConsequences.push_back   (JinmenjuConsequence1);

    JinmenjuAttackList.push_back     (JinmenjuAttack2);
    JinmenjuAttackModifiers.push_back(JinmenjuAttackMod2);
    JinmenjuDamageList.push_back     (JinmenjuAttackDamage2);
    JinmenjuAttackSaves.push_back    (JinmenjuAttackSave2);
    JinmenjuDifficulty.push_back     (JinmenjuSaveDifficulty2);
    JinmenjuConsequences.push_back   (JinmenjuConsequence2);

    this->itsAttacks         = JinmenjuAttackList;
    this->itsAttackSaves     = JinmenjuAttackSaves;
    this->itsDamageList      = JinmenjuDamageList;
    this->itsAttackModifiers = JinmenjuAttackModifiers;
    this->itsDifficulty      = JinmenjuDifficulty;
    this->itsConsequences    = JinmenjuConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// BoneDevil Constructor
BoneDevil::BoneDevil() : Monster(std::string("BoneDevil"),
                                     142, // health
                                     19, // armor class
                                     40, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     29, // library index
                                     4, 3, 4, 1, 2, 3) // modifiers
{
    challengeRating = 9;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities BoneDevilAbilities;
              BoneDevilAbilities.reserve(5);

    // declare abilities sequentially
    Ability BoneDevilAbility1("DevilsSight");
    Ability BoneDevilAbility2("MagicResistance");
    Ability BoneDevilAbility3("Resistant to Cold and damage from nonmagical / unsilvered weapons");
    Ability BoneDevilAbility4("Immune to fire and poison");
    Ability BoneDevilAbility5("MultiAttack");

    // push abilities back in order above
    BoneDevilAbilities.push_back(BoneDevilAbility1);
    BoneDevilAbilities.push_back(BoneDevilAbility2);
    BoneDevilAbilities.push_back(BoneDevilAbility3);
    BoneDevilAbilities.push_back(BoneDevilAbility4);
    BoneDevilAbilities.push_back(BoneDevilAbility5);
    this->abilities = BoneDevilAbilities;

    // holders for attack details
    AttackList         BoneDevilAttackList;
    vector<AttackSave> BoneDevilAttackSaves;
    DamageList         BoneDevilDamageList;
    vector<int>        BoneDevilAttackModifiers;
    vector<int>        BoneDevilDifficulty;
    Consequence        BoneDevilConsequences;

    // all attack details
    Attack     BoneDevilAttack1("Claw");
    int        BoneDevilAttackMod1 = 8;
    DamageDice BoneDevilAttackDamage1 = {0, 1, 1, 0, 0, 0};
    AttackSave BoneDevilAttackSave1 = AttackSave::NONE;
    int        BoneDevilSaveDifficulty1 = 0;
    string     BoneDevilConsequence1("NONE");

    Attack     BoneDevilAttack2("Sting");
    int        BoneDevilAttackMod2 = 8;
    DamageDice BoneDevilAttackDamage2 = {0, 1, 2, 2, 0, 0};
    AttackSave BoneDevilAttackSave2 = AttackSave::CON;
    int        BoneDevilSaveDifficulty2 = 14;
    string     BoneDevilConsequence2("Poisoned for 1 minute");

    BoneDevilAttackList.push_back     (BoneDevilAttack1);
    BoneDevilAttackModifiers.push_back(BoneDevilAttackMod1);
    BoneDevilDamageList.push_back     (BoneDevilAttackDamage1);
    BoneDevilAttackSaves.push_back    (BoneDevilAttackSave1);
    BoneDevilDifficulty.push_back     (BoneDevilSaveDifficulty1);
    BoneDevilConsequences.push_back   (BoneDevilConsequence1);

    BoneDevilAttackList.push_back     (BoneDevilAttack2);
    BoneDevilAttackModifiers.push_back(BoneDevilAttackMod2);
    BoneDevilDamageList.push_back     (BoneDevilAttackDamage2);
    BoneDevilAttackSaves.push_back    (BoneDevilAttackSave2);
    BoneDevilDifficulty.push_back     (BoneDevilSaveDifficulty2);
    BoneDevilConsequences.push_back   (BoneDevilConsequence2);

    this->itsAttacks         = BoneDevilAttackList;
    this->itsAttackSaves     = BoneDevilAttackSaves;
    this->itsDamageList      = BoneDevilDamageList;
    this->itsAttackModifiers = BoneDevilAttackModifiers;
    this->itsDifficulty      = BoneDevilDifficulty;
    this->itsConsequences    = BoneDevilConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// ChainDevil Constructor
ChainDevil::ChainDevil() : Monster(std::string("ChainDevil"),
                                     85, // health
                                     16, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     30, // library index
                                     4, 2, 4, 0, 1, 2) // modifiers
{
    challengeRating = 8;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities ChainDevilAbilities;
              ChainDevilAbilities.reserve(5);

    // declare abilities sequentially
    Ability ChainDevilAbility1("DevilsSight");
    Ability ChainDevilAbility2("MagicResistance");
    Ability ChainDevilAbility3("MultiAttack");
    Ability ChainDevilAbility4("Resistant to cold, weapons not magical or silvered");
    Ability ChainDevilAbility5("Immune to fire and poison");

    // push abilities back in order above
    ChainDevilAbilities.push_back(ChainDevilAbility1);
    ChainDevilAbilities.push_back(ChainDevilAbility2);
    ChainDevilAbilities.push_back(ChainDevilAbility3);
    ChainDevilAbilities.push_back(ChainDevilAbility4);
    ChainDevilAbilities.push_back(ChainDevilAbility5);
    this->abilities = ChainDevilAbilities;

    // holders for attack details
    AttackList         ChainDevilAttackList;
    vector<AttackSave> ChainDevilAttackSaves;
    DamageList         ChainDevilDamageList;
    vector<int>        ChainDevilAttackModifiers;
    vector<int>        ChainDevilDifficulty;
    Consequence        ChainDevilConsequences;

    // all attack details
    Attack     ChainDevilAttack1("Chain");
    int        ChainDevilAttackMod1 = 8;
    DamageDice ChainDevilAttackDamage1 = {0, 3, 0, 0, 0, 0};
    AttackSave ChainDevilAttackSave1 = AttackSave::NONE;
    int        ChainDevilSaveDifficulty1 = 100;
    string     ChainDevilConsequence1("Grappled until DC14 STR success; restrained and takes 2d6 piercing each turn");

    Attack     ChainDevilAttack2("Unnerving Mask");
    int        ChainDevilAttackMod2 = 100;
    DamageDice ChainDevilAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave ChainDevilAttackSave2 = AttackSave::WIS;
    int        ChainDevilSaveDifficulty2 = 14;
    string     ChainDevilConsequence2("Looks like creature's beloved departed one...frightened until end of turn");

    ChainDevilAttackList.push_back     (ChainDevilAttack1);
    ChainDevilAttackModifiers.push_back(ChainDevilAttackMod1);
    ChainDevilDamageList.push_back     (ChainDevilAttackDamage1);
    ChainDevilAttackSaves.push_back    (ChainDevilAttackSave1);
    ChainDevilDifficulty.push_back     (ChainDevilSaveDifficulty1);
    ChainDevilConsequences.push_back   (ChainDevilConsequence1);

    ChainDevilAttackList.push_back     (ChainDevilAttack2);
    ChainDevilAttackModifiers.push_back(ChainDevilAttackMod2);
    ChainDevilDamageList.push_back     (ChainDevilAttackDamage2);
    ChainDevilAttackSaves.push_back    (ChainDevilAttackSave2);
    ChainDevilDifficulty.push_back     (ChainDevilSaveDifficulty2);
    ChainDevilConsequences.push_back   (ChainDevilConsequence2);

    this->itsAttacks         = ChainDevilAttackList;
    this->itsAttackSaves     = ChainDevilAttackSaves;
    this->itsDamageList      = ChainDevilDamageList;
    this->itsAttackModifiers = ChainDevilAttackModifiers;
    this->itsDifficulty      = ChainDevilDifficulty;
    this->itsConsequences    = ChainDevilConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}

// LitchLord Constructor
LitchLord::LitchLord() : Monster(std::string("LitchLord"),
                                     91, // health
                                     14, // armor class
                                     30, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     31, // library index
                                     1, 1, 2, 1, 5, 3) // modifiers
{
    challengeRating = 9;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::TOWN);
    environment.push_back(Environment::FOREST);
    environment.push_back(Environment::DESERT);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities LitchLordAbilities;
              LitchLordAbilities.reserve(8);

    // declare abilities sequentially
    Ability LitchLordAbility1("TrueSight");
    Ability LitchLordAbility2("Resistant to cold, lightning, necrotic");
    Ability LitchLordAbility3("Immune to poison, weapons which aren't magical");
    Ability LitchLordAbility4("Cannot be charmed, exhausted, frightened, paralyzed, or poisoned");
    Ability LitchLordAbility5("Legendary Resistance: can choose to succeed up to 3 failed saves");
    Ability LitchLordAbility6("Turn Resistance: advantage on saving throws against any effect that turns undead");
    Ability LitchLordAbility7("Levitate: can levitate up to 20ft and remain there; no duration or concentration");

    // push abilities back in order above
    LitchLordAbilities.push_back(LitchLordAbility1);
    LitchLordAbilities.push_back(LitchLordAbility2);
    LitchLordAbilities.push_back(LitchLordAbility3);
    LitchLordAbilities.push_back(LitchLordAbility4);
    LitchLordAbilities.push_back(LitchLordAbility5);
    LitchLordAbilities.push_back(LitchLordAbility6);
    LitchLordAbilities.push_back(LitchLordAbility7);
    this->abilities = LitchLordAbilities;

    // holders for attack details
    AttackList         LitchLordAttackList;
    vector<AttackSave> LitchLordAttackSaves;
    DamageList         LitchLordDamageList;
    vector<int>        LitchLordAttackModifiers;
    vector<int>        LitchLordDifficulty;
    Consequence        LitchLordConsequences;

    LitchLordAttackList.reserve(20);
    LitchLordAttackSaves.reserve(20);
    LitchLordDamageList.reserve(20);
    LitchLordAttackModifiers.reserve(20);
    LitchLordDifficulty.reserve(20);
    LitchLordConsequences.reserve(20);

    // all attack details
    Attack     LitchLordAttack1("Unholy Smite (only action per turn)");
    int        LitchLordAttackMod1 = 5;
    DamageDice LitchLordAttackDamage1 = {0, 2, 2, 0, 0, 0};
    AttackSave LitchLordAttackSave1 = AttackSave::WIS;
    int        LitchLordSaveDifficulty1 = 17;
    string     LitchLordConsequence1("Charmed for 1 minute, defending the litch until DC17 or duration passes");

    Attack     LitchLordAttack2("Damnation");
    int        LitchLordAttackMod2 = 100;
    DamageDice LitchLordAttackDamage2 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave2 = AttackSave::WIS;
    int        LitchLordSaveDifficulty2 = 100;
    string     LitchLordConsequence2("Creature theatened with eternal damnation. If DC17 failed (repeatable), frightened for 1 minute");

    Attack     LitchLordAttack3("Guidance");
    int        LitchLordAttackMod3 = 100;
    DamageDice LitchLordAttackDamage3 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave3 = AttackSave::WIS;
    int        LitchLordSaveDifficulty3 = 100;
    string     LitchLordConsequence3("Touch willing creature; can add 1d4 to any ability check");

    Attack     LitchLordAttack4("Mending");
    int        LitchLordAttackMod4 = 100;
    DamageDice LitchLordAttackDamage4 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave4 = AttackSave::WIS;
    int        LitchLordSaveDifficulty4 = 100;
    string     LitchLordConsequence4("Repair Damage to Object");

    Attack     LitchLordAttack5("Sacred Flame");
    int        LitchLordAttackMod5 = 100;
    DamageDice LitchLordAttackDamage5 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave5 = AttackSave::DEX;
    int        LitchLordSaveDifficulty5 = 17;
    string     LitchLordConsequence5("On failure 1d8 fire radiant damage");

    Attack     LitchLordAttack6("Thaumatergy");
    int        LitchLordAttackMod6 = 100;
    DamageDice LitchLordAttackDamage6 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave6 = AttackSave::WIS;
    int        LitchLordSaveDifficulty6 = 100;
    string     LitchLordConsequence6("Enhance Sounds / Lights / etc");

    Attack     LitchLordAttack7("Command");
    int        LitchLordAttackMod7 = 100;
    DamageDice LitchLordAttackDamage7 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave7 = AttackSave::WIS;
    int        LitchLordSaveDifficulty7 = 17;
    string     LitchLordConsequence7("Whisper 1 word command; if failed save, must obey (non-harmful)");

    Attack     LitchLordAttack8("Detect Magic");
    int        LitchLordAttackMod8 = 100;
    DamageDice LitchLordAttackDamage8 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave8 = AttackSave::WIS;
    int        LitchLordSaveDifficulty8 = 100;
    string     LitchLordConsequence8("Range 30 ft");

    Attack     LitchLordAttack9("Protection From Good and Evil");
    int        LitchLordAttackMod9 = 100;
    DamageDice LitchLordAttackDamage9 = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSave9 = AttackSave::WIS;
    int        LitchLordSaveDifficulty9 = 100;
    string     LitchLordConsequence9("Touched creature has resistance and protection from choice of entity types");

    Attack     LitchLordAttackA("Sanctuary");
    int        LitchLordAttackModA = 100;
    DamageDice LitchLordAttackDamageA = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveA = AttackSave::WIS;
    int        LitchLordSaveDifficultyA = 100;
    string     LitchLordConsequenceA("Ward attacks from creature of choice; attacker must pass DC17 WIS or choose new target");

    Attack     LitchLordAttackB("Blindness / Deafness");
    int        LitchLordAttackModB = 100;
    DamageDice LitchLordAttackDamageB = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveB = AttackSave::CON;
    int        LitchLordSaveDifficultyB = 17;
    string     LitchLordConsequenceB("Creature of choice blinded or deafened until CON DC17 passed");

    Attack     LitchLordAttackC("Hold Person");
    int        LitchLordAttackModC = 100;
    DamageDice LitchLordAttackDamageC = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveC = AttackSave::WIS;
    int        LitchLordSaveDifficultyC = 17;
    string     LitchLordConsequenceC("Paralyzed until WIS DC17 passed or 1 minute");

    Attack     LitchLordAttackD("Silence");
    int        LitchLordAttackModD = 100;
    DamageDice LitchLordAttackDamageD = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveD = AttackSave::WIS;
    int        LitchLordSaveDifficultyD = 100;
    string     LitchLordConsequenceD("For <10min, no sound can be created in 20ft sphere; no thunder damage or V spells");

    Attack     LitchLordAttackE("Animate Dead");
    int        LitchLordAttackModE = 100;
    DamageDice LitchLordAttackDamageE = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveE = AttackSave::WIS;
    int        LitchLordSaveDifficultyE = 100;
    string     LitchLordConsequenceE("Creates undead servant (bones or corpse in sight)");

    Attack     LitchLordAttackF("Dispel Magic");
    int        LitchLordAttackModF = 100;
    DamageDice LitchLordAttackDamageF = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveF = AttackSave::WIS;
    int        LitchLordSaveDifficultyF = 100;
    string     LitchLordConsequenceF("Dispel any effect level 3 or lower; if higher, DC10+spell level WIS");

    Attack     LitchLordAttackG("Spirit Guardians");
    int        LitchLordAttackModG = 100;
    DamageDice LitchLordAttackDamageG = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveG = AttackSave::WIS;
    int        LitchLordSaveDifficultyG = 100;
    string     LitchLordConsequenceG("Wall of spirits protects you (<10min); creatures entering / starting turn w/in 15ft take 3d8 necrotic");

    Attack     LitchLordAttackH("Banishment");
    int        LitchLordAttackModH = 100;
    DamageDice LitchLordAttackDamageH = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveH = AttackSave::CHA;
    int        LitchLordSaveDifficultyH = 17;
    string     LitchLordConsequenceH("Banished to another plane of existence (1 minute); incapacitated");

    Attack     LitchLordAttackI("Freedom of Movement");
    int        LitchLordAttackModI = 100;
    DamageDice LitchLordAttackDamageI = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveI = AttackSave::WIS;
    int        LitchLordSaveDifficultyI = 100;
    string     LitchLordConsequenceI("Willing creature (touch) unaffected by difficult terrain; if grappled can use 5ft move to free itself");

    Attack     LitchLordAttackJ("Guardian of Faith");
    int        LitchLordAttackModJ = 100;
    DamageDice LitchLordAttackDamageJ = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveJ = AttackSave::WIS;
    int        LitchLordSaveDifficultyJ = 100;
    string     LitchLordConsequenceJ("Large spectral guardian w gleaming sword/shield appears; creature in space makes DC17 DEX (20rad) else (10rad)");

    Attack     LitchLordAttackK("Flame Strike");
    int        LitchLordAttackModK = 100;
    DamageDice LitchLordAttackDamageK = {0, 0, 0, 0, 0, 0};
    AttackSave LitchLordAttackSaveK = AttackSave::DEX;
    int        LitchLordSaveDifficultyK = 100;
    string     LitchLordConsequenceK("10ft radius columb of divine fire falls; DC17 DEX save, 4d6 fire 4d6 rad failure, else half");

    LitchLordAttackList.push_back     (LitchLordAttack1);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod1);
    LitchLordDamageList.push_back     (LitchLordAttackDamage1);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave1);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty1);
    LitchLordConsequences.push_back   (LitchLordConsequence1);

    LitchLordAttackList.push_back     (LitchLordAttack2);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod2);
    LitchLordDamageList.push_back     (LitchLordAttackDamage2);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave2);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty2);
    LitchLordConsequences.push_back   (LitchLordConsequence2);

    LitchLordAttackList.push_back     (LitchLordAttack3);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod3);
    LitchLordDamageList.push_back     (LitchLordAttackDamage3);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave3);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty3);
    LitchLordConsequences.push_back   (LitchLordConsequence3);

    LitchLordAttackList.push_back     (LitchLordAttack4);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod4);
    LitchLordDamageList.push_back     (LitchLordAttackDamage4);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave4);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty4);
    LitchLordConsequences.push_back   (LitchLordConsequence4);

    LitchLordAttackList.push_back     (LitchLordAttack5);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod5);
    LitchLordDamageList.push_back     (LitchLordAttackDamage5);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave5);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty5);
    LitchLordConsequences.push_back   (LitchLordConsequence5);

    LitchLordAttackList.push_back     (LitchLordAttack6);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod6);
    LitchLordDamageList.push_back     (LitchLordAttackDamage6);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave6);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty6);
    LitchLordConsequences.push_back   (LitchLordConsequence6);

    LitchLordAttackList.push_back     (LitchLordAttack7);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod7);
    LitchLordDamageList.push_back     (LitchLordAttackDamage7);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave7);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty7);
    LitchLordConsequences.push_back   (LitchLordConsequence7);

    LitchLordAttackList.push_back     (LitchLordAttack8);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod8);
    LitchLordDamageList.push_back     (LitchLordAttackDamage8);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave8);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty8);
    LitchLordConsequences.push_back   (LitchLordConsequence8);

    LitchLordAttackList.push_back     (LitchLordAttack9);
    LitchLordAttackModifiers.push_back(LitchLordAttackMod9);
    LitchLordDamageList.push_back     (LitchLordAttackDamage9);
    LitchLordAttackSaves.push_back    (LitchLordAttackSave9);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficulty9);
    LitchLordConsequences.push_back   (LitchLordConsequence9);

    LitchLordAttackList.push_back     (LitchLordAttackA);
    LitchLordAttackModifiers.push_back(LitchLordAttackModA);
    LitchLordDamageList.push_back     (LitchLordAttackDamageA);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveA);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyA);
    LitchLordConsequences.push_back   (LitchLordConsequenceA);

    LitchLordAttackList.push_back     (LitchLordAttackB);
    LitchLordAttackModifiers.push_back(LitchLordAttackModB);
    LitchLordDamageList.push_back     (LitchLordAttackDamageB);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveB);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyB);
    LitchLordConsequences.push_back   (LitchLordConsequenceB);

    LitchLordAttackList.push_back     (LitchLordAttackC);
    LitchLordAttackModifiers.push_back(LitchLordAttackModC);
    LitchLordDamageList.push_back     (LitchLordAttackDamageC);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveC);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyC);
    LitchLordConsequences.push_back   (LitchLordConsequenceC);

    LitchLordAttackList.push_back     (LitchLordAttackD);
    LitchLordAttackModifiers.push_back(LitchLordAttackModD);
    LitchLordDamageList.push_back     (LitchLordAttackDamageD);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveD);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyD);
    LitchLordConsequences.push_back   (LitchLordConsequenceD);

    LitchLordAttackList.push_back     (LitchLordAttackE);
    LitchLordAttackModifiers.push_back(LitchLordAttackModE);
    LitchLordDamageList.push_back     (LitchLordAttackDamageE);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveE);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyE);
    LitchLordConsequences.push_back   (LitchLordConsequenceE);

    LitchLordAttackList.push_back     (LitchLordAttackF);
    LitchLordAttackModifiers.push_back(LitchLordAttackModF);
    LitchLordDamageList.push_back     (LitchLordAttackDamageF);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveF);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyF);
    LitchLordConsequences.push_back   (LitchLordConsequenceF);

    LitchLordAttackList.push_back     (LitchLordAttackG);
    LitchLordAttackModifiers.push_back(LitchLordAttackModG);
    LitchLordDamageList.push_back     (LitchLordAttackDamageG);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveG);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyG);
    LitchLordConsequences.push_back   (LitchLordConsequenceG);

    LitchLordAttackList.push_back     (LitchLordAttackH);
    LitchLordAttackModifiers.push_back(LitchLordAttackModH);
    LitchLordDamageList.push_back     (LitchLordAttackDamageH);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveH);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyH);
    LitchLordConsequences.push_back   (LitchLordConsequenceH);

    LitchLordAttackList.push_back     (LitchLordAttackI);
    LitchLordAttackModifiers.push_back(LitchLordAttackModI);
    LitchLordDamageList.push_back     (LitchLordAttackDamageI);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveI);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyI);
    LitchLordConsequences.push_back   (LitchLordConsequenceI);

    LitchLordAttackList.push_back     (LitchLordAttackJ);
    LitchLordAttackModifiers.push_back(LitchLordAttackModJ);
    LitchLordDamageList.push_back     (LitchLordAttackDamageJ);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveJ);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyJ);
    LitchLordConsequences.push_back   (LitchLordConsequenceJ);

    LitchLordAttackList.push_back     (LitchLordAttackK);
    LitchLordAttackModifiers.push_back(LitchLordAttackModK);
    LitchLordDamageList.push_back     (LitchLordAttackDamageK);
    LitchLordAttackSaves.push_back    (LitchLordAttackSaveK);
    LitchLordDifficulty.push_back     (LitchLordSaveDifficultyK);
    LitchLordConsequences.push_back   (LitchLordConsequenceK);


    this->itsAttacks         = LitchLordAttackList;
    this->itsAttackSaves     = LitchLordAttackSaves;
    this->itsDamageList      = LitchLordDamageList;
    this->itsAttackModifiers = LitchLordAttackModifiers;
    this->itsDifficulty      = LitchLordDifficulty;
    this->itsConsequences    = LitchLordConsequences;

    std::cout << this->creatureName << " has been created." << endl;
}








/**********************************************************************************
 * TEMPLATE MONSTER CONSTRUCTOR
 * Make sure to include monster in createMonster switch and to include in header
 * and MonstersAvailable enumeration!!!!!
 * *******************************************************************************/
// MONSTER Constructor 
/*


Monster::Monster() : Monster(std::string("MONSTER"),
                                     0, // health
                                     0, // armor class
                                     0, // speed
                                     BASE_ABILITIES,
                                     DEFAULT_ENVIRONMENT,
                                     0, // library index
                                     0, 0, 0, 0, 0, 0) // modifiers
{
    challengeRating = ;

    vector<Environment> environment;
    environment.reserve(5);
    environment.push_back(Environment::NOWHERE);
    itsEnvironment = environment;

    // insert names before all instance names
    Abilities Abilities;
              Abilities.reserve(5);

    // declare abilities sequentially
    Ability Ability1("ability");
    Ability Ability2("ability");
    Ability Ability3("ability");
    Ability Ability4("ability");

    // push abilities back in order above
    Abilities.push_back(Ability1);
    Abilities.push_back(Ability2);
    Abilities.push_back(Ability3);
    Abilities.push_back(Ability4);
    this->abilities = Abilities;

    // holders for attack details
    AttackList         AttackList;
    vector<AttackSave> AttackSaves;
    DamageList         DamageList;
    vector<int>        AttackModifiers;
    vector<int>        Difficulty;
    Consequence        Consequences;

    // all attack details
    Attack     Attack1("attack");
    int        AttackMod1 = 0;
    DamageDice AttackDamage1 = {0, 0, 0, 0, 0, 0};
    AttackSave AttackSave1 = AttackSave::NONE;
    int        SaveDifficulty1 = 13;
    string     Consequence1("consequence");

    AttackList.push_back     (Attack1);
    AttackModifiers.push_back(AttackMod1);
    DamageList.push_back     (AttackDamage1);
    AttackSaves.push_back    (AttackSave1);
    Difficulty.push_back     (SaveDifficulty1);
    Consequences.push_back   (Consequence1);

    this->itsAttacks         = AttackList;
    this->itsAttackSaves     = AttackSaves;
    this->itsDamageList      = DamageList;
    this->itsAttackModifiers = AttackModifiers;
    this->itsDifficulty      = Difficulty;
    this->itsConsequences    = Consequences;

    std::cout << this->creatureName << " has been created." << endl;
}


*/

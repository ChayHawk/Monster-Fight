//============================================================================
// Name             : Monster Fight
// Author           : Chay Hawk
// Version          : 0.46.1
// Date and Time    : April 22nd 2023 @ 2:15 AM
// Lines of Code    : 1,210
// Description      : Game where you battle random monsters
//============================================================================

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <random>
#include <chrono>
#include <limits>
#include <format>

#include "Player.h"
#include "Inventory.h"
#include "Character.h"
#include "Enemy.h"
#include "Item.h"
#include "Attack.h"

//=================================================================================================
//BUGS
// 
// After fighting, the player is asked to re enter their name.
//=================================================================================================

//=================================================================================================
//Use a struct to define constructor object variables so we dont have magic numbers and each number 
//has a name associated with it so we know what it does.
//=================================================================================================

struct Init
{
    int attackPower{ 0 };
    int money{ 0 };
    int effect{ 0 };
    int health{ 0 };
    int maxHealth{ 0 };
    int xpToGive{ 0 };
    int experience{ 0 };
    int level{ 0 };
};

struct UserInterface
{
    void DisplayAttackMenu(Player& Hero);
    void DisplayPlayerStats(Player& Hero);

    int turn{ 1 };
    int totalTurns{ 1 };
    int battles{ 0 };
};


int RandomNumber(std::mt19937& mt, int first, int second);
void GameInfo();


int main()
{
    Init init;
    UserInterface UI;

    //=================================================================================================
    //INITIALIZE A MERSENNE TWISTER ENGINE FOR RANDOMIZATION
    //=================================================================================================

    std::mt19937 mt(static_cast<int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

    //=================================================================================================
    //CREATE ATTACKS AND SET std::vectorS
    //=================================================================================================

    Attack Punch   ("Punch",     init.attackPower = 3);
    Attack Kick    ("Kick",      init.attackPower = 1);
    Attack Slash   ("Slash",     init.attackPower = 2);
    Attack BodySlam("Body Slam", init.attackPower = 4);

    //=================================================================================================
    //CREATE ITEMS AND SET STD::VECTOR
    //=================================================================================================

    Item WeakPotion  ("Weak Potion",   init.effect = 10);
    Item StrongPotion("Strong Potion", init.effect = 20);
    Item SuperPotion ("Super Potion",  init.effect = 35);
    Item UltraPotion ("Ultra Potion",  init.effect = 50);
    Item MaxPotion   ("Max Potion",    init.effect = 100);

    std::vector<Item> itemList;

    itemList.push_back(WeakPotion);
    itemList.push_back(StrongPotion);
    itemList.push_back(SuperPotion);
    itemList.push_back(UltraPotion);
    itemList.push_back(MaxPotion);

    //=================================================================================================
    //CREATE INVENTOIRIES
    //=================================================================================================

    Inventory PlayerInventory;
    Inventory EnemyInventory;

    //=================================================================================================
    //INSTANTIATE PLAYER CONSTRUCTOR
    //=================================================================================================

    Player Hero
    (
        "Hero",
        init.health = 100,
        init.maxHealth = 100,
        init.money = 0,
        init.experience = 0,
        init.level = 1
    );

    Hero.GiveAttack(Punch);
    Hero.GiveAttack(BodySlam);
    Hero.GiveAttack(Slash);

    //=================================================================================================
    //CREATE ENEMIES
    //=================================================================================================

    Enemy Dragon  ("Dragon",    init.health = 10, init.maxHealth = 70, init.xpToGive = 40, init.money = 0);
    Enemy Skeleton("Skeleton",  init.health = 10, init.maxHealth = 10, init.xpToGive = 20, init.money = 0);
    Enemy Troll   ("Troll",     init.health = 25, init.maxHealth = 25, init.xpToGive = 30, init.money = 0);
    Enemy GiantRat("Giant Rat", init.health = 15, init.maxHealth = 15, init.xpToGive = 25, init.money = 0);
    Enemy Raptor  ("Raptor",    init.health = 35, init.maxHealth = 35, init.xpToGive = 15, init.money = 0);

    //=================================================================================================
    //SET ENEMY ATTACKS
    //=================================================================================================

    Dragon.GiveAttack(Punch);
    Dragon.GiveAttack(BodySlam);

    Skeleton.GiveAttack(Punch);
    Skeleton.GiveAttack(BodySlam);
    Skeleton.GiveAttack(Slash);

    Troll.GiveAttack(Punch);
    Troll.GiveAttack(BodySlam);
    Troll.GiveAttack(Slash);

    GiantRat.GiveAttack(BodySlam);
    GiantRat.GiveAttack(Slash);

    Raptor.GiveAttack(BodySlam);
    Raptor.GiveAttack(Slash);
    Raptor.GiveAttack(Kick);
    Raptor.GiveAttack(Kick);

    //=================================================================================================
    //SET ENEMIES IN CONTAINER FOR RANDOMIZATION
    // 
    // Had an error where these were before the SetAttackList function and attacks were not setting, 
    // its because the enemies were being added to the std::vector before they had a chance to have the 
    // attacks set to them so their attack sizes would always be 0.
    //=================================================================================================

    std::vector<Enemy> enemyRoster;

    enemyRoster.push_back(Dragon);
    enemyRoster.push_back(Skeleton);
    enemyRoster.push_back(Troll);
    enemyRoster.push_back(GiantRat);
    enemyRoster.push_back(Raptor);

    //=================================================================================================
    //INITIALIZE SOME THINGS
    //=================================================================================================

    int choice{ 0 };
    const int attackHitChance{ 8 }; //80% chance

    //todo Make a struct for this
    const int common  { 100 };
    const int uncommon{ 30 };
    const int rare    { 10 };
    int itemRarity    { 0 };

    PlayerInventory.Add(WeakPotion, 3);
    PlayerInventory.Add(SuperPotion, 4);

    while (choice != -1)
    {
        choice = 0;

        //=================================================================================================
        //SET ENEMY ATTACKS
        // 
        //Here we randomly choose an enemy and an item to give and set it to the item list
        //We instantiate them here so they are only called once becuase if we call them
        //inside the game loop, the player will fight a random enemy each turn, when
        //we only want them to fight 1 enemy per battle, then when the enemy is
        //defeated the program returns here where a new enemy and new item are randomly
        //chosen for the next battle. The same is done for money and XP as well.
        //=================================================================================================

        size_t randomEnemy = RandomNumber(mt, 0, enemyRoster.size() - 1);

        //Set enemies health back to its max. If we dont do this, next time we encounter an enemy
        //we defeated, it will have no health left.
        enemyRoster[randomEnemy].ResetHealth();

        //Select a random item to give to the player upon enemies defeat.
        size_t randomItem = RandomNumber(mt, 0, itemList.size() - 1);

        //Randomize money amount to give to player
        enemyRoster[randomEnemy].GiveMoney(RandomNumber(mt, 10, 100));

        //Randomize XP to give to player
        enemyRoster[randomEnemy].XpToGive(RandomNumber(mt, 10, 60));

        itemRarity = RandomNumber(mt, 0, 100);

        //=================================================================================================
        //MAIN GAME
        //=================================================================================================

        std::cout << "Monster Fight Version 0.46.1\n\n";

        Hero.SetName();

        std::cout << "What would you like to do?\n\n";

        std::cout << "1) Fight\n";
        std::cout << "2) Heal\n";
        std::cout << "3) View Game Info\n";
        std::cout << "4) Quit\n";

        std::cout << "\n> ";
        std::cin >> choice;


        switch (choice)
        {
        case 1:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            //Setup Initial encounter
            std::cout << "\n" << Hero.GetName() << " encountered a " << enemyRoster[randomEnemy].GetName() << "!\n";
            std::cout << "It has " << enemyRoster[randomEnemy].GetHealth() << " Health!\n\n";

            //Reset turn back to 1
            UI.turn = 1;

            while (Hero.GetHealth() > 0)
            {
                std::cout << std::format("{:#<60}", '#') << '\n';
                std::cout << std::format("{:^60}", "MONSTER FIGHT") << '\n';
                std::cout << std::format("{:#<60}", '#') << '\n';

                //=================================================================================================
                //Player chooses Attack
                //=================================================================================================

                int attackChoice{ 0 };

                UI.DisplayAttackMenu(Hero);

                std::cin >> attackChoice;

                //=================================================================================================
                //See if attack missed and if not, then use an attack.
                //=================================================================================================

                if (RandomNumber(mt, 0, attackHitChance) == 0)
                {
                    std::cout << Hero.GetName() << "'s attack missed!\n\n";
                }
                else
                {
                    std::cout << std::format("{:-^85}", "ACTION") << "\n\n";

                    std::cout << Hero.GetName() << " used " << Hero.GetAttackList()[attackChoice - 1].GetName()
                        << " against the " << enemyRoster[randomEnemy].GetName() << ", it does "
                        << Hero.GetAttackList()[attackChoice - 1].GetPower() << " damage.\n";

                    enemyRoster[randomEnemy].TakeDamage(Hero.GetAttackList()[attackChoice - 1].GetPower());
                }

                //=================================================================================================
                //Check to see if enemy is dead and if so
                //then give player money, xp, and items
                //=================================================================================================

                if (enemyRoster[randomEnemy].GetHealth() <= 0)
                {
                    std::cout << Hero.GetName() << " defeated " << enemyRoster[randomEnemy].GetName();
                    std::cout << " and got " << enemyRoster[randomEnemy].GetMoney() << " gold and ";

                    Hero.GiveExperience(enemyRoster[randomEnemy].GetXpToGive());

                    std::cout << enemyRoster[randomEnemy].GetXpToGive() << " experience.\n\n";

                    Hero.LevelUp();
                    Hero.GiveMoney(enemyRoster[randomEnemy].GetMoney());

                    std::cout << enemyRoster[randomEnemy].GetName() << " dropped " << RandomNumber(mt, 1, 3)
                        << " " << itemList[randomItem].GetName() << "'s.\n";

                    //Randomize Item given based on rarity
                    //TO DO: Make functions of each rarity with
                    //options to choose rarity level.

                    if (itemRarity > uncommon && itemRarity <= common)
                    {
                        PlayerInventory.Add(WeakPotion, RandomNumber(mt, 1, 7));
                    }
                    if (itemRarity > rare && itemRarity <= uncommon)
                    {
                        PlayerInventory.Add(StrongPotion, RandomNumber(mt, 1, 4));
                    }
                    if (itemRarity <= rare)
                    {
                        PlayerInventory.Add(SuperPotion, RandomNumber(mt, 1, 2));
                    }

                    //PlayerInventory.Add(itemList[randomItem], RandomNumber(generator, 1, 3));

                    UI.battles++;

                    Hero.IncrememntKillCounter();

                    std::cout << '\n';

                    std::cout << std::format("{:=<60}", '=') << "\n";
                    break;
                }

                //=================================================================================================
                //Randomly Choose enemy Attack
                //=================================================================================================

                if (RandomNumber(mt, 0, attackHitChance) == 0)
                {
                    std::cout << enemyRoster[randomEnemy].GetName() << "'s attack missed!\n";
                }
                else
                {
                    if (enemyRoster[randomEnemy].GetAttackList().size() == 0)
                    {
                        std::cout << "ERROR: Enemy attack list std::vector is empty.\n";
                    }
                    else
                    {
                        std::cout << enemyRoster[randomEnemy].GetName() << " uses "
                            << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(mt, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetName();
                        std::cout << " against " << Hero.GetName() << ", and it does ";
                        std::cout << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(mt, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower() << " damage!\n\n";

                        Hero.TakeDamage(enemyRoster[randomEnemy].GetAttackList()[RandomNumber(mt, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower());
                    }
                }

                //=================================================================================================
                //Check if player is dead, and if so, end
                //the game.
                //=================================================================================================

                if (Hero.GetHealth() <= 0)
                {
                    std::cout << enemyRoster[randomEnemy].GetName() << " defeated " << Hero.GetName() << "\n\n";

                    std::cout << "\n\n\n";

                    std::cout << "\nGAME OVER\n\n";

                    return 0;
                }

                //=================================================================================================
                //Display players stats
                //=================================================================================================

                std::cout << std::format("{:-^85}", "STATS") << '\n';

                UI.DisplayPlayerStats(Hero);

                std::cout << '\n' << enemyRoster[randomEnemy].GetName() << "\n\n";

                std::cout << enemyRoster[randomEnemy].GetName() << "'s Health: " << enemyRoster[randomEnemy].GetHealth() << "\n\n";

                std::cout << std::format("{:=<60}", '=') << "\n\n";

                std::cout << "What Now?\n\n";

                std::cout << "1) Continue\n";
                std::cout << "2) Heal\n";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    continue;
                    break;
                case 2:
                    PlayerInventory.UseItem(Hero);
                    break;
                default:
                    std::cout << "\nInvalid Decision.\n\n";
                    std::cin.clear(); //Clear failure state
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard bad characters
                }

                std::cin.get();
            }
            break;

        case 2:
            PlayerInventory.UseItem(Hero);

            break;
        case 3:
            GameInfo();

            break;
        case 4:
            std::cout << "\n\nGoodbye\n\n\n";

            return 0;
            break;

        default:
            std::cout << "\nInvalid Decision, please enter an integer or valid integer choice.\n\n";
            std::cin.clear(); //Clear failure state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard bad characters
        }
    }

    return 0;
}

int RandomNumber(std::mt19937& mt, int first, int second)
{
    std::uniform_int_distribution<int> randomNum(first, second);

    return randomNum(mt);
}

void UserInterface::DisplayAttackMenu(Player& Hero)
{
    int counter{ 1 };

    std::cout << "\nUse what attack?\n\n";

    std::cout << std::format("{} {:7}Power", "Attack", ' ') << '\n';

    for (const auto& attacks : Hero.GetAttackList())
    {
        if (Hero.GetAttackList().empty())
        {
            std::cout << Hero.GetName() << "'s attack list is empty!\n";
        }
        else
        {
            std::cout << std::format("{}) {:10} {}", counter++, attacks.GetName(), attacks.GetPower()) << '\n';
        }
    }
}

void UserInterface::DisplayPlayerStats(Player& Hero)
{
    std::cout << std::format("Current Turn: {} | Total Turns: {} | Battles Won: {} | Enemies Defeated: {}", turn++, totalTurns++, battles, Hero.GetKillCount()) << '\n';

    std::cout << Hero.GetName() << "\n\n";

    std::cout << Hero.GetName() << "'s Health:     " << Hero.GetHealth() << '\n';
    std::cout << Hero.GetName() << "'s Gold:       " << Hero.GetMoney() << '\n';
    std::cout << Hero.GetName() << "'s Experience: " << Hero.GetCurrentExperience() << "/" << Hero.CalculateExperience() << '\n';
    std::cout << Hero.GetName() << "'s Level:      " << Hero.GetLevel() << "/" << Hero.GetMaxLevel() << '\n';
}

void GameInfo()
{
    std::cout << "Created by: Chay Hawk\n";
    std::cout << "Lines of code: 1,210\n";
    std::cout << "Created on: 3/7/2021 @ 4:27 AM\n";
}
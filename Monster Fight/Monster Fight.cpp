// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//============================================================================
// Name             : Monster Fight
// Author           : Chay Hawk
// Version          : 0.14
// Lines of Code    : 886
// Description      : Game where you battle random monsters
//============================================================================

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <random>
#include <limits>
#include <tuple>

#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Attack.h"
#include "Item.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::random_device;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::getline;
using std::tuple;
using std::make_tuple;

/*BUGS
* 1. Items that have been randomly given to player do not restore health. - CLOSED
* 2. Game will sometimes output "You are already at full health" 3 times. - OPEN
*/

/*ISSUES
* 1. Need to delete items from inventory when no more of them exist.
*    Also need to make it so when the player gets another of the
*    same item, it adds it to the already existing item count
*    instead of adding it in a new slot.
*/

/*TO DO
* 1. Add a save and load feature.
* 2. Allow player to name their character.
*/

//============================================
//Use a struct to define constructor
//object variables so we dont have magic numbers
//and each number has a name associated
//with it so we know what it does.
//============================================

struct Init
{
    int attackPower{ 0 };
    int money{ 0 };
    int cost{ 0 };
    int effect{ 0 };
    int health{ 0 };
    int xpToGive{ 0 };
    int experience{ 0 };
    int level{ 0 };
};

int RandomNumber(default_random_engine generator, int first, int second);

int main()
{
    Init init;

    random_device rd;
    default_random_engine generator(rd());

    //============================================
    //CREATE ATTACKS AND SET VECTORS
    //============================================

    Attack Punch   ("Punch",     init.attackPower = 3);
    Attack Kick    ("Kick",      init.attackPower = 1);
    Attack Slash   ("Slash",     init.attackPower = 2);
    Attack BodySlam("Body Slam", init.attackPower = 4);


	vector<Attack> playerAttacks;

    playerAttacks.push_back(Punch);
    playerAttacks.push_back(Kick);
    playerAttacks.push_back(BodySlam);


	vector<Attack> enemyAttacks;

    enemyAttacks.push_back(Slash);
    enemyAttacks.push_back(BodySlam);

	uniform_int_distribution<int> randomEnemyAttacks(0, enemyAttacks.size() - 1);

    //============================================
    //CREATE ITEMS AND SET VECTOR
    //============================================

    Item WeakPotion  ("Weak Potion",   init.cost = 20, init.effect = 10);
    Item StrongPotion("Strong Potion", init.cost = 40, init.effect = 25);
    Item SuperPotion ("Super Potion",  init.cost = 65, init.effect = 45);

    vector<Item> itemList;

    itemList.push_back(WeakPotion); 
    itemList.push_back(StrongPotion); 
    itemList.push_back(SuperPotion); 


    //============================================
    //SET PLAYER INVENTORY VECTOR
    //============================================

    vector<tuple<Item, int>> playerInventory;

    //============================================
    //SET ENEMY INVENTORY VECTOR
    //============================================

    vector<tuple<Item, int>> enemyInventory;

    //============================================
    //INSTANTIATE PLAYER CONSTRUCTOR
    //============================================
    
    Player Hero
    (
        "Disaster Chief", 
        init.health = 100, 
        playerAttacks, 
        playerInventory, 
        init.money = 0, 
        init.experience = 0, 
        init.level = 1
    );

    //============================================
    //CREATE ENEMIES AND SET VECTOR
    //============================================

    Enemy Dragon  ("Dragon",    init.health = 70, enemyAttacks, enemyInventory, init.xpToGive = 40, init.money = 0);
    Enemy Skeleton("Skeleton",  init.health = 10, enemyAttacks, enemyInventory, init.xpToGive = 20, init.money = 0);
    Enemy Troll   ("Troll",     init.health = 25, enemyAttacks, enemyInventory, init.xpToGive = 30, init.money = 0);
    Enemy GiantRat("Giant Rat", init.health = 15, enemyAttacks, enemyInventory, init.xpToGive = 25, init.money = 0);
    Enemy Raptor  ("Raptor",    init.health = 35, enemyAttacks, enemyInventory, init.xpToGive = 15, init.money = 0);

    vector<Enemy> enemyContainer;

    enemyContainer.push_back(Dragon);
    enemyContainer.push_back(Skeleton);
    enemyContainer.push_back(Troll);
    enemyContainer.push_back(GiantRat);
    enemyContainer.push_back(Raptor);

    int choice{ 0 };
    int turn{ 1 };
    int totalTurns{ 1 };
    int battles{ 0 };
    int totalEnemiesDefeated{ 0 };

    while (choice != -1)
    {
        choice = 0;

        //Choose a random enemy and set it inside vector, if we dont do this
        //A random enemy will be chosen for each call in the fight, we want 
        //the same eney for the duration of the fight.
        uniform_int_distribution<int> chooseRandomEnemy(0, enemyContainer.size() - 1);
        Enemy randomEnemy{ enemyContainer[chooseRandomEnemy(generator)] };


		uniform_int_distribution<int> randomItemReward(0, itemList.size() - 1);
        Item randomItem{ itemList[randomItemReward(generator)] };
   
        //Randomly generate a reward and set it for this fight, then re-randomize it
        //for the next fight.
        randomEnemy.GiveMoney(RandomNumber(generator, 10, 100));
        randomEnemy.XpToGive(RandomNumber(generator, 10, 60));

        //This makes it so most attacks have a 90% chance to hit.

        cout << "Monster Fight Version 0.14 - 886 Lines of Code\n" << endl;
        cout << "What would you like to do?\n" << endl;

        cout << "1) Fight" << endl;
        cout << "2) Quit" << endl;

        cout << "\n> ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //Initial encounter
            cout << "\n" << Hero.GetName() << " encountered a " << randomEnemy.GetName() << "!" << endl;
            cout << "It has " << randomEnemy.GetHealth() << " Health!\n" << endl;

            turn = 1;

            while (Hero.GetHealth() > 0)
            {
                //Re-roll player and enemy attacks and power levels for random attacks and powers.
                Attack randomEnemyAttack{ enemyAttacks[randomEnemyAttacks(generator)] };

                cout << "\n################################################################" << endl;
                cout << "##" << "                     MONSTER FIGHT                          ##" << endl;
                cout << "################################################################" << endl;

                //============================================
                //Player chooses Attack
                //============================================

                int counter{ 1 };
                int attackChoice{ 0 };

                cout << "\nUse what attack?\n" << endl;

				for (auto& i : Hero.GetAttackList())
                {

					cout << counter++ << ") " << i << endl;
                }
                cin >> attackChoice;

				generator();

                if(RandomNumber(generator, 0, 8) == 0)
                {
                    cout << Hero.GetName() << "'s attack missed!\n" << endl;
                }
                else
                {
					cout << "\nACTION------------------------------------------------------------------" << endl;
					cout << Hero.GetName() << " used " << playerAttacks[attackChoice -1].GetName() 
                         << " against the " << randomEnemy.GetName() << ", it does " << playerAttacks[attackChoice -1].GetPower() << " damage." << endl;
					randomEnemy.TakeDamage(playerAttacks[attackChoice -1]);
                }

				//============================================
                //Check to see if enemy is dead and if so
                //then give player money, xp, and items
                //============================================

                if (randomEnemy.GetHealth() <= 0)
                {
                    cout << Hero.GetName() << " defeated " << randomEnemy.GetName();
                    cout << " and got " << randomEnemy.GetMoney() << " gold and ";

                    Hero.GiveExperience(randomEnemy.GetXpToGive());

                    cout << randomEnemy.GetXpToGive() <<  " experience.\n" << endl;

                    Hero.LevelUp();
                    Hero.GiveMoney(randomEnemy.GetMoney());

                    cout << randomEnemy.GetName() << " dropped " << RandomNumber(generator, 1, 3) << " " << randomItem.GetName() << "'s." << endl;
                    Hero.AddItemToInventory(randomItem, RandomNumber(generator, 1, 3));

                    battles++;
                    totalEnemiesDefeated++;
                    cout << "\n================================================================\n" << endl;
                    break;
                }

				//============================================
                //Randomly Choose enemy Attack
                //============================================

				generator();

                if(RandomNumber(generator, 0, 8) == 0)
                {
                    cout << randomEnemy.GetName() << "'s attack missed!" << endl;
                }
                else
                {
                    cout << randomEnemy.GetName() << " uses " << randomEnemyAttack.GetName();
                    cout << " against " << Hero.GetName() << ", and it does ";
                    cout << randomEnemyAttack.GetPower() << " damage!\n" << endl;

					Hero.TakeDamage(randomEnemyAttack.GetPower());
                }

				//============================================
                //Check if player is dead, and if so, end
                //the game.
                //============================================

                if (Hero.GetHealth() <= 0)
                {
                    cout << randomEnemy.GetName() << " defeated " << Hero.GetName() << endl;

                    cout << "\n================================================================\n" << endl;

                    cout << "\nGAME OVER\n" << endl;

                    return 0;
                }

				//============================================
                //Display players stats
                //============================================

                cout << "\nSTATS===================================================================" << endl;

                cout << "\nCurrent Turn: " << turn++ << " | Total Turns: " << totalTurns++ << " | Battles Won: " << battles << " | Enemies Defeated: " << totalEnemiesDefeated << "\n" << endl;

                cout << Hero.GetName() << '\n' << endl;

                cout << Hero.GetName() << "'s Health:     " << Hero.GetHealth() << endl;
                cout << Hero.GetName() << "'s Gold:       " << Hero.GetMoney() << endl;
                cout << Hero.GetName() << "'s Experience: " << Hero.GetCurrentExperience() << "/" << Hero.CalculateExperience() << endl;
                cout << Hero.GetName() << "'s Level:      " << Hero.GetLevel() << "/" << Hero.GetMaxLevel() << endl;

                cout << '\n' << randomEnemy.GetName() << '\n' << endl;

                cout << randomEnemy.GetName() << "'s Health: " << randomEnemy.GetHealth() << endl;

                cout << "\n========================================================================\n" << endl;

                cout << "Do What?\n" << endl;
                cout << "1) Continue" << endl;
                cout << "2) Heal" << endl;
                cin >> choice;

                switch (choice)
                {
                    case 1:
						continue;
                        break;
                    case 2:
                        Hero.UseItem();
                        break;
                    default:
						cout << "\nInvalid Decision.\n" << endl;
                        cin.clear(); //Clear failure state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard bad characters
                }

                cin.get();
            }
                break;

            case 2:
                    return 0;
                break;

            default:
                cout << "\nInvalid Decision, please enter an integer or valid integer choice.\n" << endl;
                cin.clear(); //Clear failure state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard bad characters
        }
    }

    return 0;
}

int RandomNumber(default_random_engine generator, int first, int second)
{
    uniform_int_distribution<int> randomNum(first, second);

    return randomNum(generator);
}
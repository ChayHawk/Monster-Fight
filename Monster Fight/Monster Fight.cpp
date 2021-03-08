// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//============================================================================
// Name             : Monster Fight
// Author           : Chay Hawk
// Version          : 0.24.0
// Date and Time    : 3/7/2021 @ 4:27 AM
// Lines of Code    : 956
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

//=================================================================================================
//Use a struct to define constructor
//object variables so we dont have magic numbers
//and each number has a name associated
//with it so we know what it does.
//=================================================================================================

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

    //=================================================================================================
    //CREATE ATTACKS AND SET VECTORS
    //=================================================================================================

    Attack Punch   ("Punch",     init.attackPower = 3);
    Attack Kick    ("Kick",      init.attackPower = 1);
    Attack Slash   ("Slash",     init.attackPower = 2);
    Attack BodySlam("Body Slam", init.attackPower = 4);

    //=================================================================================================
    //CREATE ITEMS AND SET VECTOR
    //=================================================================================================

    Item WeakPotion  ("Weak Potion",   init.cost = 20, init.effect = 10);
    Item StrongPotion("Strong Potion", init.cost = 40, init.effect = 25);
    Item SuperPotion ("Super Potion",  init.cost = 65, init.effect = 45);

    vector<Item> itemList;

    itemList.push_back(WeakPotion); 
    itemList.push_back(StrongPotion); 
    itemList.push_back(SuperPotion); 

    //=================================================================================================
    //SET PLAYER INVENTORY VECTOR
    //=================================================================================================

    vector<tuple<Item, int>> playerInventory;

    //=================================================================================================
    //SET ENEMY INVENTORY VECTOR
    //=================================================================================================

    vector<tuple<Item, int>> enemyInventory;

    //=================================================================================================
    //INSTANTIATE PLAYER CONSTRUCTOR
    //=================================================================================================
    
    Player Hero
    (
        "Disaster Chief", 
        init.health = 10, 
        playerInventory, 
        init.money = 0, 
        init.experience = 0, 
        init.level = 1
    );

    Hero.SetAttackList(Punch);
    Hero.SetAttackList(BodySlam);
    Hero.SetAttackList(Slash);

    //=================================================================================================
    //CREATE ENEMIES
    //=================================================================================================

    Enemy Dragon  ("Dragon",    init.health = 70, enemyInventory, init.xpToGive = 40, init.money = 0);
    Enemy Skeleton("Skeleton",  init.health = 10, enemyInventory, init.xpToGive = 20, init.money = 0);
    Enemy Troll   ("Troll",     init.health = 25, enemyInventory, init.xpToGive = 30, init.money = 0);
    Enemy GiantRat("Giant Rat", init.health = 15, enemyInventory, init.xpToGive = 25, init.money = 0);
    Enemy Raptor  ("Raptor",    init.health = 35, enemyInventory, init.xpToGive = 15, init.money = 0);

	//=================================================================================================
    //SET ENEMY ATTACKS
    //=================================================================================================

    Dragon.SetAttackList(Punch);
	Dragon.SetAttackList(BodySlam);

    Skeleton.SetAttackList(Punch);
    Skeleton.SetAttackList(BodySlam);
    Skeleton.SetAttackList(Slash);

	Troll.SetAttackList(Punch);
    Troll.SetAttackList(BodySlam);
    Troll.SetAttackList(Slash);

    GiantRat.SetAttackList(BodySlam);
    GiantRat.SetAttackList(Slash);

    Raptor.SetAttackList(BodySlam);
    Raptor.SetAttackList(Slash);
    Raptor.SetAttackList(Kick);

	//=================================================================================================
    //SET ENEMIES IN CONTAINER FOR RANDOMIZATION
    // 
    // Had an error where these were before the SetAttackList function and attacks were not setting, 
    // its because the enemies were being added to the vector before they had a chance to have the 
    // attacks set to them so their attack sizes would always be 0.
    //=================================================================================================

	vector<Enemy> enemyContainer;

    //enemyContainer.push_back(Dragon);
    enemyContainer.push_back(Skeleton);
    //enemyContainer.push_back(Troll);
    //enemyContainer.push_back(GiantRat);
    //enemyContainer.push_back(Raptor);

	//=================================================================================================
    //INITIALIZE SOME THINGS
    //=================================================================================================

    int choice{ 0 };
    int turn{ 1 };
    int totalTurns{ 1 };
    int battles{ 0 };
    const int attackHitChance{ 8 };

	Hero.AddItemToInventory(WeakPotion, 3);

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

        int randomEnemySelection = RandomNumber(generator, 0, enemyContainer.size() - 1);
        enemyContainer[randomEnemySelection];

        int randomItemSelection = RandomNumber(generator, 0, itemList.size() - 1);
        itemList[randomItemSelection];
   
        enemyContainer[randomEnemySelection].GiveMoney(RandomNumber(generator, 10, 100));
        enemyContainer[randomEnemySelection].XpToGive(RandomNumber(generator, 10, 60));

        //=================================================================================================
        //MAIN GAME
        //=================================================================================================

        cout << "Monster Fight Version 0.24.0 - 956 Lines of Code\n" << endl;
        cout << "What would you like to do?\n" << endl;

        cout << "1) Fight" << endl;
        cout << "2) Heal" << endl;
        cout << "3) Quit" << endl;

        cout << "\n> ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //Setup Initial encounter
            cout << "\n" << Hero.GetName() << " encountered a " << enemyContainer[randomEnemySelection].GetName() << "!" << endl;
            cout << "It has " << enemyContainer[randomEnemySelection].GetHealth() << " Health!\n" << endl;

            turn = 1;

            while (Hero.GetHealth() > 0)
            {
                cout << "\n################################################################" << endl;
                cout << "                     MONSTER FIGHT                        " << endl;
                cout << "################################################################" << endl;

                //=================================================================================================
                //Player chooses Attack
                //=================================================================================================

                int counter{ 1 };
                int attackChoice{ 0 };

                cout << "\nUse what attack?\n" << endl;

				for (auto& i : Hero.GetAttackList())
                {
                    if (Hero.GetAttackList().empty())
                    {
                        cout << Hero.GetName() << "'s attack list is empty!" << endl;
                    }
                    else
                    {
						cout << counter++ << ") " << i << endl;
                    }
                }
                cin >> attackChoice;

                //Call generator to re-randomize
				generator();

				//=================================================================================================
                //See if attack missed and if not, then
                //use an attack.
                //=================================================================================================

                if(RandomNumber(generator, 0, attackHitChance) == 0)
                {
                    cout << Hero.GetName() << "'s attack missed!\n" << endl;
                }
                else
                {
					cout << "\nACTION------------------------------------------------------------------" << endl;
					cout << Hero.GetName() << " used " << Hero.GetAttackList()[attackChoice -1].GetName() 
                         << " against the " << enemyContainer[randomEnemySelection].GetName() << ", it does " << Hero.GetAttackList()[attackChoice -1].GetPower() << " damage." << endl;
					enemyContainer[randomEnemySelection].TakeDamage(Hero.GetAttackList()[attackChoice -1].GetPower());
                }

				//=================================================================================================
                //Check to see if enemy is dead and if so
                //then give player money, xp, and items
                //=================================================================================================

                if (enemyContainer[randomEnemySelection].GetHealth() <= 0)
                {
                    cout << Hero.GetName() << " defeated " << enemyContainer[randomEnemySelection].GetName();
                    cout << " and got " << enemyContainer[randomEnemySelection].GetMoney() << " gold and ";

                    Hero.GiveExperience(enemyContainer[randomEnemySelection].GetXpToGive());

                    cout << enemyContainer[randomEnemySelection].GetXpToGive() <<  " experience.\n" << endl;

                    Hero.LevelUp();
                    Hero.GiveMoney(enemyContainer[randomEnemySelection].GetMoney());

                    cout << enemyContainer[randomEnemySelection].GetName() << " dropped " << RandomNumber(generator, 1, 3) << " " << itemList[randomItemSelection].GetName() << "'s." << endl;
                    Hero.AddItemToInventory(itemList[randomItemSelection], RandomNumber(generator, 1, 3));

                    battles++;
                    Hero.IncrememntKillCounter();
                    cout << "\n================================================================\n" << endl;
                    break;
                }

				//=================================================================================================
                //Randomly Choose enemy Attack
                //=================================================================================================

				generator();

                if(RandomNumber(generator, 0, attackHitChance) == 0)
                {
                    cout << enemyContainer[randomEnemySelection].GetName() << "'s attack missed!" << endl;
                }
                else
                {
                    if (enemyContainer[randomEnemySelection].GetAttackList().size() == 0)
                    {
                        cout << "ERROR: Enemy attack list vector is empty." << endl;
                    }
                    else
                    {
						cout << enemyContainer[randomEnemySelection].GetName() << " uses " << enemyContainer[randomEnemySelection].GetAttackList()[RandomNumber(generator, 0, enemyContainer[randomEnemySelection].GetAttackList().size() - 1)].GetName();
                        cout << " against " << Hero.GetName() << ", and it does ";
                        cout << enemyContainer[randomEnemySelection].GetAttackList()[RandomNumber(generator, 0, enemyContainer[randomEnemySelection].GetAttackList().size() - 1)].GetPower() << " damage!\n" << endl;

					    Hero.TakeDamage(enemyContainer[randomEnemySelection].GetAttackList()[RandomNumber(generator, 0, enemyContainer[randomEnemySelection].GetAttackList().size() - 1)].GetPower());
                    }
                    
                }

				//=================================================================================================
                //Check if player is dead, and if so, end
                //the game.
                //=================================================================================================

                if (Hero.GetHealth() <= 0)
                {
                    cout << enemyContainer[randomEnemySelection].GetName() << " defeated " << Hero.GetName() << endl;

                    cout << "\n================================================================\n" << endl;

                    cout << "\nGAME OVER\n" << endl;

                    return 0;
                }

				//=================================================================================================
                //Display players stats
                //=================================================================================================

                cout << "\nSTATS===================================================================" << endl;

                cout << "\nCurrent Turn: " << turn++ << " | Total Turns: " << totalTurns++ << " | Battles Won: " << battles << " | Enemies Defeated: " << Hero.GetKillCount() << "\n" << endl;

                cout << Hero.GetName() << '\n' << endl;

                cout << Hero.GetName() << "'s Health:     " << Hero.GetHealth() << endl;
                cout << Hero.GetName() << "'s Gold:       " << Hero.GetMoney() << endl;
                cout << Hero.GetName() << "'s Experience: " << Hero.GetCurrentExperience() << "/" << Hero.CalculateExperience() << endl;
                cout << Hero.GetName() << "'s Level:      " << Hero.GetLevel() << "/" << Hero.GetMaxLevel() << endl;

                cout << '\n' << enemyContainer[randomEnemySelection].GetName() << '\n' << endl;

                cout << enemyContainer[randomEnemySelection].GetName() << "'s Health: " << enemyContainer[randomEnemySelection].GetHealth() << endl;

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
				Hero.UseItem();
                break;
            case 3:
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
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//============================================================================
// Name             : Monster Fight
// Author           : Chay Hawk
// Version          : 0.35.0
// Date and Time    : 3/7/2021 @ 4:27 AM
// Lines of Code    : 1,156
// Description      : Game where you battle random monsters
//============================================================================

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>

#include "Player.h"
#include "Inventory.h"
#include "Character.h"
#include "Enemy.h"
#include "Item.h"
#include "Attack.h"


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
using std::ofstream;
using std::ifstream;

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


int RandomNumber(default_random_engine generator, int first, int second);
void Save(Player& Hero, Inventory& inventory);
vector<int> Load();


int main()
{
    Init init;
    UserInterface UI;

	//=================================================================================================
    //INITIALIZE OUR CODE USED FOR RANDOMIZATION
    //=================================================================================================

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

    Item WeakPotion  ("Weak Potion",   init.effect = 10);
    Item StrongPotion("Strong Potion", init.effect = 20);
    Item SuperPotion ("Super Potion",  init.effect = 35);
    Item UltraPotion ("Ultra Potion",  init.effect = 50);
    Item MaxPotion   ("Max Potion",    init.effect = 100);

    vector<Item> itemList;

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
        "Disaster Chief",
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
    // its because the enemies were being added to the vector before they had a chance to have the 
    // attacks set to them so their attack sizes would always be 0.
    //=================================================================================================

	vector<Enemy> enemyRoster;

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

	const int common = 100;
    const int uncommon = 30;
    const int rare = 10;
    int itemRarity{ 0 };

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

        size_t randomEnemy = RandomNumber(generator, 0, enemyRoster.size() - 1);
        enemyRoster[randomEnemy];

        //Set enemies health back to its max. If we dont do this, next time we encounter an enemy
        //we defeated, it will have no health left.
        enemyRoster[randomEnemy].ResetHealth();

        //Select a random item to give to the player upon enemies defeat.
        size_t randomItem = RandomNumber(generator, 0, itemList.size() - 1);
        itemList[randomItem];
        
        //Randomize money amount to give to player
        enemyRoster[randomEnemy].GiveMoney(RandomNumber(generator, 10, 100));

        //Randomize XP to give to player
        enemyRoster[randomEnemy].XpToGive(RandomNumber(generator, 10, 60));

        itemRarity = RandomNumber(generator, 0, 100);

        //=================================================================================================
        //MAIN GAME
        //=================================================================================================

        cout << "Monster Fight Version 0.35.0 - 1,156 Lines of Code\n" << endl;
        cout << "What would you like to do?\n" << endl;

        cout << "1) Fight" << endl;
        cout << "2) Heal" << endl;
        cout << "3) Save" << endl;
        cout << "4) Load" << endl;
        cout << "5) Quit" << endl;

        cout << "\n> ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //Setup Initial encounter
            cout << "\n" << Hero.GetName() << " encountered a " << enemyRoster[randomEnemy].GetName() << "!" << endl;
            cout << "It has " << enemyRoster[randomEnemy].GetHealth() << " Health!\n" << endl;

            //Reset turn back to 1
            UI.turn = 1;

            while (Hero.GetHealth() > 0)
            {
                cout << "\n################################################################" << endl;
                cout << "                     MONSTER FIGHT                        " << endl;
                cout << "################################################################" << endl;

                //=================================================================================================
                //Player chooses Attack
                //=================================================================================================

                int attackChoice{ 0 };

                UI.DisplayAttackMenu(Hero);
            
                cin >> attackChoice;

                cout << "ITEM RARITY: " << itemRarity << endl;

                //Call generator to re-randomize
				generator();

				cout << "ITEM RARITY: " << itemRarity << endl;

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
                         << " against the " << enemyRoster[randomEnemy].GetName() << ", it does " 
                         << Hero.GetAttackList()[attackChoice -1].GetPower() << " damage." << endl;

					enemyRoster[randomEnemy].TakeDamage(Hero.GetAttackList()[attackChoice -1].GetPower());
                }

				//=================================================================================================
                //Check to see if enemy is dead and if so
                //then give player money, xp, and items
                //=================================================================================================

                if (enemyRoster[randomEnemy].GetHealth() <= 0)
                {
                    cout << Hero.GetName() << " defeated " << enemyRoster[randomEnemy].GetName();
                    cout << " and got " << enemyRoster[randomEnemy].GetMoney() << " gold and ";

                    Hero.GiveExperience(enemyRoster[randomEnemy].GetXpToGive());

                    cout << enemyRoster[randomEnemy].GetXpToGive() <<  " experience.\n" << endl;

                    Hero.LevelUp();
                    Hero.GiveMoney(enemyRoster[randomEnemy].GetMoney());

                    cout << enemyRoster[randomEnemy].GetName() << " dropped " << RandomNumber(generator, 1, 3)
                        << " " << itemList[randomItem].GetName() << "'s." << endl;

					//Randomize Item given based on rarity
                    //TO DO: Make functions of each rarity with
                    //options to choose rarity level.

                    if (itemRarity > uncommon && itemRarity <= common)
                    {
                        PlayerInventory.Add(WeakPotion, RandomNumber(generator, 1, 7));
                    }
		            if (itemRarity > rare && itemRarity <= uncommon)
                    {
						PlayerInventory.Add(StrongPotion, RandomNumber(generator, 1, 4));
                    }
		            if (itemRarity <= rare)
                    {
						PlayerInventory.Add(SuperPotion, RandomNumber(generator, 1, 2));
                    }

                    //PlayerInventory.Add(itemList[randomItem], RandomNumber(generator, 1, 3));

                    UI.battles++;

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
                    cout << enemyRoster[randomEnemy].GetName() << "'s attack missed!" << endl;
                }
                else
                {
                    if (enemyRoster[randomEnemy].GetAttackList().size() == 0)
                    {
                        cout << "ERROR: Enemy attack list vector is empty." << endl;
                    }
                    else
                    {
						cout << enemyRoster[randomEnemy].GetName() << " uses " 
                             << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetName();
                        cout << " against " << Hero.GetName() << ", and it does ";
                        cout << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower() << " damage!\n" << endl;

					    Hero.TakeDamage(enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower());
                    }
                }

				//=================================================================================================
                //Check if player is dead, and if so, end
                //the game.
                //=================================================================================================

                if (Hero.GetHealth() <= 0)
                {
                    cout << enemyRoster[randomEnemy].GetName() << " defeated " << Hero.GetName() << endl;

                    cout << "\n================================================================\n" << endl;

                    cout << "\nGAME OVER\n" << endl;

                    return 0;
                }

				//=================================================================================================
                //Display players stats
                //=================================================================================================

                cout << "\nSTATS===================================================================" << endl;

                UI.DisplayPlayerStats(Hero);

                cout << '\n' << enemyRoster[randomEnemy].GetName() << '\n' << endl;

                cout << enemyRoster[randomEnemy].GetName() << "'s Health: " << enemyRoster[randomEnemy].GetHealth() << endl;

                cout << "\n========================================================================\n" << endl;

                cout << "What Now?\n" << endl;

                cout << "1) Continue" << endl;
                cout << "2) Heal" << endl;
                cin >> choice;

                switch (choice)
                {
                    case 1:
						continue;
                        break;
                    case 2:
                        PlayerInventory.UseItem(Hero);
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
				PlayerInventory.UseItem(Hero);

                break;
            case 3:
                cout << "\nGame Saved\n" << endl;
                Save(Hero, PlayerInventory);

                break;
            case 4:
                cout << "Functionality not working." << endl;

                break;
            case 5:
                cout << "\n\nGoodbye\n\n" << endl;

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

void Save(Player& Hero, Inventory& inventory)
{
    ofstream save("monster fight.txt");

    save << Hero.GetHealth() << endl;
	save << Hero.GetMoney() << endl;
    save << Hero.GetCurrentExperience();
	save << Hero.GetLevel() << endl;
    save << Hero.GetKillCount() << endl;

    for (auto& i : inventory.GetInventory())
    {
        save << i.first << " " << i.second << endl;
    }
}

vector<int> Load()
{
    vector<int> loadedData(6);

    ifstream load("monster fight.txt");

    load >> loadedData[0];
    load >> loadedData[1];
    load >> loadedData[2];
    load >> loadedData[3];
    load >> loadedData[4];

	return loadedData;
}

void UserInterface::DisplayAttackMenu(Player& Hero)
{
	int counter{ 1 };
                
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
}

void UserInterface::DisplayPlayerStats(Player& Hero)
{
	cout << "\nCurrent Turn: " << turn++ << " | Total Turns: " << totalTurns++ << " | Battles Won: " << battles << " | Enemies Defeated: " << Hero.GetKillCount() << "\n" << endl;

    cout << Hero.GetName() << '\n' << endl;

    cout << Hero.GetName() << "'s Health:     " << Hero.GetHealth() << endl;
    cout << Hero.GetName() << "'s Gold:       " << Hero.GetMoney() << endl;
    cout << Hero.GetName() << "'s Experience: " << Hero.GetCurrentExperience() << "/" << Hero.CalculateExperience() << endl;
    cout << Hero.GetName() << "'s Level:      " << Hero.GetLevel() << "/" << Hero.GetMaxLevel() << endl;
}
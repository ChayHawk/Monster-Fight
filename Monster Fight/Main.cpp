// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//============================================================================
// Name             : Monster Fight
// Author           : Chay Hawk
// Version          : 0.38.0
// Date and Time    : 3/7/2021 @ 4:27 AM
// Lines of Code    : 1,152
// Description      : Game where you battle random monsters
//============================================================================

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <random>
#include <limits>

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
void GameInfo();


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

    string gui(60, '#');
	string gui2(20, ' ');
	string gui3(60, '-');
	string gui4(60, '=');

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

        cout << "Monster Fight Version 0.38.0\n\n";
        cout << "What would you like to do?\n\n";

        cout << "1) Fight\n";
        cout << "2) Heal\n";
        cout << "3) View Game Info\n";
        cout << "4) Quit\n";

        cout << "\n> ";
        cin >> choice;


        switch (choice)
        {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //Setup Initial encounter
            cout << "\n" << Hero.GetName() << " encountered a " << enemyRoster[randomEnemy].GetName() << "!\n";
            cout << "It has " << enemyRoster[randomEnemy].GetHealth() << " Health!\n\n";

            //Reset turn back to 1
            UI.turn = 1;

            while (Hero.GetHealth() > 0)
            {
                cout << '\n' << gui << '\n';
                cout << gui2 << "MONSTER FIGHT" << gui2 << '\n';
                cout << '\n' << gui << '\n';

                //=================================================================================================
                //Player chooses Attack
                //=================================================================================================

                int attackChoice{ 0 };

                UI.DisplayAttackMenu(Hero);
            
                cin >> attackChoice;

                //Call generator to re-randomize
				generator();

				//=================================================================================================
                //See if attack missed and if not, then
                //use an attack.
                //=================================================================================================

                if(RandomNumber(generator, 0, attackHitChance) == 0)
                {
                    cout << Hero.GetName() << "'s attack missed!\n\n";
                }
                else
                {
					cout << "\nACTION" << gui3 << '\n';
					cout << Hero.GetName() << " used " << Hero.GetAttackList()[attackChoice -1].GetName() 
                         << " against the " << enemyRoster[randomEnemy].GetName() << ", it does " 
                         << Hero.GetAttackList()[attackChoice -1].GetPower() << " damage.\n";

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

                    cout << enemyRoster[randomEnemy].GetXpToGive() <<  " experience.\n\n";

                    Hero.LevelUp();
                    Hero.GiveMoney(enemyRoster[randomEnemy].GetMoney());

                    cout << enemyRoster[randomEnemy].GetName() << " dropped " << RandomNumber(generator, 1, 3)
                        << " " << itemList[randomItem].GetName() << "'s.\n";

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

                    cout << '\n' << gui4 << '\n';
                    break;
                }

				//=================================================================================================
                //Randomly Choose enemy Attack
                //=================================================================================================

				generator();

                if(RandomNumber(generator, 0, attackHitChance) == 0)
                {
                    cout << enemyRoster[randomEnemy].GetName() << "'s attack missed!\n";
                }
                else
                {
                    if (enemyRoster[randomEnemy].GetAttackList().size() == 0)
                    {
                        cout << "ERROR: Enemy attack list vector is empty.\n";
                    }
                    else
                    {
						cout << enemyRoster[randomEnemy].GetName() << " uses " 
                             << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetName();
                        cout << " against " << Hero.GetName() << ", and it does ";
                        cout << enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower() << " damage!\n\n";

					    Hero.TakeDamage(enemyRoster[randomEnemy].GetAttackList()[RandomNumber(generator, 0, enemyRoster[randomEnemy].GetAttackList().size() - 1)].GetPower());
                    }
                }

				//=================================================================================================
                //Check if player is dead, and if so, end
                //the game.
                //=================================================================================================

                if (Hero.GetHealth() <= 0)
                {
                    cout << enemyRoster[randomEnemy].GetName() << " defeated " << Hero.GetName() << '\n';

                    cout << '\n' << gui4 << "\n\n";

                    cout << "\nGAME OVER\n\n";

                    return 0;
                }

				//=================================================================================================
                //Display players stats
                //=================================================================================================

                cout << "\nSTATS" << gui4 << '\n';

                UI.DisplayPlayerStats(Hero);

                cout << '\n' << enemyRoster[randomEnemy].GetName() << "\n\n";

                cout << enemyRoster[randomEnemy].GetName() << "'s Health: " << enemyRoster[randomEnemy].GetHealth() << '\n';

                cout << '\n' << gui4 << "\n\n";

                cout << "What Now?\n\n";

                cout << "1) Continue\n";
                cout << "2) Heal\n";
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
						cout << "\nInvalid Decision.\n\n";
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
                GameInfo();

                break;
            case 4:
                cout << "\n\nGoodbye\n\n\n";

				return 0;
                break;

            default:
                cout << "\nInvalid Decision, please enter an integer or valid integer choice.\n\n";
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

void UserInterface::DisplayAttackMenu(Player& Hero)
{
	int counter{ 1 };
                
    cout << "\nUse what attack?\n\n";

	for (auto& i : Hero.GetAttackList())
    {
        if (Hero.GetAttackList().empty())
        {
            cout << Hero.GetName() << "'s attack list is empty!\n";
        }
        else
        {
			cout << counter++ << ") " << i << '\n';
        }
    }
}

void UserInterface::DisplayPlayerStats(Player& Hero)
{
	cout << "\nCurrent Turn: " << turn++ << " | Total Turns: " << totalTurns++ << " | Battles Won: " << battles << " | Enemies Defeated: " << Hero.GetKillCount() << "\n\n";

    cout << Hero.GetName() << "\n\n";

    cout << Hero.GetName() << "'s Health:     " << Hero.GetHealth() << '\n';
    cout << Hero.GetName() << "'s Gold:       " << Hero.GetMoney() << '\n';
    cout << Hero.GetName() << "'s Experience: " << Hero.GetCurrentExperience() << "/" << Hero.CalculateExperience() << '\n';
    cout << Hero.GetName() << "'s Level:      " << Hero.GetLevel() << "/" << Hero.GetMaxLevel() << '\n';
}

void GameInfo()
{
    cout << "Created by: Chay Hawk\n";
    cout << "Lines of code: 1,152\n";
    cout << "Created on: 3/7/2021 @ 4:27 AM\n";
}
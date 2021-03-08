// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>
#include <limits>
#include <tuple>

#include "Character.h"

void Character::TakeDamage(int amount)
{
    mHealth -= amount;
}

void Character::GiveMoney(int amount)
{
    mMoney += amount;
}

//This will simply just set health to 100
void Character::ResetHealth()
{
    mHealth = MAX_HEALTH;
}

void Character::Heal(int amount)
{
    if (mHealth + amount > MAX_HEALTH)
    {
        mHealth = MAX_HEALTH;
    }
    else
    {
		mHealth += amount;
    }
}

void Character::AddItemToInventory(Item& item, int amount)
{
    mInventory.push_back(make_tuple(item, amount));
}

vector<Attack>& Character::GetAttackList()
{
    return mAttackList;
}

vector<tuple<Item, int>> Character::GetInventory() const
{
    return mInventory;
}

//This will allow each character to have their own moves, it will
//require more typing but allows for finer control over what character
//has what move instead of creating a vector and adding attacks to
//that and then adding that set move list to each character.
void Character::SetAttackList(Attack& attack)
{
    mAttackList.push_back(attack);
}

//void SetCharacterList(Character& character) const
//{
//    for (auto& i : /*Character list*/)
//    {
//        if (i.GetName() == /*Character*/.GetName())
//        {
//            cout << /*Character list*/.GetName() << " is already in this character's moveset." << endl;
//        }
//        else
//        {
//			/*Character list*/.push_back(/*Character*/);
//        }
//    }
//}

/*TO DO
* This function doesnt have any way to discern which item was used.
* can only be used with healing items. It is fine like it is but it 
* needs to be able to affect the right items when used, so if the 
* player uses a health item it should add to health, if the player
* picks up ammo, it should add ammo to the correct weapon, etc.
*/

void Character::UseItem()
{
    int choice{ 0 };
    int counter{ 1 };

    while (choice != -1)
    {
		if (mInventory.empty())
        {
            cout << "You do not have any items to use." << endl;
            choice = -1;
        }
        else
        {
			cout << "\n################################################################" << endl;
            cout << "                          INVENTORY                        " << endl;
            cout << "################################################################" << endl;

			cout << "What item do you want to use? Type -1 to quit\n" << endl;
			cout << GetName() << "'s current health is: " << mHealth << "\n" << endl;

            counter = 1;

			//=================================================================================================
            //DISPLAY INVENTORY
            //=================================================================================================

            for (auto& i : mInventory)
            {
                cout << counter++ << ") " << get<0>(i) << " (" << get<1>(i) << ")" << " Effect: " << get<0>(i).GetEffect() << endl;
            }

            cin >> choice;

            counter = 1;

			//=================================================================================================
            //VALIDATE INPUT AND UPDATE INVENTORY WITH PLAYER CHOICE
            //=================================================================================================

            if (!cin.fail() && choice < mInventory.size() + 1)
            {
				//If amount of items owned is greater than 0, and health is not full
                if (get<1>(mInventory[choice - 1]) > 0 && mHealth != MAX_HEALTH)
                {
                    get<1>(mInventory[choice - 1])--;
                    Heal(get<0>(mInventory[choice - 1]).GetEffect());
                    cout << "\n" << GetName() << "'s health restored to " << GetHealth() << "\n" << endl;

                    //Remove item from inventory if there is no more of it.
                    if (get<1>(mInventory[choice - 1]) == 0)
                    {
                        mInventory.erase(mInventory.begin() + choice -1);
                    }
                }
                else if (mHealth == MAX_HEALTH)
                {
                    cout << "\nYou are already at full health.\n" << endl;
                }
                else
                {
                    cout << "\nYou do not have enough " << get<0>(mInventory[choice - 1]).GetName() << "'s" << " to use\n\n" << endl;
                }
            }
            else
            {
                cout << "Error, Invalid Input" << endl;
			    cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }   
        }
    }
}
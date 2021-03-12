// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>
#include <limits>

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
    mHealth = GetMaxHealth();
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

vector<Attack>& Character::GetAttackList()
{
    return mAttackList;
}

//This will allow each character to have their own moves, it will
//require more typing but allows for finer control over what character
//has what move instead of creating a vector and adding attacks to
//that and then adding that set move list to each character.
void Character::GiveAttack(Attack& attack)
{
	mAttackList.push_back(attack);
}

/*TO DO
* This function doesnt have any way to discern which item was used.
* can only be used with healing items. It is fine like it is but it 
* needs to be able to affect the right items when used, so if the 
* player uses a health item it should add to health, if the player
* picks up ammo, it should add ammo to the correct weapon, etc.
*/

void Character::UseItem()
{
  //  int choice{ 0 };
  //  int counter{ 1 };

  //  while (choice != -1)
  //  {
		//if (mInventory.GetInventory().size())
  //      {
  //          cout << "You do not have any items to use." << endl;
  //          choice = -1;
  //      }
  //      else
  //      {
		//	cout << "\n################################################################" << endl;
  //          cout << "                          INVENTORY                        " << endl;
  //          cout << "################################################################" << endl;

		//	cout << "What item do you want to use? Type -1 to quit\n" << endl;
		//	cout << GetName() << "'s current health is: " << mHealth << "\n" << endl;

  //          counter = 1;

		//	//=================================================================================================
  //          //DISPLAY INVENTORY
  //          //=================================================================================================

  //          for (auto& i : mInventory.GetInventory())
  //          {
  //              cout << counter++ << ") " << mInventory.GetName() << " (" << mInventory.GetItemsOwned() << ")" << " Effect: " << i.GetEffect() << endl;
  //          }

  //          cin >> choice;

  //          counter = 1;

		//	//=================================================================================================
  //          //VALIDATE INPUT AND UPDATE INVENTORY WITH PLAYER CHOICE
  //          //=================================================================================================

  //          if (!cin.fail() && choice < mInventory.GetInventory().size() + 1)
  //          {
		//		//If amount of items owned is greater than 0, and health is not full
  //              if (mInventory.GetItemsOwned() > 0 && mHealth != MAX_HEALTH)
  //              {
  //                  mInventory.DecrementItemsOwned(1);
  //                  Heal(item.GetEffect());
  //                  cout << "\n" << GetName() << "'s health restored to " << GetHealth() << "\n" << endl;

  //                  //Create an index variable to make things a little easier to read.
  //                  int index = choice - 1;

  //                  //Remove item from inventory if there is no more of it.
  //                  if (mInventory.GetItemsOwned() == 0)
  //                  {
  //                      mInventory.GetInventory().erase(mInventory.GetInventory().begin() + index);
  //                  }
  //              }
  //              else if (mHealth == MAX_HEALTH)
  //              {
  //                  cout << "\nYou are already at full health.\n" << endl;
  //              }
  //              else
  //              {
  //                  cout << "\nYou do not have enough " << item.GetName() << "'s" << " to use\n\n" << endl;
  //              }
  //          }
  //          else
  //          {
  //              cout << "Error, Invalid Input" << endl;
		//	    cin.clear();
  //              cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //          }   
  //      }
  //  }
}
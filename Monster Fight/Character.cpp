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
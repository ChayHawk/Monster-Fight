// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Player.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

int Player::GetCurrentExperience() const 
{ 
    return mExperience; 
}

void Player::GiveExperience(int amount)
{
    if (amount <= mMaxLevel * xpMultiplier)
    {
        mExperience += amount;
    }
    if(amount > mMaxLevel * xpMultiplier || mExperience > mMaxLevel * xpMultiplier)
    {
        mExperience = mMaxLevel * xpMultiplier; //Set to max experience if its higher than the max.
    }
}

void Player::IncrememntKillCounter()
{
    mKills++;
}

int Player::GetKillCount() const 
{ 
    return mKills; 
}

void Player::LevelUp()
{
    if (mCurrentLevel >= mMaxLevel)
    {
        mCurrentLevel = mMaxLevel;
        std::cout << "Max Level Reached." << endl;
    }
    else if (mExperience >= CalculateExperience())
    {
        while (mExperience > CalculateExperience())
        {
            ++mCurrentLevel;
        }
    }
}

int Player::GetLevel() const 
{ 
    return mCurrentLevel; 
}

int Player::GetMaxLevel() const 
{ 
    return mMaxLevel; 
}

int Player::CalculateExperience()
{
    return xpMultiplier * mCurrentLevel;
}

ostream& operator<<(ostream& os, const Player& player)
{
    os << player.GetMoney() << endl;
    os << player.GetCurrentExperience() << endl;

    os << static_cast<const Character&>(player);

    return os;
}
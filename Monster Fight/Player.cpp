// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Player.h"

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

void Player::LevelUp()
{
    if (mCurrentLevel >= mMaxLevel)
    {
        mCurrentLevel = mMaxLevel;
        cout << "Max Level Reached." << endl;
    }
    else if (mExperience >= CalculateExperience())
    {
        while (mExperience > CalculateExperience())
        {
            ++mCurrentLevel;
        }
    }
}

int Player::CalculateExperience()
{
    return xpMultiplier * mCurrentLevel;
}

void Player::SetLevel(int setLevelTo)
{
    mCurrentLevel = setLevelTo;
}

void Player::IncrememntKillCounter()
{
    mKills++;
}
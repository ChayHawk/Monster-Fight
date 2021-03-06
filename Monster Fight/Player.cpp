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

void Player::TestLevellingAndXPSystem()
{
    Player test;
    test.SetLevel(1); 

    int choice{ 0 };
    int amount{ 0 };

    while (choice != -1)
    {
        cout << "Type -1 to end testing" << endl;
        cout << "Give How much XP?" << endl;
        cout << ">";
        cin >> amount;

        if (cin.fail())
        {
            cout << "Invalid integral type entered." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            //Apply amount entered above
            test.GiveExperience(amount);
            test.LevelUp();

            while (choice != -1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nCurrent Experience: " << test.GetCurrentExperience() << "/" << test.CalculateExperience() << endl;
                cout << "Current Level: " << test.GetLevel() << endl;
                cout << "Give " << amount << " XP" << endl;
                test.GiveExperience(amount);
                cout << "Try Level Up" << endl;
                test.LevelUp();

                cin >> choice;
            }
        }
    }
}
#pragma once
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <limits>

#include "Attack.h"
#include "Enemy.h"

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

class Player : public Character
{
    public:
        Player
        (
            const string& name,
            int health, 
            vector<Attack>& attackList,
            vector<tuple<Item, int>>& inventory,
            int money,
            int experience,
            int level
        ) : Character{ name, health, attackList, inventory, money}, mExperience(experience), mCurrentLevel(level)
        {}
        Player() = default;

        int GetCurrentExperience() const { return mExperience; }
        void GiveExperience(int amount);

        void LevelUp();

        int GetLevel() const { return mCurrentLevel; }
        int GetMaxLevel() const { return mMaxLevel; }

        int CalculateExperience();

        friend ostream& operator<<(ostream& os, const Player& player)
        {
            os << player.GetMoney() << endl;
            os << player.GetCurrentExperience() << endl;

            os << static_cast<const Character&>(player);

            return os;
        }

        static void TestLevellingAndXPSystem(); //For debugging
        void SetLevel(int setLevelTo); //For debugging

    private:
        int mExperience{ 0 };
        int mCurrentLevel{ 1 };
        const int mMaxLevel{ 100 };
        const int xpMultiplier = 300;
};
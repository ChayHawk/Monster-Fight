#pragma once
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

#include "Attack.h"
#include "Character.h"

using std::endl;
using std::ostream;
using std::string;
using std::vector;

class Character;

class Enemy : public Character
{
    public:
        Enemy
        (
            const string& name,
            int health,
            vector<tuple<Item, int>>& inventory,
            int xpToGive,
            int money
        ) : Character{ name, health, inventory, money}, mXpToGive(xpToGive)
        {}

        int GetXpToGive() const { return mXpToGive; }
        void XpToGive(int amount);

    private:
        int mXpToGive{ 0 }; //How much XP the player will recieve when this enemy is defeated
};
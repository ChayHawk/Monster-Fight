// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

using std::endl;
using std::ostream;
using std::string;
using std::vector;

class Character;
class Inventory;

class Enemy : public Character
{
    public:
        Enemy
        (
            const string& name,
            int health,
            int maxHealth,
            int xpToGive,
            int money
        ) : Character{ name, health, maxHealth, money}, mXpToGive(xpToGive)
        {}

        int GetXpToGive() const { return mXpToGive; }
        void XpToGive(int amount);

    private:
        int mXpToGive{ 0 }; //How much XP the player will recieve when this enemy is defeated
};

#endif
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef CHARACTER_H
#define CHARACTER_H
#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

#include "Item.h"
#include "Attack.h"
#include "Inventory.h"

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::string;
using std::vector;

class Enemy;

class Character
{
    public:
        string GetName() const { return mName; }
        int GetHealth() const { return mHealth; }
        int GetMoney() const { return mMoney; }

        void TakeDamage(int amount);
        void GiveMoney(int amount);
        void ResetHealth();
		void Heal(int amount);

        vector<Attack>& GetAttackList();
        void GiveAttack(Attack& attack);
        
        int GetMaxHealth() const { return MAX_HEALTH; }

        friend ostream& operator<<(ostream& os, const Character& character)
        {
            os << character.GetName() << endl;
            os << character.GetHealth() << endl;

            return os;
        }

        //Protected because we dont want the user to create Characters, we want them to create players.
    protected:
        Character
        (
            const string& name, 
            int health, 
            const int maxHealth,
            int money
        ) :     mName(name), 
                mHealth(health),
                MAX_HEALTH(maxHealth),
                mAttackList(0),
                mMoney(money)
        {}
        Character() = default;

    private:
        string mName{ "Character Name" };
        int mHealth{ 100 };
        vector<Attack> mAttackList{ 0 };
        Item item;
        int mMoney{ 10 };

		const int MAX_HEALTH{ 100 };
};

#endif
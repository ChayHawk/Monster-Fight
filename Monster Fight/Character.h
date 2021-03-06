#pragma once
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <tuple>

#include "Attack.h"
#include "Item.h"

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::string;
using std::vector;
using std::numeric_limits;
using std::max;
using std::streamsize;
using std::tuple;
using std::make_tuple;
using std::get;

class Enemy;

class Character
{
    public:
        string GetName() const { return mName; }
        int GetHealth() const { return mHealth; }
        int GetMoney() const { return mMoney; }

        void TakeDamage(const Attack& attack);
        void TakeDamage(int amount);
        void GiveMoney(int amount);
        void ResetHealth();
		void Heal(int amount);
        void UseItem();
        vector <tuple<Item, int>> GetInventory() const;

        void AddItemToInventory(Item& item, int amount);
        void SetAttackList(vector<Attack>& attackList);
        vector<Attack> GetAttackList() const;
        void UseAttack(vector<Attack> attack);

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
            vector<Attack>& attackList,
            vector<tuple<Item, int>>& inventory,
            int money
        ) :     mName(name), 
                mHealth(health), 
                mAttackList(attackList),
                mInventory(inventory),
                mMoney(money)
        {}
        Character() = default;

    private:
        string mName{ "Character Name" };
        int mHealth{ 100 };
        vector<Attack> mAttackList;
        vector<tuple<Item, int>> mInventory;
        int mMoney{ 10 };

		const int MAX_HEALTH{ 100 };
};
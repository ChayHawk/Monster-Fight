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

class Enemy;

class Character
{
    public:
        std::string GetName() const;
        int GetHealth() const;
        int GetMaxHealth() const;
		void ResetHealth();
		void Heal(int amount);
		void GiveMoney(int amount);
        int GetMoney() const;

        void AddItemToInventory(Item& item, int amount);
        void OpenInventory();
        void ClearInventory();
        void UseInventoryItem();
        std::vector<std::pair<Item, int>>& GetInventory();

        void TakeDamage(int amount);

        void GiveAttack(Attack& attack);
		std::vector<Attack>& GetAttackList();

        friend std::ostream& operator<<(std::ostream& os, const Character& character);

    //Protected because we dont want the user to create Characters, we want them to create players and enemies.
    protected:
        Character
        (
            const std::string& name, 
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

		std::string mName{ "Character Name" };

    protected:
        Inventory mInventory;

    private:
        int mHealth{ 100 };
        std::vector<Attack> mAttackList{ 0 };
        Item mItem;
        int mMoney{ 10 };

		const int MAX_HEALTH{ 100 };
};

#endif
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef INVENTORY_H
#define INVENTORY_H
#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#include "Player.h"
#include "Item.h"


class Inventory
{
	public:
		Inventory() = default;

		void Add(Item& item, int amount);
		void Open();
		void Clear();
		void UseItem(Player& Hero);

	private:
		vector<Item> mInventory{ 0 };
		int amountOwned{ 0 };
		int mItemsOwned{ 0 };

		int GetItemsOwned() const { return mItemsOwned; }
		void SetItemsOwned(int amount) { mItemsOwned = amount; }
		void IncrementItemsOwned(int amount) { mItemsOwned += amount; }
		void DecrementItemsOwned(int amount) { mItemsOwned -= amount; }

		vector<Item>& GetInventory();
};

#endif
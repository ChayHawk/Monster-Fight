#pragma once

#ifndef INVENTORY_H
#define INVENTORY_H

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

		int GetItemsOwned() const { return mItemsOwned; }
		void SetItemsOwned(int amount) { mItemsOwned = amount; }
		void IncrementItemsOwned(int amount) { mItemsOwned += amount; }
		void DecrementItemsOwned(int amount) { mItemsOwned -= amount; }

		vector<Item>& GetInventory();

	private:
		vector<Item> mInventory{ 0 };
		int amountOwned{ 0 };
		int mItemsOwned{ 0 };
};

#endif
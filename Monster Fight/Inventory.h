#ifndef INVENTORY_H
#define INVENTORY_H
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <utility>
#include <iterator>

#include "Item.h"

class Player;

class Inventory
{
	public:
		Inventory() = default;

		void Add(Item& item, int amount);
		void Open();
		void Clear();
		void UseItem(Player& Hero);

		std::vector<std::pair<Item, int>>& GetInventory();

	private:
		std::vector<std::pair<Item, int>> mInventory{ 0 };
		int mItemsOwned{ 0 };
		Item item;


		void IncrementItemsOwned(int amount, int index);
		void DecrementItemsOwned(int amount, int index);
};

#endif
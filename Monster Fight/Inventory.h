// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef INVENTORY_H
#define INVENTORY_H
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
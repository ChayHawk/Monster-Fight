// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef ITEM_H
#define ITEM_H
#pragma once

#include <iostream>
#include <string>
#include <ostream>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

class Item
{
	public:
		Item(const string& name, int cost, int effect): mName(name), mCost(cost), mEffect(effect)
		{}
		Item() = default;

		string GetName() const { return mName; }
		int GetCost() const { return mCost; }
		int GetEffect() const { return mEffect; }
		string GetInfo() const { return mInfo; }
		void SetInfo(const string& info) { mInfo = info; }

		friend ostream& operator<<(ostream& os, const Item& item)
        {
            os << item.GetName();


            return os;
        }

	private:
		string mName{ "Item Name" };
		int mCost{ 0 };
		int mEffect{ 0 }; //Effect can be used to give soemthing like health, ammo etc.
		string mInfo{ "Item Info" }; //Not setup yet
};

#endif
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef ITEM_H
#define ITEM_H
#pragma once

#include <string>
#include <ostream>

class Item
{
	public:
		Item(const std::string& name, int effect): mName(name), mEffect(effect)
		{}
		Item() = default;

		std::string GetName() const;
		int GetEffect() const;
		std::string GetInfo() const;
		void SetInfo(const std::string& info);

		friend std::ostream& operator<<(std::ostream& os, const Item& item);

	private:
		std::string mName{ "Item Name" };
		int mEffect{ 0 }; //Effect can be used to give soemthing like health, ammo etc.
		std::string mInfo{ "Item Info" }; //Not setup yet
};

#endif
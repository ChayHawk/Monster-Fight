// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Item.h"

using std::string;
using std::ostream;

string Item::GetName() const 
{ 
	return mName; 
}

int Item::GetEffect() const 
{ 
	return mEffect; 
}

string Item::GetInfo() const 
{ 
	return mInfo; 
}

void Item::SetInfo(const string& info) 
{ 
	mInfo = info; 
}

ostream& operator<<(ostream& os, const Item& item)
{
    os << item.GetName();


    return os;
}
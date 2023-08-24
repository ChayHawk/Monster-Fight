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
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Attack.h"

using std::endl;
using std::ostream;
using std::string;

string Attack::GetName() const 
{ 
    return mName; 
}

int Attack::GetPower() const 
{ 
    return mPower; 
}

ostream& operator<<(ostream& os, const Attack& attack)
{
    os << attack.GetName() << " | Power: ";
    os << attack.GetPower();

    return os;
}
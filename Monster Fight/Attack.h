#pragma once
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <string>
#include <ostream>

using std::endl;
using std::ostream;
using std::string;

class Attack
{
    public:
        Attack(const string& name, int power) : mName(name), mPower(power)
        {}
        Attack() = default;

        string GetName() const { return mName; }
        int GetPower() const { return mPower; }

        friend ostream& operator<<(ostream& os, const Attack& attack)
        {
            os << attack.GetName() << " | Power: ";
            os << attack.GetPower();

            return os;
        }

    private:
        string mName{ "Attack Name" };
        int mPower{ 0 };
};
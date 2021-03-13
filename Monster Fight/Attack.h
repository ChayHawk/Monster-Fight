// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#pragma once

#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include <string>
#include <ostream>

class Attack
{
    public:
        Attack(const std::string& name, int power) : mName(name), mPower(power)
        {}
        Attack() = default;

        std::string GetName() const;
        int GetPower() const;

        friend std::ostream& operator<<(std::ostream& os, const Attack& attack);

    private:
        std::string mName{ "Attack Name" };
        int mPower{ 0 };
};

#endif
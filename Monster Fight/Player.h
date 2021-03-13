// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

#include "Character.h"


class Player : public Character
{
    public:
        Player
        (
            const std::string& name,
            int health, 
            int maxHealth,
            int money,
            int experience,
            int level
        ) : Character{ name, health, maxHealth, money}, mExperience(experience), 
                                                        mCurrentLevel(level),
                                                        mKills(0)
        {}
        Player() = default;

        int GetCurrentExperience() const;
        void GiveExperience(int amount);
        void IncrememntKillCounter();
        int GetKillCount() const;

        void LevelUp();

        int GetLevel() const;
        int GetMaxLevel() const;

        int CalculateExperience();

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

    private:
        int mExperience{ 0 };
        int mCurrentLevel{ 1 };
        const int mMaxLevel{ 100 };
        const int xpMultiplier = 300;
		int mKills{ 0 };
};

#endif
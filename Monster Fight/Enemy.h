#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include <string>
#include <iterator>

#include "Character.h"

class Enemy : public Character
{
    public:
        Enemy
        (
            const std::string& name,
            int health,
            int maxHealth,
            int xpToGive,
            int money
        ) : Character{ name, health, maxHealth, money}, mXpToGive(xpToGive)
        {}

        int GetXpToGive() const;
        void XpToGive(int amount);

    private:
        int mXpToGive{ 0 }; //How much XP the player will recieve when this enemy is defeated
};

#endif
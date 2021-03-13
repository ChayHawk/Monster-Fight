// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Enemy.h"

int Enemy::GetXpToGive() const 
{ 
	return mXpToGive; 
}

void Enemy::XpToGive(int amount)
{
	mXpToGive += amount;
}
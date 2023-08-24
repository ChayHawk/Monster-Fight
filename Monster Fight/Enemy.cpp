#include "Enemy.h"

int Enemy::GetXpToGive() const 
{ 
	return mXpToGive; 
}

void Enemy::XpToGive(int amount)
{
	mXpToGive += amount;
}
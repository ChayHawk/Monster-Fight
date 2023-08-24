#include "Player.h"

using std::cout;
using std::cin;
using std::ostream;
using std::string;
using std::vector;

int Player::GetCurrentExperience() const 
{ 
    return mExperience; 
}

void Player::GiveExperience(int amount)
{
    if (amount <= mMaxLevel * xpMultiplier)
    {
        mExperience += amount;
    }
    if(amount > mMaxLevel * xpMultiplier || mExperience > mMaxLevel * xpMultiplier)
    {
        mExperience = mMaxLevel * xpMultiplier; //Set to max experience if its higher than the max.
    }
}

void Player::IncrememntKillCounter()
{
    mKills++;
}

int Player::GetKillCount() const 
{ 
    return mKills; 
}

void Player::LevelUp()
{
    if (mCurrentLevel >= mMaxLevel)
    {
        mCurrentLevel = mMaxLevel;
        std::cout << "Max Level Reached.\n\n";
    }
    else if (mExperience >= CalculateExperience())
    {
        while (mExperience > CalculateExperience())
        {
            ++mCurrentLevel;
        }
    }
}

int Player::GetLevel() const 
{ 
    return mCurrentLevel; 
}

int Player::GetMaxLevel() const 
{ 
    return mMaxLevel; 
}

int Player::CalculateExperience()
{
    return xpMultiplier * mCurrentLevel;
}

void Player::SetName()
{
    std::string name;
    bool nameIsValid = false;
    int invalidNameCounter{ 0 };


    while (nameIsValid != true)
    {
		cout << "What is your name?\n\n";

        getline(cin, name);

        if (name.empty())
        {
            invalidNameCounter++;

            switch (invalidNameCounter)
            {
                case 1:
					cout << "You cannot have an empty name!\n\n";
                    break;

                case 2:
					cout << "Didnt I just tell you that you cannot have an empty name?!\n\n";
                    break;

                case 3:
					cout << "Dude, enter a damn name already!\n\n";
                    break;

                case 4:
					cout << "Ok, now you're really pissing me off.\n\n";
                    break;

				case 5:
					cout << "Last warning, ENTER A NAME!!!.\n\n";
                    break;

                case 6:
                    cout << "Clearly, you're an asshole, so you know what? your name is asshole now!\n\n";

                    mName = "Asshole";
					cout << "\nWelcome " << mName << "!\n\n";
                    nameIsValid = true;

                    break;

                default:
                    cout << "That was an invalid entry\n\n";
            }
        }
        else
        {
			mName = name;
            cout << "\nWelcome " << mName << "!\n\n";
            nameIsValid = true;
        }
    }
}

ostream& operator<<(ostream& os, const Player& player)
{
    os << player.GetMoney() << '\n';
    os << player.GetCurrentExperience() << '\n';

    os << static_cast<const Character&>(player);

    return os;
}
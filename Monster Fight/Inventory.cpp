#include "Inventory.h"
#include "Player.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::max;
using std::numeric_limits;
using std::streamsize;
using std::distance;
using std::pair;
using std::make_pair;

void Inventory::Add(Item& item, int amount)
{
	std::string name = item.GetName();

    vector<pair<Item, int>>::iterator itr = find_if(mInventory.begin(), mInventory.end(), 
                                            [name](const std::pair<Item, int> & p)
                                            {  
                                                return p.first.GetName() == name; 
                                            }); 

    int index = distance(mInventory.begin(), itr);

    //If we find an item that already exists in the vector, then just add to
    //the current amount owned, and if not then push back the item and the amount.
    if (itr != mInventory.end())
    {
        //cout << "Found " << item.GetName() << " in vector, at index: " << index << " which is the #" << index + 1 << " spot in the vector." << endl;
        IncrementItemsOwned(amount, index + 1);
    }
    else
    {
        //cout << "Did not find " << item.GetName() << " in vector, so it was added." << endl;
        mInventory.push_back(std::make_pair(item, amount));
    }
}

void Inventory::Open()
{
	for (auto& i : mInventory)
	{
		cout << i.first.GetName() << "(" << i.second << ")";
	}
}

void Inventory::Clear()
{
    GetInventory().clear();
}

vector<std::pair<Item, int>>& Inventory::GetInventory()
{
	return mInventory;
}

void Inventory::DecrementItemsOwned(int amount, int index) 
{ 
    mInventory[index -1].second -= amount;
}

void Inventory::IncrementItemsOwned(int amount, int index)
{
    mInventory[index - 1].second += amount;
}

void Inventory::UseItem(Player& Hero)
{
	int choice{ 0 };
    int counter{ 1 };

    while (choice != -1)
    {
		if (GetInventory().size() == 0)
        {
            cout << "You do not have any items to use.\n";
            choice = -1;
        }
        else
        {
			cout << "\n################################################################\n";
            cout << "                          INVENTORY                        \n";
            cout << "################################################################\n";

			cout << "What item do you want to use? Type -1 to quit\n\n";
			cout << Hero.GetName() << "'s current health is: " << Hero.GetHealth() << "\n\n";

            counter = 1;

			//=================================================================================================
            //DISPLAY INVENTORY
            //=================================================================================================

            for (auto& i : GetInventory())
            {
                cout << counter++ << ") " << i.first.GetName() << " (" << i.second << ")" << " Effect: " << i.first.GetEffect() << '\n';
            }

            cin >> choice;

            counter = 1;

			//=================================================================================================
            //VALIDATE INPUT AND UPDATE INVENTORY WITH PLAYER CHOICE
            //=================================================================================================
            if (choice == -1)
            {
                break;
            }
            else
            {
				if (!cin.fail() && choice < GetInventory().size() + 1)
                {
					//Create an index variable to make things a little easier to read.
                    int index = choice - 1;

				    //If amount of items owned is greater than 0, and health is not full
                    if (mInventory[index].second > 0 && Hero.GetHealth() != Hero.GetMaxHealth())
                    {
                        DecrementItemsOwned(1, choice);
                        Hero.Heal(mInventory[index].first.GetEffect());
                        cout << "\n" << Hero.GetName() << "'s health restored to " << Hero.GetHealth() << "\n\n";

                        //Remove item from inventory if there is no more of it.
                        if (mInventory[index].second == 0)
                        {
                            GetInventory().erase(GetInventory().begin() + index);
                        }
                    }
                    else if (Hero.GetHealth() == Hero.GetMaxHealth())
                    {
                        cout << "\nYou are already at full health.\n\n";
                    }
                    else
                    {
                        cout << "\nYou do not have enough " << mInventory[choice].first.GetName() << "'s" << " to use\n\n";
                    }
                }
                else
                {
                    cout << "Error, Invalid Input\n";
			        cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }       
            }
        }
    }
}
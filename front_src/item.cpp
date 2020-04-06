//Description: Class that stores information of the for-sale items

//Inputs: the sale item's name, the sale item's current bid, the sellers username, the end date of the auction
#include <string>
#include "item.h"
using namespace std;
	
Item::Item(string itemName, string sellerUsername, double currentBid, string bidUsername, int daysLeft){
	itemName = itemName;
	sellerUsername = sellerUsername;
	currentBid = currentBid;
	bidUsername = bidUsername;
	daysLeft = daysLeft;
}

string Item::getItemName()
{
	return itemName;
}

string Item::getSellerUsername()
{
	return sellerUsername;
}

// returns the highest current bid
double Item::getCurrentBid()
{
	return currentBid;
}

// returns the highest current bidder's username
string Item::getBidUsername()
{
	return bidUsername;
}

// returns the amount of time until the auction is done
int Item::getDaysLeft()
{
	return daysLeft;
}

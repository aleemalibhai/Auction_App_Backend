#ifndef ITEM_HEADER
#define ITEM_HEADER
//Description: Class that stores information of the for-sale items

//Inputs: the sale item's name, the sale item's current bid, the sellers username, the end date of the auction
#include <string>
using namespace std;

class Item{
	
	private:
		string itemName;
		double currentBid;
		string bidUsername;
		int daysLeft;
		string sellerUsername;

	public:
		string getItemName(); // returns the name of the item
		double getCurrentBid(); // returns the highest current bid
		string getBidUsername(); // returns the highest current bidder's username
		int getDaysLeft(); // returns the amount of time until the auction is done
		string getSellerUsername(); // returns the name of the user selling the item
		
		Item(string itemName, string sellerUsername, double currentBid, string bidUsername, int daysLeft); // constructor
};

#endif

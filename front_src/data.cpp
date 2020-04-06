//Description: Class to store the items
//Stores the items for auction

//Inputs: array of items for bid

//Imports the Item class from item.cpp
#include <vector>
#include <string>
#include <fstream>
#include "data.h"
#include "item.h"

using namespace std;

Data::Data(string itemFile, string userFile, string transactionFile)
{
    itemFileName = itemFile;
    userFileName = userFile;
    transactionFileName = transactionFile;
}

// returns a list of all items for sale
void Data::readItemList()
{
	std::ifstream infile(itemFileName);
	
	string name;
	string seller;
	string highBidder;
	int days;
	double highBid;
	
	while(infile >> name >> seller >> highBidder >> days >> highBid)
	{
		Item newItem(name, seller, highBid, highBidder, days);
		items.push_back(newItem);
	}
}

string Data::getUserFileName() {
    return userFileName;
}

string Data::getItemFileName() {
    return itemFileName;
}
string Data::getTransactionFileName() {
    return transactionFileName;
}
void Data::addTransaction(string transaction){
    transactions.push_back(transaction);
}

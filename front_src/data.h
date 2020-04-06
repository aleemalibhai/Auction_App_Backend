#ifndef DATA_HEADER
#define DATA_HEADER

//Description: Class to store the items
//Stores the items for auction

//Inputs: array of items for bid

//Imports the Item class from item.cpp
#include <vector>
#include "item.h"
#include <string>
using namespace std;

class Data{
	
	private:
		void readItemList(); // returns a list of all items for sale
		string userFileName;
		string itemFileName;
		string transactionFileName;
		
	public:
    	vector<Item> items;
    	vector<string> transactions;
		Data(string itemFile, string userFile, string transactionFile); // constructor
		string getUserFileName(); // returns the name of the file that stores the users
		string getItemFileName(); // returns the name of the file that stores the items
		string getTransactionFileName(); // returns the name of the transaction file
        void addTransaction(string transaction);
};

#endif
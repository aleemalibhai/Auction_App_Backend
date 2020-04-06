#include <iostream>
#include <string>
#include "driver.h"
#include "data.h"

using namespace std;

int main(int argc, char** argv){
    // create data object
    string accounts;
    string items;
    string transactions;
    if (argc != 4){
        cout << "Wrong number of arguments input must be ./Auction_app <AccountFile> <ItemsFile> <TransactionFile>" <<endl;
        cout << "Using hard coded defaults!" <<endl;
        accounts = (string)"resources/users.txt";
        items = (string)"resources/items.txt";
        transactions = (string)"resources/daily_transactions.txt";
    } else {
        accounts = argv[1];
        items = argv[2];
        transactions = argv[3];
    }

    Data data(items, accounts, transactions);
    Driver dr;
	// while loop that continues until exit command is input	
	while (true) {
		// loop to allow continuous input
		dr.input(data);
	}
	
	return 0;
}


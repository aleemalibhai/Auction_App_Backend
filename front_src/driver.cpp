//Description: Class to initiate the code.
//Allows any user to login and logout. Acts as the standard location for input.

//Inputs: the logged in user (of type User)

//Imports the User class from users.cpp
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "user.h"
#include "driver.h"
#include "data.h"

using namespace std;

//User *currentUser;
//bool isLoggedIn = false;

void Driver::logout(Data &data){ // ugly af, if we store the current user's original line from users.txt we just need to add a 00_ to the front of it
	// write daily transaction file.

	string writeOut = "00                    000000000"; // end of session
	data.addTransaction(writeOut);

	ofstream outputFile;
	outputFile.open(data.getTransactionFileName(), ios_base::app);
	if (!outputFile){
	    outputFile.open(data.getTransactionFileName(), ios_base::out);
	}
	for (string out : data.transactions){
	    outputFile << out << endl;
	}
	outputFile.close();

	isLoggedIn = false;
	currentUser = NULL;
	data.transactions.clear();
}


User Driver::getCurrentUser(Data &data){
	return *currentUser;
}


void Driver::setCurrentUser(string userName, Data &data){
	// reading the username file
	ifstream inFile;
	inFile.open(data.getUserFileName());
	if (!inFile){
		cout << data.getUserFileName() << " not found, check configuration" << endl;
		exit(1);
	}

	// add each line from the users text file to the "users" variable
	string line;
	vector<string> users;
	while (getline(inFile, line)){
		users.push_back(line);
	} 	
	

	for (int i = 0; i < users.size(); i++){
		// if username is valid
		if (userName == users[i].substr(0, userName.size())){
			string accountType;
			double credits;
	
			cout << "Valid username " << userName << endl;
			
			// finds user's account type
			accountType = users[i].substr(16, 2);
			cout << "User type: " << accountType << endl;
			
			// finds user's credits
			credits = stod(users[i].substr(19, 9));
            cout << "User credits: " << credits << endl;
			
			// assign a user subclass based on the user code's account type
			if (accountType == "AA"){
                Admin *temp = new Admin(userName, accountType, credits);
                currentUser = temp;
			} 
			else if (accountType == "FS"){
                Full_Standard *temp = new Full_Standard(userName, accountType, credits);
                currentUser = temp;
			} 
			else if (accountType == "BS"){
                Buy_Standard *temp = new Buy_Standard(userName, accountType, credits);
                currentUser = temp;
            } 
			else if (accountType == "SS"){
                Sell_Standard *temp = new Sell_Standard(userName, accountType, credits);
                currentUser = temp;
            }
			
			isLoggedIn = true;
		}
	}
	
	// if username is not valid
	if (!isLoggedIn){
		cout << userName << " is not a valid username" << endl;
	}
}


void Driver::login(Data &data){
	// first, ask for a username
	string userName;
	cout << "Enter username: " << endl; // username cannot have spaces
	cin >> userName;
	
	setCurrentUser(userName, data);

}


void Driver::input(Data &data) {
    string transaction = "";
	//while (true) {

		// ask for input
		string userInput;
		cout << "Input: " << endl;
		cin >> userInput;

		// if input is "login"
		if ((userInput == "login") || (userInput == "Login")) {
			if (!isLoggedIn){
				login(data);
			}
			else{
				cout << "Cannot complete login: already logged in. Try 'logout'" << endl;
			}
		}

		// if input is "logout"
		else if ((userInput == "logout") || (userInput == "Logout")){
			if (isLoggedIn){
				logout(data);
			}
			else{
				cout << "Cannot complete logout: not logged in. Try 'login'" << endl;
			}
		}





		// if input is "create"
		else if ((userInput == "create") || (userInput == "Create")){
			if ((isLoggedIn) && (currentUser->accountType == "AA")){
			    transaction = currentUser->createUser(data);
				cout << transaction << endl;
			}
			else{
				cout << "Cannot complete create." << endl;
			}
		}

		// if unput is "delete"
		else if ((userInput == "delete") || (userInput == "Delete")){
			if ((isLoggedIn) && (currentUser->accountType == "AA")){
				transaction = currentUser->deleteUser(data);
			}
			else{
				cout << "Cannot complete delete" << endl;
			}
		}

		// if unput is "advertise"
		else if ((userInput == "advertise") || (userInput == "Advertise")){
			if ((isLoggedIn) && ((currentUser->accountType == "AA") || (currentUser->accountType == "FS") || (currentUser->accountType == "SS"))){
				transaction = currentUser->advertise(data);
			}
			else{
				cout << "Cannot complete advertise." << endl;
			}
		}

		// if unput is "bid"
		else if ((userInput == "bid") || (userInput == "Bid")){
			if ((isLoggedIn) && ((currentUser->accountType == "AA") || (currentUser->accountType == "FS") || (currentUser->accountType == "BS"))){
				transaction = currentUser->bid(data);
			}
			else{
				cout << "Cannot complete bid." << endl;
			}
		}

		// if unput is "refund"
		else if ((userInput == "refund") || (userInput == "Refund")){
			if ((isLoggedIn) && (currentUser->accountType == "AA")){
				transaction = currentUser->refund(data);
			}
			else{
				cout << "Cannot complete refund." << endl;
			}
		}

		// if unput is "addCredit"
		else if ((userInput == "addcredit") || (userInput == "addCredit")){
			if (isLoggedIn){
			    cout << currentUser->accountType;
				transaction = currentUser->addCredits(data);

			}
			else{
				cout << "Cannot complete addcredit: not logged in." << endl;
			}
		}




		// if input is "exit"
		else if ((userInput == "exit") || (userInput == "Exit")){
			cout << "Goodbye!" << endl;

			if (isLoggedIn){
				// call logout to write daily transaction file if logged in
				logout(data);
			}

			exit(0);
		}

		// if input is not a valid command
		else{
			cout << userInput << " not a valid action." << endl;
		}
		if (transaction != ""){
            data.addTransaction(transaction);
		}

	//}
}






























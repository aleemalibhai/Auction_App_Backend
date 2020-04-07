#include <iostream>
#include <string>
#include <iostream>

#include "session.h"
#include "user.h"
#include "item.h"

using namespace std;

/*
    The driver of the program is going to be the session class. When the program first 
    starts, it is going to create a session instance and read the current user accounts. 
    
    Once it finishes reading the current user accounts, the main program will loop
    infinitely and in each loop, it will check whether the session is logged in or not
    If it isn't then it is going to prompt the user to keep on enterring a username. Once
    a login is successful, the session will read the available items file, then wait for a
    transaction input.  
*/
int main(int argc, char** argv){
    Session session(argv[1], argv[2], argv[3]);

    string username;
    string command;

    cout << "Welcome to auction site!" << endl;

    while (true) {
        if (!session.getIsLogin()) { 
            cout << "Enter username: ";
            cin >> username;
            cout << username << endl;
            // Add validation
            if (username == "exit"){
                cout << "\nGood bye!" << endl;
                break;
            }
            if(username == "bid" || username == "advertise" || username == "refund" || username == "addcredit" || username == "create" || username == "delete" || username == "logout"){
                cout << "\n[ERROR] Not logged in\n";
                continue;
            }
            session.login(username);   
        } else {
            User* u = session.currentUser;
            cout << "\nEnter command: ";
            cin >> command;
            if (command == "create") {
                if (u->userType == "AA"){
                    string uname, utype;
                    float credit;
                    cout << "\nEnter new username: ";
                    cin >> uname;
                    // Username validation
                    if(uname.length() > 15) {
                        cout << "\n[ERROR] Username has a 15 character limit" << endl;
                        continue;
                    } else if(session.isExist(uname)) {
                        cout << "\n[ERROR] Username has been taken" << endl;
                        continue;
                    } else if(uname == "bid" || uname == "advertise" || uname == "refund" || uname == "addcredit" || uname == "create" || uname == "delete" || uname == "logout"){
                        cout << "\n[ERROR] Invalid username" << endl;
                        continue;
                    }

                    cout << "\nUser Types:" << endl;
                    cout << "\tAA: Admin \n\tFS: Full-standard \n\tBS: Buy-standard \n\tSS: Sell-standard" << endl;
                    cout << "\nEnter user type: ";
                    cin >> utype;
                    // User Type validation
                    if(utype != "AA" && utype != "SS" && utype != "FS" && utype != "BS") { 
                        cout << "\n[ERROR] Invalid options" << endl;
                        continue;
                    }

                    cout << "\nEnter credit value: ";
                    cin >> credit;
                    // Credit amount validation
                    if(credit < 0 || credit > 999999) {
                        cout << "\n[ERROR] Invalid input" << endl;
                        continue;
                    }

                    session.transactions.push_back(u->create(uname, utype, credit));
                    cout << "\n[DONE] User created" << endl;
                    cout << u->create(uname, utype, credit) << endl;
                } else
                    cout << "\n[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "delete") {
                if (u->userType == "AA"){
                    string uname;
                    cout << "\nEnter target username: ";
                    cin >> uname;
                    // Username validation
                    if(!session.isExist(uname)) {
                        cout << "\n[ERROR] Username does not exist" << endl;
                        continue;
                    } else if(uname == username) {
                        cout << "\n[ERROR] Cannot delete your own account" << endl;
                        continue;
                    }

                    session.transactions.push_back(u->deleteUser(uname, session.userAccount));
                    cout << "\n[DONE] User deleted" << endl;
                    cout << u->deleteUser(uname, session.userAccount) << endl;
                } else
                    cout << "\n[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "bid") {
                if (u->userType == "SS")
                    cout << "\n[ERROR] Account Not Privilleged!" << endl;
                else {
                    string itemName, sellerName;
                    float price;
                    cout << "\nEnter item name: ";
                    cin >> itemName;
                    // Item name validation
                    if(!session.isItemExist(itemName)) {
                        cout << "\n[ERROR] Item unavailable" << endl;
                        continue;
                    } 
                    cout << "\nEnter seller's username: ";
                    cin >> sellerName;
                    // Seller name validation
                    if(!session.isExist(sellerName)) {
                        cout << "\n[ERROR] Invalid seller username" << endl;
                        continue;
                    }
                    float highestBid;
                    for(int i=0;i<session.availableItems.size();i++) {
                        if(session.availableItems[i].getSeller() == sellerName && session.availableItems[i].getItemName() == itemName) {
                            highestBid = session.availableItems[i].getCurrentPrice();
                            break;
                        }
                    }
                    cout << "\nCurrent highest bid is " << highestBid << endl;
                    cout << "Please enter new bid amount: ";
                    cin >> price;
                    // Add validation
                    //for user type: admin
                    if(u->userType == "AA"){
                        if (price < highestBid){
                            cout << "[ERROR] New bid needs to be higher than previous bid \n";
                            continue;
                        }
                    }

                    //checking if the user has enough funds to place the bid
                    if(u->credit < price){
                        cout << "[ERROR] Not enough credits to place the bid\n";
                        continue;
                    }

                    //for other valid user types 
                    if((u->userType != "AA") && price < (1.05*highestBid)){
                        cout << "[ERROR] New bid needs to be 5% higher than previous bid \n";
                        continue;
                    }

                    if (price > 999.99){
                        cout << "[ERROR] Item price can't exceed 999.99 \n";
                        continue;
                    }
                    session.transactions.push_back(u->bid(itemName, sellerName, u->getUsername(), price));
                    cout << "\n[DONE] Bid placed" << endl;
                    cout << u->bid(itemName, sellerName,  u->getUsername(), price) << endl;
                }
            } else if (command == "refund") {
                if (u->userType == "AA") {
                    string sellerName, buyerName;
                    float credit;
                    cout << "\nEnter seller's username: ";
                    cin >> sellerName;

                    // Seller name validation
                    if(!session.isExist(sellerName)) {
                        cout << "\n[ERROR] Seller does not exist" << endl;
                        continue;
                    } 

                    cout << "\nEnter buyer's username: ";
                    cin >> buyerName;

                    // Buyer name validation
                    if(!session.isExist(buyerName)) {
                        cout << "\n[ERROR] Buyer does not exist" << endl;
                        continue;
                    }

                    cout << "\nEnter amount of credit to be transferred: ";
                    cin >> credit;
                    
                    // Add validation
                    // checking if seller has sufficient funds(test: refund5)
                    if(session.isExist(sellerName)){
                        if(session.getUser(sellerName).getCredit() < credit){
                            cout << "[ERROR] Not enough funds to complete the transaction \n";
                            continue;
                        } 
                    }
                    //checking if issuing refund will exceed buyer's credit limit
                    if(session.getUser(buyerName).getCredit() + credit > 999999){
                        cout << "[ERROR] transaction cancelled as transfers leads to violation of credit limit\n";
                        continue; 
                    }
     

                    session.transactions.push_back(u->refund(sellerName, buyerName, credit));
                    
                    cout << "\n[DONE] Funds refunded" << endl;
                    cout << u->refund(sellerName, buyerName, credit) << endl;
                } else
                    cout << "\n[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "addcredit") {
                if (u->userType == "AA") {
                    string uname;
                    float credit;
                    cout << "\nEnter amount: ";
                    cin >> credit;
                    // Add validation
                    //checking if credit is <1001
                    if(credit > 1000){
                        cout << "[ERROR]: Credit to be added should not exceed 1000\n";
                        continue;
                    }
                    //checking if credit is >0.01
                    if(credit < 0.01){
                        cout << "[ERROR]: Minnimun credit to be added should be more than 0.01\n";
                        continue;
                    }
                    cout << "\nEnter target username: ";
                    cin >> uname;
                    // Seller name validation
                    if(!session.isExist(uname)) {
                        cout << "\n[ERROR] Username does not exist" << endl;
                        continue;
                    }

                    //checking if adding the credit will exceed the max credit limit
                    if(session.getUser(uname).getCredit() + credit > 999999){
                        cout << "[ERROR] can't perform transaction as tranfer exceeds max credit limit\n";
                        continue;
                    }
                    session.transactions.push_back(u->addCredit(uname, credit, session.userAccount));
                    cout << "\n[DONE] Credit added" << endl;
                    cout << u->addCredit(uname, credit, session.userAccount) << endl;
                } else{
                    float credit;
                    cout << "\nEnter amount: ";
                    cin >> credit;
                    // Add validation
                    //checking if credit is <1001
                    if(credit > 1000){
                        cout << "[ERROR]: Credit to be added should not exceed 1000\n";
                        continue;
                    }
                    //checking if credit is >0.01
                    if(credit < 0.01){
                        cout << "[ERROR]: Minnimun credit to be added should be more than 0.01\n";
                        continue;
                    }
                    session.transactions.push_back(u->addCredit(u->getUsername(), credit, session.userAccount));
                    cout << "\n[DONE] Credit added" << endl;
                    cout << u->addCredit(u->username, credit, session.userAccount) << endl;
                }

            } else if (command == "advertise") {
                if (session.currentUser->userType == "BS")
                    cout << "\n[ERROR] Account Not Privilleged!" << endl;
                else {
                    string itemName;
                    float bid;
                    int days;
                    cout << "\nEnter item name: ";
                    cin >> itemName;
                    // Item name validation
                    if(itemName.length() > 19) {
                        cout << "\n[ERROR] Item name has a 19 character limit" << endl;
                        continue;
                    }
                    cout << "\nEnter minimum bid: ";
                    cin >> bid;
                    // Minimum bid
                    if (bid > 999.99) {
                        cout << "\n[ERROR] Maximum bidding is 999.99" << endl;
                        continue;
                    }
                    cout << "\nEnter days of auction: ";
                    cin >> days;
                    // Auction days validation
                    if (days <= 0) {
                        cout << "\n[ERROR] Minimum auction days is 1" << endl;
                        continue;

                    } else if(days > 100) {
                        cout << "\n[ERROR] Maximum auction days is 100" << endl;
                        continue;
                    } 
                    session.transactions.push_back(u->advertise(itemName, bid, days));
                    /*
                        For Testing
                    */
                    cout << u->advertise(itemName, bid, days) << endl;
                }
            } else if (command == "logout") {
                for(int i =0;i<session.transactions.size();i++) {
                    cout << session.transactions[i] << endl;
                }
                session.logout();
                continue;
            } else if (command == "login") {
                cout << "\n[ERROR] Already logged in" << endl;
            } else if(command == "exit") {
                cout << "\nGood bye!" << endl;
                break;
            } else
                std::cout << "\nInvalid input";
        }
    }
}

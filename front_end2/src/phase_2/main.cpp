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
int main(){
    Session session;
    
    string username;
    string command;

    cout << "Welcome to auction site!" << endl;

    while (true) {
        if (!session.getIsLogin()) {
            cout << "Enter username: ";
            cin >> username;
            // Add validation
            session.login(username);   
        } else {
            User u = session.getCurrentUser();
            cout << "Enter command: ";
            cin >> command;
            if (command == "create") {
                if (u.userType == "AA"){
                    string uname, utype;
                    float credit;
                    cout << "Enter username: ";
                    cin >> uname;
                    // Add validation
                    cout << "User Types:" << endl;
                    cout << "\tAA: Admin \n\tFS: Full-standard \n\tBS: Buy-standard \n\tSS: Sell-standard" << endl;
                    cout << "Enter user type: ";
                    cin >> utype;
                    // Add validation
                    cout << "Enter credit value: ";
                    cin >> credit;
                    // Add validation
                    u.create(uname, utype, credit);
                } else
                    cout << "[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "delete") {
                if (u.userType == "AA"){
                    string uname;
                    cout << "Enter target username: ";
                    cin >> uname;
                    // Add validation
                    u.deleteUser(uname);
                } else
                    cout << "[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "bid") {
                if (u.userType == "SS")
                    cout << "[ERROR] Account Not Privilleged!" << endl;
                else {
                    string itemName, sellerName;
                    float price;
                    cout << "Enter item name: ";
                    cin >> itemName;
                    // Add validation
                    cout << "Enter seller's username: ";
                    cin >> sellerName;
                    // Add validation
                    cout << "Current highest bid is " << endl;
                    cout << "Please enter new bid amount: ";
                    cin >> price;
                    // Add validation
                    u.bid(itemName, sellerName, price);
                }
            } else if (command == "refund") {
                if (u.userType == "AA") {
                    string sellerName, buyerName;
                    float credit;
                    cout << "Enter seller's username: ";
                    cin >> sellerName;
                    // Add validation
                    cout << "Enter buyer's username: ";
                    cin >> buyerName;
                    // Add validation
                    cout << "Enter amount of credit to be transferred: ";
                    cin >> credit;
                    // Add validation
                    u.refund(sellerName, buyerName, credit);
                } else
                    cout << "[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "addcredit") {
                if (u.userType == "AA") {
                    string uname;
                    float credit;
                    cout << "Enter amount: ";
                    cin >> credit;
                    // Add validation
                    cout << "Enter target username: ";
                    cin >> uname;
                    // Add validation
                    u.addCredit(uname, credit);
                } else
                    cout << "[ERROR] Account Not Privilleged!" << endl;
            } else if (command == "advertise") {
                if (u.userType == "BS")
                    cout << "[ERROR] Account Not Privilleged!" << endl;
                else {
                    string itemName;
                    float bid;
                    int days;
                    cout << "Enter item name: ";
                    cin >> itemName;
                    // Add validation
                    cout << "Enter minimum bid: ";
                    cin >> bid;
                    // Add validation
                    cout << "Enter days of auction: ";
                    cin >> days;
                    // Add validation
                    u.advertise(itemName, bid, days);
                }
            } else if (command == "logout") {
                session.logout();
                break;
            } else
                std::cout << "Invalid input";
        }
    }
}

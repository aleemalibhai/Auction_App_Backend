#ifndef USER_HEADER
#define USER_HEADER
//Description: Class to store the items
//Stores the items for auction

//Inputs: array of items for bid

//Imports the Item class from item.cpp
#include <string>
#include "data.h"
#include "item.h"

using namespace std;

bool isInUsers(string uname, Data data);
bool inInItems(string iname, Data data);

class User {
public:
    string username;
    string accountType;
    double credits;

    User(string uname, string accttyp, double cred);
    User(string inString);
    string getAccountType();
    string getUsername();
    double getCredits();
    virtual string addCredits(Data data);
    virtual string createUser(Data data);
    virtual string deleteUser(Data data);
    virtual string advertise(Data data);
    virtual string bid(Data data);
    virtual string refund(Data data);
};

class Admin : public User {
public:
    Admin(string uname, string accttyp, double cred);
    string createUser(Data data);
    string deleteUser(Data data);
    string refund(Data data);
    string advertise(Data data);
    string bid(Data data);
    string addCredits(Data data);
};

class Full_Standard : public User{
public:
    Full_Standard(string uname, string accttyp, double cred);
    string advertise(Data data);
    string bid(Data data);
};

class Sell_Standard : public User{
public:
    Sell_Standard(string uname, string accttyp, double cred);
    string advertise(Data data);
};

class Buy_Standard : public User{
public:
    Buy_Standard(string uname, string accttyp, double cred);
    string bid(Data data);
};

#endif
#include "user.h"

#include <iostream>
#include <string>

/******************************************************* User Class ****************************************************************/
 /*
    Purpose: Default constructor for user class, initializes an object of User 
    Input: None
    Output: None
*/
User::User(){
    std::cout << "User object is created" << std::endl;
}

/*
    Purpose: Constructor that initiates an instance of class User with given parameters
    Input:
        username: The name of the user
        credit: The amount of credit of the user
        userType: The account type of the user
    Output: None
*/
User::User(std::string username, float credit, std::string userType){ 
    this->username = username;
    this->userType = userType;
    this->credit = credit;
}

/*
    Purpose: Get the name of the username    
    Input: None
    Output: String which is the username of the user
*/
std::string User::getUsername(){
    return this->username;
}

/*
    Purpose: Set the name of the the user to a passed argument   
    Input: String for username of the user
    Output: None
*/
void User::setUsername(std::string username){
    this->username = username;
}

/*
    Purpose: Get the available credit for the user
    Input: None
    Output: Float which is the amount of user's credit
*/
float User::getCredit(){
    return this->credit;
}

 /*
    Purpose: Set the credit amount of the user to a passed argument
    Input: Float to set the amount of the credit of the user
    Output: None
*/
void User::setCredit(float credit){
    this->credit = credit;
}

/*
    Purpose: Get the type of the user
    Input: None
    Output: String which is the account type of the user
*/
std::string User::getType(){
    return this->userType;
}

/*
    Purpose: Set the type of the user to a passed argument
    Input: String specifying the type of user 
    Output: None
*/
void User::setType(std::string userType){
    this->userType = userType;
}

/******************************************************* Admin Class ****************************************************************/

/*
    Purpose: Default constructor that initialized an object of Admin
    Input: None
    Output: None
*/
Admin::Admin(){
    std::cout << "Admin account created" << std::endl;
}

 /*
    Purpose: Constructor that initiates an instance of class Admin with given parameters
    Input:
        username: String for the username of the user
        credit: Float for credit of the user
        userType: string for the account type of the user
    Output: None
*/
Admin::Admin(std::string username, float credit, std::string userType) : User(username, credit, userType){
    std::cout << "Admin account created" << std::endl;
}

/*
    Purpose: Create transaction to create a new user
    Input:
        username: String for the new user's username
        credit: Float for the new user's credit
        userType: String for the new user's account type
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::create(std::string username, std::string userType, float credit){
    return "transaction";
}

/*
    Purpose: Delete transaction to delete a user with the specified username
    Input:
        username: The username of the user that will be deleted
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::deleteUser(std::string username){
    return "transaction";
}

/*
    Purpose: Bid transaction to place a bid on an existing item            
    Input: 
        itemName : Name of the item on which bid is to be placed 
        sellerName : Username of the user who advertised the item
        price: Value of bid being placed 
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::bid(std::string itemName, std::string sellerName, float price){
    return "transaction";
}

/*
    Purpose: Issue a refund amount from seller to buyer
    Input:
        sellerName: Username of the seller issueing the refund
        buyerName: Username of the user getting the refund
        credit: The amount being refunded 
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::refund(std::string sellerName, std::string buyerName, float credit){
    return "transaction";
}

/*
    Purpose: To add credit of a specific amount to a user
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::addCredit(std::string username, float credit){
    return "transaction";
}

/*
    Purpose: Advertise command to create a new advertisement of an item
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string Admin::advertise(std::string username, float price, int days){
    return "transaction";
}

/******************************************************* Full Standard Class ****************************************************************/

/*
    Purpose: Default constructor that initialized an object of FullStandard
    Input: None
    Output: None
*/
FullStandard::FullStandard(){
    std::cout << "Full Standard account created" << std::endl;
}

/*
    Purpose: Overloading the default constructor to create an instance of class FullStandard with the given parameters
    Input:
        username: Username of the user
        credt: Credit in the user's account

    Output: returns an instance of class FullStandard
*/
FullStandard::FullStandard(std::string username, float credit, std::string userType) : User(username, credit, userType){
    std::cout << "Full Standard account created" << std::endl;
}

/*
    Purpose: Bid transaction to place a bid on an existing item            
    Input: 
        itemName : Name of the item on which bid is to be placed 
        sellerName : Username of the user who advertised the item
        price: Value of bid being placed 
    Output: Returns a formatted string to write to daily transaction file
*/
std::string FullStandard::bid(std::string itemName, std::string sellerName, float price){
    return itemName;
}

/*
    Purpose: To add credit of a specific amount to a user
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string FullStandard::addCredit(float credit){         
    return "transaction";
}

/*
    Purpose: Advertise command to create a new advertisement of an item
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string FullStandard::advertise(std::string itemName, float price, int days){
    return itemName;
}

/******************************************************* Buy Standard Class ****************************************************************/

/*
    Purpose: Default constructor for class that initialized an object of BuyStandard 
    Input: None
    Output: None
*/
BuyStandard::BuyStandard(){
    std::cout << "Buy Standard account created" << std::endl;
}


 /*
    Purpose: Overriding the default constructor to initialize an object of the class with the given parameters
    Input:
        userName: Username of the user
        credit: Amount of credit in the account
        userType: String for the type of user account
    Output: None
*/
BuyStandard::BuyStandard(std::string username, float credit, std::string userType) : User(username, credit, userType){
    std::cout << "Buy Standard account created" << std::endl;
}

/*
    Purpose: Bid transaction to place a bid on an existing item            
    Input: 
        itemName : Name of the item on which bid is to be placed 
        sellerName : Username of the user who advertised the item
        price: Value of bid being placed 
    Output: Returns a formatted string to write to daily transaction file
*/
std::string BuyStandard::bid(std::string itemName, std::string sellerName, float price){
    return itemName;
}

/*
    Purpose: Advertise command to create a new advertisement of an item
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string BuyStandard::addCredit(float credit){
    return "transaction";
}

/******************************************************* Sell Standard Class ****************************************************************/

/*
    Purpose: Default constructor that initialized an object of SellStandard
    Input: None
    Output: None
*/
SellStandard::SellStandard(){
    std::cout << "Sell Standard account created" << std::endl;
}

/*
    Purpose: Overriding the default constructor to initialize an object of the class with the given parameters
    Input:
        userName: Username of the user
        credit: Amount of credit in the account
        userType: String for the type of user account
    Output: None
*/
SellStandard::SellStandard(std::string username, float credit, std::string userType) : User(username, credit, userType){
    std::cout << "Sell Standard account created" << std::endl;
}

/*
    Purpose: Advertise command to create a new advertisement of an item
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string SellStandard::addCredit(float credit){
    return "transaction";
}

/*
    Purpose: Advertise command to create a new advertisement of an item
    Input: 
        username: Username of the user getting the credit
        credit: Amount of credit being added
    Output: Returns a formatted string to write to daily transaction file
*/
std::string SellStandard::advertise(std::string itemName, float price, int days){
    return itemName;
}

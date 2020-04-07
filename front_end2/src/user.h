// Description: Class to represent users of this system, including admin, full-standard, etc. 
// Contains functions to allow users to bid, auction, create users
// Inputs: the user's unique username, the user's usertype (admin,full-standard,etc.)

#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

/*
    User class is the parent class for all user types(Admin, FullStandard, BuyStandard, SellStandard)
    Containing the username, userType and credit of the user
*/
class User {
    public:
        std::string username;       //The username of the user
        std::string userType;       //The account type of the user
        float credit;               //The amount of credit of the user

        // Helper function
        bool operator==(const User& rhs) const { 
            return this->username == rhs.username;
        }

        // Abstract functions, to be implemented by child classes
        virtual std::string create(std::string username, std::string userType, float credit){}
        virtual std::string deleteUser(std::string username, std::vector<User> userAccount) {}
        virtual std::string bid(std::string itemName, std::string sellerName, std::string buyerName, float price) {}
        virtual std::string refund(std::string sellerName, std::string buyerName, float credit){}
        virtual std::string addCredit(std::string username, float credit, std::vector<User> userAccount){}
        virtual std::string advertise(std::string itemName, float price, int days){}
        
        /*
            Purpose: Default constructor for user class, initializes an object of User 
            Input: None
            Output: None
        */
        User();
                   
        /*
            Purpose: Constructor that initiates an instance of class User with given parameters
            Input:
                username: The name of the user
                credit: The amount of credit of the user
                userType: The account type of the user
            Output: None
        */
        User(std::string username, float credit, std::string userType);
        
            
        /*
            Purpose: Get the name of the username    
            Input: None
            Output: String which is the username of the user
        */
        std::string getUsername();
        
            
        /*
            Purpose: Set the name of the the user to a passed argument   
            Input: String for username of the user
            Output: None
        */
        void setUsername(std::string username);
        
            
        /*
            Purpose: Get the available credit for the user
            Input: None
            Output: Float which is the amount of user's credit
        */
        float getCredit();
            
            
        /*
            Purpose: Set the credit amount of the user to a passed argument
            Input: Float to set the amount of the credit of the user
            Output: None
        */
        void setCredit(float credit);
            
            
        /*
            Purpose: Get the type of the user
            Input: None
            Output: String which is the account type of the user
        */
        std::string getType();
            
            
        /*
            Purpose: Set the type of the user to a passed argument
            Input: String specifying the type of user 
            Output: None
        */
        void setType(std::string userType);
};



/*
    Admin class that is used to create admin accounts, containing all the commands including
    privileged and non-privileged commands.
*/
class Admin: public User {
    public:
        /*
            Purpose: Default constructor that initialized an object of Admin
            Input: None
            Output: None
        */
        Admin();


        /*
            Purpose: Constructor that initiates an instance of class Admin with given parameters
            Input:
                username: String for the username of the user
                credit: Float for credit of the user
                userType: string for the account type of the user
            Output: None
        */
        Admin(std::string username, float credit, std::string userType);
            
            
        
        /*
            Purpose: Create transaction to create a new user
            Input:
                username: String for the new user's username
                credit: Float for the new user's credit
                userType: String for the new user's account type
            Output: Returns a formatted string to write to daily transaction file

        */
        std::string create(std::string username, std::string userType, float credit) override; 
            

        /*
            Purpose: Delete transaction to delete a user with the specified username
            Input:
                username: The username of the user that will be deleted
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string deleteUser(std::string username, std::vector<User> userAccount);      


        /*
            Purpose: Bid transaction to place a bid on an existing item            
            Input: 
                itemName : Name of the item on which bid is to be placed 
                sellerName : Username of the user who advertised the item
                price: Value of bid being placed 
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string bid(std::string itemName, std::string sellerName, std::string buyerName, float price);
            
            
        /*
            Purpose: Issue a refund amount from seller to buyer
            Input:
                sellerName: Username of the seller issueing the refund
                buyerName: Username of the user getting the refund
                credit: The amount being refunded 
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string refund(std::string sellerName, std::string buyerName, float credit);
            
            
        /*
            Purpose: To add credit of a specific amount to a user
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string addCredit(std::string username, float credit, std::vector<User> userAccount);
                  

        /*
            Purpose: Advertise command to create a new advertisement of an item
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string advertise(std::string itemName, float price, int days);
};

/*
    Create a class FullStandard that extends from class User
*/
class FullStandard: public User {
    public: 

        /*
            Purpose: Default constructor that initialized an object of FullStandard
            Input: None
            Output: None
        */
        FullStandard();
                       
        
        /*
            Purpose: Overloading the default constructor to create an instance of class FullStandard with the given parameters
            Input:
                username: Username of the user
                credt: Credit in the user's account

            Output: returns an instance of class FullStandard
        */
        FullStandard(std::string username, float credit, std::string userType);
            

        /*
            Purpose: Bid transaction to place a bid on an existing item            
            Input: 
                itemName : Name of the item on which bid is to be placed 
                sellerName : Username of the user who advertised the item
                price: Value of bid being placed 
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string bid(std::string itemName, std::string sellerName, std::string buyerName, float price);          


        /*
            Purpose: To add credit of a specific amount to a user
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string addCredit(std::string username, float credit, std::vector<User> userAccount);          
        
        /*
            Purpose: Advertise command to create a new advertisement of an item
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string advertise(std::string itemName, float price, int days);
};


/*
    Create a class BuyStandard that extends from class User
*/
class BuyStandard: public User {
    public:
        /*
            Purpose: Default constructor for class that initialized an object of BuyStandard 
            Input: None
            Output: None
        */
        BuyStandard();      


        /*
            Purpose: Overriding the default constructor to initialize an object of the class with the given parameters
            Input:
                userName: Username of the user
                credit: Amount of credit in the account
                userType: String for the type of user account
            Output: None
        */
        BuyStandard(std::string username, float credit, std::string userType);
        
        
        /*
            Purpose: Bid transaction to place a bid on an existing item            
            Input: 
                itemName : Name of the item on which bid is to be placed 
                sellerName : Username of the user who advertised the item
                price: Value of bid being placed 
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string bid(std::string itemName, std::string sellerName, std::string buyerName, float price);          

        /*
            Purpose: Advertise command to create a new advertisement of an item
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string addCredit(std::string username, float credit, std::vector<User> userAccount);
};


/*
    Purpose: class for representing user with type: SellStandard
*/
class SellStandard: public User {
    public:

        /*
            Purpose: Default constructor that initialized an object of SellStandard
            Input: None
            Output: None
        */
        SellStandard();      

        /*
            Purpose: Overriding the default constructor to initialize an object of the class with the given parameters
            Input:
                userName: Username of the user
                credit: Amount of credit in the account
                userType: String for the type of user account
            Output: None
        */
        SellStandard(std::string username, float credit, std::string userType);
  

        /*
            Purpose: Advertise command to create a new advertisement of an item
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string addCredit(std::string username, float credit, std::vector<User> userAccount);
    

        /*
            Purpose: Advertise command to create a new advertisement of an item
            Input: 
                username: Username of the user getting the credit
                credit: Amount of credit being added
            Output: Returns a formatted string to write to daily transaction file
        */
        std::string advertise(std::string itemName, float price, int days);
};



#endif
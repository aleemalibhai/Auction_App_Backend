#ifndef SESSION_H
#define SESSION_H

#include "user.h"
#include "item.h"

#include <vector>
#include <string>
#include <iostream>

/*
    Session is the core of the application, in which it will keep track of the
    login status, read user accounts file, read available items file, write to 
    the daily transaction files whenever the logout transaction is invoked.
*/
class Session {
    public:
        std::vector<User> userAccount;                              //Vector that stores all the available user accounts 
        std::vector<Item> availableItems;                           //Vector that stores the list of availble items
        std::vector<std::string> transactions;                      //Vector that stores list of all transactions made in current session
        User currentUser;                                           //User that is currently logged in 
        bool isLogin = false;                                       //Boolean to check the login status 
        

        /*
            Purpose: Default constructor to initialize an instance Session
            Input: None
            Output: None
        */
        Session();
        
        /*
            Purpose: Get the current user 
            Input: None
            Output: Returns an object of type User
        */
        User getCurrentUser();
        

        /*
            Purpose: Get the status of current user in sesion
            Input: None
            Output: Boolean value (true/false)
        */
        bool getIsLogin();     
        

        /*
            Purpose: Set the user that is currently in the session 
            Input: An object of type User
            Output: None
        */
        void setCurrentUser(User user);
        

        /*
            Purpose: Set the login status of the current user to the passed flag
            Input: A boolean flag
            Output: None
        */
        void setIsLogin(bool isLogin); 
        

        /*
            Purpose: Logs in the user with the entered username 
            Input: Username of the user 
            Output: None
        */
        void login(std::string username);
        
        
        /*
            Purpose: Logs out the current user from the session
            Input: None      
            Output: None
        */
        void logout();   
       

       /*
            Purpose: Write the content of transaction vector to the daily transaction file 
            Input: None
            Output: None
        */
        void writeDailyTransaction();   
        

        /*
            Purpose: Read the current user accounts file and add them to the userAccounts vector
            Input: None
            Output: None
        */
        void readCurrentUserAccount();  
        

        /*
            Purpose: Read the available items file and add the available entries to the availableItems vector
            Input: None 
            Output: None
        */
        void readAvailableItems();
        

        /*
            Purpose: Split a string into several strings which is seperated by a character
            Input:
                str: Original string that will be split
                splitter: Character that will e used to determine the split
            Output: A string vector containing seperated string
        */
        static vector<string> split(string str, char splitter);
        
};



#endif
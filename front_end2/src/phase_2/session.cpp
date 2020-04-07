#include "session.h"
#include "user.h"
#include "item.h"

 /*
    Purpose: Default constructor to initialize an instance Session
    Input: None
    Output: None
*/
Session::Session(){
    std::cout << "Session started" << std::endl;
    readCurrentUserAccount();
}

/*
    Purpose: Get the current user 
    Input: None
    Output: Returns an object of type User
*/
User Session::getCurrentUser(){
    return currentUser;
}

/*
    Purpose: Get the status of current user in sesion
    Input: None
    Output: Boolean value (true/false)
*/
bool Session::getIsLogin(){
    return isLogin;
}

/*
    Purpose: Set the user that is currently in the session 
    Input: An object of type User
    Output: None
*/
void Session::setCurrentUser(User user){
    this->currentUser = user;
}

/*
    Purpose: Set the login status of the current user to the passed flag
    Input: A boolean flag
    Output: None
*/
void Session::setIsLogin(bool isLogin){
    this->isLogin = isLogin;
}


/*
    Purpose: Logs in the user with the entered username 
    Input: Username of the user 
    Output: None
*/
void Session::login(std::string username){
    bool userExists = false;
    for(auto i = userAccount.begin(); i != userAccount.end(); i++){
        if(i->getUsername() == username){
            userExists = true;
            User currentUser(i->getUsername(), i->getCredit(), i->getType());
            setCurrentUser(currentUser);
            setIsLogin(true);
            break;
        }
    }

    if(!userExists){
        setIsLogin(false);
        std::cout << "Invalid username" << std::endl;
    }
}


/*
    Purpose: Logs out the current user from the session
    Input: None      
    Output: None
*/
void Session::logout(){
    setIsLogin(false);
    std::cout << "Successfully logged out" << std::endl;

    try {
        writeDailyTransaction();
    } catch (int e) {
        std::cout << "[ERROR] Error saving transaction log to Daily Transaction File" << std::endl;
    }

    std::cout << "[DONE] Write Daily Transaction File" << std::endl;
}

/*
    Purpose: Write the content of transaction vector to the daily transaction file 
    Input: None
    Output: None
*/
void Session::writeDailyTransaction(){}

/*
    Purpose: Read the current user accounts file and add them to the userAccounts vector
    Input: None
    Output: None
*/
void Session::readCurrentUserAccount(){
    // This is commented, can be used for testing purposes
    /* User bs = BuyStandard("buyer", 98.99, "BS");
    User aa = BuyStandard("admin", 98.99, "AA");
    userAccount.push_back(bs);
    userAccount.push_back(aa);*/

    std::cout << "[DONE] Read User Account File" << std::endl;
}

/*
    Purpose: Read the available items file and add the available entries to the availableItems vector
    Input: None 
    Output: None
*/
void Session::readAvailableItems(){}

/*
    Purpose: Split a string into several strings which is seperated by a character
    Input:
        str: Original string that will be split
        splitter: Character that will e used to determine the split
    Output: A string vector containing seperated string
*/
static vector<string> split(string str, char splitter){
    vector<string> vec;
    string temp;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != splitter)
            temp += str[i];
        else {
            vec.push_back(temp);
            temp = "";
        }
    }
    vec.push_back(temp);
    return vec;
}
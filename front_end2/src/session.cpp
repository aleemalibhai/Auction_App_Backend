  
#include "session.h"
#include "user.h"
#include "item.h"


#include <fstream>
#include <sstream>
#include <iomanip>
#include <typeinfo>

 /*
    Purpose: Default constructor to initialize an instance Session
    Input: None
    Output: None
*/
Session::Session(string userAccount, string availableItems, string dailyTransaction){
    //std::cout << "Session started" << std::endl;
    this->userAccountsFile = userAccount;
    this->availableItemsFile = availableItems;
    this->dailyTransactionFile = dailyTransaction;

    // std::cout << "User accoutns file : " << this->userAccountsFile << std::endl;
    // std::cout << "Available items file : " << this->availableItemsFile << std::endl;
    // std::cout << "Daily transaction file : " << this->dailyTransactionFile << std::endl;

    this->readCurrentUserAccount();
}

/*
    Purpose: Get the current user 
    Input: None
    Output: Returns an object of type User
*/
User* Session::getCurrentUser(){
    return this->currentUser;
}

/*
    Purpose: Get the status of current user in sesion
    Input: None
    Output: Boolean value (true/false)
*/
bool Session::getIsLogin(){
    return this->isLogin;
}

/*
    Purpose: Set the user that is currently in the session 
    Input: An object of type User
    Output: None
*/
void Session::setCurrentUser(User* user){
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
    Purpose: Check if the user exists in the database
    Input: A string 
    Output: A boolean flag
*/
bool Session::isExist(std::string username) {
    for(auto i = this->userAccount.begin(); i != this->userAccount.end(); i++){
        if(i->getUsername() == username){
            return true;
        }
    }
    return false;
}

/*
    Purpose: Check if the item exists in the database
    Input: A string 
    Output: A boolean flag
*/
bool Session::isItemExist(std::string item) {
    for(auto i = this->availableItems.begin(); i != this->availableItems.end(); i++){
        if(i->getItemName() == item){
            return true;
        }
    }
    return false;
}

/* Purpose: get a user object given the name of the user
    Input: String for name of the user
    output: an object of user type
*/

User Session::getUser(std::string username){
    for(auto i = this->userAccount.begin(); i != this->userAccount.end(); i++){
        if(i->getUsername() == username){
            return *i; 
        }
    }
}


/*
    Purpose: Logs in the user with the entered username 
    Input: Username of the user 
    Output: None
*/
void Session::login(std::string username){
    bool userExists = false;
    for(auto i = this->userAccount.begin(); i != this->userAccount.end(); i++){
        if(i->getUsername() == username){
            userExists = true;
            
            if(i->getType() == "AA"){
                Admin* currentUser = new Admin(i->getUsername(), i->getCredit(), i->getType());
                this->setCurrentUser(currentUser);
           
            }else if(i->getType() == "FS"){
                FullStandard* currentUser = new FullStandard(i->getUsername(), i->getCredit(), i->getType());
                this->setCurrentUser(currentUser);

            }else if(i->getType() == "BS"){
                BuyStandard* currentUser = new BuyStandard(i->getUsername(), i->getCredit(), i->getType());
                this->setCurrentUser(currentUser);
            }else if(i->getType() == "SS"){
                SellStandard* currentUser= new SellStandard(i->getUsername(), i->getCredit(), i->getType());
                this->setCurrentUser(currentUser);
            }
            // cout << "TESTING" << this->currentUser.advertise("testing",12.99,12) << endl;
            this->setIsLogin(true);
            this->readAvailableItems();
            
            break;
        }
    }
    if(!isExist(username)){
        this->setIsLogin(false);
        std::cout << "[ERROR] Invalid username" << std::endl;
    }
}


/*
    Purpose: Logs out the current user from the session
    Input: None      
    Output: None
*/
void Session::logout(){
    string transaction = "00 ";
    transaction += this->getCurrentUser()->getUsername();

    for(int i=this->getCurrentUser()->getUsername().size(); i<16;i++){
        transaction += " ";
    }

    transaction += this->getCurrentUser()->getType() + " ";

    std::ostringstream streamObj;
    streamObj << std::setprecision(2);
    streamObj << std::fixed;
    streamObj << this->getCurrentUser()->getCredit();
    string creditFormat = streamObj.str();
    int originalLength = creditFormat.length();
    
    for(int i=0;i<9-originalLength;i++){
        creditFormat = "0"+creditFormat;
    }
    transaction += creditFormat;

    this->transactions.push_back(transaction);
    
    setIsLogin(false);
    delete currentUser;
    currentUser = NULL;

    // userAccount.clear();                            
    // availableItems.clear();                       
    // transactions.clear();


    std::cout << "Successfully logged out" << std::endl;

    try {
        writeDailyTransaction();
        //userAccount.clear();                            
        //availableItems.clear();                       
        transactions.clear();
        std::cout << "[DONE] Write Daily Transaction File" << std::endl;
    } catch (...) {  //Syntax to catch all sorts of exception
        std::cout << "[ERROR] Error saving transaction log to Daily Transaction File" << std::endl;
    }
}

/*
    Purpose: Write the content of transaction vector to the daily transaction file 
    Input: None
    Output: Nones
*/
void Session::writeDailyTransaction(){
    ofstream out(this->dailyTransactionFile, ios::app);
    for(int i=0;i<this->transactions.size();i++){
        out << this->transactions[i] << endl;
    }
    out << "END\n";
    out.close();
}


/*
    Purpose: Read the current user accounts file and add them to the userAccounts vector
    Input: None
    Output: None
*/
void Session::readCurrentUserAccount(){
    ifstream in(this->userAccountsFile);
    string in_string;
    while(getline(in, in_string)){
        if(in_string == "END"){
          in.close();  
          break;
        } else {
            vector<string> userInfo = this->split(in_string, ' ');

            if(userInfo[1]=="AA"){
                Admin user(userInfo[0], stof(userInfo[2]), userInfo[1]);
                //cout << "User credit: " << stof(userInfo[2]) << endl;
                this->userAccount.push_back(user);
            }
            else if(userInfo[1]=="FS"){
                FullStandard user(userInfo[0], stof(userInfo[2]), userInfo[1]);
                this->userAccount.push_back(user);
                //cout << "User credit: " << stof(userInfo[2]) << endl;
            }
            else if(userInfo[1]=="BS"){
                BuyStandard user(userInfo[0], stof(userInfo[2]), userInfo[1]);
                this->userAccount.push_back(user);
                //cout << "User credit: " << stof(userInfo[2]) << endl;
            }
            else if(userInfo[1]=="SS"){
                SellStandard user(userInfo[0], stof(userInfo[2]), userInfo[1]);
                this->userAccount.push_back(user);
                //cout << "User credit: " << stof(userInfo[2]) << endl;
            } else {
                std::cout << "Invalid user type" << std::endl;
                continue;
            }
            
            //cout << in_string << endl;
        }
    }
    std::cout << "[DONE] Read User Account File\n" << std::endl;
}

/*
    Purpose: Read the available items file and add the available entries to the availableItems vector
    Input: None 
    Output: None
*/
void Session::readAvailableItems(){
    ifstream in(this->availableItemsFile);
    string in_string;
    while(getline(in, in_string)){
        
        if(in_string == "END"){
          in.close();  
          break;
        } 
        vector<string> itemInfo = this->split(in_string, ' ');
        // std::cout << typeid(itemInfo[0]).name() << std::endl;
        //item_name           reg_user        admin           100 000011
        Item item(itemInfo[0], itemInfo[1], itemInfo[2] , stoi(itemInfo[4]), stof(itemInfo[3]));
        //Item item(itemInfo[0], itemInfo[1]/*Seller user name*/, float(itemInfo[3]), int(itemInfo[4]));
        this->availableItems.push_back(item);
    }
    std::cout << "[DONE] Read Available Items File\n";
}
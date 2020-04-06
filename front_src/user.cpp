#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include "user.h"
#include <algorithm>


using namespace std;

bool isInUsers(string uname, Data data){
    ifstream inFile;
    inFile.open(data.getUserFileName());

    string user;
    while (getline(inFile, user)) {
        User tempU(user);
        if (tempU.username == uname){
            return true;
        }
    }
    return false;
}

bool isInItems(string iname, Data data){
    vector<Item> items = data.items;
    for(size_t i=0; i<items.size(); ++i) {
        if (items[i].getItemName() == iname) {
            return true;
        }
    }
    return false;
}

string User::createUser(Data data){ cout <<"How did you get here?" <<endl;}
string User::deleteUser(Data data){ cout <<"How did you get here?" <<endl;}
string User::advertise(Data data){ cout <<"How did you get here?" <<endl;}
string User::bid(Data data){ cout <<"How did you get here?" <<endl;}
string User::refund(Data data){ cout <<"How did you get here?" <<endl;}
string User::addCredits(Data data) { cout <<"How did you get here?" <<endl;}


User::User(string uname, string accttyp, double cred){
    username = uname;
    accountType = accttyp;
    credits = cred;
}
User::User(string inString){
    // format: UUUUUUUUUUUUUUU_TT_CCCCCCCCC
    string uname = inString.substr(0, 15);
    char c = ' ';
    uname.erase(remove(uname.begin(), uname.end(), ' '), uname.end());

    string acttyp = inString.substr(16, 2);

    string creds = inString.substr(19, 9);

    username = uname;
    accountType = acttyp;
    credits = stof(creds);

}

string User::getAccountType() {
      // input: no parameters
      // output: Account type of user
      // Description: gets Account type from User object

      return accountType;
}

string User::getUsername() {
    // input: no parameters
    // output: Username of user
    // Description: gets Username from User object

    return username;
}

double User::getCredits() {
    // input: no parameters
    // output: Credits of user
    // Description: gets available credits from User object

    return credits;
}






  /*
Child class of the user object
handles all functions that only Admins can do

inputs: username, account type, credits
outputs: returns a User object
*/

Admin::Admin(string uname, string accttyp, double cred) : User(uname, accttyp, cred){}
string Admin::createUser(Data data) {
  // input: none, user inputs: username, account type and credit balance to create new user with
  // output: User Object, returns transaction record
  // Description: creates a user account with specific type based on parameters
  string uname;
  string acttyp;
  string creds;
  string transactionCode = "01";

  // get info from user
  cout << "Please provide a username:" << endl;
  cin >> uname;

  // check input
  if (uname.length() > 15){
      cout << "username can only be 15 characters" << endl;
      return "";
  }

  // check user doesn't already exist
  if (isInUsers(uname, data)){
      cout << "User already exists" << endl;
      return "";
  }

  // pad username with appropriate number of zeros to make string 15 elements long
  int n = 15 - uname.length();
  for(int i = 0; i < n; i++){
      uname = uname + ' ';
  }

  //get account type
  cout << "Please enter account type" << endl;
  cin >> acttyp;

  // check inout
  if (acttyp != "AA" && acttyp != "BS" && acttyp != "SS" && acttyp != "FS"){
      cout << "Account type must be: AA, FS, BS, SS" << endl;
      return "";
  }

  // get starting credits
  double amt;
  cout << "Enter starting credit balance" << endl;
  cin >> amt;

  // pad amt to be 9 elements long
  // set any input to two decimal places and cast to string
  stringstream stream;
  stream << fixed << setprecision(2) << amt;
  creds = stream.str();

  int l = 9 - creds.length();
  for (int i = 0; i < l; i++){
      creds = '0' + creds;
  }

  return (transactionCode + ' ' + uname + ' ' + acttyp + ' ' + creds);
}

string Admin::deleteUser(Data data) {
  // input: none, user inputs: username of account to delete
  // output: prints transaction info to screen, writes delete information to transaction file
  // Description: deletes user with specified username, writes delete info to transaction file
  string uname;
  string acttyp = "  ";
  string creds = "000000000";
  string transactionCode = "02";

  // get user to delete
  cout << "Enter username to delete:" <<endl;
  cin >> uname;

  // check if current user
  if (uname == username){
      // trying to delete self
      cout << "Can't delete yourself" << endl;
      return "";
  }
  // check if name exists
  if (!isInUsers(uname, data)){
      cout << "User does not exist" <<endl;
      return "";
  }

  // pad username
  int n = 15 - uname.length();
  for(int i = 0; i < n; i++){
      uname = uname + ' ';
  }

  cout << "User " <<uname <<" deleted successfully." <<endl;

  return (transactionCode + ' ' + uname + ' ' + acttyp + ' ' + creds);

}

string Admin::refund(Data data) {
  // input: none, user inputs: username of buyer, seller, and amount to refund buyer
  // output: prints transaction info to screen, write refund information to transaction
  // Description: reduces seller account balance and increases buyer account balance by specified amount
  string bname;
  string sname;
  string creds;
  string transactionCode = "05";

  // get buyer username
  cout << "Enter buyer username" <<endl;
  cin >> bname;

  if (!isInUsers(bname, data)){
      cout << "User does not exist" <<endl;
      return "";
  }

  // pad username
  int n = 15 - bname.length();
  for(int i = 0; i < n; i++){
      bname = bname + ' ';
  }

  // get seller username
  cout << "Enter seller username" <<endl;
  cin >> sname;

  if (!isInUsers(sname, data)){
      cout << "User does not exist" <<endl;
      return "";
  }

  // pad username
  n = 15 - sname.length();
  for(int i = 0; i < n; i++){
      sname = sname + ' ';
  }

  // get amt to refund
  double amt;
  cout << "Enter amount to refund" <<endl;
  cin >> amt;

  // pad amt to be 9 elements long
  // set any input to two decimal places and cast to sting
  stringstream stream;
  stream << fixed << setprecision(2) << amt;
  creds = stream.str();

  int l = 9 - creds.length();
  for (int i = 0; i < l; i++){
      creds = '0' + creds;
  }

  return (transactionCode + ' ' + bname + ' ' + sname + ' ' + creds);
}

string Admin::advertise(Data data) {
  // input: none, user inputs: username of seller, item name, minimum bid, days to option
  // output: prints transaction info to screen, write advertise info to transaction file
  // Description: creates a record of advertisement on specified user's behalf and writes this information to the transaction file
  string iname;
  string numDays;
  string minBid;
  string uname;
  string transactionCode = "03";

  // get username
  cout << "Enter username of account advertising:" <<endl;
  cin >> uname;

  // check username
  if (!isInUsers(uname, data)){
      cout << "User does not exist" << endl;
      return "";

  }

  // pad username with appropriate number of zeros to make string 15 elements long
  int n = 15 - uname.length();
  for(int i = 0; i < n; i++){
      uname = uname + ' ';
  }

  // get item name
  cout << "Enter item name:" <<endl;
  cin >> iname;


  // check length
  if (iname.length() > 25){
      cout << "Item name too long, can be a maximum of 25 characters" << endl;
      return "";
  }
    // pad item name
    n = 25 - iname.length();
    for(int i = 0; i < n; i++){
        iname = iname + ' ';
    }

  // get min bid
  double amt;
  cout << "Enter minimum bid:" <<endl;
  cin >> amt;

  // check min bid is under 999.99
  if (amt > 999.99){
      cout << "Item can be at maximum $999.99" << endl;
      return "";
  }

  // pad amt to be 9 elements long
  // set any input to two decimal places and cast to string
  stringstream stream;
  stream << fixed << setprecision(2) << amt;
  minBid = stream.str();

  int l = 9 - minBid.length();
  for (int i = 0; i < l; i++){
      minBid = '0' + minBid;
  }

  // get max days
  int days;
  cout << "Enter days until sale ends" << endl;
  cin >> days;

  // check days is under 100
  if (days > 100){
      cout << "Max number of days is 100" << endl;
      return "";
  }
  // pad num days to 3 digits
  numDays = to_string(days);
  n = 3 - numDays.length();
  for (int i=0; i < n; i++){
      numDays = '0' + numDays;
  }

  return (transactionCode + ' ' + iname + ' ' + uname + ' ' + numDays + ' ' + minBid);
}

string Admin::bid(Data data) {
    // input: none, user inputs: item name, seller name, buyer name, bid amount
    // output: prints transaction info to screen, writes bid information to transaction file
    // Description: creates bid record for specified user and writes info to transaction file
    // get seller username and item name
    string iname;
    string sname;
    string transactionCode = "04";
    string creds;
    string uname;

    cout << "Enter Item name" << endl;
    cin >> iname;

    // check item exists
    if(!isInItems(iname, data)){
        cout << "Item does not exist" << endl;
        return "";
    }

    // pad item name
    int n = 25 - iname.length();
    for(int i = 0; i < n; i++){
        iname = iname + ' ';
    }

    cout << "Enter seller's username" << endl;
    cin >> sname;

    // check user exists
    if(!isInUsers(sname, data)){
        cout << "User does not exist" << endl;
        return "";
    }
    // pad seller name
    n = 15 - sname.length();
    for(int i = 0; i < n; i++){
        sname = sname + ' ';
    }
    // get buyer name
    cout << "Enter buyer's username" << endl;
    cin >> uname;

    // check user exists
    if(!isInUsers(uname, data)){
        cout << "User does not exist" << endl;
        return "";
    }
    // pad buyer name
    n = 15 - uname.length();
    for(int i = 0; i < n; i++){
        uname = uname + ' ';
    }

    // output current bid info
    double currentBid;
    vector<Item> items = data.items;
    for(size_t i=0; i<items.size(); ++i) {
        if (items[i].getItemName() == iname) {
            currentBid = items[i].getCurrentBid();
        }
    }

    cout <<"Current bid: " << currentBid << endl;
    // get amt to bid
    double amt;
    cout << "Enter amount to bid" << endl;
    cin >> amt;

    // bid restriction
    if (amt < currentBid * 1.05){
        cout << "Bid must be 5% higher than previous bid" <<endl;
        return "";
    }
    // pad amt to be 9 elements long
    // set any input to two decimal places and cast to sting
    stringstream stream;
    stream << fixed << setprecision(2) << amt;
    creds = stream.str();

    int l = 6 - creds.length();
    for (int i = 0; i < l; i++){
        creds = '0' + creds;
    }
    return (transactionCode + ' ' + iname + ' ' + sname + ' ' + uname + ' ' + creds);

}

string Admin::addCredits(Data data) {
  // input: none, user inputs: username, amount to add to user's balance
  // output: prints transaction info to screen, writes add information to transaction file
  // Description: adds specified number of credit to account of specified User

  string transactionCode = "06";
  string uname;
  string creds;
  // input: none, user input: credit amount to add
  // output: prints transaction info to screen, returns transaction record
  // Description: adds specified number of credit to account of User instance

  // get username
  cout << "Enter username of account to add credit to:" <<endl;
  cin >> uname;

  // check username
  if (!isInUsers(uname, data)){
      cout << "User does not exist" << endl;
      return "";

  }

  // pad username with appropriate number of zeros to make string 15 elements long
  int n = 15 - uname.length();
  for(int i = 0; i < n; i++){
      uname = uname + ' ';
  }

  // get number of credits
  double amt;
  cout << "Amount to add to account:" << endl;
  cin >> amt;

  // pad amt to be 9 elements long
  // set any input to two decimal places and cast to sting
  stringstream stream;
  stream << fixed << setprecision(2) << amt;
  creds = stream.str();

  int l = 9 - creds.length();
  for (int i = 0; i < l; i++){
      creds = '0' + creds;
  }

  return (transactionCode + ' ' + uname + ' ' + accountType + ' ' + creds);

}


/*
Child class of the user object
handles all functions that only Full-Standard users can do

inputs: username, account type, credits
outputs: returns a User object
*/
Full_Standard::Full_Standard(string uname, string accttyp, double cred) : User(uname, accttyp, cred){}

string Full_Standard::advertise(Data data) {
  // input: none, user inputs: item name, minimum bid, days to option
  // output: none, write advertise info to transaction file
  // Description: ceates a record of advertisement on User instance and writes this information to the transaction file

  string iname;
  string numDays;
  string minBid;
  string uname;
  string transactionCode = "03";

  // get item name
  cout << "Enter item name:" <<endl;
  cin >> iname;

  // check length
  if (iname.length() > 25){
      cout << "Item name too long, can be a maximum of 25 characters" << endl;
      return "";
  }
  // pad item name
  int n = 25 - iname.length();
  for(int i = 0; i < n; i++){
      iname = iname + ' ';
  }

  // get min bid
  double amt;
  cout << "Enter minimum bid:" <<endl;
  cin >> amt;

  // check min bid is under 999.99
  if (amt > 999.99){
      cout << "Item can be at maximum $999.99" << endl;
      return "";
  }

  // pad amt to be 9 elements long
  // set any input to two decimal places and cast to string
  stringstream stream;
  stream << fixed << setprecision(2) << amt;
  minBid = stream.str();

  int l = 9 - minBid.length();
  for (int i = 0; i < l; i++){
      minBid = '0' + minBid;
  }

  // get max days
  int days;
  cout << "Enter days until sale ends" << endl;
  cin >> days;

  // check days is under 100
  if (days > 100){
      cout << "Max number of days is 100" << endl;
      return "";
  }
  // pad num days to 3 digits
  numDays = to_string(days);
  n = 3 - numDays.length();
  for (int i=0; i < n; i++){
      numDays = '0' + numDays;
  }

  // pad username
  uname = username;
  n = 15 - uname.length();
  for(int i = 0; i < n; i++){
      uname = uname + ' ';
  }

  return (transactionCode + ' ' + iname + ' ' + uname + ' ' + numDays + ' ' + minBid);
}

string Full_Standard::bid(Data data) {
    // get seller username and item name
    string iname;
    string sname;
    string transactionCode = "04";
    string creds;
    string uname;

    cout << "Enter Item name" << endl;
    cin >> iname;

    // check item exists
    if(!isInItems(iname, data)){
        cout << "Item does not exist" << endl;
        return "";
    }

    // pad item name
    int n = 25 - iname.length();
    for(int i = 0; i < n; i++){
        iname = iname + ' ';
    }

    cout << "Enter seller's username" << endl;
    cin >> sname;

    // check user exists
    if(!isInUsers(sname, data)){
        cout << "User does not exist" << endl;
        return "";
    }
    // pad seller name
    n = 15 - sname.length();
    for(int i = 0; i < n; i++){
        sname = sname + ' ';
    }

    // pad buyer (current user) username
    uname = username;
    n = 15 - uname.length();
    for(int i = 0; i < n; i++){
        uname = uname + ' ';
    }

    // output current bid info
    double currentBid;
    vector<Item> items = data.items;
    for(size_t i=0; i<items.size(); ++i) {
        if (items[i].getItemName() == iname) {
            currentBid = items[i].getCurrentBid();
        }
    }

    cout <<"Current bid: " << currentBid << endl;
    // get amt to bid
    double amt;
    cout << "Enter amount to bid" << endl;
    cin >> amt;

    // bid restriction
    if (amt < currentBid * 1.05){
        cout << "Bid must be 5% higher than previous bid" <<endl;
        return "";
    }
    // pad amt to be 9 elements long
    // set any input to two decimal places and cast to sting
    stringstream stream;
    stream << fixed << setprecision(2) << amt;
    creds = stream.str();

    int l = 6 - creds.length();
    for (int i = 0; i < l; i++){
        creds = '0' + creds;
    }
    return (transactionCode + ' ' + iname + ' ' + sname + ' ' + uname + ' ' + creds);

}


/*
Child class of the user object
handles all functions that only Sell-Standard users can do

inputs: username, account type, credits
outputs: returns a User object
*/

Sell_Standard::Sell_Standard(string uname, string accttyp, double cred) : User(uname, accttyp, cred){}

string Sell_Standard::advertise(Data data) {
    // input: none, user inputs: item name, minimum bid, days to option
    // output: none, write advertise info to transaction file
    // Description: ceates a record of advertisement on User instance and writes this information to the transaction file

    string iname;
    string numDays;
    string minBid;
    string uname;
    string transactionCode = "03";

    // get item name
    cout << "Enter item name:" <<endl;
    cin >> iname;

    // check length
    if (iname.length() > 25){
        cout << "Item name too long, can be a maximum of 25 characters" << endl;
        return "";
    }
    // pad item name
    int n = 25 - iname.length();
    for(int i = 0; i < n; i++){
        iname = iname + ' ';
    }

    // get min bid
    double amt;
    cout << "Enter minimum bid:" <<endl;
    cin >> amt;

    // check min bid is under 999.99
    if (amt > 999.99){
        cout << "Item can be at maximum $999.99" << endl;
        return "";
    }

    // pad amt to be 9 elements long
    // set any input to two decimal places and cast to string
    stringstream stream;
    stream << fixed << setprecision(2) << amt;
    minBid = stream.str();

    int l = 9 - minBid.length();
    for (int i = 0; i < l; i++){
        minBid = '0' + minBid;
    }

    // get max days
    int days;
    cout << "Enter days until sale ends" << endl;
    cin >> days;

    // check days is under 100
    if (days > 100){
        cout << "Max number of days is 100" << endl;
        return "";
    }
    // pad num days to 3 digits
    numDays = to_string(days);
    n = 3 - numDays.length();
    for (int i=0; i < n; i++){
        numDays = '0' + numDays;
    }

    // pad username
    uname = username;
    n = 15 - uname.length();
    for(int i = 0; i < n; i++){
        uname = uname + ' ';
    }

    return (transactionCode + ' ' + iname + ' ' + uname + ' ' + numDays + ' ' + minBid);
}

/*
Child class of the user object
handles all functions that only Buy-Standard users can do

inputs: username, account type, credits
outputs: returns a User object
*/

Buy_Standard::Buy_Standard(string uname, string accttyp, double cred) : User(uname, accttyp, cred){}

string Buy_Standard::bid(Data data){
    // get seller username and item name
    string iname;
    string sname;
    string transactionCode = "04";
    string creds;
    string uname;

    cout << "Enter Item name" << endl;
    cin >> iname;

    // check item exists
    if(!isInItems(iname, data)){
        cout << "Item does not exist" << endl;
        return "";
    }

    // pad item name
    int n = 25 - iname.length();
    for(int i = 0; i < n; i++){
        iname = iname + ' ';
    }

    cout << "Enter seller's username" << endl;
    cin >> sname;

    // check user exists
    if(!isInUsers(sname, data)){
        cout << "User does not exist" << endl;
        return "";
    }
    // pad seller name
    n = 15 - sname.length();
    for(int i = 0; i < n; i++){
        sname = sname + ' ';
    }

    // pad buyer (current user) username
    uname = username;
    n = 15 - uname.length();
    for(int i = 0; i < n; i++){
        uname = uname + ' ';
    }

    // output current bid info
    double currentBid;
    vector<Item> items = data.items;
    for(size_t i=0; i<items.size(); ++i) {
        if (items[i].getItemName() == iname) {
            currentBid = items[i].getCurrentBid();
        }
    }

    cout <<"Current bid: " << currentBid << endl;
    // get amt to bid
    double amt;
    cout << "Enter amount to bid" << endl;
    cin >> amt;

    // bid restriction
    if (amt < currentBid * 1.05){
        cout << "Bid must be 5% higher than previous bid" <<endl;
        return "";
    }
    // pad amt to be 9 elements long
    // set any input to two decimal places and cast to sting
    stringstream stream;
    stream << fixed << setprecision(2) << amt;
    creds = stream.str();

    int l = 6 - creds.length();
    for (int i = 0; i < l; i++){
        creds = '0' + creds;
    }
    return (transactionCode + ' ' + iname + ' ' + sname + ' ' + uname + ' ' + creds);

}



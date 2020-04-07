#include "item.h"
#include "user.h"

#include <string>


/*
    Purpose: Constructor that initiates an instance of class Item with given parameters
    Input:
        itemName: Name of the item 
        seller: User that is selling the item
        currentPrice: Current highest bid for the item
    Output: None
*/
Item::Item(string itemName, User seller, float currentPrice, int auctionDays){
    this->itemName = itemName;
    this->seller = seller;
    this->currentPrice = currentPrice;
    this->auctionDays = auctionDays;
}

/*
    Purpose: Set the name of the item to the passed string parameter
    Input: Name of the item
    Output: None
*/
void Item::setItemName(std::string itemName){
    this->itemName = itemName;
}

/*
    Purpose: Get the name of the item
    Input: None
    Output: Returns the item's name
*/
std::string Item::getItemName(){
    return itemName;
}

/*
    Purpose: To get the seller of the item
    Input: None
    Output: Returns the the seller 
*/
User Item::getSeller(){
    return seller;
}

/*
    Purpose: Set the seller of the current item
    Input: Instance of User
    Output: None
*/
void Item::setSeller(User seller){
    this->seller = seller;
}

/*
    Purpose: Get the current highest bid for the item 
    Input: None
    Output: Current highest bid returned as a float 
*/
float Item::getCurrentPrice(){
    return currentPrice;
}

/*
    Purpose: Sets the current highest bid to the given price 
    Input: Float for the the current price
    Output: None
*/
void Item::setCurrentPrice(float price){
    this->currentPrice = price;
}

/*
    Purpose: Get the number of days that the item is available for auction 
    Input: None
    Output: Number of days the item is available for auction 
*/
int Item::getAuctiondays(){
    return auctionDays;
}

/*
    Purpose: Set the number of days that the item is available for auction
    Input: Number days as an integer
    Output: None
*/ 
void Item::setAuctionDays(int days){
    this->auctionDays = days;
}

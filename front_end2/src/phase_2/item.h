#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "user.h"

#include <string>
#include <iostream>

/*
    The item class is used to create an instance of Item class that will be stored in
    an Item vector in a session instance after reading in available items.
*/
class Item {
    public:
        std::string itemName;           //Name of the item
        User seller;                    //User selling the item
        float currentPrice;             //Current highest bid on the item
        int auctionDays;                //Number days that item is available for auction 

    
        /*
            Purpose: Constructor that initiates an instance of class Item with given parameters
            Input:
                itemName: Name of the item 
                seller: User that is selling the item
                currentPrice: Current highest bid for the item
            Output: None
        */
        Item(string itemName, User seller, float currentPrice, int auctionDays);
        
        
        /*
            Purpose: Set the name of the item to the passed string parameter
            Input: Name of the item
            Output: None
        */
        void setItemName(std::string itemName);
        

        /*
            Purpose: Get the name of the item
            Input: None
            Output: Returns the item's name
        */
        std::string getItemName();
        
        
        /*
            Purpose: To get the seller of the item
            Input: None
            Output: Returns the the seller 
        */
        User getSeller();
        

        /*
            Purpose: Set the seller of the current item
            Input: Instance of User
            Output: None
        */
        void setSeller(User seller);
        

        /*
            Purpose: Get the current highest bid for the item 
            Input: None
            Output: Current highest bid returned as a float 
        */
        float getCurrentPrice();
        

        /*
            Purpose: Sets the current highest bid to the given price 
            Input: Float for the the current price
            Output: None
        */
        void setCurrentPrice(float price);
        

        /*
            Purpose: Get the number of days that the item is available for auction 
            Input: None
            Output: Number of days the item is available for auction 
        */
        int getAuctiondays();


        /*
            Purpose: Set the number of days that the item is available for auction
            Input: Number days as an integer
            Output: None
        */  
        void setAuctionDays(int days);
        
};

#endif
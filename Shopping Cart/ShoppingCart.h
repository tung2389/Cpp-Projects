#include<iostream>
#include<string>
#include<vector>
#include"ItemToPurchase.h"
using namespace std;

#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

class ShoppingCart {
    public:
        ShoppingCart();
        ShoppingCart(string name, string date);

        string GetCustomerName() const;
        string GetDate() const;

        void AddItem(ItemToPurchase newItem);
        void RemoveItem(string itemName);
        void ModifyItem(ItemToPurchase item);

        int GetNumItemsInCart() const;
        int GetCostOfCart() const;
        void PrintTotal() const;
        void PrintDescriptions() const;

        // Extra method
        void PrintCustomerInfo() const;

    private:
        string customerName;
        string currentDate;
        vector<ItemToPurchase> cartItems;
    
};

#endif
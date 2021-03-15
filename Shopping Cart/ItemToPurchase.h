#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H

#include<iostream>
#include<string>
using namespace std;

class ItemToPurchase {
    public:
        ItemToPurchase();
        ItemToPurchase(string name, string description, int price, int quantity);

        void SetName(string name);
        string GetName() const;

        void SetDescription(string description);
        string GetDescription() const;

        void SetPrice(int price);
        int GetPrice() const;

        void SetQuantity(int quantity);
        int GetQuantity() const; 

        void PrintItemCost() const;
        void PrintItemDescription() const;

    private:
        string itemName;
        string itemDescription;
        int itemPrice;
        int itemQuantity;
};

#endif

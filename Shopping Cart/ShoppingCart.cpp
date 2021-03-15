#include<iostream>
#include<string>
#include<vector>
#include"ShoppingCart.h"
#include"ItemToPurchase.h"
using namespace std;

ShoppingCart::ShoppingCart() {
    customerName = "none";
    currentDate = "January 1, 2016";
}

ShoppingCart::ShoppingCart(string name, string date) {
    customerName = name;
    currentDate = date;
}

string ShoppingCart::GetCustomerName() const {
    return customerName;
}

string ShoppingCart::GetDate() const {
    return currentDate;
}

void ShoppingCart::AddItem(ItemToPurchase newItem) {
    cartItems.push_back(newItem);
}

void ShoppingCart::RemoveItem(string itemName) {
    int itemIndex = -1;

    for(int itemId = 0; itemId < cartItems.size(); itemId++) {
        if(cartItems.at(itemId).GetName() == itemName) {
            itemIndex = itemId;
            break;
        }
    }

    if(itemIndex != -1) {
        cartItems.erase(cartItems.begin() + itemIndex);
    }
    else {
        cout << "Item not found in cart. Nothing removed." << endl;
    }
}

void ShoppingCart::ModifyItem(ItemToPurchase item) {
    bool found = false;

    // Use reference variable of ItemToPurchase so that we can modify the original item directly.
    for(ItemToPurchase& originalItem : cartItems) {

        if(originalItem.GetName() == item.GetName()) {
            string newDescription = item.GetDescription();
            // If new description is not default value, update original item.
            if(newDescription != "none") {
                originalItem.SetDescription(newDescription);
            }

            int newPrice = item.GetPrice();
            // If new price is not default value, update original item.
            if(newPrice != 0) {
                originalItem.SetPrice(newPrice);
            }

            int newQuantity = item.GetQuantity();
            // If new quantity is not default value, update original item.
            if(newQuantity != 0) {
                originalItem.SetQuantity(newQuantity);
            }

            found = true;
            break;
        }

    }

    if(!found) {
        cout << "Item not found in cart. Nothing modified." << endl;
    }
}

int ShoppingCart::GetNumItemsInCart() const {
    int size = 0;
    for(const ItemToPurchase& item : cartItems) {
        size += item.GetQuantity();
    }
    return size;
}

int ShoppingCart::GetCostOfCart() const {
    int totalCost = 0;
    for(const ItemToPurchase& item : cartItems) {
        totalCost += item.GetPrice() * item.GetQuantity();
    }
    return totalCost;
}

void ShoppingCart::PrintTotal() const {
    cout << customerName << "'s Shopping Cart - " << currentDate << endl;
    cout << "Number of Items: " << GetNumItemsInCart() << endl;
    cout << endl;

    for(const ItemToPurchase& item : cartItems) {
        item.PrintItemCost();
    } 

    if(GetNumItemsInCart() == 0) {
        cout << "SHOPPING CART IS EMPTY" << endl;
        cout << endl;
    }
    else {
        cout << endl;
    }

    cout << "Total: $" << GetCostOfCart() << endl;
}

void ShoppingCart::PrintDescriptions() const {
    cout << customerName << "'s Shopping Cart - " << currentDate << endl;
    cout << endl;

    cout << "Item Descriptions" << endl;
    for(const ItemToPurchase& item : cartItems) {
        item.PrintItemDescription();
    }
}

void ShoppingCart::PrintCustomerInfo() const {
    cout << "Customer name: " << customerName << endl;
    cout << "Today's date: " << currentDate << endl;
}


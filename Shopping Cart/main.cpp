#include<iostream>
#include<string>
#include"ItemToPurchase.h"
#include"ShoppingCart.h"
#include"Manager.h"
using namespace std;

int main() {
    string name, date;
    Manager::GetCustomerInfo(name, date);
    cout << endl;

    ShoppingCart shoppingCart(name, date);
    shoppingCart.PrintCustomerInfo();

    char option = 'z';

    while(option != 'q') {
        cout << endl;
        Manager::PrintMenu();
        cout << endl;
        cout << "Choose an option:" << endl;
        cin >> option;

        while(!Manager::isOptionValid(option)) {
            cout << "Choose an option:" << endl;
            cin >> option;
        }

        if(option == 'o') {
            cout << "OUTPUT SHOPPING CART" << endl;
            shoppingCart.PrintTotal();
        }
        else if(option == 'i') {
            cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
            shoppingCart.PrintDescriptions();
        }
        else if(option == 'a') {
            ItemToPurchase newItem;
            cout << "ADD ITEM TO CART" << endl;

            string temp;
            // Skip the newline character.
            getline(cin, temp);

            Manager::GetItemInfo(newItem);
            shoppingCart.AddItem(newItem);
        }
        else if(option == 'd') {
            string itemName;
            cout << "REMOVE ITEM FROM CART" << endl;
            cout << "Enter name of item to remove:" << endl;
            
            string temp;
            // Skip the newline character.
            getline(cin, temp);

            getline(cin, itemName);
            shoppingCart.RemoveItem(itemName);
        }
        else if(option == 'c') {
            ItemToPurchase updatedItem;
            string itemName;
            int itemQuantity;

            cout << "CHANGE ITEM QUANTITY" << endl;
            cout << "Enter the item name:" << endl;
            string temp;
            // Skip the newline character.
            getline(cin, temp);
            
            getline(cin, itemName);

            cout << "Enter the new quantity:" << endl;
            cin >> itemQuantity;
            
            updatedItem.SetName(itemName);
            updatedItem.SetQuantity(itemQuantity);

            shoppingCart.ModifyItem(updatedItem);
        }
    }
}   
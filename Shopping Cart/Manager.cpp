#include<string>
#include"ItemToPurchase.h"
#include"Manager.h"
using namespace std;

void Manager::GetCustomerInfo(string& name, string& date) {
    cout << "Enter customer's name:" << endl;
    getline(cin, name);

    cout << "Enter today's date:" << endl;
    getline(cin, date);
}

void Manager::PrintMenu() {
    cout << "MENU" << endl;
    cout << "a - Add item to cart" << endl;
    cout << "d - Remove item from cart" << endl;
    cout << "c - Change item quantity" << endl;
    cout << "i - Output items' descriptions" << endl;
    cout << "o - Output shopping cart" << endl;
    cout << "q - Quit" << endl;
}

void Manager::GetItemInfo(ItemToPurchase& item) {
    string name, description;
    int price, quantity;

    cout << "Enter the item name:" << endl;
    getline(cin, name);
    
    cout << "Enter the item description:" << endl;
    getline(cin, description);

    cout << "Enter the item price:" << endl;
    cin >> price;

    cout << "Enter the item quantity:" << endl;
    cin >> quantity;

    item.SetName(name);
    item.SetDescription(description);
    item.SetPrice(price);
    item.SetQuantity(quantity);
}

bool Manager::isOptionValid(char option) {
    return (option == 'a' || option == 'd' || option == 'c' || option == 'i' || option == 'o' || option == 'q');
}
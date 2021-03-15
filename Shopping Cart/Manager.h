#include<iostream>
#include<string>
#include"ItemToPurchase.h"
using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager {
    public:
        static void GetCustomerInfo(string& name, string& date);
        static void PrintMenu();
        static void GetItemInfo(ItemToPurchase& item);
        static bool isOptionValid(char option);
};

#endif


#ifndef UTILITY_H
#define UTILITY_H

#include<iostream>
#include<vector>
using namespace std;

void swap(vector<int>& nums, int i, int j);
int randInt(int min, int max);
void printVector(const vector<int>& nums); 
vector<int> generateLists(int length);

#endif


#ifndef SORT_H
#define SORT_H

#include<iostream>
#include<vector>
using namespace std;

void selectionSort(vector<int>& nums);
void insertionSort(vector<int>& nums);
void mergeSort(vector<int>& nums, int left, int right);
void quickSort(vector<int>& nums, int left, int right);


#endif
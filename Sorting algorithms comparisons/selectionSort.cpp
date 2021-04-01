

#include<iostream>
#include<vector>
#include"utility.h"
using namespace std;

void selectionSort(vector<int>& nums)  {
    int len = nums.size();

    for(int i = 0; i < len - 1; i++) {
        int indexOfMin = i;

        for(int j = i + 1; j < len; j++) {
            if(nums[j] < nums[indexOfMin]) {
                indexOfMin = j;
            }
        }

        swap(nums, i, indexOfMin);
    }
}


#include<iostream>
#include<vector>
using namespace std;

void insertionSort(vector<int>& nums) {
    int len = nums.size();

    for(int i = 0; i < len; i++) {
        int currentElement = nums[i];
        int j = i - 1;

        // While there is any elemement which is before the current element and greater then the current element
        //, shift that element one step to the right
        while(j >= 0 && nums[j] > currentElement) {
            nums[j + 1] = nums[j]; // Shift that element one step to the right
            j--;
        }
        nums[j + 1] = currentElement;
    }
}

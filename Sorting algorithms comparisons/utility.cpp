#include<iostream>
#include<vector>
using namespace std;

void swap(vector<int>& nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int randInt(int min, int max) {
    /* 
    Return a random number within a range.

    Parameters:
        min: the minimum number
        max: the maximum number

    Returns:
        A random number within the range [min, max], inclusive
    */
    return rand() % (max - min + 1) + min;
}

void printVector(const vector<int>& nums) {
    for(int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

vector<int> generateLists(int length) {
    vector<int> nums(length);
    
    for(int i = 0; i < length; i++) {
        int randNum = randInt(1, length);
        nums[i] = randNum;
    }

    return nums;
}
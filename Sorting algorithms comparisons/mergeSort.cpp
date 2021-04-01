

#include<iostream>
#include<vector>
using namespace std;

void mergeInCorrectOrder(vector<int>& nums, int left, int mid, int right) {

    int leftIndex = left;
    int rightIndex = mid + 1;
    int mergedIndex = 0;
    int mergedSize = right - left + 1;
    vector<int> mergedData(mergedSize);

    while(leftIndex <= mid && rightIndex <= right) {
        if(nums[leftIndex] < nums[rightIndex]) {
            mergedData[mergedIndex] = nums[leftIndex];
            leftIndex += 1;
        }
        else {
            mergedData[mergedIndex] = nums[rightIndex];
            rightIndex += 1;
        }
        mergedIndex += 1;
    } 

    while(leftIndex <= mid) {
        mergedData[mergedIndex] = nums[leftIndex];
        leftIndex += 1;
        mergedIndex += 1;
    }

    while(rightIndex <= right) {
        mergedData[mergedIndex] = nums[rightIndex];
        rightIndex += 1;
        mergedIndex += 1;
    }

    for(int i = left; i <= right; i++) {
        nums[i] = mergedData[i - left];
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    int mid = (left + right) / 2;
    if(left < right) {
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        mergeInCorrectOrder(nums, left, mid, right);
    }
}
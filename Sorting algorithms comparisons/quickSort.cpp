

#include<iostream>
#include<vector>
#include"utility.h"
using namespace std;

int Partition(vector<int>& nums, int left, int right) {
    int greaterIdx;
    int smallerIdx;
    int midpoint;
    int pivot;
    bool done;

    /* Pick middle element as pivot */
    midpoint = (left + right) / 2;
    pivot = nums[midpoint];

    done = false;
    greaterIdx = left;
    smallerIdx = right;

    while (!done) {
        
        /* Increment greaterIdx while nums[greaterIdx] < pivot */
        while (nums[greaterIdx] < pivot) {
            ++greaterIdx;
        }

        /* Decrement smallerIdx while pivot < nums[smallerIdx] */
        while (pivot < nums[smallerIdx]) {
            --smallerIdx;
        }

        /* If there are 0 or 1 elements remaining, all nums are partitioned. Return smallerIdx */
        if (greaterIdx >= smallerIdx) {
            done = true;
        }
        else {
            swap(nums, greaterIdx, smallerIdx);
            ++greaterIdx;
            --smallerIdx;
        }
    }

    return smallerIdx;
}


void quickSort(vector<int>& nums, int left, int right) {
    /* Base case is (left >= right): If there are 0 or 1 elements to sort, this partition is already sorted */

    if(left < right) {
        /* Partition the data within the array. Value j returned from partitioning is location of last element in low partition. */
        int lowLastIdx = Partition(nums, left, right);

        /* Recursively sort low partition (left to lowLastIdx) and high partition (lowLastIdx + 1 to right) */
        quickSort(nums, left, lowLastIdx);
        quickSort(nums, lowLastIdx + 1, right);
    }
}
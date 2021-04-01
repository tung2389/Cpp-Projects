

#include<iostream>
#include<vector>
#include<sys/time.h>
#include"sort.h"
#include"utility.h"
using namespace std;

// Pass function sortFunc as parameter to function testSingleSort
void testSingleSort(vector<int> nums, void sortFunc(vector<int>& numbers)) {
    sortFunc(nums);
    printVector(nums);
}

void testAllSorts() {
    vector<int> nums = {5,6,4,8,7,2,9,3,1};

    // Use lambda expression for easy testing
    testSingleSort(nums, [](vector<int>& numbers) {selectionSort(numbers);});
    testSingleSort(nums, [](vector<int>& numbers) {insertionSort(numbers);});
    testSingleSort(nums, [](vector<int>& numbers) {mergeSort(numbers, 0, numbers.size() - 1);});
    testSingleSort(nums, [](vector<int>& numbers) {quickSort(numbers, 0, numbers.size() - 1);});
}

// Pass function sortFunc as parameter to function measureTime for convenient measurement.
double measureTime(vector<int> nums, void sortFunc(vector<int>& numbers)) {
    timeval timeBefore, timeAfter; // timeval type defined in sys/time.h
    long long diffSeconds, diffUSeconds; // elapsed seconds and microseconds
    
    gettimeofday(&timeBefore, NULL); // get the time before
    sortFunc(nums);
    gettimeofday(&timeAfter, NULL); // get the time after
    
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec; // elapsed seconds
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec; // elapsed microseconds
    double runTime = diffSeconds + (diffUSeconds / 1000000.0); // total elapsed time
    
    return runTime;
}

int main() {
    
    // Uncomment this line to test all sorting algorithms
    // testAllSorts();

    // Export these output to .csv file using Linux I/O redirection

    cout << "length,selectionSort,insertionSort,mergeSort,quickSort"  ;
    cout << endl;

    for(int len = 1000; len <= 100000; len += 10000) {
        vector<int> nums = generateLists(len);

        // Use lambda expression for easy time measurement
        double time1 = measureTime(nums, [](vector<int>& numbers) {selectionSort(numbers);});
        double time2 = measureTime(nums, [](vector<int>& numbers) {insertionSort(numbers);});
        double time3 = measureTime(nums, [](vector<int>& numbers) {mergeSort(numbers, 0, numbers.size() - 1);});
        double time4 = measureTime(nums, [](vector<int>& numbers) {quickSort(numbers, 0, numbers.size() - 1);});

        cout << len << "," << time1 << "," << time2 << "," << time3 << "," << time4 << endl;
    }
}
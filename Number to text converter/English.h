#ifndef ENGLISH_H
#define ENGLISH_H

#include<string>
using namespace std;

class English {
    public:
        const static string textOfDigit[10];
        const static string textOfTwoDigitsLessThan20[10];
        const static string textOfTenMultiples[];
        const static string textOfTenPower[];
        const static string negative;
};

const string English::textOfDigit[10] = {
    "", "one", "two",
    "three", "four", "five", 
    "six", "seven", "eight", "nine"
};

const string English::textOfTwoDigitsLessThan20[10] = {
    "ten", "eleven", "twelve",
    "thirteen",  "fourteen", "fifteen", 
    "sixteen", "seventeen", "eighteen", "nineteen"
};

const string English::textOfTenMultiples[] = {
    "", "", "twenty",
    "thirty", "forty", "fifty", 
    "sixty", "seventy", "eighty", "ninety" 
};

const string English::textOfTenPower[] = {
    "", "", "hundred",
    "thousand", "", "",
    "million", "", "",
    "billion"
};

const string English::negative = "negative";

#endif
/*
Author: Tung Luu
Date: March 9, 2021
Purpose: Answer for TEST FOR SOFTWARE ENGINEER, DESKTOP BROWSER. This program will work for number with the maximum of 12 digits, but not greater than INT_MAX
*/

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include"NumberToText.h"
#include"English.h"
#include"Vietnamese.h"
using namespace std;

template<class Language>
string NumToTextConverter::convert3DigitsNumToText(int num) {
    string text = "";
    int firstDigit = num / 100;
    // Hundred
    if(firstDigit > 0) {
        text += Language::textOfDigit[firstDigit] + " " + Language::textOfTenPower[2] + " ";
    }

    int lastTwoDigits = (num % 100);

    if(lastTwoDigits < 10) {
        text += Language::textOfDigit[lastTwoDigits] + " ";
    }
    else if(lastTwoDigits < 20) {
        text += Language::textOfTwoDigitsLessThan20[lastTwoDigits % 10] + " ";
    }
    else {
        text += Language::textOfTenMultiples[lastTwoDigits / 10];
        int lastDigit = lastTwoDigits % 10;
        if(lastDigit > 0) {
            text += "-" + Language::textOfDigit[lastDigit];
        }
        text += " ";
    }
    
    return text;
}

string NumToTextConverter::removeTrailingSpaces(string text) {
    int spacesCount = 0;
    int index = text.size() - 1;
    while(text[index] == ' ') {
        index--;
        spacesCount++;
    }
    return text.substr(0, text.size() - spacesCount);
}

template<class Language>
string NumToTextConverter::convertToText(int num) {
    string text = "";
    if(num < 0) {
        text = text + Language::negative + " ";
        num = fabs(num);
    }

    // Billion
    int billionDigits = num / 1000000000;
    if(billionDigits > 0) {
        text += convert3DigitsNumToText<Language>(billionDigits) + Language::textOfTenPower[9] + " ";
    }
    num = num % 1000000000;

    // Million
    int millionDigits = num / 1000000;
    if(millionDigits > 0) {
        text += convert3DigitsNumToText<Language>(millionDigits) + Language::textOfTenPower[6] + " ";
    }
    num = num % 1000000;

    // Thousand
    int thousandDigits = num / 1000;
    if(thousandDigits > 0) {
        text += convert3DigitsNumToText<Language>(thousandDigits) + Language::textOfTenPower[3] + " ";
    }
    num = num % 1000;

    text += convert3DigitsNumToText<Language>(num);
    
    return removeTrailingSpaces(text);
}

int main() {
    NumToTextConverter converter;
    int num;
    cin >> num;
    cout << converter.convertToText<English>(num) << endl;
    cout << converter.convertToText<Vietnamese>(num);
}
#ifndef VIETNAMESE_H
#define VIETNAMESE_H

#include<string>
using namespace std;

class Vietnamese {
    public:
        const static string textOfDigit[10];
        const static string textOfTwoDigitsLessThan20[10];
        const static string textOfTenMultiples[];
        const static string textOfTenPower[];
        const static string negative;
};

const string Vietnamese::textOfDigit[10] = {
    "", "một", "hai",
    "ba", "bốn", "năm", 
    "sáu", "bảy", "tám", "chín"
};

const string Vietnamese::textOfTwoDigitsLessThan20[10] = {
    "mười", "mười một", "mười hai",
    "mười ba",  "mười bốn", "mười năm", 
    "mười sáu", "mười bảy", "mười tám", "mười chín"
};

const string Vietnamese::textOfTenMultiples[] = {
    "", "", "hai mươi",
    "ba mươi", "bốn mươi", "năm mươi", 
    "sáu mươi", "bảy mươi", "tám mươi", "chín mươi" 
};

const string Vietnamese::textOfTenPower[] = {
    "", "", "trăm",
    "nghìn", "", "",
    "triệu", "", "",
    "tỉ"
};

const string Vietnamese::negative = "âm";

#endif
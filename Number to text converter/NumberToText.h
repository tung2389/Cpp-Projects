#ifndef NUMBERTOTEXT_H
#define NUMBERTOTEXT_H
#include<string>
using namespace std;

class NumToTextConverter {
    public:
        template<class Language>
        string convertToText(int num);
    private:
        template<class Language>
        string convert3DigitsNumToText(int num);
        
        string removeTrailingSpaces(string text);
};

#endif
/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string str;
    cout << "const int raw_value[ARR_MAX_SIZE] PROGMEM = ";
    cout << "{";
    size_t i = 0;
    while(getline(cin, str))
    {
        ++i;
        cout << str << ", ";
    }
    cout << "};" << endl;;
    cout << "const size_t ARR_MAX_SIZE = " << i << ";" << endl;

    return 0;
}


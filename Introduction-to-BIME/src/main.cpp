/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */


#include <iostream>
#include <algorithm>
#include <fstream>

extern "C"
{
#include "emg.h"
}

//#define NDEBUG

using namespace std;

enum value_type
{
    invalid_value_type,
    muscle_sensor_value,
    raw_muscle_sensor_value,
};

inline value_type identification_type(const string& type_str)
{
    if(type_str.compare("muscle_sensor_value") == 0)
        return muscle_sensor_value;
    if(type_str.compare("raw_muscle_sensor_value") == 0)
        return raw_muscle_sensor_value;
    return invalid_value_type;
}

bool receive_parser(const string& token, value_type& type, int& value)
{
#ifndef NDEBUG
    clog << "token: " << token << endl;
#endif
    size_t quote_pos[4];
    for(size_t i = 0;i < 4;++i)
    {
        if(i == 0)
            quote_pos[i] = token.find("\"");
        else
            quote_pos[i] = token.find("\"", quote_pos[i - 1] + 1);

        if(quote_pos[i] == string::npos)
            return false;
    }
    string value_type_str = token.substr(quote_pos[0] + 1, quote_pos[1] - quote_pos[0] - 1);
    string value_str      = token.substr(quote_pos[2] + 1, quote_pos[3] - quote_pos[2] - 1);
#ifndef NDEBUG
    clog << "value_type_str: " << value_type_str << endl;
    clog << "value_str:" << value_str << endl;
#endif
    type = identification_type(value_type_str);
    try
    {
        value = stoi(value_str);
    }
    catch(exception& e)
    {
        clog << e.what();
        return false;
    }

    return true;
}


int main()
{
    ios_base::sync_with_stdio(false);

    string device_name = "/dev/ttyACM0";
    string set_baud_rate_command = string("stty -F ") + device_name + string(" 115200");

    cout << "execute: " << set_baud_rate_command << endl;
    if(system(set_baud_rate_command.c_str()))
    {
        cerr << set_baud_rate_command << " return none zero status.\n";
        return 1;
    }

    ifstream device(device_name);
    if(!device.is_open())
    {
        device.close();
        cerr << "Cannot open " << device_name << " .\n";
        return 1;
    }

    string token;
    //EMG* my_emg = new_EMG((unsigned short)115200, (float)0.5, (unsigned short)40, (unsigned short)150, HIGH_PASS_FILTER_ON, REFERENCE_UNAVAILABLE);
    EMG* my_emg = new_EMG((unsigned short)5200, (float)0.5, (unsigned short)40, (unsigned short)150, HIGH_PASS_FILTER_ON, REFERENCE_UNAVAILABLE);
    while(getline(device, token))
    {
        if(token.empty())
            continue;

        value_type token_type;
        int token_value;

        // parser
        if(receive_parser(token, token_type, token_value))
        {
            cout << "raw value: " << token_value << endl;
        }
        else
        {
            clog << "Cannot parser \"" << token << "\".\n";
            continue;
        }

        int emg_value;
        // analysis
        if(token_type == muscle_sensor_value)
        {
            emg_value = token_value;
        }
        if(token_type == raw_muscle_sensor_value)
        {
            emg_value = filter_EMG(my_emg, token_value);
            // warning
            emg_value *= 11;
        }
        cout << "emg value: " << emg_value << endl;
    }
    free_EMG(my_emg);
    return 0;
}


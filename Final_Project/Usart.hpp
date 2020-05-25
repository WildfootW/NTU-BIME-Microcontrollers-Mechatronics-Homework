/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */


#ifndef USART_HPP
#define USART_HPP

class Usart
{
public:
    Usart(unsigned int baud_rate = 9600): baud_rate(baud_rate){}
    void initial();
    void put_str(char* str_ptr);
private:
    unsigned int baud_rate;
};

#endif //USART_HPP


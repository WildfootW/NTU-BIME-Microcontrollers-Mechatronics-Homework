/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef UASRT_H
#define USART_H
typedef struct Usart
{
    uint16_t baud_rate;
}Usart;
typedef struct Usart Usart;
void Usart__init(Usart* self, uint16_t baud_rate);
void Usart__put_string(Usart* self, char* str_ptr);

#endif // USART_H


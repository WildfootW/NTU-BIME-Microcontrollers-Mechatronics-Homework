/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef Usart
#define Usart

typedef struct Usart
{
    uint8_t baud_rate;
}Usart;
void Usart__init(Usart* self, uint8_t baud_rate);
void Usart__put_string(Usart* self, char* str_ptr);

#endif // Usart


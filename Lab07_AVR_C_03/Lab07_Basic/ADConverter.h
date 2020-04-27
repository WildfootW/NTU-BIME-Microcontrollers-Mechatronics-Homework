/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#ifndef ADConverter
#define ADConverter
typedef struct ADConverter
{

}ADConverter;
void ADConverter__init(ADConverter* self);
void ADConverter__start(ADConverter* self);
uint16_t ADConverter__read(ADConverter* self);
#endif //ADConverter


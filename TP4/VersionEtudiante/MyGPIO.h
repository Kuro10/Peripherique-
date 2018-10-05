#ifndef __MYGPIO_H__
#define __MYGPIO_H__
#include "stm32f10x.h"


typedef struct
{
  GPIO_TypeDef * GPIO;
  char GPIO_Pin;             
  char GPIO_Techno;  
}GPIO_Struct_TypeDef;

#define In_Floating 0x0100
#define In_PullDown 0x1000
#define In_PullUp 0x1000
#define In_Analog 0x0000
#define Out_Ppull 0x0001
#define Out_OD 0x0101

void GPIO_Init( GPIO_Struct_TypeDef *  GPIOStructPtr);   // configuration d'une pin
int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin);      // renvoie 0 ou autre chose différent de 0
void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);      // met 3,3V sur la pin et le GPIO souhaités
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);  // met 0V sur la pin et le GPIO souhaités

#endif

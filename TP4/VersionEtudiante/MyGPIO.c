#include "MyGPIO.h"


void GPIO_Init( GPIO_Struct_TypeDef *  GPIOStructPtr){   // configuration d'une pin 
	if (GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL &= ~(0xF<<(4*GPIOStructPtr->GPIO_Pin));
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Techno<<(4*GPIOStructPtr->GPIO_Pin));
	}
	else{
		GPIOStructPtr->GPIO->CRH &= ~(0xF<<(4*(GPIOStructPtr->GPIO_Pin-8)));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Techno<<(4*(GPIOStructPtr->GPIO_Pin-8)));	
	}
}

int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin){      // renvoie 0 ou autre chose différent de 0
	return (GPIO->IDR >> GPIO_Pin) & 0x1;
}

void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin){	// met 3,3V sur la pin et le GPIO souhaités
	//GPIO->ODR |= (1<<GPIO_Pin);
	GPIO->BSRR |= (1<<GPIO_Pin);
}
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin){  // met 0V sur la pin et le GPIO souhaités
	//GPIO->ODR &= ~(1<<GPIO_Pin);
	GPIO->BRR |= (1<<GPIO_Pin);
}

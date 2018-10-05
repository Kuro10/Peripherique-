#include "stm32f10x.h"
#include "tp2lib.h"
#include "MyGPIO.h" 

int main (void)
{	

	/* TP4 : GPIO */


	//Configurer le BP PC.10 en entree (0x0100)
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(0xF<<(4*2));
	GPIOC->CRH |= (0x4<<(4*2));
	
	//Configurer la LED PD.2 en sortie (0x0001)
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	GPIOD->CRL &= ~(0xF<<(4*2));
	GPIOD->CRL |= (0x1<<(4*2));
	
  // boucle de traitement

  while(1)
    {
      // On vérifie si IDR.10 vaut 0 (lecture de l'état de la broche d'entrée PC.10)
      //if ( ! (GPIOC->IDR & (0x1<<10)) ){
			if ( ! GPIO_Read(GPIOC,10) ){
				// Si l'entrée PC.10 est à 0 on met ODR.2 = 0 (mise à 0 de la broche de sortie PD.2)
				//GPIOD->ODR &= ~(1<<2);
				GPIO_Reset(GPIOD,2);
			}
      else {
				// Si l'entrée PC.10 est à 1 on met ODR.2 = 1 (mise à 1 de la broche de sortie PD.2)
				//GPIOD->ODR |= (1<<2);
				GPIO_Set(GPIOD,2);
			}
    }

}


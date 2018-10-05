#include "stm32f10x.h"
#include "tp2lib.h"
#include "timer.h"  

//int TimerInit(TIM_TypeDef *timer, int arr, int psc);

int LED;
/* Fichier de la couche "application" */
void Ma_Fonction_IT ( void )
{
/* Le code à exécuter pendant l’interruption */
	LED = GPIOA->ODR>>5;
	if (LED==0)
	{
		//allumer la LED
		GPIOA->ODR |= (0x1<<5);
	}
	else
	{
		//eteindre la LED
		GPIOA->ODR &= ~(0x1<<5);
	}
	TIM2->SR &= ~0x1;
}


/* Fichier de la couche pilote */
void (* pFnc) (void) ; /* déclaration d’un pointeur de fonction */

void Init_periph (void (* ptrFonction) (void)) {
	pFnc = ptrFonction; /* affectation du pointeur */
}

//mis en place d'une routine de traitement de l'interruprion
void TIM2_IRQHandler (void){
	if (pFnc != 0)
		(*pFnc) (); /* appel indirect de la fonction */
	
}




int main (void)
{	

	/* TP3 : Timer */

	
	//Activer l'horloge locale de TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Activer counter
	TIM2->CR1 |= (1<<0);
	
	//TimerInit(TIM2,99,5759);
	TIM2->ARR = 0x63;
	TIM2->PSC = 0x167F;
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	TIM2->DIER |= (1<<0);
	TIM2->CR1 |= (1<<0);
	NVIC->ISER[0] |= (1<<28);
	NVIC->IP[28] |= (uint8_t)(0x2<<4);
 
	//Configurer la LED PA.5 en sortie
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x1<<20);
	
	//TimerStart(TIM2);
	
  // boucle de traitement
		while(1)
    {  

    }

}

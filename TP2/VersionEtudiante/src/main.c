#include "stm32f10x.h"
#include "tp2lib.h"
#include "IT.h"
#include "timer.h"  

int TimerInit(TIM_TypeDef *timer, int arr, int psc);
int timerInitIT (TIM_TypeDef * timer, int priority);

int static iteTimer3 ;


/* Fichier de la couche "application" */
void Ma_Fonction_IT ( void )
{
/* Le code à exécuter pendant l’interruption */
	if(iteTimer3++ >= 5){
		iteTimer3 = 0;
	}
	TIM3->SR &= ~0x1;  // mettre à 0 le registre FLAG du TIMER3
}


/* Fichier de la couche pilote */
void (* pFnc) (void) ; /* déclaration d’un pointeur de fonction */

void Init_periph (void (* ptrFonction) (void)) {
	pFnc = ptrFonction; /* affectation du pointeur */
}

//mis en place d'une routine de traitement de l'interruprion
void TIM3_IRQHandler (void){
	
	//if(iteTimer3++ >= 5){
	//	iteTimer3 = 0;
	//}
	//TIM3->SR &= ~0x1;  // mettre à 0 le registre FLAG du TIMER3
	//TempoCPU();
	
	if (pFnc != 0)
		(*pFnc) (); /* appel indirect de la fonction */
	
}




int main (void)
{	

	/* TP2 : Interruption */
	iteTimer3 = 0 ;

	/* à faire dans le main */
	Init_periph(Ma_Fonction_IT);
	
	InitialiserTIM3 ();
	
	//configurer l'interruption sur débordement avec priorié de 2
	TIM3->DIER |= 0x1; 	//mettre à 1 le registre UIE
	
	NVIC->ISER[0] |= (uint32_t)(0x1<<29); //metrre à 1 le registre ISER[0]
	
	//NVIC->IP[29] |= (uint8_t)(0x2<<4); //set priorité à 2 
	timerInitIT (TIM3,2);
	
	DemarrerTIM3();
	
	
  // boucle de traitement
		while(1)
    {  

    }

}

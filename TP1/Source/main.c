#include "stm32f10x.h"

int main (void)
{
  /* Dans p�riph�rique RCC (Reset and Clock Control) le registre APB2ENR
	(Auxiliary Peripheral Bridge 2 Enable Register) permet de valider 
	les horloges des p�riph�riques qui sont branch�s dessus.
	Le but de la ligne suivante est d'activer l'horloge de GPIOA
	(General Purpose Input Output A) en mettant � 1 le bit PIOAEN (PIO A 
	ENable) qui est le bit de rang 2 de APB2ENR et de mettre � z�ro tout 
	les autres bits (voir vid�o de cours).
  */
  *(char *)0x40021018  = 4;
	
	
  /* Dans le p�riph�rique GPIOA le registre CRL (Config Register Low) permet
     de configurer les broches 0 � 7 du GPIOA. Le but des lignes suivantes est de
     configurer PA.0 (broche 0 du port A ou GPIOA) en entr�e.
     Pour cela les 4 bits de poids faible de CRL (donc CRL.3 CRL.2 CRL.1 CRL.0) 
     doivent valoir = 1000 (en binaire), les autres bits devant rester inchang�s !
  */
	//GPIOA->BRR |= 0x1000;  // mettre � 1 uniquement le bit de rang 3
  //GPIOA->BRR &= ~0x0111; // mettre � z�ro uniquement les bits 0 � 2
	GPIOA->CRL |= 0x8;  
  GPIOA->CRL &= ~0x7; 
  /*
    Configure PA.1 en sortie Push Pull 10 MHz, les 4 bits de rang 4 � 7 
    (CRL.7 CRL.6 CRL.5 CRL.4) doivent valoir  0001 (en binaire)
  */
  //GPIOA->CRL &= ~(0xF << (4*0));
  //GPIOA->CRL |= (0x1 << (4*0));
	GPIOA->CRL &= ~(0x7 << (4*1));
  GPIOA->CRL |= (0x1 << (4*1));
	
  // boucle de traitement
  while(1)
    {
      // On v�rifie si IDR.0 vaut 0 (lecture de l'�tat de la broche d'entr�e PA.0)
      if ( ! (GPIOA->IDR & (0x1)) ){
				// Si l'entr�e PA.0 est � 0 on met ODR.1 = 0 (mise � 0 de la broche de sortie PA.1)
				//GPIOA->ODR |= (1<<1);
				GPIOA->ODR &= ~(1<<1);
			}
      else {
				// Si l'entr�e PA.0 est � 1 on met ODR.1 = 1 (mise � 1 de la broche de sortie PA.1)
				//GPIOA->ODR &= ~(1<<0);
				GPIOA->ODR |= (1<<1);
			}
    }

}

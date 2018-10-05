#include "stm32f10x.h"

int main (void)
{
  /* Dans périphérique RCC (Reset and Clock Control) le registre APB2ENR
	(Auxiliary Peripheral Bridge 2 Enable Register) permet de valider 
	les horloges des périphériques qui sont branchés dessus.
	Le but de la ligne suivante est d'activer l'horloge de GPIOA
	(General Purpose Input Output A) en mettant à 1 le bit PIOAEN (PIO A 
	ENable) qui est le bit de rang 2 de APB2ENR et de mettre à zéro tout 
	les autres bits (voir vidéo de cours).
  */
  *(char *)0x40021018  = 4;
	
	
  /* Dans le périphérique GPIOA le registre CRL (Config Register Low) permet
     de configurer les broches 0 à 7 du GPIOA. Le but des lignes suivantes est de
     configurer PA.0 (broche 0 du port A ou GPIOA) en entrée.
     Pour cela les 4 bits de poids faible de CRL (donc CRL.3 CRL.2 CRL.1 CRL.0) 
     doivent valoir = 1000 (en binaire), les autres bits devant rester inchangés !
  */
	//GPIOA->BRR |= 0x1000;  // mettre à 1 uniquement le bit de rang 3
  //GPIOA->BRR &= ~0x0111; // mettre à zéro uniquement les bits 0 à 2
	GPIOA->CRL |= 0x8;  
  GPIOA->CRL &= ~0x7; 
  /*
    Configure PA.1 en sortie Push Pull 10 MHz, les 4 bits de rang 4 à 7 
    (CRL.7 CRL.6 CRL.5 CRL.4) doivent valoir  0001 (en binaire)
  */
  //GPIOA->CRL &= ~(0xF << (4*0));
  //GPIOA->CRL |= (0x1 << (4*0));
	GPIOA->CRL &= ~(0x7 << (4*1));
  GPIOA->CRL |= (0x1 << (4*1));
	
  // boucle de traitement
  while(1)
    {
      // On vérifie si IDR.0 vaut 0 (lecture de l'état de la broche d'entrée PA.0)
      if ( ! (GPIOA->IDR & (0x1)) ){
				// Si l'entrée PA.0 est à 0 on met ODR.1 = 0 (mise à 0 de la broche de sortie PA.1)
				//GPIOA->ODR |= (1<<1);
				GPIOA->ODR &= ~(1<<1);
			}
      else {
				// Si l'entrée PA.0 est à 1 on met ODR.1 = 1 (mise à 1 de la broche de sortie PA.1)
				//GPIOA->ODR &= ~(1<<0);
				GPIOA->ODR |= (1<<1);
			}
    }

}

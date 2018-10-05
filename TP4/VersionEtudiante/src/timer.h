#ifndef __TIMER_H__
#define __TIMER_H__
#include "stm32f10x.h"

/**
 Configure la période d'un timer
 @param timer Pointeur vers le jeu de registre de type TIM_TypeDef du timer considéré (TIM1, TIM2, TIM3 ou TIM4)
 @param arr valeur de l'Autoreload
 @param psc valeur du prescaler
 @return 0 si la configuration est réalisée, -1 si arr ou psc ne sont pas des valeurs acceptables
 */
int TimerInit(TIM_TypeDef *timer, int arr, int psc);

/**
 Configure l'interruption liée au débordement du timer.
 La fonction de traitement de l'interruption est à écrire directement dans le handler.
 @param timer Pointeur vers le jeu de registre de type TIM_TypeDef du timer considéré (TIM1, TIM2, TIM3 ou TIM4)
 @param priority Niveau de priorité de l'interruption
 @return 0 si la configuration est réalisée, -1 si le niveau de priorité n'est pas une valeur acceptable
 */
int TimerInistIT(TIM_TypeDef *timer, int priority);

/**
 Démarre le timer
 @param timer Pointeur vers le jeu de registre de type TIM_TypeDef du timer considéré (TIM1, TIM2, TIM3 ou TIM4)
 */
void TimerStart(TIM_TypeDef *timer);

/**
 Stop le timer
 @param timer Pointeur vers le jeu de registre de type TIM_TypeDef du timer considéré (TIM1, TIM2, TIM3 ou TIM4)
 */
void TimerStop(TIM_TypeDef *timer);

/**
 Retourne l'état de l'événement lié au débordement
 @param timer Pointeur vers le jeu de registre de type TIM_TypeDef du timer considéré (TIM1, TIM2, TIM3 ou TIM4)
 @return 1 si un événement est en attente, 0 sinon
 */
int TimerIsEventUpdated(TIM_TypeDef *timer);

#endif

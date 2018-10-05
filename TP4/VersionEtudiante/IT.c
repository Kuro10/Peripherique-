#include "IT.h"

int timerInitIT (TIM_TypeDef * timer, int priority){

	int nIT; 
	
	if (timer == TIM2){
		nIT=28; 
	}
	if (timer == TIM3){
		nIT=29; 
	}
	if (timer == TIM4){
		nIT=30; 
	}
	if (timer == TIM5){
		nIT=50; 
	}
	if (timer == TIM6){
		nIT=54; 
	}
	if (timer == TIM7){
		nIT=55; 
	}
	
	NVIC->IP[nIT] |= (uint8_t)(priority<<4);  
	
	return 0;
}

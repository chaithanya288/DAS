/*delay_ms*/
#include <LPC21xx.H>
void delay_ms(unsigned int ms)
{
	T0PC=T0TC=0;
	T0PR=15000-1;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}


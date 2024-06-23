/*main.c*/
#include"header.h"
int main()
{
	int pot,ldr,ldrout;
	float vtg,tempr,press;
	uart0_init(9600);
	adc_init();
	spi0_init();
	while(1)
	{
		pot=adc_read(1); //acd ch1
		vtg=(pot*3.3)/1023;
		tempr=(vtg-0.5)/0.01;
		uart0_tx_string("\r\nTemperature:");
		uart0_tx_float(tempr);
		//uart0_tx_ftoa(tempr);
		uart0_tx(' ');
		uart0_tx(186);
		uart0_tx('c');

		ldrout=mcp3204_adc_read(2); //mcp3204 c    h2
		ldr=(ldrout)*100/4095;
		uart0_tx_string("\r\nLight Intensity:")    ;
		uart0_tx_integer(ldr);
		uart0_tx('%');

		/*pot=adc_read(2);
		  vtg=(pot*3.3)/1023;
		  uart0_tx_string("\r\nPressure:");
		  uart0_tx_float(vtg);  */

		pot=adc_read(2);   //adc ch2
		vtg=(pot*3.3)/1023;
		press=(vtg+0.095)/(3.3 * 0.009);
		uart0_tx_string("\r\nPressure:");
		uart0_tx_float(press);
		//uart0_tx_ftoa(press);
		uart0_tx_string("kPa");
		delay_ms(1000);
	}

}


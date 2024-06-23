/*spi0_driver.c*/
#include <LPC21xx.H>
#define cs0 (1<<7)
void spi0_init(void)
{
	PINSEL0|=0x1500;
	IODIR0|=cs0;
	IOSET0=cs0;
	S0SPCR=0x20;
	S0SPCCR=150;
}
#define SPIF ((S0SPSR>>7)&1)
unsigned char spi0(unsigned char data)
{
	S0SPDR=data;
	while(SPIF==0);
	return S0SPDR;
}

/*mcp3204_adc*/
unsigned short int mcp3204_adc_read(int ch_num)
{
	unsigned int result;
	char byteH=0,byteL=0,channel=0;
	channel=ch_num<<6;
	spi0(0x06);
	byteH=spi0(channel);
	byteL=spi0(0x00);
	byteH&=0x0F;
	result=byteH<<8|byteL;
	return result;
}


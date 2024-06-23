/*uarto_driver.c*/
#include <LPC21xx.H>
#include<stdio.h>
void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,15,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	unsigned int result=pclk/(16*baud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL=result&0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0x03;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(char *ptr)
{
	while(*ptr)
	{
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}

#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_integer(int num)
{
	char buf[20];
	sprintf(buf,"%d",num);
	uart0_tx_string(buf);
}

void uart0_tx_float(float num)
{
	char buf[20];
	sprintf(buf,"%.2f",num);
	uart0_tx_string(buf);
}

void uart0_tx_itoa(int num)
{
	int a[10],i=0;
	if(num==0)
		uart0_tx('0');
	if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(--i;i>=0;i--)
		uart0_tx(a[i]);
}

void uart0_tx_ftoa(float num)
{
	char str[10],ch;
	float f1;
	int n1,n2,i,j,l=0,c,l1;
	n1=num;
l1:
	if(n1<0)
	{
		uart0_tx('-');
		num=-num;
		n1=num;
		goto l1;
	}
	else if(n1==0)
	{
		uart0_tx_string("0.");
		f1=(1+num)*1000000;
		n2=f1/10000;
		for(i=n2;i;i=i/10)
			str[l++]=i%10+48;
		for(i=0,j=l-1;i<j;i++,j--)
		{
			ch=str[i];
			str[i]=str[j];
			str[j]=ch;
		}
		for(i=0;i<l;i++)
			str[i]=str[i+1];
		uart0_tx_string(str);
	}
	else
	{
		f1=num*1000000;
		n2=f1/10000;
		for(i=n1,c=0;i;i=i/10)
			c++;
		for(i=n2;i;i=i/10)
			str[l++]=i%10+48;
		for(i=0,j=l-1;i<j;i++,j--)
		{
			ch=str[i];
			str[i]=str[j];
			str[j]=ch;
		}
		for(i=l;i>c;i--)
			str[i]=str[i-1];
		str[i]='.';
		str[l+1]='\0';
		uart0_tx_string(str);
	}
}




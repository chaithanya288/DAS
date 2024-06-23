/*header.h*/

//timer0
extern void delay_ms(unsigned int ms);

//uart0
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern unsigned char uart0_rx(void);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float num);
extern void uart0_tx_itoa(int num);
extern void uart0_tx_ftoa(float num);

//adc
extern void adc_init(void);
extern unsigned int adc_read(int ch_num);

//spi0_driver
extern void spi0_init(void);
extern unsigned char spi0(unsigned char data);
extern unsigned short int mcp3204_adc_read(int ch_num);



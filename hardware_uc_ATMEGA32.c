#define F_CPU 8000000UL 
#define USART_BAUDRATE 9600 // Baud Rate value
#define BAUD_PRESCALE 51//(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
  
#include<avr/io.h>
#include<util/delay.h>
  
 
  
unsigned int datt;
void usart_init();
void usart_putch(unsigned char send);
unsigned int usart_getch();
  
int main()
{
 
    DDRA=0xff;      // LCD_DATA port as output port
    DDRB=0xff;
    DDRC=0xff;
    DDRD=0xFF;
    PORTA=0x00;PORTB=0x00;PORTC=0x00;
while(1)
{
    usart_init();       // initialization of USART
     
    datt=usart_getch(); // Call a function to get data from serial port
//_delay_ms(2009);  
    PORTA=datt;
    PORTB=datt;
    PORTC=datt;
 
    switch(datt)
    {
    case 0xFA:
    PORTD=(1<<PD4);
    break;
 
    case 0xDA:
    PORTD=(1<<PD4);
    break;
 
    case 0xF9:
        PORTD=0x30;
    break;
 
    case 0xD9:
    PORTD=0x30;
    break;
 
    case 0xF8:
    PORTD&=0x0F;
    break;
 
    case 0xD8:
    PORTD&=0x0F;
    break;
 
    case 0xF7:
    PORTC=(1<<PC2);
    _delay_ms(1000);
    PORTC=0x00;
 
    case 0xD7:
    PORTC=(1<<PC2);
    _delay_ms(1000);
    PORTC=0x00;
 
    default:
    break;
}
/*  if(datt==0xFA || datt==0xDA)
    {
    PORTD=(1<<PD4);
    }
if(datt==0xF9 || datt==0xD9)
    {
    PORTD=0x30;
 
    }   
if(datt==0xF8 || datt==0xD8)
    {
    PORTD&=0x0F;
 
    }   
*/
}
    return 1;
}
  
 
  
 
  
void usart_init()
{
    UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
    UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
                                            // Use 8-bit character sizes
  
    UBRRL = BAUD_PRESCALE; 
            // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
    UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
                                    // into the high byte of the UBRR register
}
  
unsigned int usart_getch()
{
    while ((UCSRA & (1 << RXC)) == 0); 
 
    datt=UDR;
        // Do nothing until data has been received and is ready to be read from UDR
    return(datt); // return the byte
}

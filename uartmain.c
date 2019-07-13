
#include <xc.h>
#include <stdio.h>
#include <string.h>
//#define __delay_ms(x) _delay((unsigned long)((x)*(1000000/4000.0)))
#pragma config FOSC = INTOSCIO// Oscillator Selection bits (Internal oscillator, port
//function on RA6, EC used by USB (INTIO))
#pragma CONFIG DEBUG = ON;// Enable Debug Mode
#pragma config WDTEN = OFF // Watchdog Timer Enable bit (WDT disabled (control is
//placed on the SWDTEN bit))
#pragma config PBADEN = OFF // PORTB A/D Enable bit (PORTB&lt;4:0&gt; pins are
// configured as digital I/O on Reset)
#pragma config MCLRE = ON // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin
//disabled)
#pragma config LVP = ON // Single-Supply ICSP Enable bit (Single-Supply ICSP
//disabled)
#define _XTAL_FREQ 1000000 //Crystal Frequency, used in delay
#define speed 50 // Speed Range 10 to 1  10 = lowest , 1 = highest
#define steps 250 // how much step it will take
#define clockwise 0 // clockwise direction macro
#define anti_clockwise 1 // anti clockwise direction macro

#define rs PORTCbits.RC0
#define rw PORTCbits.RC1
#define en PORTDbits.RD3
//LCD Data pins
#define lcdport PORTA

/*Variable declarations*/
int singalFlag = 0;
int directionFlag = 0;
char a;
char first; // Variable for first instruction
int i=0;
unsigned char unlock[15] = "Unlocking... ";
unsigned char lock[15] = "Locking... ";
/*Wifi module function prototype*/
char Read_Data();// read data from screen

/*
 *Motor related function and definition
 */
 
void system_init (void); // This function will initialise the ports.
void full_drive (char direction); // This function will drive the motor in full drive mode
void half_drive (char direction); // This function will drive the motor in full drive mode
void wave_drive (char direction); // This function will drive the motor in full drive mode

/*LCD related functions*/
void lcd_ini();
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void MSDelay(unsigned int itime);
void writeString(unsigned char sendData[]);

void main(void) {
//Configure PORTC for RX/TX
TRISCbits.TRISC6 = 1;// TX PIN
TRISCbits.TRISC7 = 1;// RX PIN
//TRISC = 0b11000000;
//ANSELC =  0b11000000;
ANSELC =  1;
        
// Configure PORTB for motor use
TRISB=0; //set all pins in port b as outputs
PORTB=0x00;

ANSELA = 0x00; // Digital input buffer on PORTA = ON
TRISA = 0x00;
LATA = 0x00;
PORTA = 0x00;
TRISD = 0;
LATD = 0;
PORTD = 0;

OSCCON=0x62; // oscillaton config 8MHz
T2CON=0X01; //Configure timer2 with a prescaler of 4

TMR2=0;
T2CONbits.TMR2ON=1; //Turn on timer2
// Baudrate and UART config
RCSTA1=0x90; //reciever config
SPBRG = 12;// baud rate close to 9600
//RCSTA1 = 0x90;

lcd_ini();
__delay_ms(50);


while(1) //Infinite loop
{
    //Instruction #1
    first=Read_Data();



    if(first==0x65)
    { singalFlag =1;}
    
    if (singalFlag){
        if (directionFlag){
            writeString(unlock);
            for(int i=0;i<steps;i++)
            {
                wave_drive(anti_clockwise);
            }
            directionFlag = 0;
            __delay_ms(500);
            
        }
        else{
            writeString(lock);
            for(int i=0;i<steps;i++)
            {
                wave_drive(clockwise);
            }
            directionFlag = 1;
        }
        /*for (int i= 0 ; i< 10; i++)
            { //LEDS ACTIVIATED HERE
        PORTA =0xFF; // set PORTA = 0x00
        __delay_ms(1000);
        PORTA=0x00;
        __delay_ms(1000);
        }*/
        
        singalFlag =0;
        first==0x00;
    }
}

return;
}
char Read_Data() //Read data from the LCD screen

//{
//while(RCIF==0);
//RCIF=0;
//return(RCREG);
//}
{
while(RCIF==0);       /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);   /*receive data is stored in RCREG register and return */
}
void full_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000011;
        __delay_ms(speed);
        PORTB = 0b00000110;
        __delay_ms(speed);
        PORTB = 0b00001100;
        __delay_ms(speed);
        PORTB = 0b00001001;
        __delay_ms(speed);
        PORTB = 0b00000011;
        __delay_ms(speed);
    }
    if (direction == clockwise){
        PORTB = 0b00001001;
        __delay_ms(speed);
        PORTB = 0b00001100;
        __delay_ms(speed);
        PORTB = 0b00000110;
        __delay_ms(speed);
        PORTB = 0b00000011;
        __delay_ms(speed);
        PORTB = 0b00001001;
        __delay_ms(speed);
    }
        
}
 
/* This method will drive the motor in half-drive mode using direction input */
 
void half_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        __delay_ms(speed);
        PORTB = 0b00000011;
        __delay_ms(speed);
        PORTB = 0b00000010;
        __delay_ms(speed);
        PORTB = 0b00000110;
        __delay_ms(speed);
        PORTB = 0b00000100;
        __delay_ms(speed);
        PORTB = 0b00001100;
        __delay_ms(speed);
        PORTB = 0b00001000;
        __delay_ms(speed);
        PORTB = 0b00001001;
        __delay_ms(speed);
    }
    if (direction == clockwise){
       PORTB = 0b00001001;
       __delay_ms(speed);
       PORTB = 0b00001000;
       __delay_ms(speed);
       PORTB = 0b00001100;
       __delay_ms(speed); 
       PORTB = 0b00000100;
       __delay_ms(speed);
       PORTB = 0b00000110;
       __delay_ms(speed);
       PORTB = 0b00000010;
       __delay_ms(speed);
       PORTB = 0b00000011;
       __delay_ms(speed);
       PORTB = 0b00000001;
       __delay_ms(speed);
    }
}
 
/* This function will drive the the motor in wave drive mode with direction input*/
 
void wave_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        __delay_ms(speed);
        PORTB = 0b00000010;
        __delay_ms(speed);
        PORTB = 0b00000100;
        __delay_ms(speed);
        PORTB = 0b00001000;
        __delay_ms(speed);
    }
     if (direction == clockwise){
        PORTB = 0b00001000;
        __delay_ms(speed);
        PORTB = 0b00000100;
        __delay_ms(speed);
        PORTB = 0b00000010;
        __delay_ms(speed);
        PORTB = 0b00000001;
        __delay_ms(speed);
    }
    
}
// This function writes a string to LCD 1 byte at time
// Pass variable data to this function)
void writeString(unsigned char sendData[])
{
unsigned int i = 0;
while(sendData[i]!='\0')
{
lcddata(sendData[i]); // Call lcddata function to send characters
// one by one from "data" array
i++;
__delay_ms(20);
}
}

void lcd_ini(){
lcdcmd(0x38); // Configure the LCD in 8-bit mode, 2 line and 5x7 font
lcdcmd(0x0C); // Display On and Cursor Off
lcdcmd(0x01); // Clear display screen
lcdcmd(0x06); // Increment cursor
lcdcmd(0x80); // Set cursor position to 1st line, 1st column
}

void lcdcmd(unsigned char cmdout){
lcdport=cmdout; //Send command to lcdport=PORTB
rs=0;
rw=0;
en=1;
__delay_ms(10);
en=0;
}
void lcddata(unsigned char dataout){
lcdport=dataout; //Send data to lcdport=PORTB
rs=1;
rw=0;
en=1;
__delay_ms(10);
en=0;
}

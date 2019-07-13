
/*
 * File:   main.c
 * Author: Sourav Gupta
 * By:- circuitdigest.com
 * Created on May 10, 2018, 1:26 PM
 * This program will drive a servo motor.
 */
 
// PIC16F877A Configuration Bit Settings
 
// 'C' source line config statements
 
// CONFIG
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
//LCD Control pins
 
 
 
#include <xc.h>
#include <stdio.h>
 
/*
 Hardware related definition
 */
 
#define _XTAL_FREQ 1000000 //Crystal Frequency, used in delay
#define speed 10 // Speed Range 10 to 1  10 = lowest , 1 = highest
#define steps 250 // how much step it will take
#define clockwise 0 // clockwise direction macro
#define anti_clockwise 1 // anti clockwise direction macro
 
 
/*
 *Application related function and definition
 */
 
void system_init (void); // This function will initialise the ports.
void full_drive (char direction); // This function will drive the motor in full drive mode
void half_drive (char direction); // This function will drive the motor in full drive mode
void wave_drive (char direction); // This function will drive the motor in full drive mode
 
/*
 * main function starts here
 */
 
 
void main(void)
{
system_init();
while(1){
/* Drive the motor in full drive mode clockwise */
for(int i=0;i<steps;i++)
{
            full_drive(clockwise);
}
        
__delay_ms(1000);
 
/* Drive the motor in wave drive mode anti-clockwise */
for(int i=0;i<steps;i++)
{
            wave_drive(anti_clockwise);
            //full_drive(anti_clockwise);
}
__delay_ms(1000);
}
}
 
/*System Initialising function to set the pin direction Input or Output*/
 
void system_init (void){
    TRISB = 0x00;     // PORT B as output port
    PORTB = 0x0F;
}
 
/*This will drive the motor in full drive mode depending on the direction*/
 
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
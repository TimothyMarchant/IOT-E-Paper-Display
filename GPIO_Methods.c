/* 
 * File:   GPIO_Methods.c
 * Author: Timothy Marchant
 *
 * Created on March 6, 2025, 6:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
//We are only working with Port A.
#define PA PORT_REGS->GROUP[0]
#define disable 0xFF
/*
 * 
 */
//allow pins to act as IO pins
void Init_IO(void){
    for (unsigned char i=0;i<32;i++){
    PA.PORT_PINCFG[i]=0x02;
    }
}
void configpin(const volatile unsigned int pin,const unsigned char type){
    if (type){
        PA.PORT_DIRCLR|=pin;
    }
    else {
        PA.PORT_DIRSET|=pin;
    }
}
void pinwrite(const volatile unsigned int pin,const unsigned char level){
    if (level){
        PA.PORT_OUTSET|=pin;
    }
    else {
        PA.PORT_OUTCLR|=pin;
    }
}
//read input
unsigned char pinread(const volatile unsigned int pin,const unsigned char pinnum){
    return (PA.PORT_IN&pin)>>pinnum;
}
void pinmuxconfig(const unsigned char pinnum,const unsigned char group){
    unsigned char n=pinnum/2;
    //upper bits are odd pin numbers
    unsigned char isUpper=pinnum%2;
    
    //create a bit mask.  If upper shift the bits 4 places to the left.  Otherwise just write to the register.
    unsigned char mask=group;
    if (isUpper){
        mask=((mask)<<4);
    }
    //enable peripheral functionality
    
    PA.PORT_PINCFG[pinnum]|=0x01;
    PA.PORT_PMUX[n]|=mask;
    
}
void pinmuxconfigdisable(const unsigned char pinnum){
    unsigned char n=pinnum/2;
    //upper bits are odd pin numbers
    unsigned char isUpper=pinnum%2;
    //create a bit mask.  If upper shift the bits 4 places to the left.  Otherwise just write to the register.
    unsigned char mask=0x02;
    if (isUpper){
        mask=((mask)<<4);
    }
    PA.PORT_PINCFG[pinnum]=0x02;
    PA.PORT_PMUX[n]|=mask;
}
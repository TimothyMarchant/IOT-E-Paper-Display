#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#define TC0 TC0_REGS
#define enablebit 0x02
const unsigned int bitmasks[10]={};
//we only will increment the timer
void Init_TC0(const unsigned char prescaler,const unsigned char runinstandby){
    //enable timer0
    
    GCLK_REGS->GCLK_PCHCTRL[14]|=0b01000000;
    TC0->COUNT8.TC_CTRLBCLR=0x01;
    
    TC0->COUNT8.TC_CTRLA|=0x104;
}
void Start_TC0(void){
    TC0->COUNT8.TC_CTRLA|=enablebit;
}
void Stop_TC0(void){
    TC0->COUNT8.TC_CTRLA&=!(enablebit);
}
void EnableinterruptOVF(void){
    TC0->COUNT8.TC_INTENSET|=0x01;
}
void DisableinterruptOVF(void){
    TC0->COUNT8.TC_INTENCLR|=0x01;
}
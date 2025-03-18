#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "TC1_Methods.h"
#include "Sleep.h"

#ifndef TC1
#define TC1 TC1_REGS
#endif
static volatile unsigned int delaycount=0;
static volatile unsigned int lastcount=0;
void TC1_Callback_Delay(void){
    delaycount++;
    if (delaycount>=lastcount){
        TC1->COUNT8.TC_INTENCLR=0x01;
        Stop_TC1();
    }
    TC1->COUNT8.TC_COUNT=6;
    TC1->COUNT8.TC_INTFLAG=0x01;
}
void delay(unsigned int ms){
    lastcount=ms;
    EnableinterruptOVF_TC1();
    Start_TC1();
    
    while (delaycount<lastcount){
        SLEEP;
    }
    delaycount=0;
}
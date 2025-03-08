#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "GPIO.h"
#include "CircularQueue.h"
#define CTRLBmask 0x00030000
#define CTRLAmask 0x40100004
//value needed for 115200 baud rate
#define requiredbaudvalue 35337
#define UART SERCOM1_REGS->USART_INT
void InitUART(unsigned short baud){
    //activate peripherial
    GCLK_REGS->GCLK_PCHCTRL[12]=0x40;
    UART.SERCOM_BAUD=requiredbaudvalue;
    UART.SERCOM_CTRLA=CTRLAmask;
    UART.SERCOM_CTRLB=CTRLBmask;
    //needs to be higher priority than other interrupts
    NVIC_SetPriority(SERCOM1_0_IRQn,2);
}
//turn on sercom1
void StartUART(void){
    UART.SERCOM_CTRLA|=0x02;
}
//turn off sercom1
void EndUART(void){
    UART.SERCOM_CTRLA&=~(0x02);
}
void Enableinterrupt(void){
    UART.SERCOM_INTENSET|=0x06;
    NVIC_EnableIRQ(SERCOM1_0_IRQn);
}
void Disableinterrupt(void){
    UART.SERCOM_INTENCLR|=0x06;
    NVIC_DisableIRQ(SERCOM1_0_IRQn);
}
void BeginTransmission(unsigned short length,unsigned char* packet){
    //pins are already configured we simply just need to figure out where to put or interrupt ISR
}
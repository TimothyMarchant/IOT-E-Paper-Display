#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "GPIO.h"
#include "CircularQueue.h"
#define CTRLBmask 0x00030000
#define CTRLAmask 0x40100084
//value needed for 115200 baud rate
#define requiredbaudvalue 35337
#define UART SERCOM1_REGS->USART_INT
#define RXC_Flag 0x04
#define TXC_Flag 0x02
#define GCLKPERDefaultMask 0x40
//enable specific interrupts.  These are the ones we want to activate normally
#define defaultinterrupts 0x06 //RXC and TXC bits
#define enablebit 0x02
unsigned char datatoread[50] = {};
unsigned char* transmissionpacket;
unsigned short packetlengthT = 0;
unsigned short packetlengthR = 0;
//transmission pointer
volatile unsigned short packetpointerT = 0;
//receiving pointer
volatile unsigned short packetpointerR = 0;

void __attribute__((interrupt)) SERCOM1_1_Handler(void) {
    if ((UART.SERCOM_INTFLAG & RXC_Flag)) {
        if (packetpointerR == packetlengthR) {
            UART.SERCOM_INTENCLR = RXC_Flag;
            packetpointerR = 0;

        } else {
            while (!(UART.SERCOM_INTFLAG&0x01));
            datatoread[packetpointerR] = UART.SERCOM_DATA;
            packetpointerR++;
        }
    }
    if (UART.SERCOM_INTFLAG & TXC_Flag) {
        if (packetpointerT == packetlengthT) {
            UART.SERCOM_INTENCLR = TXC_Flag;
            packetpointerT = 0;

        } else {
            while (!(UART.SERCOM_INTFLAG&0x01));
            UART.SERCOM_DATA = *(transmissionpacket + packetpointerT);
            packetpointerT++;
        }
    }
}

void InitUART(void) {
    //activate peripherial
    GCLK_REGS->GCLK_PCHCTRL[12] = GCLKPERDefaultMask;
    pinmuxconfig(0,GROUPD);
    pinmuxconfig(1,GROUPD);
    UART.SERCOM_BAUD = requiredbaudvalue;
    UART.SERCOM_CTRLA = CTRLAmask;
    UART.SERCOM_CTRLB = CTRLBmask;
    //needs to be higher priority than other interrupts
    NVIC_SetPriority(SERCOM1_1_IRQn, 2);
}
//turn on sercom1

void StartUART(void) {
    UART.SERCOM_CTRLA |= enablebit;
}
//turn off sercom1

void EndUART(void) {
    UART.SERCOM_CTRLA &= ~(enablebit);
}

void Enableinterrupt(void) {
    UART.SERCOM_INTENSET = defaultinterrupts;
    NVIC_EnableIRQ(SERCOM1_1_IRQn);
}

void Disableinterrupt(void) {
    UART.SERCOM_INTENCLR = defaultinterrupts;
    NVIC_DisableIRQ(SERCOM1_1_IRQn);
}

void BeginTransmission(unsigned short Tlength, unsigned char* packet, unsigned short Rlength) {
    transmissionpacket = packet;
    packetlengthT = Tlength;
    packetlengthR = Rlength;
    Enableinterrupt();
    if (Rlength==0){
        UART.SERCOM_INTENCLR=0x04;
    }
    UART.SERCOM_DATA=*packet;
    packetpointerT++;
    
    //pins are already configured we simply just need to figure out where to put or interrupt ISR
}
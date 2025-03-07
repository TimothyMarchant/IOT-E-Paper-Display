//This is not for general use, we are only transmitting
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "GPIO.h"
#include "CircularQueue.h"
//SERCOM0 SPIM
#define SPI SERCOM0_REGS->SPIM
#define DataREG SPI.SERCOM_DATA
//for enabling peripherals
#define GCLKSERCOM0 GCLK_REGS->GCLK_PCHCTRL[11]
#define CTRLBRegisterSettings 0x00020000
#define Transmit_Complete 0x02
#define DRE 0x01
#define GCLKPERDefaultMask 0x40
#define CTRLARegisterMask 0x000000A0
#define Success 1
#define Failure 0
void __attribute__((interrupt)) SERCOM0_0_Handler(void){
    if (SPI.SERCOM_INTFLAG&Transmit_Complete){
        //wait then send new data
        while (!(SPI.SERCOM_INTFLAG&DRE));
        DataREG=Dequeue();
        SPI.SERCOM_INTFLAG&=Transmit_Complete;
    }
}
void InitSPI(const unsigned char baudrate){
    //using SSOP24 package
    pinmuxconfig(2,GROUPD); //pad[2] PA2 pin 7
    pinmuxconfig(3,GROUPD); //pad[3] PA3 pin 8
    pinmuxconfig(4,GROUPD); //pad[0] PA4 pin 9
    pinmuxconfig(5,GROUPD); //pad[1] PA5 pin 10
    //enable SERCOM0
    GCLKSERCOM0|=GCLKPERDefaultMask;
    SPI.SERCOM_BAUD=baudrate;
    SPI.SERCOM_CTRLB=CTRLBRegisterSettings;
    SPI.SERCOM_INTENSET|=Transmit_Complete;
    SPI.SERCOM_CTRLA=CTRLARegisterMask;
    NVIC_SetPriority(SERCOM0_0_IRQn,3);
    NVIC_EnableIRQ(SERCOM0_0_IRQn);
}
void EnableSPI(void){
    SPI.SERCOM_CTRLA|=0x02;
}
void DisableSPI(void){
    SPI.SERCOM_CTRLA&=~(0x02);
}

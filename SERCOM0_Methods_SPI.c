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
#define CTRLBRegisterSettings 0x00022000
#define Transmit_Complete 0x02
#define DRE 0x01
#define GCLKPERDefaultMask 0x40
#define CTRLARegisterMask 0x1030008C
#define Success 1
#define Failure 0
volatile unsigned char databuffer=0x00;
volatile unsigned short packetlength=0;
volatile unsigned short packetpointer=0;
volatile unsigned char* Packet;
volatile unsigned char QueueMode=0;
volatile unsigned int currentCS=0;
static inline void Disableinterrupts(void);
void SPI_Queue_Callback(void);
volatile void SPI_End(const volatile unsigned char pin);
volatile unsigned char cansend=0;
void __attribute__((interrupt)) SERCOM0_0_Handler(void){
    if (SPI.SERCOM_INTFLAG&DRE){
            //clears interrupt flag
        DataREG|=(*(Packet+packetpointer));
        packetpointer++;
        
    }
    //end SPI
    if (packetpointer==packetlength){
        packetpointer=0;
        packetlength=0;
        //clear interrupt enable bit
        SPI.SERCOM_INTENCLR|=DRE;
        //blocking wait for last byte; should be very short
        while (!(SPI.SERCOM_INTFLAG&DRE));
        SPI_End(currentCS);
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
    
    SPI.SERCOM_CTRLA=CTRLARegisterMask;
    NVIC_SetPriority(SERCOM0_0_IRQn,3);
    
}
void EnableSPI(void){
    SPI.SERCOM_CTRLA|=0x02;
}
void DisableSPI(void){
    SPI.SERCOM_CTRLA&=~(0x02);
}
static inline void Enableinterrupts(void){
    SPI.SERCOM_INTENSET|=DRE;
    NVIC_EnableIRQ(SERCOM0_0_IRQn);
}
static inline void Disableinterrupts(void){
    SPI.SERCOM_INTENCLR|=DRE;
    NVIC_DisableIRQ(SERCOM0_0_IRQn);
}
volatile void SPI_Start(const volatile unsigned char pin,const volatile unsigned short length,unsigned char* givenPacket){
    pinwrite(pin,LOW);
    currentCS=pin;
    packetlength=length;
    Packet=givenPacket;
    Enableinterrupts();
}
void SPI_Start_Queue_Packet(const volatile unsigned pin,volatile Queue* queue){
    currentCS=pin;
    QueueMode=1;
}
//for packets of unknown length, or sending packets of very small length.
void SPI_Start_Unknown_Packet(const volatile unsigned char pin){
    currentCS=pin;
    pinwrite(pin,LOW);
    
}
volatile void SPI_End(const volatile unsigned char pin){
    Disableinterrupts();
    currentCS=0x00;
    pinwrite(pin,HIGH);
}
//this write method uses a blocking loop until we can write again.  For testing purposes mostly or small amount of writes
void SPI_Write_Blocking(unsigned char data){
    while (!SPI.SERCOM_INTFLAG&DRE);
    SPI.SERCOM_DATA=data;
}
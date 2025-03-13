#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
#include "definitions.h"
#include "SPI_Methods.h"
#include "GPIO.h"
#include "Timer0_Methods.h"
#include "UART_Methods.h"
#include "Delay.h"
#define UART SERCOM1_REGS->USART_INT
#define RXC 0x04
//outputs
#define DC PORT_PA15
#define RES PORT_PA08
//input
#define Busy PORT_PA14
#define CS PORT_PA01
//I took this from my previous working of this screen
#define Softreset 0x12
#define TemperatureREG 0x1A
#define PanelSetting 0x22
#define PanelSettingData 0xD7
#define DTM1REG 0x24
#define DTM2REG 0x26
#define UpdateDisplay 0x20
//image size in bytes
unsigned short imagelength=5000;
unsigned short currentcount=0;
unsigned char currentpacketlengthptr=0;
//TCP packet lengths we know in advanced what it should be doing
unsigned short packetlengths[4]={1460,1460,1460,620};
unsigned short packetlengthcount=0;
unsigned char isImagedata=0;
//this is to write image data
void EpaperReadWrite_UART_Callback(unsigned char data){
    if (isImagedata){
        //for now we will use the blocking write until I bother to write a better solution
        SPI_Write_Blocking(data);
        packetlengthcount++;
        if (packetlengthcount==1460){
            packetlengthcount=0;
            
        }
        currentcount++;
        //disable interrupt and stop transmission
        if (currentcount==imagelength){
            UART.SERCOM_INTENCLR=RXC;
            SPI_End(CS);
        }
    }
    if (!isImagedata){
        //this is how the ESP sends data back something, length and finally : afterwards is all data.
        if (data==':'){
            isImagedata=1;
        }
    }
}
//only called once
void Init_Epaper_IO(void){
    configpin(DC,Output);
    configpin(RES,Input);
    configpin(CS,Output);
    configpin(Busy,Input);
    pinwrite(CS,HIGH);
    pinwrite(DC,HIGH);
    //pinwrite(RES,LOW);
}
//Pervaise Displays wants you to stop powering the screen once you are done writing to it, so this would be called more than once.
//However for this project we will skip that for now.
void sendcommand(unsigned char CMD){
    pinwrite(DC,LOW);
    SPI_Write_Blocking(CMD);
    pinwrite(DC,HIGH);
}
void Init_Screen(void){
    delay(5);
    configpin(RES,Output);
    pinwrite(RES,HIGH);
    delay(10);
    pinwrite(RES,LOW);
    delay(10);
    pinwrite(RES,HIGH);
    delay(20);
    //wait for busy to go LOW
    while (pinread(Busy,14)>=1);
    pinwrite(DC,LOW);
    SPI_Start_Unknown_Packet(CS);
    SPI_Write_Blocking(Softreset);
    pinwrite(DC,HIGH);
    SPI_End(CS);
    while (pinread(Busy,14)>=1);
    
    
    //pinwrite(DC,LOW);
    SPI_Start_Unknown_Packet(CS);
    sendcommand(TemperatureREG);
    //temperature
    SPI_Write_Blocking(0x14);
    //SPI_End(CS);
    //pinwrite(DC,LOW);
    //SPI_Start_Unknown_Packet(CS);
    sendcommand(PanelSetting);
    SPI_Write_Blocking(PanelSettingData);
    SPI_End(CS);
}
//testing purposes
void testsendbuffer(void){
    //pinwrite(DC,LOW);
    SPI_Start_Unknown_Packet(CS);
    sendcommand(DTM1REG);
    for (unsigned short i=0;i<5000;i++){
        SPI_Write_Blocking(0xFF);
    }
    SPI_End(CS);
    //pinwrite(DC,LOW);
    SPI_Start_Unknown_Packet(CS);
    sendcommand(DTM2REG);
    for (unsigned short i=0;i<5000;i++){
        SPI_Write_Blocking(0x00);
    }
    SPI_End(CS);
    //update display
    while(pinread(Busy,14));
    //pinwrite(DC,LOW);
    SPI_Start_Unknown_Packet(CS);
    sendcommand(0x20);
    SPI_End(CS);
    while(pinread(Busy,14));
}
void Preparesendforqueue(void){
    
}
//send necessary data to update screen
void updatescreen(void){
    Init_Screen();
    testsendbuffer();
}
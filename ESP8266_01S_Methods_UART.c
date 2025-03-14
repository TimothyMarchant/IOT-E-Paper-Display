#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularQueue.h"
#include "definitions.h"
#include "SPI_Methods.h"
#include "GPIO.h"
#include "Timer0_Methods.h"
#include "UART_Methods.h"
//nothing should change for this
#define ATString "AT\r\n"
const unsigned char* AT="AT\r\n";
//disable echo
const unsigned char* const ATE0="ATE0\r\n";
//sleep for 1 second default sleep string
const unsigned char* const SLEEP="AT+GSLP=1000\r\n";
//These strings would be needed to connect to a network, but this will be done off this microcontroller for privacy (don't want to expose my network)
//default WiFi mode; set to station mode
//const char* const ATCWMODE_DEF="AT+CWMODE_DEF=1";
//connect to this network with the correct SSID and password; for reference only
//const char* const ATCWJAP_DEF+"AT+CWJAP_DEF=\"NAME\",\"PASSWORD\"";
//get current status
const char* const ATCIPSTATUS="AT+CIPSTATUS\r\n";
//start the TCP connection
#define TCPSTART "AT+CIPSTART=\"TCP\",\"10.0.0.82\",7777\r\n"
#define TCPSENDSTART "AT+CIPSEND=1\r\n" //send this with the length of the message.
//AT response array.
unsigned char ATResponse[100]={};
//ensure the device is working by using the AT command
void Test(void){
    BeginTransmission(strlen(ATString),ATString,6,ATResponse,0);
}
void TestSend(void){
    BeginTransmission(strlen(TCPSTART),TCPSTART,6,ATResponse,0);
    while (isBusy());
    BeginTransmission(strlen(TCPSENDSTART),TCPSENDSTART,1,ATResponse,0);
    while (isBusy());
    //use callback function
    BeginTransmission(1,0x00,1,ATResponse,1);
    while (isBusy());
}
/*
//listen for a packet
void Listen(unsigned short length){
    
}
 * */
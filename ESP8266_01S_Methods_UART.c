#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
#include "definitions.h"
#include "SPI_Methods.h"
#include "GPIO.h"
#include "Timer0_Methods.h"
#include "UART_Methods.h"
//nothing should change for this
const char* const AT="AT\r\n";
const char* const ATE0="ATE0\r\n";
//These strings would be needed to connect to a network, but this will be done off this microcontroller for privacy (don't want to expose my network)
//default WiFi mode; set to station mode
//const char* const ATCWMODE_DEF="AT+CWMODE_DEF=1";
//connect to this network with the correct SSID and password; for reference only
//const char* const ATCWJAP_DEF+"AT+CWJAP_DEF=\"NAME\",\"PASSWORD\"";
//get current status
const char* const ATCIPSTATUS="AT+CIPSTATUS";
//start the TCP connection
const char* const TCPSTART="AT+CIPSTART=\"TCP\",\"IP\",PORTNUM";
char* const TCPSENDSTART="AT+CIPSEND="; //send this with the length of the message.
//ensure the device is working by using the AT command
void Test(void){
    
}
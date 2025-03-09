#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
#include "definitions.h"
#include "SPI_Methods.h"
#include "GPIO.h"
#include "Timer0_Methods.h"
#include "UART_Methods.h"
//only called once
void Init_Epaper_IO(void){
    
}
//Pervaise Displays wants you to stop powering the screen once you are done writing to it, so this would be called more than once.
//However for this project we will skip that for now.
void Init_Screen(void){
    
}
//testing purposes
void testsendbuffer(void){
    
}
void Preparesendforqueue(void){
    
}
//send update command
void updatescreen(void){
    
}
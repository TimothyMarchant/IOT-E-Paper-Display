#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "Timer0_Methods.h"
/*unsigned int count=0;
unsigned int lastcount=0;
void TC1_Callback_Delay(void){
    return;
}*/
//just needs to delay around the time given.  This isn't exact, I just need it to wait close to the given time.
volatile void delay(unsigned int ms){
    for (unsigned int i = 0; i < ms; i++) {
        for (unsigned int i = 0; i < 0x799; i++) {
            __NOP();
        }
    }
}
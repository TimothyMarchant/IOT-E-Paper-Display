
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
//SERCOM0 SPIM
#define SPI SERCOM0_REGS->SPIM
//for enabling peripherals
#define GCLKSERCOM0 GCLK_REGS->GCLK_PCHCTRL[11]

#define GCLKPERDefaultMask 0x40
void InitSPI(unsigned char baudrate){
    GCLKSERCOM0|=GCLKPERDefaultMask;
    SPI.SERCOM_BAUD=baudrate;
}

#include "Sleep.h"
#include "EIC_Methods.h"
#include "SPI_Methods.h"
#include "TC1_Methods.h"
#include "UART_Methods.h"
#include "Timer0_Methods.h"
void EnterDeepSleep(void){
    ConfigSleep(STANDBY);
    //I just noticed the inconsistency of my naming scheme
    Enable_EIC();
    DisableSPI();
    EndUART();
}
void ExitDeepSleep(void){
    ConfigSleep(IDLE);
    //don't want to be interrupted with push buttons after pressing one
    Disable_EIC();
    EnableSPI();
    StartUART();
}

#include "Definitions.h"
#include "EICFlagbits.h"
void TC0_Callback(void);
void TC1_Callback_Delay(void);
void __attribute__((interrupt))TC0_Handler(void){
    TC0_Callback();
}
void __attribute__((interrupt))TC1_Handler(void){
    TC1_Callback_Delay();
}
void __attribute__((interrupt)) EIC_EXTINT_0_Handler(void){
    EICClearFlag(EIC0);
}
void __attribute__((interrupt)) EIC_EXTINT_1_Handler(void){
    EICClearFlag(EIC1);
}
void __attribute__((interrupt)) EIC_EXTINT_2_Handler(void){
    EICClearFlag(EIC2);
}
void __attribute__((interrupt)) EIC_EXTINT_3_Handler(void){
    EICClearFlag(EIC3);
}
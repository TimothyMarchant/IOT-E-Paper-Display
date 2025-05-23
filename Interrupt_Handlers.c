#include "Definitions.h"
#include "EICFlagbits.h"
void TC0_Callback(void);
void TC1_Callback_Delay(void);
void EIC0_Callback(void);
void EIC1_Callback(void);
void __attribute__((interrupt))TC0_Handler(void){
    TC0_Callback();
}
void __attribute__((interrupt))TC1_Handler(void){
    TC1_Callback_Delay();
}
void __attribute__((interrupt)) EIC_EXTINT_0_Handler(void){
    EIC0_Callback();
    EICClearFlag(EIC0);
}
void __attribute__((interrupt)) EIC_EXTINT_1_Handler(void){
    EIC1_Callback();
    EICClearFlag(EIC1);
}
void __attribute__((interrupt)) EIC_EXTINT_2_Handler(void){
    EICClearFlag(EIC2);
}
void __attribute__((interrupt)) EIC_EXTINT_3_Handler(void){
    EICClearFlag(EIC3);
}
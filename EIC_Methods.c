#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "EICFlagbits.h"
#include "EIC_Configbits.h"
#include "definitions.h"
#define EIC EIC_REGS
#define EICCTRLAmask 0x10
#define EnableDebounce 0x0F
#define Prescalersettings 0x000100012

void Init_EIC(const unsigned char EICINTEN,const unsigned int configvalue){
    EIC->EIC_CTRLA=EICCTRLAmask;
    EIC->EIC_DEBOUNCEN=EnableDebounce;
    EIC->EIC_DPRESCALER=Prescalersettings;
    EIC->EIC_INTENSET=EICINTEN;
    NVIC_SetPriority(EIC_EXTINT_0_IRQn,3);
    NVIC_SetPriority(EIC_EXTINT_0_IRQn,3);
    NVIC_SetPriority(EIC_EXTINT_0_IRQn,3);
    NVIC_SetPriority(EIC_EXTINT_0_IRQn,3);
}
void Set_EIC0(const unsigned char Edge){
    NVIC_EnableIRQ(EIC_EXTINT_0_IRQn);
}
void Set_EIC1(const unsigned char Edge){
    NVIC_EnableIRQ(EIC_EXTINT_1_IRQn);
}
void Set_EIC2(const unsigned char Edge){
    NVIC_EnableIRQ(EIC_EXTINT_2_IRQn);
}
void Set_EIC3(const unsigned char Edge){
    NVIC_EnableIRQ(EIC_EXTINT_3_IRQn);
}
void Clear_EIC0(void){
    NVIC_DisableIRQ(EIC_EXTINT_0_IRQn);
}
void Clear_EIC1(void){
    NVIC_DisableIRQ(EIC_EXTINT_1_IRQn);
}
void Clear_EIC2(void){
    NVIC_DisableIRQ(EIC_EXTINT_2_IRQn);
}
void Clear_EIC3(void){
    NVIC_DisableIRQ(EIC_EXTINT_3_IRQn);
}
void Enable_EIC(void){
    EIC->EIC_CTRLA|=0x02;
}
void Disable_EIC(void){
    EIC->EIC_CTRLA&=~(0x02);
}
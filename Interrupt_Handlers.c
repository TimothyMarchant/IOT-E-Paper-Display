void TC0_Callback(void);
#define TC0 TC0_REGS
void __attribute__((interrupt))TC0_Handler(void){
    TC0_Callback();
}

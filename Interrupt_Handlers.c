void TC0_Callback(void);
void TC1_Callback_Delay(void);
void __attribute__((interrupt))TC0_Handler(void){
    TC0_Callback();
}
void __attribute__((interrupt))TC1_Handler(void){
    TC1_Callback_Delay();
}

#ifndef UART_Methods_h
#define UART_Methods_h
void InitUART(void);
void StartUART(void);
void EndUART(void);
void Enableinterrupt(void);
void Disableinterrupt(void);
void BeginTransmission(unsigned short Tlength,unsigned char* packet,unsigned short Rlength);
#endif
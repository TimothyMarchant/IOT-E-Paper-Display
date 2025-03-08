#ifndef UART_Methods_h
#define UART_Methods_h
void InitUART(unsigned short baud);
void StartUART(void);
void EndUART(void);
void Enableinterrupt(void);
void Disableinterrupt(void);
void BeginTransmission(unsigned short length,unsigned char* packet);
#endif
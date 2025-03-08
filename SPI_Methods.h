#ifndef SPI_Methods_h
#define SPI_Methods_h
void InitSPI(const unsigned char baudrate);
void EnableSPI(void);
void DisableSPI(void);
void SPI_Start(const volatile unsigned char pin,const volatile unsigned short length,unsigned char* givenPacket);
void SPI_Start_Queue_Packet(const volatile unsigned pin,volatile Queue* queue);
void SPI_Start_Unknown_Packet(const volatile unsigned char pin);
void SPI_Start_Repeated(const volatile unsigned char pin, const volatile unsigned short length, unsigned char data);
volatile void SPI_End(const volatile unsigned char pin);
void SPI_Write_Blocking(unsigned char data);
#endif
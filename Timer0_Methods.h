#ifndef Timer0_Methods_h
#define Timer0_Methods_h
void Init_TC0(const volatile unsigned char prescaler,const volatile unsigned char runinstandby);
void Start_TC0(void);
void Stop_TC0(void);
void EnableinterruptOVF(void);
void DisableinterruptOVF(void);
#endif

/* 
 * File:   UART1.h
 * Author: mane2
 *
 * Created on May 16, 2021, 8:55 PM
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif
//	Function Prototypes

#define CTS _RF8//_LATF8
#define RTS _RF13//_LATF13
#define TRTS TRISFbits.TRISF13 //for RTS pin

#define CLK 120000000
#define BAUDRATE 9600//115200
#define RATE 95//129//8//(CLK/8/BAUDRATE)-1 //129
#define U_ENABLE 0x8008
#define U_TX 0x0400

#define BACKSPACE 0x8
#define Clrscr() putsU1("\x1b[2J");
#define Home() putsU1("\x1b[1;1H");
#define pcr() putU1('\r'); putU1('\n')
#define BUF_SIZE 128
    
//#pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow multiple reconfigurations) //include this line in main!

void putU1(char c);
void putsU1(char *s);
char getU1(void);
void getsnU1(char* s, int len);
void InitU1(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */


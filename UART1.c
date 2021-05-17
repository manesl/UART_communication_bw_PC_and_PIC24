/*
 * File:   UART1.c
 * Author: mane2
 *
 * Created on May 16, 2021, 8:57 PM
 */

/******************************************************************************
 * Software License Agreement
 *
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED ìAS ISî WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/


#if defined(__PIC24E__) 
#include <p24Exxxx.h>
#include "UART1.h"

#elif defined (__PIC24F__) 
#include <p24Fxxxx.h>

#elif defined(__PIC24H__)
#include <p24Hxxxx.h>

#elif defined(__dsPIC30F__)
#include <p30Fxxxx.h>

#elif defined (__dsPIC33E__) 
#include <p33Exxxx.h>

#elif defined(__dsPIC33F__) 
#include <p33Fxxxx.h>

#endif


void putU1(char c){
    while(CTS); //when high wait for PC to complete its other task then pay attention to PIC24
    while(U1STAbits.UTXBF); //assume you call this function twice back to back, what if the previous write was not completed yet
    //so wait when the TXBUF is empty
    U1TXREG = c;
}

void putsU1(char *s){
    int i = 0;
    while(s[i]){
        putU1(s[i]);
        i++;
    }
    putU1('\r');
    putU1('\n');
}

char getU1(void){
    RTS = 0;
    while(!U1STAbits.URXDA); //wait until the receive buffer is full
    RTS = 1;
    return U1RXREG;
}

void getsnU1(char* s, int len){
    char *p = s;
    do{
        *s = getU1();
        putU1(*s);
        if((*s==BACKSPACE) && (s>p)){
            putU1(' ');//overwrite the last char
            putU1(BACKSPACE);
            len++;
            s--;
            continue;
        }
        if(*s == '\n') continue;
        if(*s == '\r') break;
        s++;
        len--;
    } while(len>1);
    *s = '\0';
    //return p;
}

void InitU1(void){
    __builtin_write_OSCCONL(OSCCON & ~(1<<6));
    _U1RXR=67;//RX
    _RP65R=1;//TX
    __builtin_write_OSCCONL(OSCCON | (1<<6));
    TRISDbits.TRISD3 = 1; //input
    TRISDbits.TRISD1 = 0; //output
    ANSELD = 0x0000;
    RTS = 1;
    TRISFbits.TRISF13 = 0;
    TRISFbits.TRISF8 = 1;
    //Baud rate
    U1BRG = RATE;
    //interrupt enabling
//    IFS0bits.U1TXIF = 0;
//    IFS0bits.U1RXIF = 0;
//    IEC0bits.U1TXIE = 1;
//    IEC0bits.U1RXIE = 1;
    U1MODE = U_ENABLE;
    U1STA = U_TX;
}




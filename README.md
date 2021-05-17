# UART_with_Interrupts
This lab is about setting up UART communication between the PC terminal (Putty) and PIC24. The input to the PIC24 is via keyboard and the output of the PIC24 goes to the terminal.

UART Data format: 8 bits data, no parity, 1 stop bit and 9600 bps.

There are two separate libraries:
UART.h and UART.c does not have interrupt functionality, they rather poll the U1STA register values to see if transmit buffer is empty or certain data has been received by the UART.

UARTInt.h and UARTInt.c support the interrupt functionality and uses the Interrupts to synchronize the transmission and reception. 

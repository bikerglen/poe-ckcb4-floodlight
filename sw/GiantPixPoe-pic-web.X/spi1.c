#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "spi1.h"

// e48_Csb on RB4
// SCK on SCK1/RC3
// MISO on SDI1/RC4
// MOSI on SDO1/RC5

void spi1_Init (void)
{
    SSP1CON1bits.SSPEN1 = 0;

    TRISBbits.TRISB4 = 0; // e48 csb - output
    LATBbits.LATB4   = 1; // e48 csb - set to high / not asserted
    TRISCbits.TRISC3 = 0; // sck     - output
    TRISCbits.TRISC4 = 1; // miso    - input
    TRISCbits.TRISC5 = 0; // mosi    - output

    SSP1STATbits.CKE = 1;
    SSP1STATbits.SMP = 1;    
    SSP1CON1 = 0x02;
    SSP1CON2 = 0x00;
    SSP1CON1bits.SSPEN = 1;
}

uint8_t spi1_ExchangeByte (uint8_t data )
{
#define _XTAL_FREQ 25000000
    
    SSP1BUF = data;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    return SSP1BUF;
}

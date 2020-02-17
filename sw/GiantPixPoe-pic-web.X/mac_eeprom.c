#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "spi1.h"
#include "mac_eeprom.h"

// e48_Csb on RB4
// SCK on SCK1/RC3
// MISO on SDI1/RC4
// MOSI on SDO1/RC5

void e48_read_mac(uint8_t *mac)
{
    uint8_t i;
    
    // set cs low
    LATBbits.LATB4   = 0;
    
    spi1_ExchangeByte (MAC_EE_READ);
    spi1_ExchangeByte (MAC_ADDR_48);
    
    for (i = 0; i < 6; i++) {
        mac[i] = spi1_ExchangeByte (0x00);
    }
    
    // set high low
    LATBbits.LATB4   = 1;
    
    // printf("macAddr:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X \r\n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}


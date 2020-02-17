#include <stdint.h>
#include "udp_rx_artnet.h"
#include "ws2812b.h"
#include "mcc_generated_files/TCPIPLibrary/udpv4.h"
#include "mcc_generated_files/TCPIPLibrary/tcpip_config.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"


void UdpRxArtNetInit (void)
{
    // nothing to do here
}


void UdpRxArtNetRecv (int16_t length)
{
    uint8_t i;
    uint8_t leds;
    uint8_t r, g, b;
    uint8_t giantR, giantG, giantB;
    // uint16_t tmp;
    
    if (length >= 18) {
        for (i = 0; i < 18; i++) {
            UDP_Read8 ();
        }
        
        length = length - 18;
        if (length > NUM_CHANS) {
            length = NUM_CHANS;
        }
        leds = length / 3;
        length = 3 * leds;
        
        for (i = 0; i < length; i+=3) {
            r = UDP_Read8 ();
            g = UDP_Read8 ();
            b = UDP_Read8 ();
            ledData[i+0] = gamma8[g];
            ledData[i+1] = gamma8[r];
            ledData[i+2] = gamma8[b];
            
            if (i == 0) {
                giantR = r;
                giantG = g;
                giantB = b;
            }
            
        }
        
        for (; i < 150; i++) {
            ledData[i] = 0;
        }
        
        WS2812b_Write ();
        
        INTERRUPT_GlobalInterruptDisable();
        INTERRUPT_PeripheralInterruptDisable();
        
        // enable 9 bit mode
        TXSTA1bits.TX9 = 1;
        TXSTA1bits.TX9D = 1;
        
        // send break
        TRISCbits.TRISC6 = 0;
        LATCbits.LATC6 = 0;
        RCSTA1bits.SPEN = 0;

        __delay_us (88);

    	// 88 / .125 = 704
        // for (tmp = 0; tmp < 704; tmp++) {
        // }
                
        // send mark after break
        RCSTA1bits.SPEN = 1;

        __delay_us (8);
        
        // 8 / .125 = 64
        // for (tmp = 0; tmp < 64; tmp++) {
        // }
        
        // send 0x00 followed by three art-net data bytes
        EUSART1_Write (0x00);
        EUSART1_Write (giantR);
        EUSART1_Write (giantG);
        EUSART1_Write (giantB);
        
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();

        // toggle art-net status led
        LATEbits.LATE4 = ~LATEbits.LATE4;
    }
}

/* 
 * File:   ws2812b.h
 * Author: glen
 *
 * Created on November 23, 2019, 2:49 PM
 */

#ifndef WS2812B_H
#define	WS2812B_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NUM_LEDS 60
#define NUM_CHANS (3*NUM_LEDS)
    
#define WS2812b_LAT LATBbits.LB2
#define WS2812b_TRIS TRISBbits.TRISB2

void WS2812b_Init (void);
void WS2812b_Write (void);

extern uint8_t ledData[NUM_CHANS];
extern const uint8_t gamma8[256];

#ifdef	__cplusplus
}
#endif

#endif	/* WS2812B_H */


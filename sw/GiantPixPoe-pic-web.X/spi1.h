/* 
 * File:   spi1.h
 * Author: glen
 *
 * Created on December 14, 2019, 8:55 AM
 */

#ifndef SPI1_H
#define	SPI1_H

#ifdef	__cplusplus
extern "C" {
#endif

void spi1_Init (void);
uint8_t spi1_ExchangeByte (uint8_t in);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI1_H */


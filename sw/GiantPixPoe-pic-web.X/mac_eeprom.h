/* 
 * File:   mac_eeprom.h
 * Author: glen
 *
 * Created on December 14, 2019, 8:48 AM
 */

#ifndef MAC_EEPROM_H
#define	MAC_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAC_ADDR_48                 0xFA
#define MAC_ADDR_64                 0xF8

/***************** 25AA02E48 Instruction Set Summary *********************/
#define MAC_EE_READ     0x03
#define MAC_EE_WRITE    0x02
#define MAC_EE_WRDI     0x04
#define MAC_EE_WREN     0x06
#define MAC_EE_RDSR     0x05
#define MAC_EE_WRSR     0x01

void e48_read_mac(uint8_t *mac);

#ifdef	__cplusplus
}
#endif

#endif	/* MAC_EEPROM_H */


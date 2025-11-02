#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#include <stdint.h>

uint8_t sd_bootloader_init (void);
uint8_t check_for_image (void);
uint8_t load_image (void);

#endif
#include "bootloader.h"

#include "sdmmc.h"
#include "fatfs.h"
#include "BspQspiBoot.h"

#define MAX_FLASH_SIZE 16 * 1024 * 1024
uint8_t image_buff[256];

char pr_name[] = "IMAGE.BIN";
FIL image_file;

uint8_t sd_bootloader_init (void)
{
	MX_SDMMC2_SD_Init();
  MX_FATFS_Init();
  return sd_card_mount();
}

uint8_t check_for_image (void)
{
  if(f_open(&image_file, pr_name, FA_READ) == FR_OK)
  {
    f_close(&image_file);
    return 0;
  }
  return 1;
}

uint8_t load_image (void)
{
  if(f_open(&image_file, pr_name, FA_READ) == FR_OK)
  {
    if(f_size(&image_file) < MAX_FLASH_SIZE)
    {
      uint32_t sec_to_erase = (f_size(&image_file) / 4096) + (1 && (f_size(&image_file) & 0xFFF));
      uint32_t addr = 0;
      uint8_t eoi = 0;
      UINT bytes_read;

      for(uint16_t i = 0; i < sec_to_erase; i++)
      {
        BspQspiBoot_EraseSector(addr);
        addr += 4096;
      }
      
      addr = 0;
      while(!eoi)
      {
        f_read(&image_file, image_buff, 256, &bytes_read);
        if(bytes_read != 0)
        {
          BspQspiBoot_WritePage(image_buff, addr, bytes_read);
          addr+= 256;
        }

        if(bytes_read != 256)
        {
          eoi = 1;
        }
      }
      f_close(&image_file);
      f_rename(pr_name, "IMAGE_LD.BIN");
      return 0;
    }
    f_close(&image_file);
  }
    return 1;
}

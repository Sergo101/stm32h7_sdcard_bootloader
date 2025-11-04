#include "bootloader.h"

#include "sdmmc.h"
#include "fatfs.h"
#include "BspQspiBoot.h"

#include <string.h>

#define APP_KEY 0x741B8CD7
#define APP_INFO_ADDR 0x400

#pragma pack(1)
typedef struct
{
  uint32_t appKey;
  uint32_t hwKey;
  uint32_t appVersion;
  uint8_t date[12];
  uint8_t time[9];
  uint8_t res[3];
}AppInfo_t;
#pragma pack(0)

AppInfo_t file_app_info = {0,};
AppInfo_t image_info = {0,};

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
  uint8_t res = 1;
  if(f_open(&image_file, pr_name, FA_READ) == FR_OK)
  {
    UINT br;
    f_lseek(&image_file, APP_INFO_ADDR);
    f_read(&image_file,(void*)&file_app_info, sizeof(AppInfo_t), &br);
    f_close(&image_file);
    if(file_app_info.appKey == APP_KEY)
    {
      BspQspiBoot_ReadBuff((uint8_t*)&image_info, APP_INFO_ADDR,sizeof(AppInfo_t));
      res = strncmp((char*)image_info.date,(char*)file_app_info.date,12) == 0;
      res &= strncmp((char*)image_info.time,(char*)file_app_info.time,9) == 0;
    }
  }
  return res;
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

      HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);

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
      HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
      return 0;
    }
    f_close(&image_file);
  }
    return 1;
}

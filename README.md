# stm32h7_sdcard_bootloader
Bootloader load from sdcard to qspi and start app from qspi flash
# Hardware
This project operate at STM32H750IBK6 dev board from aliexpresse
https://aliexpress.ru/item/1005002536639925.html?sku_id=12000038943849991
# Build & Debug
Easiest way to build and debug this project is:
1 install STM32_CubeCLT package
2 install vscode
3 install STM32extencion pack for vscode
4 config cmake preset & build
5 connect st-link v2, press debug
# Test
Root project folder contains IMAGE.BIN file. It is a blink program, that operates from qspi flash.
You can copy IMAGE.BIN file to sdcard, insert card in devboard and start debug. After sucssessfull copying image file to qspi flash, bootloader rename file to IMAGE_LD.BIN.
# Short Summary
Sdcard operation and file copying you can find in bootloader.c
Bootloader checks application key before loading to prevent copying incorrect bin file
You need to add appkey to you application
typedef struct
{
  uint32_t appKey;
  uint32_t hwKey;
  uint32_t appVersion;
  uint32_t date;
}AppInfo_t;
__attribute__((section(".AppInfo"))) const AppInfo_t AppInfo =
{
  .appKey = 0x741B8CD7,
  .hwKey  = 0x1,
  .appVersion  = 0x0,
  .date = 3112025,
  /* data */
};
And add special section in linker script

  .AppInfo 0x90000400 : 
  {
    . = ALIGN(4);
    KEEP(*(.AppInfo))
    . = ALIGN(4);
  } >FLASH

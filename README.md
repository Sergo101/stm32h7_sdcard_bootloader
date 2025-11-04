# stm32h7_sdcard_bootloader
Bootloader load from sdcard to qspi and start app from qspi flash
# Hardware
This project operate at STM32H750IBK6 dev board from aliexpress
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
You can copy IMAGE.BIN file to sdcard, insert card in devboard and start debug. Bootloader checks .date = __DATE__, .time = __TIME__, sections in app info and rewrite image if date or time incompare
# Short Summary
Sdcard operation and file copying you can find in bootloader.c  
Bootloader checks application key before loading to prevent copying incorrect bin file  
You need to add appinfo to you application at 0x90000400 address in qspi flash. It locates between .isr_vector & .text areas
AppKey in this bootloader is 0x741B8CD7  
/* Bootloader info */  
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
  
__attribute__((section(".AppInfo"))) const AppInfo_t AppInfo =  
{  
  .appKey = 0x741B8CD7,  
  .hwKey  = 0x1,  
  .appVersion  = 0x0,  
  .date = __DATE__,  
  .time = __TIME__,  
};  
And add special section in linker script  
  
  .AppInfo 0x90000400 :   
  {  
    . = ALIGN(4);  
    KEEP(*(.AppInfo))  
    . = ALIGN(4);  
  } >FLASH  

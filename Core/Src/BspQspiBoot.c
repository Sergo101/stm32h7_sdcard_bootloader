#include "main.h"
#include "BspQspiBoot.h"
#include "quadspi.h"

extern QSPI_HandleTypeDef hqspi;

static int BspQspiBoot_AutoPollingMemReady(QSPI_HandleTypeDef *p_hqspi)
{
	QSPI_CommandTypeDef     sCommand = {0};
	QSPI_AutoPollingTypeDef sConfig = {0};

	/* �������� */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1�߷�ʽ����ָ�� */
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       /* 24λ��ַ */
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* �޽����ֽ� */
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q64JV��֧��DDR */
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDRģʽ����������ӳ� */
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 /* ÿ�δ��䶼��ָ�� */

	/* ��ȡ״̬*/
	sCommand.Instruction       = BQB_Cmd_ReadStatus1;        /* ��ȡ״̬���� */
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;          /* �����ַ */
	sCommand.DataMode          = QSPI_DATA_1_LINE;           /* 1������ */
	sCommand.DummyCycles       = 0;                          /* ��������� */

	sConfig.Mask               = 0x01;
	sConfig.Match              = 0x00;
	sConfig.MatchMode          = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize    = 1;
	sConfig.Interval           = 100;
	sConfig.AutomaticStop      = QSPI_AUTOMATIC_STOP_ENABLE;

	if (HAL_QSPI_AutoPolling(p_hqspi, &sCommand, &sConfig, 10000) != HAL_OK)
	{
		return 1;
	}

	return 0;
}

int BspQspiBoot_Init(void)
{
  uint32_t i;
  char *p;
  
  p = (char *)&hqspi;
  for (i = 0; i < sizeof(QSPI_HandleTypeDef); i++)
  {
    *p++ = 0;
  }
  
  hqspi.Instance = QUADSPI;   
  
  if (HAL_QSPI_DeInit(&hqspi) != HAL_OK)
  {
    return 1;
  }
  
  // hqspi.Init.ClockPrescaler = 1;
  
  // hqspi.Init.FifoThreshold = 1;
  
  // hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  
  // hqspi.Init.FlashSize = QSPI_FLASH_SIZE; 

  // hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;

  // hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  
  // hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  
  // hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  
  // if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  // {
  //   return 1;
  // }
  
  MX_QUADSPI_Init();
  
  HAL_Delay(20);

  QSPI_CommandTypeDef sCommand = {0};

   sCommand.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
   sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
   sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
   sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
   sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
   sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

   sCommand.Instruction       = 0x66;
   sCommand.AddressMode       = QSPI_ADDRESS_NONE;
   sCommand.DataMode          = QSPI_DATA_NONE;
   sCommand.NbData            = 0;
   sCommand.DummyCycles       = 0;

   if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
   {
     Error_Handler();
   }

   sCommand.Instruction       = 0x99;

    if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
      {
        Error_Handler();
      }

   //sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;

   HAL_Delay(20);


   sCommand.Instruction       = 0x66;


   if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
   {
     Error_Handler();
   }

   sCommand.Instruction       = 0x99;

   if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
   {
     Error_Handler();
   }


  return 0;
}



uint32_t BspQspiBoot_ReadID(void)
{
  QSPI_CommandTypeDef sCommand = {0};
  uint32_t ulID;
  uint8_t ucaBuff[3] = {0};

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;   
  
  sCommand.Instruction       = BQB_Cmd_ReadID;  
  sCommand.AddressMode       = QSPI_ADDRESS_NONE; 
  sCommand.DataMode          = QSPI_DATA_1_LINE;    
  sCommand.NbData            = 3;
  sCommand.DummyCycles       = 0;                  
  
  if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
  {
    Error_Handler();
  } 
  
  if(HAL_QSPI_Receive(&hqspi, ucaBuff, 10000) != HAL_OK) 
  {
    Error_Handler();
  }

  ulID = (ucaBuff[0] << 16) | (ucaBuff[1] << 8 ) | ucaBuff[2];

  return ulID;
}



static int BspQspiBoot_WriteEnable(QSPI_HandleTypeDef *p_hqspi)
{
  QSPI_CommandTypeDef sCommand = {0};

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;   
  
  sCommand.Instruction       = BQB_Cmd_WriteEnable;  
  sCommand.AddressMode       = QSPI_ADDRESS_NONE; 
  sCommand.DataMode          = QSPI_DATA_NONE;    
  sCommand.NbData            = 0;
  sCommand.DummyCycles       = 0;                 
  
  if(HAL_QSPI_Command(p_hqspi, &sCommand, 10000) != HAL_OK)
  {
    return 1;
  } 

  return 0;
}

int BspQspiBoot_EraseSector(uint32_t ulSectorAddr)
{
  QSPI_CommandTypeDef sCommand = {0};
  
  BspQspiBoot_WriteEnable(&hqspi);

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;   
  
  sCommand.Instruction       = BQB_Cmd_SectorErase;  
  sCommand.AddressMode       = QSPI_ADDRESS_1_LINE; 
  sCommand.Address           = ulSectorAddr;
  sCommand.DataMode          = QSPI_DATA_NONE;    
  sCommand.DummyCycles       = 0;                 

  if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
  {
    return 1;
  } 

  if(BspQspiBoot_AutoPollingMemReady(&hqspi) == 1)
  {
    return 1;
  }

  return 0;
}

int BspQspiBoot_EraseChip(void)
{
  QSPI_CommandTypeDef sCommand = {0};
  
  BspQspiBoot_WriteEnable(&hqspi);

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;   
  
  sCommand.Instruction       = BQB_Cmd_ChipErase;  
  sCommand.AddressMode       = QSPI_ADDRESS_NONE; 
  sCommand.DataMode          = QSPI_DATA_NONE;   
  sCommand.NbData            = 0;
  sCommand.DummyCycles       = 0;                 
  
  if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
  {
    return 1;
  } 

  if(BspQspiBoot_AutoPollingMemReady(&hqspi) == 1)
  {
    return 1;
  }

  return 0;
}

int BspQspiBoot_WritePage(uint8_t *p_Buff,uint32_t ulWriteAddr,uint16_t usWriteSize)
{
  QSPI_CommandTypeDef sCommand = {0};
  
  BspQspiBoot_WriteEnable(&hqspi);

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;       
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  
  sCommand.SIOOMode          = QSPI_SIOO_INST_ONLY_FIRST_CMD;   
  
  sCommand.Instruction       = BQB_Cmd_PageProgram_Quad;  
  sCommand.AddressMode       = QSPI_ADDRESS_1_LINE; 
  sCommand.Address           = ulWriteAddr;
  sCommand.DataMode          = QSPI_DATA_4_LINES;    
  sCommand.NbData            = usWriteSize;
  sCommand.DummyCycles       = 0;                 

  if(HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
  {
    return 1;
  } 
  
  if (HAL_QSPI_Transmit(&hqspi, p_Buff, 10000) != HAL_OK) 
  {
    return 1;
  }

  if(BspQspiBoot_AutoPollingMemReady(&hqspi) == 1)
  {
    return 1;
  }

  return 0;
}

int BspQspiBoot_ReadBuff(uint8_t *p_Buff,uint32_t ulReadAddr,uint32_t ulReadSize)
{
	QSPI_CommandTypeDef sCommand = {0};
	
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    	/* 1�߷�ʽ����ָ�� */
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;      	/* 24λ��ַ */
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  	/* �޽����ֽ� */
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      	/* W25Q64JV��֧��DDR */
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  	/* DDRģʽ����������ӳ� */
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;		/* ÿ�δ���Ҫ��ָ�� */	
 
	sCommand.Instruction       = BQB_Cmd_FastRead_Quad;       /* 24bit��ַ��4�߿��ٶ�ȡ���� */
	sCommand.AddressMode       = QSPI_ADDRESS_4_LINES;        /* 4�ߵ�ַ */
	sCommand.Address           = ulReadAddr;                  /* ��ȡ���ݵ���ʼ��ַ */ 
	sCommand.DataMode          = QSPI_DATA_4_LINES;           /* 4������ */
	sCommand.NbData            = ulReadSize;                  /* ��ȡ�����ݴ�С */ 
	sCommand.DummyCycles       = 6;                           /* ������ */
	
	if (HAL_QSPI_Command(&hqspi, &sCommand, 10000) != HAL_OK)
	{
		return 1;
	}

	if (HAL_QSPI_Receive(&hqspi, p_Buff, 10000) != HAL_OK)
	{
		return 1;
	}

	return 0;
}

int BspQspiBoot_MemMapped(void)
{
  QSPI_CommandTypeDef s_command = {0};
  QSPI_MemoryMappedTypeDef s_mem_mapped_cfg = {0};

  s_command.InstructionMode          = QSPI_INSTRUCTION_1_LINE;     /* 1�߷�ʽ����ָ�� */ 
  s_command.AddressSize              = QSPI_ADDRESS_24_BITS;        /* 24λ��ַ */
  s_command.AlternateByteMode        = QSPI_ALTERNATE_BYTES_NONE;   /* �޽����ֽ� */
  s_command.DdrMode                  = QSPI_DDR_MODE_DISABLE;       /* W25Q64JV��֧��DDR */
  s_command.DdrHoldHalfCycle         = QSPI_DDR_HHC_ANALOG_DELAY;   /* DDRģʽ����������ӳ� */
  s_command.SIOOMode                 = QSPI_SIOO_INST_EVERY_CMD;    /* ÿ�δ��䶼��ָ�� */

  s_command.Instruction              = BQB_Cmd_FastRead_Quad;       /* ���ٶ�ȡ���� */
  s_command.AddressMode              = QSPI_ADDRESS_4_LINES;        /* 4����ַ�� */
  s_command.DataMode                 = QSPI_DATA_4_LINES;           /* 4�������� */
  s_command.DummyCycles              = 6;                           /* ������ */
  
  s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  s_mem_mapped_cfg.TimeOutPeriod = 0;
  
  if(HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg) != HAL_OK)
  {
    return 1;
  }

  return 0;
}

int BspQspiBoot_QuitMemMapped(void)
{
  HAL_QSPI_Abort(&hqspi);

  return 0;
}

uint32_t ulFlashID;
uint8_t ucaTestBuff[256] = {0};

void BspQspiBoot_Test(void)
{
  bool bTestResult = true;
  uint8_t ucTestCnt;
  uint32_t ulTestAddr;
  uint32_t ulSectorAddr = 0x2000;
  
  ulFlashID = BspQspiBoot_ReadID();
  
  if(ulFlashID != 0x00EF4017)
  {
    bTestResult = false;
  }

  while(bTestResult == false);
  
  BspQspiBoot_EraseSector(ulSectorAddr);
  
  for(ucTestCnt=0;ucTestCnt<16;ucTestCnt++)
  {
    ulTestAddr = ulSectorAddr+(ucTestCnt*QSPI_FLASH_PAGE_SIZE);
    
    {
      uint16_t i;
    
      for(i=0;i<sizeof(ucaTestBuff);i++)
      {
        ucaTestBuff[i] = i;
      }
    }
  
    BspQspiBoot_WritePage(ucaTestBuff,ulTestAddr,sizeof(ucaTestBuff));
  
    memset(ucaTestBuff,0,sizeof(ucaTestBuff));
  
    BspQspiBoot_ReadBuff(ucaTestBuff,ulTestAddr,sizeof(ucaTestBuff));
  
    {
      uint16_t i;
    
      for(i=0;i<sizeof(ucaTestBuff);i++)
      {
        if(ucaTestBuff[i] != i)
        {
          bTestResult = false;
          break;
        }
      }
    }
  }

  while(bTestResult == false);

  while(1)
  {
    
  }
}

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

void BspQspiBoot_JumpToApp(void)
{
	uint32_t i=0;
		void (*AppJump)(void);         /* ����һ������ָ�� */
		__IO uint32_t AppAddr = 0x90000000;  /* APP ��ַ */

	    /* �ر�ȫ���ж� */
		DISABLE_INT();

	    /* ��������ʱ�ӵ�Ĭ��״̬��ʹ��HSIʱ�� */
		HAL_RCC_DeInit();

		/* �رյδ�ʱ������λ��Ĭ��ֵ */
		SysTick->CTRL = 0;
	  SysTick->LOAD = 0;
	  SysTick->VAL = 0;

		/* �ر������жϣ���������жϹ����־ */
		for (i = 0; i < 8; i++)
		{
			NVIC->ICER[i]=0xFFFFFFFF;
			NVIC->ICPR[i]=0xFFFFFFFF;
		}

		/* ʹ��ȫ���ж� */
		ENABLE_INT();

		/* ��ת��Ӧ�ó����׵�ַ��MSP����ַ+4�Ǹ�λ�жϷ�������ַ */
		AppJump = (void (*)(void)) (*((uint32_t *) (AppAddr + 4)));

		/* ��������ջָ�� */
		__set_MSP(*(uint32_t *)AppAddr);

		/* ��RTOS���̣�����������Ҫ������Ϊ��Ȩ��ģʽ��ʹ��MSPָ�� */
		__set_CONTROL(0);

		/* ��ת��ϵͳBootLoader */
		AppJump();

		/* ��ת�ɹ��Ļ�������ִ�е�����û��������������Ӵ��� */
		while (1)
		{

		}
}


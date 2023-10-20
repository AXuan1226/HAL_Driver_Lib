/**
 *@file    sdram_fmc_drv.c
 *@brief   ʹ�� FMC ���� SDRAM
 *@author  mculover666
 *@date    2020-08-27
 *@note    ���������� W9825G6KH SDRAMоƬͨ��
*/

#include "sdram_fmc_drv.h"

static int SDRAM_SendCommand(uint32_t CommandMode, uint32_t Bank, uint32_t RefreshNum, uint32_t RegVal)
{
    uint32_t CommandTarget;
    FMC_SDRAM_CommandTypeDef Command;
    
    if (Bank == 1) {
        CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    } else if (Bank == 2) {
        CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
    }
    
    Command.CommandMode = CommandMode;
    Command.CommandTarget = CommandTarget;
    Command.AutoRefreshNumber = RefreshNum;
    Command.ModeRegisterDefinition = RegVal;
    
    if (HAL_SDRAM_SendCommand(&SDRAM_HANDLE, &Command, 0x1000) != HAL_OK) {
        return -1;
    }
    
    return 0;
}

void SDRAM_Init(void)
{
    uint32_t temp;
    
    /* 1. ʱ��ʹ������ */
    SDRAM_SendCommand(FMC_SDRAM_CMD_CLK_ENABLE, SDRAM_BANK, 1, 0);
    
    /* 2. ��ʱ������100us */
    HAL_Delay(1);
    
    /* 3. SDRAMȫ��Ԥ������� */
    SDRAM_SendCommand(FMC_SDRAM_CMD_PALL, SDRAM_BANK, 1, 0);
    
    /* 4. �Զ�ˢ������ */
    SDRAM_SendCommand(FMC_SDRAM_CMD_AUTOREFRESH_MODE, SDRAM_BANK, 8, 0);
    
    /* 5. ����SDRAMģʽ�Ĵ��� */   
    temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1            |          //����ͻ�����ȣ�1
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     |          //����ͻ�����ͣ�����
                     SDRAM_MODEREG_CAS_LATENCY_3             |          //����CLֵ��3
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD   |          //���ò���ģʽ����׼
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;              //����ͻ��дģʽ���������  
    SDRAM_SendCommand(FMC_SDRAM_CMD_LOAD_MODE, SDRAM_BANK, 1, temp);
    
    /* 6. ������ˢ��Ƶ�� */
    /*
        SDRAM refresh period / Number of rows��*SDRAMʱ���ٶ� �C 20
      = 64000(64 ms) / 8192 *90MHz - 20
    */
    temp = (64000.0 / 8192) * (HAL_RCC_GetHCLKFreq()/1000000) - 20;
    HAL_SDRAM_ProgramRefreshRate(&SDRAM_HANDLE, temp);
}

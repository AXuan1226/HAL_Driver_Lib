/**
 * @file    bsp_w25q64.c
 * @brief   W25Q64��������
 * @author  Mculover666(http://www.mculover666.cn)
 * @note    �������������STM32CubeMX���ɵ�QSPI��ʼ������
*/


#include "bsp_w25q64.h"

/**
 * @brief        ��SPI Flash����ָ��
 * @param        instruction ���� Ҫ���͵�ָ��
 * @param        address     ���� Ҫ���͵ĵ�ַ
 * @param        dummyCycles    ���� ��ָ��������
 * @param        instructionMode ���� ָ���ģʽ
 * @param        addressMode ���� ��ַ����ģʽ
 * @param        addressSize    ���� ��ַ��С
 * @param        dataMode    ���� ���ݷ���ģʽ
 * @retval        �ɹ�����HAL_OK
*/
HAL_StatusTypeDef QSPI_Send_Command(uint32_t instruction, 
                                    uint32_t address, 
                                    uint32_t dummyCycles, 
                                    uint32_t instructionMode, 
                                    uint32_t addressMode, 
                                    uint32_t addressSize, 
                                    uint32_t dataMode)
{
    QSPI_CommandTypeDef cmd;

    cmd.Instruction = instruction;                     //ָ��
    cmd.Address = address;                          //��ַ
    cmd.DummyCycles = dummyCycles;                  //���ÿ�ָ��������
    cmd.InstructionMode = instructionMode;            //ָ��ģʽ
    cmd.AddressMode = addressMode;                   //��ַģʽ
    cmd.AddressSize = addressSize;                   //��ַ����
    cmd.DataMode = dataMode;                         //����ģʽ
    cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;           //ÿ�ζ�����ָ��
    cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //�޽����ֽ�
    cmd.DdrMode = QSPI_DDR_MODE_DISABLE;               //�ر�DDRģʽ
    cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;

    return HAL_QSPI_Command(&hqspi, &cmd, 5000);
}

/**
* @brief    QSPI����ָ�����ȵ�����
* @param    buf  ���� �������ݻ������׵�ַ
* @param    size ���� Ҫ�������ݵ��ֽ���
 * @retval    �ɹ�����HAL_OK
 */
HAL_StatusTypeDef QSPI_Transmit(uint8_t* send_buf, uint32_t size)
{
    hqspi.Instance->DLR = size - 1;                         //�������ݳ���
    return HAL_QSPI_Transmit(&hqspi, send_buf, 5000);        //��������
}

/**
 * @brief   QSPI����ָ�����ȵ�����
 * @param   buf  ���� �������ݻ������׵�ַ
 * @param   size ���� Ҫ�������ݵ��ֽ���
 * @retval  �ɹ�����HAL_OK
 */
HAL_StatusTypeDef QSPI_Receive(uint8_t* recv_buf, uint32_t size)
{
    hqspi.Instance->DLR = size - 1;                       //�������ݳ���
    return HAL_QSPI_Receive(&hqspi, recv_buf, 5000);            //��������
}


/**
 * @brief   ��ȡFlash�ڲ���ID
 * @param   none
 * @retval    �ɹ�����device_id
 */
uint16_t W25QXX_ReadID(void)
{
    uint8_t recv_buf[2] = {0};    //recv_buf[0]���Manufacture ID, recv_buf[1]���Device ID
    uint16_t device_id = 0;
    if(HAL_OK == QSPI_Send_Command(ManufactDeviceID_CMD, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE))
    {
        //��ȡID
        if(HAL_OK == QSPI_Receive(recv_buf, 2))
        {
            device_id = (recv_buf[0] << 8) | recv_buf[1];
            return device_id;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/**
 * @brief    ��ȡSPI FLASH����
 * @param   dat_buffer ���� ���ݴ洢��
 * @param   start_read_addr ���� ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param   byte_to_read ���� Ҫ��ȡ���ֽ���(���65535)
 * @retval  none
 */
void W25QXX_Read(uint8_t* dat_buffer, uint32_t start_read_addr, uint16_t byte_to_read)
{
	  W25QXX_Wait_Busy();
    QSPI_Send_Command(READ_DATA_CMD, start_read_addr, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Receive(dat_buffer, byte_to_read);
}

/**
 * @brief    ��ȡW25QXX��״̬�Ĵ�����W25Q64һ����2��״̬�Ĵ���
 * @param     reg  ���� ״̬�Ĵ������(1~2)
 * @retval    ״̬�Ĵ�����ֵ
 */
uint8_t W25QXX_ReadSR(uint8_t reg)
{
    uint8_t cmd = 0, result = 0;    
    switch(reg)
    {
        case 1:
            /* ��ȡ״̬�Ĵ���1��ֵ */
            cmd = READ_STATU_REGISTER_1;
        case 2:
            cmd = READ_STATU_REGISTER_2;
        case 0:
        default:
            cmd = READ_STATU_REGISTER_1;
    }
    QSPI_Send_Command(cmd, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Receive(&result, 1);

    return result;
}

/**
 * @brief    �����ȴ�Flash���ڿ���״̬
 * @param   none
 * @retval  none
 */
void W25QXX_Wait_Busy(void)
{
    while((W25QXX_ReadSR(1) & 0x01) == 0x01); // �ȴ�BUSYλ���
}

/**
 * @brief    W25QXXдʹ��,��S1�Ĵ�����WEL��λ
 * @param    none
 * @retval
 */
void W25QXX_Write_Enable(void)
{
    QSPI_Send_Command(WRITE_ENABLE_CMD, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_NONE);
        W25QXX_Wait_Busy();
}

/**
 * @brief    W25QXXд��ֹ,��WEL����
 * @param    none
 * @retval    none
 */
void W25QXX_Write_Disable(void)
{
    QSPI_Send_Command(WRITE_DISABLE_CMD, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_NONE);
        W25QXX_Wait_Busy();
}

/**
 * @brief    W25QXX����һ������
 * @param   sector_addr    ���� ������ַ ����ʵ����������
 * @retval  none
 * @note    ��������
 */
void W25QXX_Erase_Sector(uint32_t sector_addr)
{
    sector_addr *= 4096;    //ÿ������16��������ÿ�������Ĵ�С��4KB����Ҫ����Ϊʵ�ʵ�ַ
    W25QXX_Write_Enable();  //����������д��0xFF����Ҫ����дʹ��
    W25QXX_Wait_Busy();        //�ȴ�дʹ�����
    QSPI_Send_Command(SECTOR_ERASE_CMD, sector_addr, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_NONE);
    W25QXX_Wait_Busy();       //�ȴ������������
}

/**
 * @brief    ҳд�����
 * @param    dat ���� Ҫд������ݻ������׵�ַ
 * @param    WriteAddr ���� Ҫд��ĵ�ַ
 * @param   byte_to_write ���� Ҫд����ֽ�����0-256��
 * @retval    none
 */
void W25QXX_Page_Program(uint8_t* dat, uint32_t WriteAddr, uint16_t byte_to_write)
{
    W25QXX_Write_Enable();
    QSPI_Send_Command(PAGE_PROGRAM_CMD, WriteAddr, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Transmit(dat, byte_to_write);
    W25QXX_Wait_Busy();
}

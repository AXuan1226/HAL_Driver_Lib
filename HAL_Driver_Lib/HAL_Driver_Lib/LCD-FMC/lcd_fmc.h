/**
 * @file    lcd_fmc.c
 * @brief   ʹ��FMC��������TFT-LCD��Ļ��MCU����
 * @author  Mculover666
 * @date    2020/08/27
*/

#ifndef _LCD_FMC_H_
#define _LCD_FMC_H_

#include "fmc.h"

typedef struct lcd_fmc_address_st {
    volatile uint16_t lcd_reg;
    volatile uint16_t lcd_ram;
} lcd_fmc_address_t;

/**
 * @brief    ����LCD��Ļ����
 * @param    lcd_width     LCD��Ļ���
 * @param    lcd_height    LCD��Ļ�߶�
 * @param    lcd_id        LCD ����IC ID
 * @param    lcd_direction LCD������ʾ����������ʾ��0-������1-����
 * @param    wram_cmd      ��ʼдgramָ��
 * @param    set_x_cmd     ����x����ָ��
 * @param    set_y_cmd     ����y����ָ��
*/
typedef struct lcd_params_st {
    uint16_t lcd_width;
    uint16_t lcd_height;
    uint16_t lcd_id;
    uint8_t  lcd_direction;
    uint16_t wram_cmd;
    uint16_t set_x_cmd;
    uint16_t set_y_cmd;
} lcd_params_t;

/**
 * @brief    LCDɨ�跽��ö��
 * @note     L-��R-�ң�U-�ϣ�D-��
*/
typedef enum lcd_scan_dir_en {
    L2R_U2D = 0,
    L2R_D2U,
    R2L_U2D,
    R2L_D2U,
    U2D_L2R,
    U2D_R2L,
    D2U_L2R,
    D2U_R2L
} lcd_scan_dir_t;

/**
 * @brief    LCD��ɫ
*/
typedef enum lcd_color_en {
    BLACK   = 0x0000, //��ɫ
    BLUE    = 0x001F, //��ɫ
    GREEN   = 0x07E0, //��ɫ
    GBLUE	= 0X07FF, //����ɫ
    CYAN    = 0x7FFF, //ǳ��ɫ
    GRAY  	= 0X8430, //��ɫ
    BROWN 	= 0XBC40, //��ɫ
    RED     = 0xF800, //��ɫ
    BRED    = 0XF81F, //��ɫ
    BRRED 	= 0XFC07, //�غ�ɫ  
    YELLOW  = 0xFFE0, //��ɫ
    WHITE   = 0xFFFF, //��ɫ
} lcd_color_t;

/*
    ���ã�
    - ���� LCD->lcd_reg ��ַ�������ݣ���FMC���跢���ź�ʱ��A18=0����LCD_RS=0
    - ���� LCD->lcd_ram ��ַ�������ݣ���FMC���跢���ź�ʱ��A18=1����LCD_RS=1
*/
#define LCD_BASE    ((uint32_t)(0x60000000 | 0x0007FFFE))
#define LCD         ((lcd_fmc_address_t*)LCD_BASE)

/* LCD MPU�������� */
#define LCD_REGION_NUMBER		MPU_REGION_NUMBER0		//LCDʹ��region0
#define LCD_ADDRESS_START		(0X60000000)			//LCD�����׵�ַ
#define LCD_REGION_SIZE			MPU_REGION_SIZE_256MB   //LCD����С

/* ʹ�ܴ������Ƿ��ӡ������־����Ҫprintf֧�֣� */
#define LCD_LOG_ENABLE          1

#if LCD_LOG_ENABLE
#include <stdio.h>
#define LCD_LOG printf
#else
#define LCD_LOG(format,...)
#endif

/* ��Ļ��С��������ʾ�µ�ֵ�� */
#define LCD_WIDTH   480
#define LCD_HEIGHT  800

extern lcd_params_t lcd_params;

void lcd_init(void);
void lcd_display_on(void);
void lcd_display_off(void);
void lcd_backlight_on(void);
void lcd_backlight_off(void);
void lcd_clear(lcd_color_t color);

#endif /* _LCD_FMC_H_ */

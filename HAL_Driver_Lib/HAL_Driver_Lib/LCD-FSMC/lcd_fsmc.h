/******************************************************
 * @file    lcd_fsmc.h
 * @brief   ʹ��FSMC��������TFT-LCD��Ļ��MCU����
 * @author  Mculover666
 * @date    2020/08/27
 * @note    
 *          Ŀǰ֧�ֵ���������
 *            - ILI9341(0x9341)
 *            - NT35310(0x5310)
 *            - NT35510(0x5510)
******************************************************/

#ifndef _LCD_FSMC_H_
#define _LCD_FSMC_H_

#include "fsmc.h"

/**
 * @brief    LCD��Ļ����
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
 * @brief    LCD����״̬
 * @param    LCD_BACKLIGHT_OFF �رձ���
 * @param    LCD_BACKLIGHT_ON  �򿪱���
*/
typedef enum lcd_backlight_state_en {
    LCD_BACKLIGHT_OFF = 0,
    LCD_BACKLIGHT_ON  = 1,
} lcd_backlight_state_t;

/**
 * @brief    LCDɨ�跽��
 * @note     L-��R-�ң�U-�ϣ�D-��
*/
typedef enum lcd_scan_dir_en {
    L2R_U2D = 0,
    L2R_D2U = 1,
    R2L_U2D = 2,
    R2L_D2U = 3,
    U2D_L2R = 4,
    U2D_R2L = 5,
    D2U_L2R = 6,
    D2U_R2L = 7,
} lcd_scan_dir_t;

/**
 * @brief    LCD��ʾ����
 * @param    VERTICAL_DISP   ������ʾ
 * @param    HORIZONTAL_DISP ������ʾ
*/
typedef enum lcd_display_dir_en {
    VERTICAL_DISP   = 0,
    HORIZONTAL_DISP = 1,
} lcd_display_dir_t;

#define    BLACK   0x0000    //��ɫ
#define    BLUE    0x001F    //��ɫ
#define    GREEN   0x07E0    //��ɫ
#define    GBLUE   0X07FF    //����ɫ
#define    CYAN    0x7FFF    //ǳ��ɫ
#define    GRAY    0X8430    //��ɫ
#define    BROWN   0XBC40    //��ɫ
#define    RED     0xF800    //��ɫ
#define    BRED    0XF81F    //��ɫ
#define    BRRED   0XFC07    //�غ�ɫ  
#define    YELLOW  0xFFE0    //��ɫ
#define    WHITE   0xFFFF    //��ɫ

/****************** User Config Start ****************/

/* ʹ�ܴ������Ƿ��ӡ������־����Ҫprintf֧�֣� */
#define LCD_LOG_ENABLE          1

/* ��Ļ��С��������ʾ�µ�ֵ�� */
#define LCD_WIDTH               480
#define LCD_HEIGHT              800

/* ����������� */
#define LCD_BL_GPIO_Port        GPIOB
#define LCD_BL_Pin              GPIO_PIN_15

/* ͨ����ַ�߿���RS���� */
#define LCD_CMD_ADDR            0x6c000040
#define LCD_DAT_ADDR            0x6c000080

/* LCDĬ����ʾ����:VERTICAL_DISP-������HORIZONTAL_DISP-���� */
#define LCD_DEFAULT_DISPLAY_DIR VERTICAL_DISP

/* LCD��ʼ��������ɫ */
#define LCD_DEFAULT_CLEAR_COLOR WHITE

/****************** User Config End ****************/

#if LCD_LOG_ENABLE
#include <stdio.h>
#define LCD_LOG printf
#else
#define LCD_LOG(format,...)
#endif

extern lcd_params_t lcd_params;

void lcd_init(void);
void lcd_display_on(void);
void lcd_display_off(void);
void lcd_backlight_ctrl(lcd_backlight_state_t state);
void lcd_clear(uint16_t color);

void lcd_draw_point(uint16_t x_pos, uint16_t y_pos, uint16_t color);
void lcd_set_window(uint16_t x_pos_start, uint16_t y_pos_start, uint16_t width, uint16_t height);
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_fill_with_buffer(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *color_buf);

#endif /* _LCD_FSMC_H_ */

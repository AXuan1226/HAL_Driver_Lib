#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#define USE_HORIZONTAL 1  //ÉèÖÃºáÆÁ»òÕßÊúÆÁÏÔÊ¾ 0»ò1ÎªÊúÆÁ 2»ò3ÎªºáÆÁ

#include "gpio.h"
#include <stdint.h>

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 128

#else
#define LCD_W 128
#define LCD_H 128
#endif


//-----------------LCDç«¯å£å®šä¹‰---------------- 

#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET)
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET)
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)

#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET)


void LCD_GPIO_Init(void);//åˆå§‹åŒ–GPIO
void LCD_Writ_Bus(uint8_t dat);//æ¨¡æ‹ŸSPIæ—¶åº
void LCD_WR_DATA8(uint8_t dat);//å†™å…¥ä¸€ä¸ªå­—èŠ‚
void LCD_WR_DATA(uint16_t dat);//å†™å…¥ä¸¤ä¸ªå­—èŠ‚
void LCD_WR_REG(uint8_t dat);//å†™å…¥ä¸€ä¸ªæŒ‡ä»¤
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//è®¾ç½®åæ ‡å‡½æ•°
void LCD_Init(void);//LCDåˆå§‹åŒ–
#endif

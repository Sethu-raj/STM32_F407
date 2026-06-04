/*
 * LCD.c
 *
 *  Created on: Jun 3, 2026
 *      Author: sethu
 */


#include "lcd.h"

#define RS_PIN GPIO_PIN_0
#define EN_PIN GPIO_PIN_1
#define D4_PIN GPIO_PIN_2
#define D5_PIN GPIO_PIN_10
#define D6_PIN GPIO_PIN_11
#define D7_PIN GPIO_PIN_12

#define LCD_PORT GPIOB

static void LCD_Enable(void)
{
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

static void LCD_Send_4Bits(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_PORT,D4_PIN,(data>>0)&1);
    HAL_GPIO_WritePin(LCD_PORT,D5_PIN,(data>>1)&1);
    HAL_GPIO_WritePin(LCD_PORT,D6_PIN,(data>>2)&1);
    HAL_GPIO_WritePin(LCD_PORT,D7_PIN,(data>>3)&1);

    LCD_Enable();
}

void LCD_Send_Command(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_PORT,RS_PIN,GPIO_PIN_RESET);

    LCD_Send_4Bits(cmd>>4);
    LCD_Send_4Bits(cmd & 0x0F);

    HAL_Delay(2);
}

void LCD_Send_Data(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_PORT,RS_PIN,GPIO_PIN_SET);

    LCD_Send_4Bits(data>>4);
    LCD_Send_4Bits(data & 0x0F);

    HAL_Delay(2);
}

void LCD_Init(void)
{
    HAL_Delay(50);

    LCD_Send_4Bits(0x03);
    HAL_Delay(5);

    LCD_Send_4Bits(0x03);
    HAL_Delay(1);

    LCD_Send_4Bits(0x03);
    LCD_Send_4Bits(0x02);

    LCD_Send_Command(0x28);
    LCD_Send_Command(0x0C);
    LCD_Send_Command(0x06);
    LCD_Send_Command(0x01);

    HAL_Delay(2);
}

void LCD_Send_String(char *str)
{
    while(*str)
    {
        LCD_Send_Data(*str++);
    }
}

void LCD_Set_Cursor(uint8_t row,uint8_t col)
{
    uint8_t addr;

    if(row==0)
        addr = 0x80 + col;
    else
        addr = 0xC0 + col;

    LCD_Send_Command(addr);
}

void LCD_Clear(void)
{
    LCD_Send_Command(0x01);
    HAL_Delay(2);
}


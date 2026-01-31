/**
 * ******************************************************************************
 * @file    oled.h
 * @brief   0.96" SSD1306 OLED Display Driver Header
 * 
 * @details OLED driver adapted for STM32F103C8T6 + RT-Thread Nano
 *          Uses bit-bang I2C communication with PB6/PB7 as GPIO_Output_OD
 * 
 * Pin Configuration:
 *  - PB6: OLED_SCL (I2C Clock, GPIO_Output_OD, GPIO_SPEED_FREQ_HIGH)
 *  - PB7: OLED_SDA (I2C Data, GPIO_Output_OD, GPIO_SPEED_FREQ_HIGH)
 *  - VCC: 3.3V
 *  - GND: Ground
 * 
 * ******************************************************************************
 */

#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>
#include "OLED_Data.h"

/* Font Size Definitions */
#define OLED_8X16    8   /* 8x16 font (ASCII) */
#define OLED_6X8     6   /* 6x8 font (ASCII) */

/* Fill Mode Definitions */
#define OLED_UNFILLED  0
#define OLED_FILLED    1

/* Initialization and Control Functions */
void OLED_Init(void);

/* Display Update Functions */
void OLED_Update(void);
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/* Screen Clear Functions */
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/* Display Character/String Functions */
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/* Graphics Drawing Functions */
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

#endif

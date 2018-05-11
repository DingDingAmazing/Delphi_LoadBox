#ifndef _GPIO_DRIVER_H
#define _GPIO_DRIVER_H

#include "stm32f0xx.h"
#include "i2c_app.h"
extern void iobus_init(void);
extern void HUB_Enable(uint8_t n);
extern void HUB_Disable(void);
extern void USB_Enable_1_5(uint8_t n);
extern void USB_Enable_6_10(uint8_t n);
extern void USB_Enable_11_15(uint8_t n);
extern void USB_Enable_16_20(uint8_t n);
extern void USB_Enable_21_25(uint8_t n);
extern void USB_Enable_26_30(uint8_t n);
extern void USB_Disable_1_5(void);
extern void USB_Disable_6_10(void);
extern void USB_Disable_11_15(void);
extern void USB_Disable_16_20(void);
extern void USB_Disable_21_25(void);
extern void USB_Disable_26_30(void);
extern void test_gpio(void);
extern void USB_5V_CT(uint8_t num, uint8_t en);
#endif

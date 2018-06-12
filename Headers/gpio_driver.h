#ifndef _GPIO_DRIVER_H
#define _GPIO_DRIVER_H

#include "stm32f0xx.h"
#include "i2c_app.h"
#include "public.h"

extern void iobus_init(void);
extern void HUB_Enable(uint8_t n);
extern void HUB_Disable(void);
extern void usb_enable(uint8_t n);
extern void usb_disable(uint8_t n);
extern void test_gpio(void);
extern void USB_5V_CT(uint8_t num, uint8_t en);
extern void usb_5v_onoff(uint8_t num, uint8_t en);
#endif

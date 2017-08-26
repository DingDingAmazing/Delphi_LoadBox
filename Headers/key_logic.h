#ifndef _KEY_LOGIC_H
#define _KEY_LOGIC_H

#include "gpio_app.h"
#include "stm32f0xx_it.h"

extern void SysTick_Configuration(void);

extern uint8_t USB_idx;
extern uint8_t USB_en;
extern uint8_t USB_flag;
extern uint8_t SD_idx;
extern uint8_t SD_flag;
extern uint8_t HUB_idx;
extern uint8_t HUB_en;
extern uint8_t HUB_flag;
#endif

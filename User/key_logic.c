#include "key_logic.h"
//set systick cycle 1ms
void SysTick_Configuration(void)
{
	SysTick_Config(SystemCoreClock/1000);
}


uint8_t USB_idx = 0;
uint8_t USB_en = 0;
uint8_t USB_flag = 0;
uint8_t SD_idx = 0;
uint8_t SD_flag = 0;
uint8_t HUB_idx = 0;
uint8_t HUB_en = 0;
uint8_t HUB_flag = 0;
uint8_t SD_en = 0;
uint8_t AUX_idx = 0;
uint8_t AUX_en = 0;
uint8_t AUX_flag = 0;

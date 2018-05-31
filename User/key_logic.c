#include "key_logic.h"
//set systick cycle 1ms
void SysTick_Configuration(void)
{
	SysTick_Config(SystemCoreClock/1000);
}


uint8_t USB_idx;
uint8_t USB_en;
uint8_t USB_flag;
uint8_t SD_idx;
uint8_t SD_flag;
uint8_t HUB_idx;
uint8_t HUB_en=0;
uint8_t HUB_flag;
uint8_t SD_en;
uint8_t AUX_idx;
uint8_t AUX_en;
uint8_t AUX_flag;

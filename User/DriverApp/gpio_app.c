#include "gpio_app.h"

/*
J13
J12
J14
*/

void USBCT(uint8_t num, uint8_t en)
{
	if(en)
	{
		usb_enable(num);
	}
	else
	{
		if((num == flag_on_record.usb1_on_idx) || (num == flag_on_record.usb2_on_idx))
		{
			usb_disable(num);//disconnect data signal first
			bsp_mDelay(20);
			usb_5v_onoff(num, 0);//then disconnect power
			if(((num-1)/5 + 1)%2)
			{
				flag_on_record.usb1_on_idx = 255;
				flag_on_record.usb_on_group1 = 255;
			}
			else
			{
				flag_on_record.usb2_on_idx = 255;
				flag_on_record.usb_on_group2 = 255;
			}
		}
	}
}

//调试时考虑加入关闭其他2路sd
void SD_CT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			SD3_Switch(en);
			break;
		case 2:
			SD1_Switch(en);
			break;
		case 3:
			SD2_Switch(en);
			break;
		default:
			break;
	}
}

//调试时考虑加入关闭其他2路aux
//调试时考虑加入lamp

#include "gpio_app.h"

void USBCT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 11:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_1_5(1);
			}
			else
			{
				USB_Disable_1_5();
			}
			break;
		case 12:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_1_5(2);
			}
			else
			{
				USB_Disable_1_5();
			}
			break;
		case 13:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_1_5(3);
			}
			else
			{
				USB_Disable_1_5();
			}
			break;
		case 14:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_1_5(4);
			}
			else
			{
				USB_Disable_1_5();
			}
			break;
		case 15:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_1_5(5);
			}
			else
			{
				USB_Disable_1_5();
			}
			break;
		case 16:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_6_10(6);
			}
			else
			{
				USB_Disable_6_10();
			}
			break;
		case 17:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_6_10(7);
			}
			else
			{
				USB_Disable_6_10();
			}
			break;
		case 18:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_6_10(8);
			}
			else
			{
				USB_Disable_6_10();
			}
			break;
		case 19:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_6_10(9);
			}
			else
			{
				USB_Disable_6_10();
			}
			break;
		case 20:
			if(en)
			{
				HUB_Enable(1);
				USB_Enable_6_10(10);
			}
			else
			{
				USB_Disable_6_10();
			}
			break;
		case 21:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_11_15(11);
			}
			else
			{
				USB_Disable_11_15();
			}
			break;
		case 22:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_11_15(12);
			}
			else
			{
				USB_Disable_11_15();
			}
			break;
		case 23:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_11_15(13);
			}
			else
			{
				USB_Disable_11_15();
			}
			break;
		case 24:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_11_15(14);
			}
			else
			{
				USB_Disable_11_15();
			}
			break;
		case 25:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_11_15(15);
			}
			else
			{
				USB_Disable_11_15();
			}
			break;
		case 26:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_16_20(16);
			}
			else
			{
				USB_Disable_16_20();
			}
			break;
		case 27:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_16_20(17);
			}
			else
			{
				USB_Disable_16_20();
			}
			break;
		case 28:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_16_20(18);
			}
			else
			{
				USB_Disable_16_20();
			}
			break;
		case 29:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_16_20(19);
			}
			else
			{
				USB_Disable_16_20();
			}
			break;
		case 30:
			if(en)
			{
				HUB_Enable(2);
				USB_Enable_16_20(20);
			}
			else
			{
				USB_Disable_16_20();
			}
			break;
		case 1:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_21_25(21);
			}
			else
			{
				USB_Disable_21_25();
			}
			break;
		case 2:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_21_25(22);
			}
			else
			{
				USB_Disable_21_25();
			}
			break;
		case 3:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_21_25(23);
			}
			else
			{
				USB_Disable_21_25();
			}
			break;
		case 4:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_21_25(24);
			}
			else
			{
				USB_Disable_21_25();
			}
			break;
		case 5:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_21_25(25);
			}
			else
			{
				USB_Disable_21_25();
			}
			break;
		case 6:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_26_30(26);
			}
			else
			{
				USB_Disable_26_30();
			}
			break;
		case 7:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_26_30(27);
			}
			else
			{
				USB_Disable_26_30();
			}
			break;
		case 8:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_26_30(28);
			}
			else
			{
				USB_Disable_26_30();
			}
			break;
		case 9:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_26_30(29);
			}
			else
			{
				USB_Disable_26_30();
			}
			break;
		case 10:
			if(en)
			{
				HUB_Enable(3);
				USB_Enable_26_30(30);
			}
			else
			{
				USB_Disable_26_30();
			}
			break;
		default:
			break;
	}
}

void SD_CT(uint8_t num)
{
	switch(num)
	{
		case 4:
			HUB_Enable(1);
			SD_Enable_1_3(1);
			break;
		case 5:
			HUB_Enable(1);
			SD_Enable_1_3(2);
			break;
		case 6:
			HUB_Enable(1);
			SD_Enable_1_3(3);
			break;
		case 7:
			HUB_Enable(2);
			SD_Enable_4_6(4);
			break;
		case 8:
			HUB_Enable(2);
			SD_Enable_4_6(5);
			break;
		case 9:
			HUB_Enable(2);
			SD_Enable_4_6(6);
			break;
		case 1:
			HUB_Enable(3);
			SD_Enable_7_9(7);
			break;
		case 2:
			HUB_Enable(3);
			SD_Enable_7_9(8);
			break;
		case 3:
			HUB_Enable(3);
			SD_Enable_7_9(9);
			break;
		default:
			break;
	}
}

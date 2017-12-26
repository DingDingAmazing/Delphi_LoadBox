#include "main.h"



int main(void)
{
	static uint8_t n;
	SysTick_Configuration();
	iobus_init();
	usart_init();
//	HUB_Enable(1);
//	USB_Enable_1_5(1);
	if(1)
	{
		for(n=1;n<11;n++)
		{
			USBCT(n, 1);
			bsp_mDelay(200);
			USBCT(n, 0);
			bsp_mDelay(50);
		}
		HUB_Disable();
		bsp_mDelay(50);
		USBCT(1, 1);
		bsp_mDelay(100);
		SD_CT(1);
	}

	while(1)
	{
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
		bsp_uDelay(5);
	}
}

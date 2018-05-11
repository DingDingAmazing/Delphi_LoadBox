#include "main.h"

int main(void)
{
	static uint8_t n;
	SysTick_Configuration();
	i2c_pin_init();
	iobus_init();
	usart_init();
//	HUB_Enable(1);
//	USB_Enable_1_5(1);
	if(1)
	{
		for(n=1;n<31;n++)
		{
			USBCT(n, 1);
			bsp_mDelay(200);
			USBCT(n, 0);
			bsp_mDelay(50);
		}
		HUB_Disable();
	}

	while(1)
	{
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
		bsp_uDelay(5);
	}
}

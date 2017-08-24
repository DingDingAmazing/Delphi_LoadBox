#include "main.h"



int main(void)
{
	static uint8_t n;
	SysTick_Configuration();
	iobus_init();
	usart_init();
//	HUB_Enable(1);
//	USB_Enable_1_5(1);
	if(0)
	{
		test_gpio();
	}

	while(1)
	{
		UartFrameHandle();
		Uart2FrameOperate();
		EnventHandle();
		bsp_uDelay(5);
	}
}

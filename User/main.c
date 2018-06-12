#include "main.h"

int main(void)
{
	static uint8_t n;
	SysTick_Configuration();
	usart_init();
	bsp_mDelay(500);
	uart_send_word("\r\nusart is ok");
	bsp_mDelay(100);
	i2c_pin_init();
	iobus_init();
	
	if(1)
	{
		for(n=1;n<11;n++)
		{
			USBCT(n, 1);
			bsp_mDelay(200);
			USBCT(n, 0);
			bsp_mDelay(200);
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

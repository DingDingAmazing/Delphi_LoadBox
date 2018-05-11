#include "i2c_app.h"
uint32_t i2c_overtime;
uint8_t config_bytes[2] = {0x00, 0x00};
I2C_output_register I2C_IO_output;

//important
void out_bytes_inversion1(void)
{
	I2C_IO_output.one_out_p1_p0[0] = I2C_IO_output.one_out_p0_p1[1];
	I2C_IO_output.one_out_p1_p0[1] = I2C_IO_output.one_out_p0_p1[0];
}
//important
void out_bytes_inversion2(void)
{
	I2C_IO_output.two_out_p1_p0[0] = I2C_IO_output.two_out_p0_p1[1];
	I2C_IO_output.two_out_p1_p0[1] = I2C_IO_output.two_out_p0_p1[0];
}
//important
void init_out_bytes(void)
{
	I2C_IO_output.one_out_p0_p1[0] = 0x00;
	I2C_IO_output.one_out_p0_p1[1] = 0x00;
	I2C_IO_output.two_out_p0_p1[0] = 0x00;
	I2C_IO_output.two_out_p0_p1[1] = 0x00;
	
	I2C_IO_output.one_out_p1_p0[0] = 0x00;
	I2C_IO_output.one_out_p1_p0[1] = 0x00;
	I2C_IO_output.two_out_p1_p0[0] = 0x00;
	I2C_IO_output.two_out_p1_p0[1] = 0x00;
}
/**
	*@brief		perform as master device, write data to PCA9535
	*@param		driver_addr: (uint8_t)7bit slave address<<1
	*@param		reg_addr:    (uint8_t)control register address
	*@param		num_bytes:   (uint8_t)the number of operation data to be transmitted
	*@param		write_byte:  (uint8_t)operation data to be transmitted
	*@retval	successfully wtrie: ICI_Ok; if not: ICI_Fail;
	**/
I2C_Status I2C2_Write_NByte(uint8_t driver_addr, uint8_t reg_addr, uint8_t num_bytes, uint8_t *write_byte)
{
//write port register
	uint8_t write_num;
//判断总线是否在忙
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET)
	{
		if((i2c_overtime--) == 0)
		{
			return I2C_Fail;
		}
	}
//发送开始信号并跟随一个写地址操作
	I2C_TransferHandling(I2C2, driver_addr, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
//	I2C_TransferHandling(I2C2, driver_addr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXIS) == RESET)
  {
    if((i2c_overtime--) == 0)
    {
      return I2C_Fail;
    }
  }
//发送寄存器地址
	I2C_SendData(I2C2, reg_addr);
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TCR) == RESET)
  {
    if((i2c_overtime--) == 0)
    {
      return I2C_Fail;
    }
  }
//发送输出口的寄存器值
	I2C_TransferHandling(I2C2, driver_addr, num_bytes, I2C_AutoEnd_Mode, I2C_No_StartStop);
	for(write_num = 0; write_num < num_bytes; write_num++)
	{
		i2c_overtime = I2C_TimeOut;
		while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXIS) == RESET)
		{
    if((i2c_overtime--) == 0)
			{
      return I2C_Fail;
			}
		}
		I2C_SendData(I2C2, write_byte[write_num]);
//		I2C_SendData(I2C2, *write_byte);
//		write_byte++;
	}
//查看结束状态
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF) == RESET)
	{
    if((i2c_overtime--) == 0)
		{
      return I2C_Fail;
		}
	}
		
	return I2C_Ok;
}

//config register
uint8_t PCA9535_config_register(uint8_t driver_addr)
{
	if(I2C2_Write_NByte(driver_addr, 0x06, 2, config_bytes) == I2C_Fail)
	{	return 1;}
//可能不需要	
	if(I2C2_Write_NByte(driver_addr, 0x07, 2, config_bytes) == I2C_Fail)
	{	return 1;}
	return 0;
}

//output register
uint8_t PCA9535_output_register(uint8_t device_index)
{
	if(device_index == 0)
	{
		if(I2C2_Write_NByte(PCA9535_1st_Address, 0x02, 2, I2C_IO_output.one_out_p0_p1) == I2C_Fail)
		{	return 1;}
//可能不需要
		if(I2C2_Write_NByte(PCA9535_1st_Address, 0x03, 2, I2C_IO_output.one_out_p1_p0) == I2C_Fail)
		{	return 1;}
	}
	else if(device_index == 1)
	{
		if(I2C2_Write_NByte(PCA9535_2nd_Address, 0x02, 2, I2C_IO_output.two_out_p0_p1) == I2C_Fail)
		{	return 1;}
//可能不需要
		if(I2C2_Write_NByte(PCA9535_2nd_Address, 0x03, 2, I2C_IO_output.two_out_p1_p0) == I2C_Fail)
		{	return 1;}
	}
	
	return 0;
}

//如果一次传2个port不行就分2次，这里不对，没有关联off_on和pin_x
//void PCA9535_IO_out(uint8_t device_index, uint8_t port_x, uint8_t pin_x, uint8_t off_on)
void PCA9535_IO_out(uint8_t device_index, uint8_t port_x)
{
	if((device_index == 0) && (port_x == 0))
	{
		if(PCA9535_output_register(0) == 1)
		{
			i2c_error();
		}
	}
	else if((device_index == 1) && (port_x == 0))
	{
		if(PCA9535_output_register(1) == 1)
		{
			i2c_error();
		}
	}
}

//用打印输出
void i2c_error(void)
{
	
}

void i2c_pin_set(uint16_t idx)
{
	switch(idx>>8)
	{
		case 0:
			I2C_IO_output.one_out_p0_p1[0] |= (uint8_t)idx;
			break;
		case 1:
			I2C_IO_output.one_out_p0_p1[1] |= (uint8_t)idx;
			break;
		case 2:
			I2C_IO_output.two_out_p0_p1[0] |= (uint8_t)idx;
			break;
		case 3:
			I2C_IO_output.two_out_p0_p1[1] |= (uint8_t)idx;
			break;
		default:
			break;
	}
}

void i2c_pin_reset(uint16_t idx)
{
	switch(idx>>8)
	{
		case 0:
			I2C_IO_output.one_out_p0_p1[0] &= ~(uint8_t)idx;
			break;
		case 1:
			I2C_IO_output.one_out_p0_p1[1] &= ~(uint8_t)idx;
			break;
		case 2:
			I2C_IO_output.two_out_p0_p1[0] &= ~(uint8_t)idx;
			break;
		case 3:
			I2C_IO_output.two_out_p0_p1[1] &= ~(uint8_t)idx;
			break;
		default:
			break;
	}
}

void i2c_pin_init(void)
{
	init_out_bytes();
	PCA9535_config_register(PCA9535_1st_Address);
	PCA9535_config_register(PCA9535_2nd_Address);
	PCA9535_IO_out(0,0);
	PCA9535_IO_out(1,0);
}

void USB_HUB3_D_SEL_EN(uint8_t en)
{
	if(en == 0)
		i2c_pin_reset(USB_HUB3_D_SEL);
	else
		i2c_pin_set(USB_HUB3_D_SEL);
	
	out_bytes_inversion1();
	PCA9535_IO_out(0,0);
}

void SD1_Switch(uint8_t en)
{
	if(en == 0)
		i2c_pin_reset(SD1_EN);
	else
		i2c_pin_set(SD1_EN);
	
	out_bytes_inversion1();
	PCA9535_IO_out(0,0);
}

void SD2_Switch(uint8_t en)
{
	if(en == 0)
		i2c_pin_reset(SD2_EN);
	else
		i2c_pin_set(SD2_EN);
	
	out_bytes_inversion1();
	PCA9535_IO_out(0,0);
}

void SD3_Switch(uint8_t en)
{
	if(en == 0)
		i2c_pin_reset(SD3_EN);
	else
		i2c_pin_set(SD3_EN);
	
	out_bytes_inversion2();
	PCA9535_IO_out(1,0);
}

void Aux_Switch(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 0:
			if(en == 0)
				i2c_pin_reset(Aux3_EN);
			else
				i2c_pin_set(Aux3_EN);
			out_bytes_inversion2();
			PCA9535_IO_out(1,0);
			break;
		case 1:
			if(en == 0)
				i2c_pin_reset(Aux1_EN);
			else
				i2c_pin_set(Aux1_EN);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		case 2:
			if(en == 0)
				i2c_pin_reset(Aux2_EN);
			else
				i2c_pin_set(Aux2_EN);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		default:
			break;
	}
}

/*
|type|board num|item|para |
|----|---------|----|-----|
|5v  |1        |usb1|(0,x)|
|5v  |1        |usb2|(1,x)|
|5v  |2        |usb1|(2,x)|
|5v  |2        |usb2|(3,x)|
|5v  |3        |usb1|(4,x)|
|5v  |3        |usb2|(5,x)|
|5v  |1        |aux1|(6,x)|
|5v  |2        |aux2|(7,x)|
|5v  |3        |aux3|(8,x)|
|5v  |1        |sd1|(9,x)|
|5v  |2        |sd2|(10,x)|
|5v  |3        |sd3|(11,x)|
*/
void LAMP_Switch(int8_t num, int8_t en)
{
	switch(num)
	{
		//@1.1 5v
		case 0:
			if(en == 0)
				i2c_pin_reset(HUB3_USB1_5V_LAMP);
			else
				i2c_pin_set(HUB3_USB1_5V_LAMP);
			out_bytes_inversion2();
			PCA9535_IO_out(1,0);
			break;
		//@1.2 5v
		case 1:
			if(en == 0)
				i2c_pin_reset(HUB3_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB3_USB2_5V_LAMP);
			out_bytes_inversion2();
			PCA9535_IO_out(1,0);
			break;
		//@2.1 5v
		case 2:
			if(en == 0)
				i2c_pin_reset(HUB1_USB1_5V_LAMP);
			else
				i2c_pin_set(HUB1_USB1_5V_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@2.2 5v
		case 3:
			if(en == 0)
				i2c_pin_reset(HUB1_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB1_USB2_5V_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@3.1 5v
		case 4:
			if(en == 0)
				i2c_pin_reset(HUB2_USB1_5V_LAMP);
			else
				i2c_pin_set(HUB2_USB1_5V_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@3.2 5v
		case 5:
			if(en == 0)
				i2c_pin_reset(HUB2_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB2_USB2_5V_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@1 aux
		case 6:
			if(en == 0)
				i2c_pin_reset(Aux3_LAMP);
			else
				i2c_pin_set(Aux3_LAMP);
			out_bytes_inversion2();
			PCA9535_IO_out(1,0);
			break;
		//@2 aux
		case 7:
			if(en == 0)
				i2c_pin_reset(Aux1_LAMP);
			else
				i2c_pin_set(Aux3_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@3 aux
		case 8:
			if(en == 0)
				i2c_pin_reset(Aux2_LAMP);
			else
				i2c_pin_set(Aux2_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@1 sd
		case 9:
			if(en == 0)
				i2c_pin_reset(SD3_LAMP);
			else
				i2c_pin_set(SD3_LAMP);
			out_bytes_inversion2();
			PCA9535_IO_out(1,0);
			break;
		//@2 sd
		case 10:
			if(en == 0)
				i2c_pin_reset(SD1_LAMP);
			else
				i2c_pin_set(SD1_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		//@3 sd
		case 11:
			if(en == 0)
				i2c_pin_reset(SD2_LAMP);
			else
				i2c_pin_set(SD2_LAMP);
			out_bytes_inversion1();
			PCA9535_IO_out(0,0);
			break;
		default:
			break;
	}
}

void HUB3_USB2_5V_Set(int8_t en)
{
	if(en == 0)
		i2c_pin_reset(HUB3_USB2_5V_EN);
	else
		i2c_pin_set(HUB3_USB2_5V_EN);
	out_bytes_inversion1();
	PCA9535_IO_out(0,0);
}

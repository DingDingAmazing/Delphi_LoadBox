#include "i2c_app.h"
uint32_t i2c_overtime;
uint8_t config_bytes[2] = {0x00, 0x00};
uint8_t outbytes[2] = {0xff, 0xff};
uint8_t outbytes_01[2] = {0xfe, 0xfe};
uint8_t outbytes_02[2] = {0xfc, 0xfc};
uint8_t outbytes_03[1] = {0xf0};
I2C_output_register I2C_IO_output;
flag_control_on flag_on_record = {255, 255, 255, 255, 255, 255, 255};

void init_out_bytes(void)
{
	I2C_IO_output.device_1st[0] = 0xC3;
	I2C_IO_output.device_1st[1] = 0x00;
	I2C_IO_output.device_2nd[0] = 0x00;
	I2C_IO_output.device_2nd[1] = 0x0C;
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
	uint8_t write_num;
	i2c_overtime = I2C_TimeOut;
	
/**
	judge whether or not i2c is busy
	**/
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET)
	{
		if((i2c_overtime--) == 0)
		{
			uart_send_word("\r\ni2c is busy");///debug uart info
			return I2C_Fail;
		}
	}
//	uart_send_word("\r\ni2c is free");///debug uart info
	
/**
	send a start signal then followed a byte writed to the slave device address
	**/
	I2C_TransferHandling(I2C2, driver_addr, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXIS) == RESET)
  {
    if((i2c_overtime--) == 0)
    {
			uart_send_word("\r\ni2c txis is wrong");///debug uart info
      return I2C_Fail;
    }
  }
//	uart_send_word("\r\ni2c start is ok");///debug uart info
	
/**
	write address/command byte to control register
	**/
	I2C_SendData(I2C2, reg_addr);
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TCR) == RESET)
  {
    if((i2c_overtime--) == 0)
    {
			uart_send_word("\r\ni2c tcr is wrong");///debug uart info
      return I2C_Fail;
    }
  }
//	uart_send_word("\r\ni2c write reg's address is ok");///debug uart info
	
/**
	write bytes to data register
	**/
	I2C_TransferHandling(I2C2, driver_addr, num_bytes, I2C_AutoEnd_Mode, I2C_No_StartStop);
	for(write_num = 0; write_num < num_bytes; write_num++)
	{
		i2c_overtime = I2C_TimeOut;
		while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXIS) == RESET)
		{
    if((i2c_overtime--) == 0)
			{
				uart_send_word("\r\ni2c txis2 is wrong");///debug uart info
				return I2C_Fail;
			}
		}
		I2C_SendData(I2C2, write_byte[write_num]);
//		I2C_SendData(I2C2, *write_byte);///another sending way
//		write_byte++;///another sending way
	}
//	uart_send_word("\r\ni2c write data is ok");///debug uart info
	
/**
	check bus stop stastus
	**/
	i2c_overtime = I2C_TimeOut;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF) == RESET)
	{
    if((i2c_overtime--) == 0)
		{
			uart_send_word("\r\ni2c stopf is wrong");
      return I2C_Fail;
		}
	}
		
	return I2C_Ok;
}

/**
	write bytes to configuration register
	**/
uint8_t PCA9535_config_register(uint8_t driver_addr)
{
	if(I2C2_Write_NByte(driver_addr, 0x06, 2, config_bytes) == I2C_Fail)
	{	return 1;}

	return 0;
}

/**
	write bytes to output port register
	**/
uint8_t PCA9535_output_register(uint8_t device_index)
{
	if(device_index == 0)
	{
		if(I2C2_Write_NByte(PCA9535_1st_Address, 0x02, 2, I2C_IO_output.device_1st) == I2C_Fail)
		{	return 1;}

	}
	else
	{
		if(I2C2_Write_NByte(PCA9535_2nd_Address, 0x02, 2, I2C_IO_output.device_2nd) == I2C_Fail)
		{	return 1;}

	}
	
	return 0;
}

void i2c_error(void)
{
	uart_send_word("iic2 has a error");
}

void i2c_pin_set(uint16_t idx)
{
	switch(idx>>8)
	{
		case 0:
			if((uint8_t)idx == 1 || (uint8_t)idx == 2 || (uint8_t)idx == 4 || (uint8_t)idx == 8)
				I2C_IO_output.device_1st[0] &= ~(uint8_t)idx;
			else
				I2C_IO_output.device_1st[0] |= (uint8_t)idx;
			break;
		case 1:
			I2C_IO_output.device_1st[1] |= (uint8_t)idx;
			break;
		case 2:
			I2C_IO_output.device_2nd[0] |= (uint8_t)idx;
			break;
		case 3:
			if(((uint8_t)idx == 1<<2) || ((uint8_t)idx == 1<<3))
				I2C_IO_output.device_2nd[1] &= ~(uint8_t)idx;
			else
				I2C_IO_output.device_2nd[1] |= (uint8_t)idx;
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
			if((uint8_t)idx == 1 || (uint8_t)idx == 2 || (uint8_t)idx == 4 || (uint8_t)idx == 8)
				I2C_IO_output.device_1st[0] |= (uint8_t)idx;
			else
				I2C_IO_output.device_1st[0] &= ~(uint8_t)idx;
			break;
		case 1:
			I2C_IO_output.device_1st[1] &= ~(uint8_t)idx;
			break;
		case 2:
			I2C_IO_output.device_2nd[0] &= ~(uint8_t)idx;
			break;
		case 3:
			if(((uint8_t)idx == 1<<2) || ((uint8_t)idx == 1<<3))
				I2C_IO_output.device_2nd[1] |= (uint8_t)idx;
			else
				I2C_IO_output.device_2nd[1] &= ~(uint8_t)idx;
			break;
		default:
			break;
	}
}

void i2c_pin_init(void)
{
	I2C2_GPIO_Init();
	uart_send_word("\r\ni2c gpio is ok");
	I2C_Config_Init();
	uart_send_word("\r\ni2c config is ok");
//	I2C2_Write_NByte(0x40, 0x06, 2, config_bytes);
//	I2C2_Write_NByte(0x40, 0x02, 2, outbytes);
//	I2C2_Write_NByte(0x48, 0x06, 2, config_bytes);
//	I2C2_Write_NByte(0x48, 0x02, 2, outbytes);
//	I2C2_Write_NByte(0x40, 0x06, 2, config_bytes);
//	I2C2_Write_NByte(0x40, 0x02, 1, outbytes_03);//是按bit0-bit7排列扩展口的
	init_out_bytes();
	PCA9535_config_register(PCA9535_1st_Address);
	PCA9535_output_register(0);
	PCA9535_config_register(PCA9535_2nd_Address);
	PCA9535_output_register(1);
}

void USB_HUB3_D_SEL_EN(uint8_t en)
{
	if(en == 0)
		i2c_pin_reset(USB_HUB3_D_SEL);
	else
		i2c_pin_set(USB_HUB3_D_SEL);
	
	PCA9535_output_register(0);
}

void SD1_Switch(uint8_t en)
{
	if(en == 0)
	{
		i2c_pin_reset(SD1_EN);
		flag_on_record.sd_on_idx = 255;
		LAMP_Switch(10, 0);
	}
	else
	{
		i2c_pin_set(SD1_EN);
		flag_on_record.sd_on_idx = 2;
		LAMP_Switch(10, 1);
	}
	
	PCA9535_output_register(0);
}

void SD2_Switch(uint8_t en)
{
	if(en == 0)
	{
		i2c_pin_reset(SD2_EN);
		flag_on_record.sd_on_idx = 255;
		LAMP_Switch(11, 0);
	}
	else
	{
		i2c_pin_set(SD2_EN);
		flag_on_record.sd_on_idx = 3;
		LAMP_Switch(11, 1);
	}
	
	PCA9535_output_register(0);
}

void SD3_Switch(uint8_t en)
{
	if(en == 0)
	{
		i2c_pin_reset(SD3_EN);
		flag_on_record.sd_on_idx = 255;
		LAMP_Switch(9, 0);
	}
	else
	{
		i2c_pin_set(SD3_EN);
		flag_on_record.sd_on_idx = 1;
		LAMP_Switch(9, 1);
	}
	
	PCA9535_output_register(1);
}

void Aux_Switch(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 1:
			if(en == 0)
			{
				i2c_pin_reset(Aux3_EN);
				flag_on_record.aux_on_idx = 255;
				LAMP_Switch(6, 0);
			}
			else
			{
				i2c_pin_set(Aux3_EN);
				flag_on_record.aux_on_idx = 1;
				LAMP_Switch(6, 1);
			}
			PCA9535_output_register(1);
			break;
		case 2:
			if(en == 0)
			{
				i2c_pin_reset(Aux1_EN);
				flag_on_record.aux_on_idx = 255;
				LAMP_Switch(7, 0);
			}
			else
			{
				i2c_pin_set(Aux1_EN);
				flag_on_record.aux_on_idx = 2;
				LAMP_Switch(7, 1);
			}
			PCA9535_output_register(0);
			break;
		case 3:
			if(en == 0)
			{
				i2c_pin_reset(Aux2_EN);
				flag_on_record.aux_on_idx = 255;
				LAMP_Switch(8, 0);
			}
			else
			{
				i2c_pin_set(Aux2_EN);
				flag_on_record.aux_on_idx = 3;
				LAMP_Switch(8, 1);
			}
			PCA9535_output_register(0);
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
|aux |1        |aux1|(6,x)|
|aux |2        |aux2|(7,x)|
|aux |3        |aux3|(8,x)|
|sd  |1        |sd1|(9,x)|
|sd  |2        |sd2|(10,x)|
|sd  |3        |sd3|(11,x)|
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
			PCA9535_output_register(1);
			break;
		//@1.2 5v
		case 1:
			if(en == 0)
				i2c_pin_reset(HUB3_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB3_USB2_5V_LAMP);
			PCA9535_output_register(1);
			break;
		//@2.1 5v
		case 2:
			if(en == 0)
				i2c_pin_reset(HUB1_USB1_5V_LAMP);
			else
				i2c_pin_set(HUB1_USB1_5V_LAMP);
			PCA9535_output_register(0);
			break;
		//@2.2 5v
		case 3:
			if(en == 0)
				i2c_pin_reset(HUB1_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB1_USB2_5V_LAMP);
			PCA9535_output_register(0);
			break;
		//@3.1 5v
		case 4:
			if(en == 0)
				i2c_pin_reset(HUB2_USB1_5V_LAMP);
			else
				i2c_pin_set(HUB2_USB1_5V_LAMP);
			PCA9535_output_register(0);
			break;
		//@3.2 5v
		case 5:
			if(en == 0)
				i2c_pin_reset(HUB2_USB2_5V_LAMP);
			else
				i2c_pin_set(HUB2_USB2_5V_LAMP);
			PCA9535_output_register(0);
			break;
		//@1 aux
		case 6:
			if(en == 0)
				i2c_pin_reset(Aux3_LAMP);
			else
				i2c_pin_set(Aux3_LAMP);
			PCA9535_output_register(1);
			break;
		//@2 aux
		case 7:
			if(en == 0)
				i2c_pin_reset(Aux1_LAMP);
			else
				i2c_pin_set(Aux3_LAMP);
			PCA9535_output_register(0);
			break;
		//@3 aux
		case 8:
			if(en == 0)
				i2c_pin_reset(Aux2_LAMP);
			else
				i2c_pin_set(Aux2_LAMP);
			PCA9535_output_register(0);
			break;
		//@1 sd
		case 9:
			if(en == 0)
				i2c_pin_reset(SD3_LAMP);
			else
				i2c_pin_set(SD3_LAMP);
			PCA9535_output_register(1);
			break;
		//@2 sd
		case 10:
			if(en == 0)
				i2c_pin_reset(SD1_LAMP);
			else
				i2c_pin_set(SD1_LAMP);
			PCA9535_output_register(0);
			break;
		//@3 sd
		case 11:
			if(en == 0)
				i2c_pin_reset(SD2_LAMP);
			else
				i2c_pin_set(SD2_LAMP);
			PCA9535_output_register(0);
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
	PCA9535_output_register(0);
}

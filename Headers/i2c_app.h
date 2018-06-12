#ifndef I2C_APP_H
#define I2C_APP_H

#include "i2c_driver.h"

#define PCA9535_1st_Address ((uint8_t)(0x20<<1))
#define PCA9535_2nd_Address ((uint8_t)(0x24<<1))
#define I2C_TimeOut         ((uint32_t)0x1000)

#define Make_PCA_IO(group, offset) (uint16_t)((uint16_t)(group<<8) + (uint16_t)(1<<offset))
#define Aux1_LAMP           Make_PCA_IO(0,0)
#define SD1_LAMP						Make_PCA_IO(0,1)
#define Aux2_EN							Make_PCA_IO(0,2)
#define SD2_EN							Make_PCA_IO(0,3)
#define HUB2_USB1_5V_LAMP		Make_PCA_IO(0,4)
#define HUB2_USB2_5V_LAMP		Make_PCA_IO(0,5)
#define Aux2_LAMP						Make_PCA_IO(0,6)
#define SD2_LAMP						Make_PCA_IO(0,7)

#define IO5_detect					Make_PCA_IO(1,0)
#define IO4_detect					Make_PCA_IO(1,1)
#define HUB1_USB2_5V_LAMP		Make_PCA_IO(1,2)
#define HUB1_USB1_5V_LAMP		Make_PCA_IO(1,3)
#define SD1_EN							Make_PCA_IO(1,4)
#define Aux1_EN							Make_PCA_IO(1,5)
#define HUB3_USB2_5V_EN			Make_PCA_IO(1,6)
#define USB_HUB3_D_SEL			Make_PCA_IO(1,7)

#define IO1_detect					Make_PCA_IO(2,0)
#define IO2_detect					Make_PCA_IO(2,1)
#define IO3_detect					Make_PCA_IO(2,2)
#define IO8_detect					Make_PCA_IO(2,3)
#define IO9_detect					Make_PCA_IO(2,4)

#define IO7_detect					Make_PCA_IO(3,0)
#define IO6_detect					Make_PCA_IO(3,1)
#define SD3_LAMP						Make_PCA_IO(3,2)
#define Aux3_LAMP						Make_PCA_IO(3,3)
#define HUB3_USB2_5V_LAMP		Make_PCA_IO(3,4)
#define HUB3_USB1_5V_LAMP		Make_PCA_IO(3,5)
#define SD3_EN							Make_PCA_IO(3,6)
#define Aux3_EN							Make_PCA_IO(3,7)


typedef enum
{
	I2C_Ok   = 0,
	I2C_Fail = 1
}I2C_Status;

typedef struct
{
	uint8_t device_1st[2];
	uint8_t device_2nd[2];
}I2C_output_register;

typedef struct
{
	uint8_t hub_on_idx;
	uint8_t usb_on_group1;
	uint8_t usb_on_group2;
	uint8_t usb1_on_idx;
	uint8_t usb2_on_idx;
	uint8_t aux_on_idx;
	uint8_t sd_on_idx;
}flag_control_on;

extern void i2c_error(void);
extern void USB_HUB3_D_SEL_EN(uint8_t key);
extern void SD1_Switch(uint8_t en);
extern void SD2_Switch(uint8_t en);
extern void SD3_Switch(uint8_t en);
extern void i2c_pin_init(void);
extern void Aux_Switch(uint8_t num, uint8_t en);
extern void LAMP_Switch(int8_t num, int8_t en);
extern void HUB3_USB2_5V_Set(int8_t en);
extern void Uart_send_feckback(void);
extern void uart_send_word(char *n);
extern flag_control_on flag_on_record;
#endif

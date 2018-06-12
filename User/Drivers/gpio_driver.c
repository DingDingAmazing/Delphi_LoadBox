#include "gpio_driver.h"
 
/*
第二次hardware PCB改版，片上脚位变化：
PB12-----SD_HUB1_C_SEL	->	5V_HUB1_USB1_EN
PA11-----SD_HUB1_D_SEL	->	5V_HUB1_USB2_EN
PB8------SD_HUB2_D_SEL	->	5V_HUB2_USB1_EN
PB9------SD_HUB2_C_SEL	->	5V_HUB2_USB2_EN
PA1------SD_HUB3_D_SEL	->	5V_HUB3_USB1_EN
PB10-----USB_HUB3_D_SEL	->	I2C_CLK_SW
PB11-----SD_HUB3_C_SEL	->	I2C_DAT_SW
*/


#define IOBUS_GPIO_RCC     (RCC_AHBPeriph_GPIOA |RCC_AHBPeriph_GPIOB |RCC_AHBPeriph_GPIOC |RCC_AHBPeriph_GPIOD)

//---------------All control GPIO define---------------//
//---------------------main board
//1to2 switch
#define USB_A_SEL          GPIO_Pin_3     //PC3
//1th 1to4 switch
#define B14_SAI            GPIO_Pin_1     //PC1
#define B14_SAO            GPIO_Pin_0     //PC0
#define B14_SBI            GPIO_Pin_2     //PC2
#define B14_SBO            GPIO_Pin_0     //PA0
//2rd 1to4 switch
#define B58_SAI            GPIO_Pin_12    //PA12
#define B58_SAO            GPIO_Pin_13    //PC13
#define B58_SBI            GPIO_Pin_14    //PC14
#define B58_SBO            GPIO_Pin_15    //PC15

#define USB_A_SEL_HIGH()     GPIO_SetBits(GPIOC, USB_A_SEL)
#define USB_A_SEL_LOW()      GPIO_ResetBits(GPIOC, USB_A_SEL)

#define B14_SAI_HIGH()       GPIO_SetBits(GPIOC, B14_SAI)
#define B14_SAI_LOW()        GPIO_ResetBits(GPIOC, B14_SAI)

#define B14_SAO_HIGH()       GPIO_SetBits(GPIOC, B14_SAO)
#define B14_SAO_LOW()        GPIO_ResetBits(GPIOC, B14_SAO)

#define B14_SBI_HIGH()       GPIO_SetBits(GPIOC, B14_SBI)
#define B14_SBI_LOW()        GPIO_ResetBits(GPIOC, B14_SBI)

#define B14_SBO_HIGH()       GPIO_SetBits(GPIOA, B14_SBO)
#define B14_SBO_LOW()        GPIO_ResetBits(GPIOA, B14_SBO)

#define B58_SAI_HIGH()       GPIO_SetBits(GPIOA, B58_SAI)
#define B58_SAI_LOW()        GPIO_ResetBits(GPIOA, B58_SAI)

#define B58_SAO_HIGH()       GPIO_SetBits(GPIOC, B58_SAO)
#define B58_SAO_LOW()        GPIO_ResetBits(GPIOC, B58_SAO)

#define B58_SBI_HIGH()       GPIO_SetBits(GPIOC, B58_SBI)
#define B58_SBI_LOW()        GPIO_ResetBits(GPIOC, B58_SBI)

#define B58_SBO_HIGH()       GPIO_SetBits(GPIOC, B58_SBO)
#define B58_SBO_LOW()        GPIO_ResetBits(GPIOC, B58_SBO)

//-----------------------01 sub board
//1st 1to2 USB switch
#define USB_HUB1_C_SEL     GPIO_Pin_2     //PA2
//1st 1to4 USB switch
#define USB_HUB1_E_SAI     GPIO_Pin_9     //PC9
#define USB_HUB1_E_SAO     GPIO_Pin_8     //PC8
#define USB_HUB1_E_SBI     GPIO_Pin_8     //PA8
#define USB_HUB1_E_SBO     GPIO_Pin_3     //PA3
//2rd 1to2 USB switch
#define USB_HUB1_D_SEL     GPIO_Pin_13    //PB13
//2rd 1to4 USB switch
#define USB_HUB1_F_SAI     GPIO_Pin_6     //PC6
#define USB_HUB1_F_SAO     GPIO_Pin_7     //PC7
#define USB_HUB1_F_SBI     GPIO_Pin_15    //PB15
#define USB_HUB1_F_SBO     GPIO_Pin_14    //PB14

//usb 5V power
#define HUB1_USB1_5V_EN      GPIO_Pin_12    //PB12
#define HUB1_USB2_5V_EN      GPIO_Pin_11    //PA11

#define USB_HUB1_C_SEL_HIGH()     GPIO_SetBits(GPIOA, USB_HUB1_C_SEL)
#define USB_HUB1_C_SEL_LOW()      GPIO_ResetBits(GPIOA, USB_HUB1_C_SEL)

#define USB_HUB1_E_SAI_HIGH()     GPIO_SetBits(GPIOC, USB_HUB1_E_SAI)
#define USB_HUB1_E_SAI_LOW()      GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI)

#define USB_HUB1_E_SAO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB1_E_SAO)
#define USB_HUB1_E_SAO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB1_E_SAO)

#define USB_HUB1_E_SBI_HIGH()     GPIO_SetBits(GPIOA, USB_HUB1_E_SBI)
#define USB_HUB1_E_SBI_LOW()      GPIO_ResetBits(GPIOA, USB_HUB1_E_SBI)

#define USB_HUB1_E_SBO_HIGH()     GPIO_SetBits(GPIOA, USB_HUB1_E_SBO)
#define USB_HUB1_E_SBO_LOW()      GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO)

#define USB_HUB1_D_SEL_HIGH()     GPIO_SetBits(GPIOB, USB_HUB1_D_SEL)
#define USB_HUB1_D_SEL_LOW()      GPIO_ResetBits(GPIOB, USB_HUB1_D_SEL)

#define USB_HUB1_F_SAI_HIGH()     GPIO_SetBits(GPIOC, USB_HUB1_F_SAI)
#define USB_HUB1_F_SAI_LOW()      GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI)

#define USB_HUB1_F_SAO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB1_F_SAO)
#define USB_HUB1_F_SAO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO)

#define USB_HUB1_F_SBI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB1_F_SBI)
#define USB_HUB1_F_SBI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB1_F_SBI)

#define USB_HUB1_F_SBO_HIGH()     GPIO_SetBits(GPIOB, USB_HUB1_F_SBO)
#define USB_HUB1_F_SBO_LOW()      GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO)

#define HUB1_USB1_5V_EN_HIGH()     GPIO_SetBits(GPIOB, HUB1_USB1_5V_EN)
#define HUB1_USB1_5V_EN_LOW()      GPIO_ResetBits(GPIOB, HUB1_USB1_5V_EN)

#define HUB1_USB2_5V_EN_HIGH()     GPIO_SetBits(GPIOA, HUB1_USB2_5V_EN)
#define HUB1_USB2_5V_EN_LOW()      GPIO_ResetBits(GPIOA, HUB1_USB2_5V_EN)

//-----------------------02 sub board
//1st 1to2 USB switch
#define USB_HUB2_C_SEL     GPIO_Pin_7     //PB7
//1st 1to4 USB switch
#define USB_HUB2_E_SAI     GPIO_Pin_4     //PB4
#define USB_HUB2_E_SAO     GPIO_Pin_3     //PB3
#define USB_HUB2_E_SBI     GPIO_Pin_5     //PB5
#define USB_HUB2_E_SBO     GPIO_Pin_6     //PB6
//2rd 1to2 USB switch
#define USB_HUB2_D_SEL     GPIO_Pin_15    //PA15
//2rd 1to4 USB switch
#define USB_HUB2_F_SAI     GPIO_Pin_12    //PC12
#define USB_HUB2_F_SAO     GPIO_Pin_2     //PD2
#define USB_HUB2_F_SBI     GPIO_Pin_11    //PC11
#define USB_HUB2_F_SBO     GPIO_Pin_10    //PC10
//usb 5v power
#define HUB2_USB2_5V_EN    GPIO_Pin_9     //PB9
#define HUB2_USB1_5V_EN    GPIO_Pin_8     //PB8

#define USB_HUB2_C_SEL_HIGH()     GPIO_SetBits(GPIOB, USB_HUB2_C_SEL)
#define USB_HUB2_C_SEL_LOW()      GPIO_ResetBits(GPIOB, USB_HUB2_C_SEL)

#define USB_HUB2_E_SAI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB2_E_SAI)
#define USB_HUB2_E_SAI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI)

#define USB_HUB2_E_SAO_HIGH()     GPIO_SetBits(GPIOB, USB_HUB2_E_SAO)
#define USB_HUB2_E_SAO_LOW()      GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO)

#define USB_HUB2_E_SBI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB2_E_SBI)
#define USB_HUB2_E_SBI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB2_E_SBI)

#define USB_HUB2_E_SBO_HIGH()     GPIO_SetBits(GPIOB, USB_HUB2_E_SBO)
#define USB_HUB2_E_SBO_LOW()      GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO)

#define USB_HUB2_D_SEL_HIGH()     GPIO_SetBits(GPIOA, USB_HUB2_D_SEL)
#define USB_HUB2_D_SEL_LOW()      GPIO_ResetBits(GPIOA, USB_HUB2_D_SEL)

#define USB_HUB2_F_SAI_HIGH()     GPIO_SetBits(GPIOC, USB_HUB2_F_SAI)
#define USB_HUB2_F_SAI_LOW()      GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI)

#define USB_HUB2_F_SAO_HIGH()     GPIO_SetBits(GPIOD, USB_HUB2_F_SAO)
#define USB_HUB2_F_SAO_LOW()      GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO)

#define USB_HUB2_F_SBI_HIGH()     GPIO_SetBits(GPIOC, USB_HUB2_F_SBI)
#define USB_HUB2_F_SBI_LOW()      GPIO_ResetBits(GPIOC, USB_HUB2_F_SBI)

#define USB_HUB2_F_SBO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB2_F_SBO)
#define USB_HUB2_F_SBO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO)

#define HUB2_USB2_5V_EN_HIGH()     GPIO_SetBits(GPIOB, HUB2_USB2_5V_EN)
#define HUB2_USB2_5V_EN_LOW()      GPIO_ResetBits(GPIOB, HUB2_USB2_5V_EN)

#define HUB2_USB1_5V_EN_HIGH()     GPIO_SetBits(GPIOB, HUB2_USB1_5V_EN)
#define HUB2_USB1_5V_EN_LOW()      GPIO_ResetBits(GPIOB, HUB2_USB1_5V_EN)

//-----------------------03 sub board
//1st 1to2 USB switch
#define USB_HUB3_C_SEL     GPIO_Pin_4     //PA4
//1st 1to4 USB switch
#define USB_HUB3_E_SAI     GPIO_Pin_7     //PA7
#define USB_HUB3_E_SAO     GPIO_Pin_4     //PC4
#define USB_HUB3_E_SBI     GPIO_Pin_6     //PA6
#define USB_HUB3_E_SBO     GPIO_Pin_5     //PA5

//2rd 1to2 USB switch
//Log: USB_HUB3_D_SEL removed

//2rd 1to4 USB switch
#define USB_HUB3_F_SAI     GPIO_Pin_0     //PB0
#define USB_HUB3_F_SAO     GPIO_Pin_5     //PC5
#define USB_HUB3_F_SBI     GPIO_Pin_1     //PB1
#define USB_HUB3_F_SBO     GPIO_Pin_2     //PB2
//usb 5v power
#define HUB3_USB1_5V_EN    GPIO_Pin_1     //PA1

#define USB_HUB3_C_SEL_HIGH()     GPIO_SetBits(GPIOA, USB_HUB3_C_SEL)
#define USB_HUB3_C_SEL_LOW()      GPIO_ResetBits(GPIOA, USB_HUB3_C_SEL)

#define USB_HUB3_E_SAI_HIGH()     GPIO_SetBits(GPIOA, USB_HUB3_E_SAI)
#define USB_HUB3_E_SAI_LOW()      GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI)

#define USB_HUB3_E_SAO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB3_E_SAO)
#define USB_HUB3_E_SAO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO)

#define USB_HUB3_E_SBI_HIGH()     GPIO_SetBits(GPIOA, USB_HUB3_E_SBI)
#define USB_HUB3_E_SBI_LOW()      GPIO_ResetBits(GPIOA, USB_HUB3_E_SBI)

#define USB_HUB3_E_SBO_HIGH()     GPIO_SetBits(GPIOA, USB_HUB3_E_SBO)
#define USB_HUB3_E_SBO_LOW()      GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO)

//Log: USB_HUB3_D_SEL removed

#define USB_HUB3_F_SAI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SAI)
#define USB_HUB3_F_SAI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI)

#define USB_HUB3_F_SAO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB3_F_SAO)
#define USB_HUB3_F_SAO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO)

#define USB_HUB3_F_SBI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SBI)
#define USB_HUB3_F_SBI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI)

#define USB_HUB3_F_SBO_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SBO)
#define USB_HUB3_F_SBO_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO)

#define HUB3_USB1_5V_EN_HIGH()     GPIO_SetBits(GPIOA, HUB3_USB1_5V_EN)
#define HUB3_USB1_5V_EN_LOW()      GPIO_ResetBits(GPIOA, HUB3_USB1_5V_EN)


void test_gpio()
{
	GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
}

//////////////////////////////////////////////////////////////
static void RCC_Configuration(void)
{
  RCC_AHBPeriphClockCmd(IOBUS_GPIO_RCC, ENABLE);
}

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = B14_SBO | B58_SAI | USB_HUB1_C_SEL | USB_HUB1_E_SBI | USB_HUB1_E_SBO | HUB1_USB2_5V_EN |
                              	USB_HUB2_D_SEL | USB_HUB3_C_SEL | USB_HUB3_E_SAI | USB_HUB3_E_SBI | USB_HUB3_E_SBO |
                              	HUB3_USB1_5V_EN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//Log: USB_HUB3_D_SEL removed
	GPIO_InitStructure.GPIO_Pin = USB_HUB1_D_SEL | USB_HUB1_F_SBI | USB_HUB1_F_SBO | HUB1_USB1_5V_EN | USB_HUB2_C_SEL | 
	                              USB_HUB2_E_SAI | USB_HUB2_E_SAO | USB_HUB2_E_SBI | USB_HUB2_E_SBO | HUB2_USB2_5V_EN |
	                              HUB2_USB1_5V_EN | USB_HUB3_F_SAI | USB_HUB3_F_SBI | USB_HUB3_F_SBO;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USB_A_SEL | B14_SAI | B14_SAO | B14_SBI | B58_SAO | B58_SBI | B58_SBO | USB_HUB1_E_SAI |
	                              USB_HUB1_E_SAO | USB_HUB1_F_SAI | USB_HUB1_F_SAO | USB_HUB2_F_SAI | USB_HUB2_F_SBI |
	                              USB_HUB2_F_SBO | USB_HUB3_E_SAO | USB_HUB3_F_SAO;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USB_HUB2_F_SAO;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}

//truth table:
//TS3USB30
//------S-----OE-----FUNCTION
//      X     H      Disconnect
//      L     L      D=D1
//------H-----L------D=D2

//TXS02612
//------S-----CLKB0-----CLKB1-----OPERATION
//      L     Active    Low       CLKA to CLKB0
//------H-----Low-------Active----CLKA to CLKB1

//------S-----DATxB0/CMDxB0--------------------------DATxB1/CMDxB1----------------------------------OPERATION
//      L     Active                                 Disabled, pulled to VCCB1 through 70k          DATxA to DATxB0, CMDxA to CMDxB0
//------H-----Disabled, pulled to VCCB0 through 70k--Active-----------------------------------------DATxA to DATxB1, CMDxA to CMDxB1

//TD3DS10224 + CD74HC154M
//------SAI,SAO,SBI,SBO-----OUTA0-----OUTA1-----OUTB0-----OUTB1------LED=1
//      0000                INB       -         INA       -
//      0001                INB       -         -         INA
//      0010                INB       -         INB       -
//      0011                INB       -         -         INB
//      0100                -         INB       INA       -  --------J6/J10----HUB3/HUB7
//      0101                -         INB       -         INA--------J7/J11----HUB4/HUB8
//      0110                -         INB       INB       -
//      0111                -         INB       -         INB
//      1010                INA       -         INB       -
//      1011                INA       -         -         INB--------J5/J9-----HUB1/HUB5
//      1110                -         INA       INB       -  --------J4/J8-----HUB2/HUB6
//      1111                -         INA       -         INB
void iobus_main_board_init()
{
	GPIO_ResetBits(GPIOC, USB_A_SEL);//1st 1to4 chip be choosed
	GPIO_ResetBits(GPIOC, B14_SAI);//HUB 01-04 be deactived
	GPIO_ResetBits(GPIOC, B14_SAO);
	GPIO_SetBits(GPIOC, B14_SBI);
	GPIO_ResetBits(GPIOA, B14_SBO);
	
	GPIO_ResetBits(GPIOA, B58_SAI);//HUB 05-08 be deactived
	GPIO_ResetBits(GPIOC, B58_SAO);
	GPIO_SetBits(GPIOC, B58_SBI);
	GPIO_ResetBits(GPIOC, B58_SBO);
}

void iobus_sub_board01_init()
{
	GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI);//USB 01-04 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB1_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO);
	
	GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);//USB 06-09 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);	
	//-----------------disable usb 5v-----------------//
	GPIO_ResetBits(GPIOB, HUB1_USB1_5V_EN);
	GPIO_ResetBits(GPIOA, HUB1_USB2_5V_EN);
}

void iobus_sub_board02_init()
{
	GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);//USB 11-14 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO);
	GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
	
	GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);//USB 16-19 be deactived
	GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
	GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
	//-----------------disable usb 5v-----------------//
	GPIO_ResetBits(GPIOB, HUB2_USB2_5V_EN);
	GPIO_ResetBits(GPIOB, HUB2_USB1_5V_EN);
}

void iobus_sub_board03_init()
{
	GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);//1st 1to4 chip be choosed, USB 25 be deactived
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);//USB 21-24 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
	
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
	USB_HUB3_D_SEL_EN(1);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);//USB 26-29 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
	//-----------------disable usb 5v-----------------//
//此处添加一个5v控制
	GPIO_ResetBits(GPIOA, HUB3_USB1_5V_EN);
}

void iobus_init(void)
{
  RCC_Configuration();
  GPIO_Configuration();
	iobus_main_board_init();
	iobus_sub_board01_init();
	iobus_sub_board02_init();
	iobus_sub_board03_init();
	HUB1_USB1_5V_EN_LOW();
	HUB1_USB2_5V_EN_LOW();
	HUB2_USB1_5V_EN_LOW();
	HUB2_USB2_5V_EN_LOW();
	HUB3_USB1_5V_EN_LOW();
}

void HUB_Half_01_deactive()
{
	GPIO_SetBits(GPIOC, USB_A_SEL);
	GPIO_ResetBits(GPIOC, B14_SAI);//HUB 01-04 be deactived
	GPIO_ResetBits(GPIOC, B14_SAO);
	GPIO_SetBits(GPIOC, B14_SBI);
	GPIO_ResetBits(GPIOA, B14_SBO);
}

void HUB_Half_02_deactive()
{
	GPIO_ResetBits(GPIOC, USB_A_SEL);
	GPIO_ResetBits(GPIOA, B58_SAI);//HUB 05-08 be deactived
	GPIO_ResetBits(GPIOC, B58_SAO);
	GPIO_SetBits(GPIOC, B58_SBI);
	GPIO_ResetBits(GPIOC, B58_SBO);
}

void HUB_Enable(uint8_t n)
{
	switch(n)
	{
		case 2:
			HUB_Half_02_deactive();
			GPIO_SetBits(GPIOC, B14_SAI);
			GPIO_ResetBits(GPIOC, B14_SAO);
			GPIO_SetBits(GPIOC, B14_SBI);
			GPIO_SetBits(GPIOA, B14_SBO);
			flag_on_record.hub_on_idx = 2;
			break;
		case 1:
			HUB_Half_02_deactive();
			GPIO_SetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_SetBits(GPIOC, B14_SBI);
			GPIO_ResetBits(GPIOA, B14_SBO);
			flag_on_record.hub_on_idx = 1;
			break;
		case 3:
			HUB_Half_02_deactive();
			GPIO_ResetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_ResetBits(GPIOC, B14_SBI);
			GPIO_ResetBits(GPIOA, B14_SBO);
			flag_on_record.hub_on_idx = 3;
		break;
		case 4:
			HUB_Half_02_deactive();
			GPIO_ResetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_ResetBits(GPIOC, B14_SBI);
			GPIO_SetBits(GPIOA, B14_SBO);
			flag_on_record.hub_on_idx = 4;
			break;
		case 8:
			HUB_Half_01_deactive();
			GPIO_SetBits(GPIOA, B58_SAI);
			GPIO_ResetBits(GPIOC, B58_SAO);
			GPIO_SetBits(GPIOC, B58_SBI);
			GPIO_SetBits(GPIOC, B58_SBO);
			flag_on_record.hub_on_idx = 8;
			break;
		case 7:
			HUB_Half_01_deactive();
			GPIO_SetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_SetBits(GPIOC, B58_SBI);
			GPIO_ResetBits(GPIOC, B58_SBO);
			flag_on_record.hub_on_idx = 7;
			break;
		case 5:
			HUB_Half_01_deactive();
			GPIO_ResetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_ResetBits(GPIOC, B58_SBI);
			GPIO_ResetBits(GPIOC, B58_SBO);
			flag_on_record.hub_on_idx = 5;
			break;
		case 6:
			HUB_Half_01_deactive();
			GPIO_ResetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_ResetBits(GPIOC, B58_SBI);
			GPIO_SetBits(GPIOC, B58_SBO);
			flag_on_record.hub_on_idx = 6;
			break;
		default:
			break;
	}
}

void HUB_Disable()
{
	iobus_main_board_init();
	flag_on_record.hub_on_idx = 255;
}

void USB_Enable_1_5(uint8_t n)
{
	switch(n)
	{
		case 3:
			GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
			GPIO_SetBits(GPIOC, USB_HUB1_E_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB1_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB1_E_SBI);
			GPIO_SetBits(GPIOA, USB_HUB1_E_SBO);
			break;
		case 4:
			GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
			GPIO_SetBits(GPIOC, USB_HUB1_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB1_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO);
			break;
		case 2:
			GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_E_SAO);
			GPIO_ResetBits(GPIOA, USB_HUB1_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO);
			break;
		case 1:
			GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_E_SAO);
			GPIO_ResetBits(GPIOA, USB_HUB1_E_SBI);
			GPIO_SetBits(GPIOA, USB_HUB1_E_SBO);
			break;
		case 5:
			GPIO_ResetBits(GPIOA, USB_HUB1_C_SEL);
			GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI);//USB 01-04 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB1_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO);
			break;
		default:
			break;
	}
}

void USB_Disable_1_5(void)
{
	GPIO_SetBits(GPIOA, USB_HUB1_C_SEL);//1st 1to4 chip be choosed, USB 05 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_E_SAI);//USB 01-04 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB1_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB1_E_SBO);
}

/**
	idx on schem
**/
void USB_Enable_6_10(uint8_t n)
{
	switch(n)
	{
		case 8:
			GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
			GPIO_SetBits(GPIOC, USB_HUB1_F_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB1_F_SBO);
			break;
		case 9:
			GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
			GPIO_SetBits(GPIOC, USB_HUB1_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);
			break;
		case 7:
			GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB1_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);
			break;
		case 6:
			GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB1_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB1_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB1_F_SBO);
			break;
		case 10:
			GPIO_ResetBits(GPIOB, USB_HUB1_D_SEL);
			GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);//USB 06-09 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);
			break;
		default:
			break;
	}
}

/**
	idx on schem
**/
void USB_Disable_6_10(void)
{
	GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);//USB 06-09 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);
}

/**
	idx on schem
**/
void USB_Enable_11_15(uint8_t n)
{
	switch(n)
	{
		case 13:
			GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
			GPIO_SetBits(GPIOB, USB_HUB2_E_SAI);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SBO);
			break;
		case 14:
			GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
			GPIO_SetBits(GPIOB, USB_HUB2_E_SAI);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SAO);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
			break;
		case 12:
			GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
			break;
		case 11:
			GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SBI);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SBO);
			break;
		case 15:
			GPIO_ResetBits(GPIOB, USB_HUB2_C_SEL);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);//USB 11-14 be deactived
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO);
			GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
			break;
		default:
			break;
	}
}

/**
	idx on schem
**/
void USB_Disable_11_15(void)
{
	GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);//USB 11-14 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO);
	GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
}

/**
	idx on schem
**/
void USB_Enable_16_20(uint8_t n)
{
	switch(n)
	{
		case 18:
			GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
			GPIO_SetBits(GPIOC, USB_HUB2_F_SAI);
			GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
			GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
			GPIO_SetBits(GPIOC, USB_HUB2_F_SBO);
			break;
		case 19:
			GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
			GPIO_SetBits(GPIOC, USB_HUB2_F_SAI);
			GPIO_SetBits(GPIOD, USB_HUB2_F_SAO);
			GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
			break;
		case 17:
			GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);
			GPIO_SetBits(GPIOD, USB_HUB2_F_SAO);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SBI);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
			break;
		case 16:
			GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);
			GPIO_SetBits(GPIOD, USB_HUB2_F_SAO);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SBI);
			GPIO_SetBits(GPIOC, USB_HUB2_F_SBO);
			break;
		case 20:
			GPIO_ResetBits(GPIOA, USB_HUB2_D_SEL);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);//USB 16-19 be deactived
			GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
			GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
			GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
			break;
		default:
			break;
	}
}

/**
	idx on schem
**/
void USB_Disable_16_20(void)
{
	GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);//USB 16-19 be deactived
	GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
	GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
}

/**
	idx on schem
**/
void USB_Enable_21_25(uint8_t n)
{
	switch(n)
	{
		case 23:
			GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SBO);
			break;
		case 24:
			GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
			break;
		case 22:
			GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_E_SAO);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
			break;
		case 21:
			GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_E_SAO);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SBI);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SBO);
			break;
		case 25:
			GPIO_ResetBits(GPIOA, USB_HUB3_C_SEL);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
			GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
			GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
			break;
		default:
			break;
	}
}

/**
	idx on schem
**/
void USB_Disable_21_25(void)
{
	GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);//1st 1to4 chip be choosed, USB 25 be deactived
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);//USB 21-24 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
}

/**
	idx on schem
**/
void USB_Enable_26_30(uint8_t n)
{
	switch(n)
	{
		case 28:
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
			USB_HUB3_D_SEL_EN(1);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 29:
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
			USB_HUB3_D_SEL_EN(1);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 27:
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
			USB_HUB3_D_SEL_EN(1);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 26:
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
			USB_HUB3_D_SEL_EN(1);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 30:
//需要变更I2C方式USB_HUB3_D_SEL低有效
			USB_HUB3_D_SEL_EN(0);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);;
			break;
		default:
			break;
	}
}

/**
	idx on schem
**/
void USB_Disable_26_30(void)
{
//2st 1to4 chip be choosed, USB 30 be deactived
//需要变更I2C方式USB_HUB3_D_SEL高有效
	USB_HUB3_D_SEL_EN(1);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);//USB 26-29 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
}

/**
|type |board num|item |para |function             |
|-----|---------|---- |-----|---------------------|
|usb  |1        |usb1 |(1)  |USB_Enable_21_25(21) |
|usb  |1        |usb2 |(2)  |USB_Enable_21_25(22) |
|usb  |1        |usb3 |(3)  |USB_Enable_21_25(23) |
|usb  |1        |usb4 |(4)  |USB_Enable_21_25(24) |
|usb  |1        |usb5 |(5)  |USB_Enable_21_25(25) |

|usb  |1        |usb6 |(6)  |USB_Enable_26_30(26) |
|usb  |1        |usb7 |(7)  |USB_Enable_26_30(27) |
|usb  |1        |usb8 |(8)  |USB_Enable_26_30(28) |
|usb  |1        |usb9 |(9)  |USB_Enable_26_30(29) |
|usb  |1        |usb10|(10) |USB_Enable_26_30(30) |

|usb  |2        |usb11|(11) |USB_Enable_1_5(1)    |
|usb  |2        |usb12|(12) |USB_Enable_1_5(2)    |
|usb  |2        |usb13|(13) |USB_Enable_1_5(3)    |
|usb  |2        |usb14|(14) |USB_Enable_1_5(4)    |
|usb  |2        |usb15|(15) |USB_Enable_1_5(5)    |

|usb  |2        |usb16|(16) |USB_Enable_6_10(6)   |
|usb  |2        |usb17|(17) |USB_Enable_6_10(7)   |
|usb  |2        |usb18|(18) |USB_Enable_6_10(8)   |
|usb  |2        |usb19|(19) |USB_Enable_6_10(9)   |
|usb  |2        |usb20|(20) |USB_Enable_6_10(10)  |

|usb  |3        |usb21|(21) |USB_Enable_11_15(11) |
|usb  |3        |usb22|(22) |USB_Enable_11_15(12) |
|usb  |3        |usb23|(23) |USB_Enable_11_15(13) |
|usb  |3        |usb24|(24) |USB_Enable_11_15(14) |
|usb  |3        |usb25|(25) |USB_Enable_11_15(15) |

|usb  |3        |usb26|(26) |USB_Enable_16_20(16) |
|usb  |3        |usb27|(27) |USB_Enable_16_20(17) |
|usb  |3        |usb28|(28) |USB_Enable_16_20(18) |
|usb  |3        |usb29|(29) |USB_Enable_16_20(19) |
|usb  |3        |usb30|(30) |USB_Enable_16_20(20) |
**/
void usb_data_on(uint8_t n)
{
	uint8_t i = (n-1)/5 + 1;//usb group
	switch(i)
	{
		case 1:
			USB_Enable_21_25(20 + n);
			break;
		case 2:
			USB_Enable_26_30(20 + n);
			break;
		case 3:
			USB_Enable_1_5(n - 10);
			break;
		case 4:
			USB_Enable_6_10(n - 10);
			break;
		case 5:
			USB_Enable_11_15(n - 10);
			break;
		case 6:
			USB_Enable_16_20(n - 10);
			break;
		default:
			break;
	}
	if(i%2)
	{
		flag_on_record.usb1_on_idx = n;
		flag_on_record.usb_on_group1 = i;
	}
	else
	{
		flag_on_record.usb2_on_idx = n;
		flag_on_record.usb_on_group2 = i;
	}
}

void usb_enable(uint8_t n)
{
	uint8_t hub_i = (n-1)/10 + 1;//now-hub
	uint8_t group_i = (n-1)/5 + 1;//now-usb group
	if(hub_i == flag_on_record.hub_on_idx)
	{
		if(group_i == flag_on_record.usb_on_group1)
		{
			if(n != flag_on_record.usb1_on_idx)
			{
				usb_disable(flag_on_record.usb1_on_idx);//disconnect usb1 signal first
				bsp_mDelay(20);
				usb_5v_onoff(flag_on_record.usb1_on_idx, 0);//then disconnect usb1 power
				bsp_mDelay(20);
				
				usb_5v_onoff(n, 1);//connect power first
				bsp_mDelay(20);
				usb_data_on(n);//then connect signal
			}
		}
		else if(group_i == flag_on_record.usb_on_group2)
		{
			if(n != flag_on_record.usb2_on_idx)
			{
				usb_disable(flag_on_record.usb2_on_idx);//disconnect usb2 signal first
				bsp_mDelay(20);
				usb_5v_onoff(flag_on_record.usb2_on_idx, 0);//then disconnect usb1 power
				bsp_mDelay(20);
				
				usb_5v_onoff(n, 1);//connect power first
				bsp_mDelay(20);
				usb_data_on(n);//then connect signal
			}
		}
		else
		{
			usb_5v_onoff(n, 1);//connect power first
			bsp_mDelay(20);
			usb_data_on(n);//then connect signal
		}
	}
	
	else
	{
		usb_5v_onoff(n, 1);//connect power first
		bsp_mDelay(20);
		usb_data_on(n);
	}
}


/**
|type       |board num|item    |para |function             |
|-----------|---------|--------|-----|---------------------|
|usb_group  |1        |usb1-5  |(1)  |USB_Disable_21_25()  |
|usb_group  |1        |usb6-10 |(2)  |USB_Disable_26_30()  |
|usb_group  |2        |usb11-15|(3)  |USB_Disable_1_5()    |
|usb_group  |2        |usb16-20|(4)  |USB_Disable_6_10()   |
|usb_group  |3        |usb21-25|(5)  |USB_Disable_11_15()  |
|usb_group  |3        |usb26-30|(6)  |USB_Disable_16_20()  |
**/
void usb_disable(uint8_t n)
{
	uint8_t i = (n-1)/5 + 1;
	switch(i)
	{
		case 1:
			USB_Disable_21_25();
			break;
		case 2:
			USB_Disable_26_30();
			break;
		case 3:
			USB_Disable_1_5();
			break;
		case 4:
			USB_Disable_6_10();
			break;
		case 5:
			USB_Disable_11_15();
			break;
		case 6:
			USB_Disable_16_20();
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
*/
void USB_5V_CT(uint8_t num, uint8_t en)
{
	switch(num)
	{
		case 0:
			if(en == 0)
				HUB3_USB1_5V_EN_LOW();
			else
				HUB3_USB1_5V_EN_HIGH();
			break;
		case 1:
			HUB3_USB2_5V_Set(en);
			break;
		case 2:
			if(en == 0)
				HUB1_USB1_5V_EN_LOW();
			else
				HUB1_USB1_5V_EN_HIGH();
			break;
		case 3:
			if(en == 0)
				HUB1_USB2_5V_EN_LOW();
			else
				HUB1_USB2_5V_EN_HIGH();
			break;
		case 4:
			if(en == 0)
				HUB2_USB1_5V_EN_LOW();
			else
				HUB2_USB1_5V_EN_HIGH();
			break;
		case 5:
			if(en == 0)
				HUB2_USB2_5V_EN_LOW();
			else
				HUB2_USB2_5V_EN_HIGH();
			break;
		default:
			break;
	}
}

void usb_5v_onoff(uint8_t num, uint8_t en)
{
	uint8_t i = (num-1)/5;
	USB_5V_CT(i, en);
}

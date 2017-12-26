#include "gpio_driver.h"

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
//1to2 SD USB switch
#define SD_HUB1_C_SEL      GPIO_Pin_12    //PB12
#define SD_HUB1_D_SEL      GPIO_Pin_11    //PA11

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

#define SD_HUB1_C_SEL_HIGH()     GPIO_SetBits(GPIOB, SD_HUB1_C_SEL)
#define SD_HUB1_C_SEL_LOW()      GPIO_ResetBits(GPIOB, SD_HUB1_C_SEL)

#define SD_HUB1_D_SEL_HIGH()     GPIO_SetBits(GPIOA, SD_HUB1_D_SEL)
#define SD_HUB1_D_SEL_LOW()      GPIO_ResetBits(GPIOA, SD_HUB1_D_SEL)

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
//1to2 SD USB switch
#define SD_HUB2_C_SEL      GPIO_Pin_9     //PB9
#define SD_HUB2_D_SEL      GPIO_Pin_8     //PB8

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

#define SD_HUB2_C_SEL_HIGH()     GPIO_SetBits(GPIOB, SD_HUB2_C_SEL)
#define SD_HUB2_C_SEL_LOW()      GPIO_ResetBits(GPIOB, SD_HUB2_C_SEL)

#define SD_HUB2_D_SEL_HIGH()     GPIO_SetBits(GPIOB, SD_HUB2_D_SEL)
#define SD_HUB2_D_SEL_LOW()      GPIO_ResetBits(GPIOB, SD_HUB2_D_SEL)

//-----------------------03 sub board
//1st 1to2 USB switch
#define USB_HUB3_C_SEL     GPIO_Pin_4     //PA4
//1st 1to4 USB switch
#define USB_HUB3_E_SAI     GPIO_Pin_7     //PA7
#define USB_HUB3_E_SAO     GPIO_Pin_4     //PC4
#define USB_HUB3_E_SBI     GPIO_Pin_6     //PA6
#define USB_HUB3_E_SBO     GPIO_Pin_5     //PA5
//2rd 1to2 USB switch
#define USB_HUB3_D_SEL     GPIO_Pin_10    //PB10
//2rd 1to4 USB switch
#define USB_HUB3_F_SAI     GPIO_Pin_0     //PB0
#define USB_HUB3_F_SAO     GPIO_Pin_5     //PC5
#define USB_HUB3_F_SBI     GPIO_Pin_1     //PB1
#define USB_HUB3_F_SBO     GPIO_Pin_2     //PB2
//1to2 SD USB switch
#define SD_HUB3_C_SEL      GPIO_Pin_11    //PB11
#define SD_HUB3_D_SEL      GPIO_Pin_1     //PA1

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

#define USB_HUB3_D_SEL_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_D_SEL)
#define USB_HUB3_D_SEL_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_D_SEL)

#define USB_HUB3_F_SAI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SAI)
#define USB_HUB3_F_SAI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI)

#define USB_HUB3_F_SAO_HIGH()     GPIO_SetBits(GPIOC, USB_HUB3_F_SAO)
#define USB_HUB3_F_SAO_LOW()      GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO)

#define USB_HUB3_F_SBI_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SBI)
#define USB_HUB3_F_SBI_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI)

#define USB_HUB3_F_SBO_HIGH()     GPIO_SetBits(GPIOB, USB_HUB3_F_SBO)
#define USB_HUB3_F_SBO_LOW()      GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO)

#define SD_HUB3_C_SEL_HIGH()     GPIO_SetBits(GPIOB, SD_HUB3_C_SEL)
#define SD_HUB3_C_SEL_LOW()      GPIO_ResetBits(GPIOB, SD_HUB3_C_SEL)

#define SD_HUB3_D_SEL_HIGH()     GPIO_SetBits(GPIOA, SD_HUB3_C_SEL)
#define SD_HUB3_D_SEL_LOW()      GPIO_ResetBits(GPIOA, SD_HUB3_C_SEL)


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
	
	GPIO_InitStructure.GPIO_Pin = B14_SBO | B58_SAI | USB_HUB1_C_SEL | USB_HUB1_E_SBI | USB_HUB1_E_SBO | SD_HUB1_D_SEL |
                              	USB_HUB2_D_SEL | USB_HUB3_C_SEL | USB_HUB3_E_SAI | USB_HUB3_E_SBI | USB_HUB3_E_SBO |
                              	SD_HUB3_D_SEL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USB_HUB1_D_SEL | USB_HUB1_F_SBI | USB_HUB1_F_SBO | SD_HUB1_C_SEL | USB_HUB2_C_SEL | 
	                              USB_HUB2_E_SAI | USB_HUB2_E_SAO | USB_HUB2_E_SBI | USB_HUB2_E_SBO | SD_HUB2_C_SEL |
	                              SD_HUB2_D_SEL | USB_HUB3_D_SEL | USB_HUB3_F_SAI | USB_HUB3_F_SBI | USB_HUB3_F_SBO |
	                              SD_HUB3_C_SEL;
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
	
	GPIO_SetBits(GPIOB, SD_HUB1_C_SEL);//SD card 01 be actived, 02-03 be deactived
	GPIO_SetBits(GPIOA, SD_HUB1_D_SEL);
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
	
	GPIO_SetBits(GPIOB, SD_HUB2_C_SEL);//SD card 04 be actived, 05-06 be deactived
	GPIO_SetBits(GPIOB, SD_HUB2_D_SEL);
}

void iobus_sub_board03_init()
{
	GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);//1st 1to4 chip be choosed, USB 25 be deactived
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);//USB 21-24 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
	
	GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);//USB 26-29 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
	
	GPIO_SetBits(GPIOB, SD_HUB3_C_SEL);//SD card 07 be actived, 08-09 be deactived
	GPIO_SetBits(GPIOA, SD_HUB3_D_SEL);
}

void iobus_init(void)
{
  RCC_Configuration();
  GPIO_Configuration();
	iobus_main_board_init();
	iobus_sub_board01_init();
	iobus_sub_board02_init();
	iobus_sub_board03_init();
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
			break;
		case 1:
			HUB_Half_02_deactive();
			GPIO_SetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_SetBits(GPIOC, B14_SBI);
			GPIO_ResetBits(GPIOA, B14_SBO);
			break;
		case 3:
			HUB_Half_02_deactive();
			GPIO_ResetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_ResetBits(GPIOC, B14_SBI);
			GPIO_ResetBits(GPIOA, B14_SBO);
		break;
		case 4:
			HUB_Half_02_deactive();
			GPIO_ResetBits(GPIOC, B14_SAI);
			GPIO_SetBits(GPIOC, B14_SAO);
			GPIO_ResetBits(GPIOC, B14_SBI);
			GPIO_SetBits(GPIOA, B14_SBO);
			break;
		case 8:
			HUB_Half_01_deactive();
			GPIO_SetBits(GPIOA, B58_SAI);
			GPIO_ResetBits(GPIOC, B58_SAO);
			GPIO_SetBits(GPIOC, B58_SBI);
			GPIO_SetBits(GPIOC, B58_SBO);
			break;
		case 7:
			HUB_Half_01_deactive();
			GPIO_SetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_SetBits(GPIOC, B58_SBI);
			GPIO_ResetBits(GPIOC, B58_SBO);
			break;
		case 5:
			HUB_Half_01_deactive();
			GPIO_ResetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_ResetBits(GPIOC, B58_SBI);
			GPIO_ResetBits(GPIOC, B58_SBO);
			break;
		case 6:
			HUB_Half_01_deactive();
			GPIO_ResetBits(GPIOA, B58_SAI);
			GPIO_SetBits(GPIOC, B58_SAO);
			GPIO_ResetBits(GPIOC, B58_SBI);
			GPIO_SetBits(GPIOC, B58_SBO);
			break;
		default:
			break;
	}
}

void HUB_Disable()
{
	iobus_main_board_init();
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
void USB_Disable_6_10(void)
{
	GPIO_SetBits(GPIOB, USB_HUB1_D_SEL);//2st 1to4 chip be choosed, USB 10 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAI);//USB 06-09 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB1_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB1_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB1_F_SBO);
}

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
void USB_Disable_11_15(void)
{
	GPIO_SetBits(GPIOB, USB_HUB2_C_SEL);//1st 1to4 chip be choosed, USB 15 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAI);//USB 11-14 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SAO);
	GPIO_SetBits(GPIOB, USB_HUB2_E_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB2_E_SBO);
}

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
void USB_Disable_16_20(void)
{
	GPIO_SetBits(GPIOA, USB_HUB2_D_SEL);//2st 1to4 chip be choosed, USB 20 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SAI);//USB 16-19 be deactived
	GPIO_ResetBits(GPIOD, USB_HUB2_F_SAO);
	GPIO_SetBits(GPIOC, USB_HUB2_F_SBI);
	GPIO_ResetBits(GPIOC, USB_HUB2_F_SBO);
}

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
void USB_Disable_21_25(void)
{
	GPIO_SetBits(GPIOA, USB_HUB3_C_SEL);//1st 1to4 chip be choosed, USB 25 be deactived
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SAI);//USB 21-24 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_E_SAO);
	GPIO_SetBits(GPIOA, USB_HUB3_E_SBI);
	GPIO_ResetBits(GPIOA, USB_HUB3_E_SBO);
}

void USB_Enable_26_30(uint8_t n)
{
	switch(n)
	{
		case 28:
			GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
			GPIO_SetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 29:
			GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
			GPIO_SetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 27:
			GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 26:
			GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_SetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBO);
			break;
		case 30:
			GPIO_ResetBits(GPIOB, USB_HUB3_D_SEL);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);
			GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
			GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
			GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);;
			break;
		default:
			break;
	}
}
void USB_Disable_26_30(void)
{
	GPIO_SetBits(GPIOB, USB_HUB3_D_SEL);//2st 1to4 chip be choosed, USB 30 be deactived
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SAI);//USB 26-29 be deactived
	GPIO_ResetBits(GPIOC, USB_HUB3_F_SAO);
	GPIO_SetBits(GPIOB, USB_HUB3_F_SBI);
	GPIO_ResetBits(GPIOB, USB_HUB3_F_SBO);
}

void SD_Enable_1_3(uint8_t n)
{
	switch(n)
	{
		case 1:
			GPIO_SetBits(GPIOB, SD_HUB1_C_SEL);
			GPIO_SetBits(GPIOA, SD_HUB1_D_SEL);
			break;
		case 2:
			GPIO_SetBits(GPIOB, SD_HUB1_C_SEL);
			GPIO_ResetBits(GPIOA, SD_HUB1_D_SEL);
			break;
		case 3:
			GPIO_ResetBits(GPIOB, SD_HUB1_C_SEL);
			break;
		default:
			break;
	}
}

void SD_Enable_4_6(uint8_t n)
{
	switch(n)
	{
		case 4:
			GPIO_SetBits(GPIOB, SD_HUB2_C_SEL);
			GPIO_SetBits(GPIOB, SD_HUB2_D_SEL);
			break;
		case 5:
			GPIO_SetBits(GPIOB, SD_HUB2_C_SEL);
			GPIO_ResetBits(GPIOB, SD_HUB2_D_SEL);
			break;
		case 6:
			GPIO_ResetBits(GPIOB, SD_HUB2_C_SEL);
			break;
		default:
			break;
	}
}

void SD_Enable_7_9(uint8_t n)
{
	switch(n)
	{
		case 7:
			GPIO_SetBits(GPIOB, SD_HUB3_C_SEL);
			GPIO_SetBits(GPIOA, SD_HUB3_D_SEL);
			break;
		case 8:
			GPIO_SetBits(GPIOB, SD_HUB3_C_SEL);
			GPIO_ResetBits(GPIOA, SD_HUB3_D_SEL);
			break;
		case 9:
			GPIO_ResetBits(GPIOB, SD_HUB3_C_SEL);
			break;
		default:
			break;
	}
}

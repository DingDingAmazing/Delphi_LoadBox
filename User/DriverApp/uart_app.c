#include "uart_app.h"

/*************************************************************************************/ 
STRUCT_UARTDEAL     gUart2Deal;
STRUCT_UARTFRAME 	  gUart2Frame;  

uint8_t key_num;
/*************************************************************************************/


/*************************************************************************************/
//
void Uart_send_feckback(void)
{
	uint8_t Data_Temp[DataLength_Max];

	memset(&Data_Temp,0,DataLength_Max); 

	Data_Temp[0] = 0xaa;
	Data_Temp[1] = 0xbb;		
	
	rt_serial_write(&Data_Temp, 2); 
}
/*************************************************************************************/


/*************************************************************************************/
//
void UartFrameHandle(void)
{
    uint8_t      Data = 0;
    static uint16_t       Cmd = 0;
    static uint16_t       Len = 0;
    static uint16_t   PackLen = 0;
    Uart2TimeOut = 3000;	//300ms¶¨Ê±
    while(1)
    {
        if(gUart2Deal.EndFlag == TRUE)	
        {
            break;
        }

        if(!Uart2TimeOut)		
        {
            gUart2Deal.EndFlag = TRUE;
            break;
        }
				
				if(rt_serial_read(&Data,1)==0)
        {
            break;
        }
				
      switch(gUart2Deal.Step)
      {
				case 0:
        if(Data == 0x55)		
        {
          gUart2Deal.Step++;
          PackLen  = 0;
        }
				else
        {
          gUart2Deal.EndFlag = TRUE;
        }
        break;
        
				case 1:
        if(Data == 0xaa)		
        {
          gUart2Deal.Step++;
          PackLen	 = 0;
        }
        else
        {
          gUart2Deal.EndFlag = TRUE;
					gUart2Deal.Step = 0;
        }
        break;
        
				case 2:								
        if(Data > 0xf0)	
        {
          Cmd = Data<<8;
          gUart2Deal.Step++;
        }
        else
        {
          memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
          Cmd = 0;
          Len = 0;
          PackLen = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
        }
        break;
         
				case 3:						
        Cmd |= Data;
        gUart2Frame.Cmd = Cmd;
        gUart2Deal.Step++;
        if(gUart2Frame.Cmd == 0)
        {
          memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
          Cmd      = 0;
          Len      = 0;
          PackLen  = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
        }
        break;
				
				case 4:
        if((Data > 0)&&(Data != 0xcc))		
        {
					gUart2Frame.DataBuf[PackLen++] = Data;
        }
				else if(Data == 0xcc)
				{
					Cmd      = 0;
          Len      = 0;
          PackLen  = 0;
          gUart2Deal.Step = 0;
					gUart2Deal.EndFlag = TRUE;
				}
				else
				{
					memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
					Cmd      = 0;
          PackLen  = 0;
          gUart2Deal.EndFlag = TRUE;
          gUart2Deal.Step = 0;
				}
				break;
            
				 default:
         memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME));
         Cmd      = 0;
         Len      = 0;
         PackLen  = 0;
         gUart2Deal.Step = 0;
         gUart2Deal.EndFlag = TRUE;
				 break;
		}
	}
}
/*************************************************************************************/


/*************************************************************************************/
//
void Uart2FrameOperate(void)
{	
    if(gUart2Deal.EndFlag == FALSE)
    {
        return;
    }
		
    switch(gUart2Frame.Cmd)
    {	
        case 0xf101:
					USB_idx = gUart2Frame.DataBuf[0];
					USB_en = 1;
					if(USB_flag == 0)
						USB_flag = 1;
            break;			

        case 0xf102:
					USB_idx = gUart2Frame.DataBuf[0];
					USB_en = 0;
					if(USB_flag == 0)
						USB_flag = 1;
            break;
					
				case 0xf201:
					SD_idx = gUart2Frame.DataBuf[0];
					if(SD_flag == 0)
						SD_flag = 1;
						break;
					
				case 0xf301:
					HUB_idx = gUart2Frame.DataBuf[0];
					if(HUB_flag == 0)
						HUB_flag = 1;
						break;
					
        default:
            break;
    }

    memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME)); 
    memset(&gUart2Deal,0, sizeof(STRUCT_UARTDEAL)); 
}
/*************************************************************************************/


/*************************************************************************************/
//


void proc_envent1(void)
{
	if(USB_flag==1)
	{
		if((USB_idx>0) && (USB_idx<31))
		{
			USBCT(USB_idx, USB_en);
			USB_flag = 0;
			Uart_send_feckback();
		}
	}
}

void proc_envent2(void)
{
	if(SD_flag==1)
	{
		if( (SD_idx<10) && (SD_idx>0) )
		{
			SD_CT(SD_idx);
			SD_flag = 0;
			Uart_send_feckback();
		}
	}
}


void proc_envent3(void)
{
	if(HUB_flag==1)
	{
		if( (HUB_idx>3) && (HUB_idx<9) )
		{
			HUB_Enable(HUB_idx);
			HUB_flag = 0;
			Uart_send_feckback();
		}
	}
}


void EnventHandle(void)
{
	proc_envent1();
	proc_envent2();
	proc_envent3();
}

//for test
tmr_t testTmr1;
void setTestTimer1(void)
{
	tmr_start(&testTmr1,500);
}
//for test
void timerUsartTest(void)
{
	if(tmr_has_expired(&testTmr1))
	{
		Uart_send_feckback();
		tmr_reset(&testTmr1);
	}
}

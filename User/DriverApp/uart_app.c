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

void uart_send_word(char *n)
{
	uint8_t len1;
//	len1 = sizeof(n);
	len1 = strlen(n);
	rt_serial_write(n, len1);
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
        if(Data == 0x56)		
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
					SD_en = 1;
					if(SD_flag == 0)
						SD_flag = 1;
						break;
					
				case 0xf202:
					SD_idx = gUart2Frame.DataBuf[0];
					SD_en = 0;
					if(SD_flag == 0)
						SD_flag = 1;
						break;
					
				case 0xf301:
					HUB_idx = gUart2Frame.DataBuf[0];
					HUB_en = 1;
					if(HUB_flag == 0)
						HUB_flag = 1;
						break;
					
				case 0xf302:
					HUB_en = 0;//disable all hubs
					if(HUB_flag == 0)
						HUB_flag = 1;
						break;
					
				case 0xf401:
					AUX_idx = gUart2Frame.DataBuf[0];
					AUX_en = 1;
					if(AUX_flag == 0)
						AUX_flag = 1;
						break;
					
				case 0xf402:
					AUX_idx = gUart2Frame.DataBuf[0];
					AUX_en = 0;
					if(AUX_flag == 0)
						AUX_flag = 1;
						break;
					
        default:
            break;
    }

    memset(&gUart2Frame,0,sizeof(STRUCT_UARTFRAME)); 
    memset(&gUart2Deal,0, sizeof(STRUCT_UARTDEAL)); 
}
/*************************************************************************************/


/*************************************************************************************/

void proc_envent1(void)
{	
	if((USB_idx>0) && (USB_idx<31))
	{
		USBCT(USB_idx, USB_en);
		USB_flag = 0;
		Uart_send_feckback();
	}
}

void proc_envent2(void)
{
	if(SD_flag==1)
	{
		if( (SD_idx<4) && (SD_idx>0) )
		{
			SD_CT(SD_idx,SD_en);
			SD_flag = 0;
			Uart_send_feckback();
		}
	}
}

void proc_envent4(void)
{
	if(AUX_flag==1)
	{
		if( (AUX_idx<4) && (AUX_idx>0) )
		{
			Aux_Switch(AUX_idx,AUX_en);
			AUX_flag = 0;
			Uart_send_feckback();
		}
	}
}

void proc_envent3(void)
{
	if(HUB_en == 1)
	{
		HUB_flag = 0;
		Uart_send_feckback();
	}
	else
	{
		HUB_Disable();
		HUB_flag = 0;
		Uart_send_feckback();
	}
}

void hub_handle(uint8_t hub_i)
{
	if(hub_i != flag_on_record.hub_on_idx)
	{
		if(hub_i == 255)
		{
			HUB_Enable(hub_i);
		}
		else
		{
			if(flag_on_record.usb1_on_idx != 255)
			{
				usb_disable(flag_on_record.usb1_on_idx);//disconnect usb1 signal first
				bsp_mDelay(20);
				usb_5v_onoff(flag_on_record.usb1_on_idx, 0);//then disconnect usb1 power
				bsp_mDelay(20);
				flag_on_record.usb1_on_idx = 255;
				flag_on_record.usb_on_group1 = 255;
			}
			if(flag_on_record.usb2_on_idx != 255)
			{
				usb_disable(flag_on_record.usb2_on_idx);//disconnect usb2 signal first
				bsp_mDelay(20);
				usb_5v_onoff(flag_on_record.usb2_on_idx, 0);//then disconnect usb1 power
				bsp_mDelay(20);
				flag_on_record.usb2_on_idx = 255;
				flag_on_record.usb_on_group2 = 255;
			}
			if(flag_on_record.aux_on_idx != 255)
			{
				Aux_Switch(flag_on_record.aux_on_idx, 0);
			}
			if(flag_on_record.sd_on_idx != 255)
			{
				SD_CT(flag_on_record.sd_on_idx, 0);
			}
			
			HUB_Enable(hub_i);
		}
	}
}

void proc_handle(void)
{
	uint8_t hub_i;//now-hub
	if(USB_flag)
	{
		if(USB_en)
		{
			hub_i = (USB_idx-1)/10 + 1;
			hub_handle(hub_i);
		}
		proc_envent1();
	}
	else if(AUX_flag)
	{
		if(AUX_en)
		{
			hub_handle(AUX_idx);
		}
		proc_envent4();
	}
	else if(SD_flag)
	{
		if(SD_en)
		{
			hub_handle(SD_idx);
		}
		proc_envent2();
	}
	else if(HUB_flag)
	{
		if(HUB_en)
		{
			hub_handle(HUB_idx);
			HUB_flag = 0;
			Uart_send_feckback();
		}
		else
		{
			proc_envent3();
		}
	}
}


void EnventHandle(void)
{
	if(USB_flag || AUX_flag || SD_flag || HUB_flag)
	{
		proc_handle();
	}
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

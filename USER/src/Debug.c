/*********************************************************************************
�ļ�������
*********************************************************************************/
#include "Debug.h"
/*********************************************************************************
����������
*********************************************************************************/
/*********************************************************************************
��������������
*********************************************************************************/
/*********************************************************************************
�ⲿ����������
*********************************************************************************/
/*********************************************************************************
˽�б���������
*********************************************************************************/ 
struct Debug_EN Debug;
/*********************************************************************************
���Ա���������
*********************************************************************************/
/*********************************************************************************
�ڲ�����������
*********************************************************************************/
/*********************************************************************************
���ܴ��붨����
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //��ʼ��
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Init(void)
{
  MeterParameter.Peripheral.debug = RUN;
  USART3_Configuration();  
  Create_Timer(ONCE,60,
               Debug_DeInit,0,PROCESS); 
}
/*********************************************************************************
 Function:      //
 Description:   //ȡ����ʼ��ΪĬ��״̬
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_DeInit(void)
{
  Free_Uart3();
  USART_DeInit(USART3);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3,DISABLE);
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_In_FL_IT);
  
  EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Falling);
  EXTI_ClearITPendingBit (EXTI_IT_Pin7);                    
  ITC_SetSoftwarePriority(EXTI7_IRQn , ITC_PriorityLevel_2);
  
  MeterParameter.Peripheral.debug = SLEEP;
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Process(void)
{
  uint8_t buff[64] = {0};
  uint8_t msgID = 0;
  uint8_t msgLen = 0;
  uint8_t dataLen = 0;
  
  if(MeterParameter.Peripheral.debug != SLEEP)
  {
    if(Uart3.Receive_Pend == TRUE)//�ж�������
    { 
      MsgLen = Uart3_Receive(buff);
      
      dataLen = Uart3.R_Buffer[3];
      if( buff[MsgLen-1] == Check_Sum8(&Uart3.R_Buffer[4],MsgLen) )
      {
        Debug.Status = TRUE;
        MsgID = Uart3.R_Buffer[5];
        switch(MsgID)
        {
          case MessageID0:
            {
            }
            break;
          case MessageID1:      //��ȡ����
            {
              Send_Meter_Info();
            }
            break;
          case MessageID2:      //У��
            {
              Cal.Water_Data.flow8[0] = Uart3.R_Buffer[6];
              Cal.Water_Data.flow8[1] = Uart3.R_Buffer[7];
              Cal.Water_Data.flow8[2] = Uart3.R_Buffer[8];
              Cal.Water_Data.flow8[3] = Uart3.R_Buffer[9];
              Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);
              
              Send_Meter_Info();
            }
            break;
          default:
            break;
        }
      }
    }
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Send_Meter_Info(void)
{
  unsigned char data[24] = {0};
  unsigned char sum = 0;
  
  //��ȡʱ��   
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
  //�����¶�
  Read_Temp();
  //������ѹ
  Read_Voltage();
  
  data[0] = 0xFE;
  data[1] = 0xFE;
  data[2] = 0x5A;
  data[3] = 0;
  data[4] = 14;
  data[5] = MessageID1;
  
  //��ǰ�ۻ�����
  data[6] = Cal.Water_Data.flow8[0];
  data[7] = Cal.Water_Data.flow8[1];
  data[8] = Cal.Water_Data.flow8[2];
  data[9] = Cal.Water_Data.flow8[3];
  //��ص�ѹ
  data[10] = MeterParameter.Voltage/0x100;
  data[11] = MeterParameter.Voltage%0x100;
  //�¶� 
  data[12] = (u8)MeterParameter.Temp;
  //��
  data[13] = RTC_DateStr.RTC_Year;
  //��
  data[14] = RTC_DateStr.RTC_Month;
  //��
  data[15] = RTC_DateStr.RTC_Date;
  //ʱ
  data[16] = RTC_TimeStr.RTC_Hours;
  //��
  data[17] = RTC_TimeStr.RTC_Minutes;
  //��
  data[18] = RTC_TimeStr.RTC_Seconds;
  
  sum = Check_Sum8(&data[5],14);
  data[19] = sum;
  
  Uart3_Send(data,20);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/


/*********************************************************************************
//������
//���ߣ����ƮԾ     ʱ�䣺       �ص㣺
//CPU�ͺţ�         ϵͳ��Ƶ��
//�汾�ţ�V0.0        
*********************************************************************************/
/*********************************************************************************
�ļ�������
*********************************************************************************/
#include "include.h"
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
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void main(void)
{ 
  disableInterrupts();                                      //�����ж�
  RCC_Configuration();
  GPIO_Configuration();
  Rtc_Config();
  Set_Alarm();
  Pulse_Acquire_Config();
  
  IWDG_INIT(); 
  enableInterrupts();                                       //�����ж�
/////////////////////////////////////////////////////////    
  Read_ACUM_Flow(ADD_FLOW_ADD,&Cal.Water_Data);         //��ȡ��ǰ�ۻ�����
  Read_Meter_Parameter();                               //��ȡˮ�����
  Read_History_Save_Index();                            //��ȡ��ʷ���ݱ�������
  
  BC95.Report_Bit = 1;
  BC95.Start_Process = BC95_RECONNECT;
  
  while (1)
  {
//    RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
//    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
    //�豸����24Сʱ�Ҳ����ϱ�״̬��λ
    if( (MeterParameter.DeviceRunTiming > ((u32)24*60*60))&&(BC95.Start_Process == BC95_POWER_DOWN) )
    {
      Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);       //���浱ǰˮ��
      WWDG->CR = 0x80;  //���Ź���λ
    }
    else
    {
      IWDG_ReloadCounter();//���ؿ��Ź�������
    }
    
    Sys_Timer_Process();
    BC95_Process();  
    
    if(MeterParameter.DeviceStatus == SLEEP)     //�豸����˯��״̬
    {
      Sleep();
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
void Sleep(void)
{ 
  USART_DeInit(USART2);                                         //���USART2�Ĵ���
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2, DISABLE);    //�ر�USART2ʱ��
  USART_DeInit(USART3);                                         //���USART3�Ĵ���
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, DISABLE);    //�ر�USART3ʱ��
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
  
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow);         // ��������
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_Out_PP_Low_Slow);         // ��������ADC����
  
  GPIO_Init(GPIOE,GPIO_Pin_0,GPIO_Mode_Out_PP_Low_Slow);       //BC95 RI
  GPIO_Init(GPIOE,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Slow);       //BC95 ��λ��
  GPIO_Init(GPIOE,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Slow);        //BC95 VBAT
  GPIO_Init(GPIOD,GPIO_Pin_6,GPIO_Mode_Out_PP_Low_Slow);        //�̵�
  GPIO_Init(GPIOD,GPIO_Pin_7,GPIO_Mode_Out_PP_Low_Slow);        //�Ƶ�

  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_Low_Slow);    //USART2 TXD
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);    //USART3 TXD
  
  if(BC95.Report_Bit == 1)
  {
    Save_History_Data();    //���汾������
  }
  HistoryData.ReadIndex = 0;
  BC95.Report_Bit = 0;
  BC95.Start_Process = BC95_POWER_DOWN;
  BC95.Run_Time = 0;

  CLK_HaltConfig(CLK_Halt_FastWakeup,ENABLE);   //���ٻ��Ѻ�ʱ��ΪHSI  
  PWR_FastWakeUpCmd(ENABLE);                    //������Դ������Ŀ��ٻ���  
  PWR_UltraLowPowerCmd(ENABLE);                 //ʹ�ܵ�Դ�ĵ͹���ģʽ          //�������ڲ��ο���ѹ��ȡֵ��С
  CLK_HSICmd(DISABLE);                          //�ر��ڲ�����ʱ��

  halt();
}
/**
*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void IWDG_INIT(void)  //���Ź���ʼ��
{ 
  IWDG_Enable();//�������Ź�
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//����дԤ��Ƶ�������ؼĴ���
  IWDG_SetPrescaler(IWDG_Prescaler_256);//����IWDGԤ��Ƶֵ
  IWDG_SetReload(0xFF);//��������ֵ1.7s��(255+1)*256/38K = 1.72s
  IWDG_ReloadCounter();//���ؼ�����
}
/*********************************************************************************
 Function:      //
 Description:   //�������Ź���λ
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

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/


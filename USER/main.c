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
extern RTC_TimeTypeDef   RTC_TimeStr;        //RTCʱ��ṹ��
extern RTC_DateTypeDef   RTC_DateStr;        //RTC���ڽṹ��
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
unsigned short i;
void main(void)
{ 
  disableInterrupts();                                      //�����ж�
  RCC_Configuration();
  GPIO_Configuration();
  Rtc_Config();
  Set_Alarm();
  Pulse_Acquire_Config();
  
  IWDG_INIT();
  //  Save_Version();  //����汾����
  enableInterrupts();                                       //�����ж�
/////////////////////////////////////////////////////////    
  Read_ACUM_Flow(ADD_FLOW_ADD,&Cal.Water_Data);         //��ȡ��ǰ�ۻ�����
  Read_BAT_Alarm_Value();                               //��ȡ��ѹ�澯ֵ
  Read_Settle_Date();                                   //��ȡ��������
  Read_Report_Cycle();                                  //��ȡ�ϱ�����
  Read_Meter_Number();                                  //��ȡ���

  BC95.Send_Bit.All_Para = 1;
  BC95.Start_Process = BC95_RECONNECT;
  
//  BC95.Send_Bit.Mag_Alarm = 1;
  
//  Device_Status = SLEEP_MODE;
//  BC95.Start_Process = BC95_POWER_DOWN;

  while (1)
  {
    IWDG_ReloadCounter();//���ؼ�����
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStr);
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStr);
    i++;
    Sys_Timer_Process();
    BC95_Process();  
    if(Device_Status == SLEEP_MODE)     //�豸����˯��״̬
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
  
//  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM5, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_SPI2, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_DAC, DISABLE);
//  CLK_PeripheralClockConfig(CLK_Peripheral_LCD, DISABLE);
//
//  ADC_ChannelCmd(ADC1,ADC_Channel_1,DISABLE );         //ͨ��ѡ��1
//  ADC_VrefintCmd (DISABLE);//�ر��ڲ��ο���ѹ
//  ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,DISABLE );
  
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow);         // ��������
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_Out_PP_Low_Slow);         // ��������ADC����
  
  GPIO_Init(GPIOE,GPIO_Pin_0,GPIO_Mode_Out_PP_Low_Slow);       //BC95 RI
  GPIO_Init(GPIOE,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Slow);       //BC95 ��λ��
  GPIO_Init(GPIOE,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Slow);        //BC95 VBAT
  GPIO_Init(GPIOD,GPIO_Pin_6,GPIO_Mode_Out_PP_Low_Slow);        //�̵�
  GPIO_Init(GPIOD,GPIO_Pin_7,GPIO_Mode_Out_PP_Low_Slow);        //�Ƶ�

  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_Low_Slow);    //USART2 TXD
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);    //USART3 TXD
  
  BC95.Start_Process = BC95_POWER_DOWN;

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

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/


/*********************************************************************************************************
//������
//���ߣ����ƮԾ    ʱ�䣺       �ص㣺
//CPU�ͺţ�         ϵͳ��Ƶ��
//�汾�ţ�V0.0        
*********************************************************************************************************/
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
 Return:	//
 Others:        //
*********************************************************************************/
void WriteRom (unsigned short addr, void *pbuff, unsigned char length)
{
 unsigned char itemp;
 unsigned char cnt;
 unsigned char *p; 
 unsigned short itemp16;
 do
 {FLASH_Unlock(FLASH_MemType_Data); }//����EEPROM���
 while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET); 
 itemp = 0;
 p = pbuff;
 cnt =0 ;
 while (itemp < length)
 {
   FLASH_ProgramByte(addr ,p[itemp]);
   itemp16 = 0xffff;
   while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == RESET)
   {
    itemp16 --;
    if(itemp16 <= 1)
    {break;}
   }
   itemp16 = FLASH_ReadByte(addr);
   if(p[itemp] != itemp16)
   {
    if(++cnt > 50)
    {
     FLASH_Lock(FLASH_MemType_Data);
    }
    continue ; 
   }
   else
   {cnt = 0;itemp ++;addr ++;}
 }
 FLASH_Lock(FLASH_MemType_Data);
}


/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_IP(unsigned char *IP,unsigned char Num)
{
  if(Num == 1)
  {
    WriteRom(SERVER_ADD1_EEPROM_ADD,IP,4);//�洢IP1
    WriteRom(SERVER_ADD1_EEPROM_ADD+4,&IP[4],1);//�洢IP1
    WriteRom(SERVER_ADD1_EEPROM_ADD+5,&IP[5],1);//�洢IP1
  }
  else if(Num == 2)
  {
    WriteRom(SERVER_ADD2_EEPROM_ADD,IP,4);//�洢IP2
    WriteRom(SERVER_ADD2_EEPROM_ADD+4,&IP[4],1);//�洢IP2
    WriteRom(SERVER_ADD2_EEPROM_ADD+5,&IP[5],1);//�洢IP2
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_Version(void)
{
  unsigned char version = SOFTWARE_VERSION;
  union Network_Par_Uni ip;
  if(VERSION != SOFTWARE_VERSION)
  {
    WriteRom(SOFTWARE_VERSION_ADD,&version,1);
    ip.Str.IP[0] = 112;
    ip.Str.IP[1] = 25;
    ip.Str.IP[2] = 204;
    ip.Str.IP[3] = 3;
    ip.Str.Port = 10001;
    Save_IP(ip.Byte,1);
    ip.Str.IP[0] = 0;
    ip.Str.IP[1] = 0;
    ip.Str.IP[2] = 0;
    ip.Str.IP[3] = 0;
    ip.Str.Port = 0;
    Save_IP(ip.Byte,2);
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
void Read_ACUM_Flow(unsigned short addr,union flow_union *Flow)       //��ȡ�ۻ�ˮ��
{
  union flow_union *flow;
  flow = (union flow_union *)(addr);
  Flow->flow32 = flow->flow32;
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
void Save_Add_Flow(union flow_union *Flow)       //�洢��ǰ�ۻ�ˮ��
{
    WriteRom (ADD_FLOW_ADD,Flow->flow8,4);      //д�ۻ�����
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
void Save_SDCF_Flow(union flow_union *Flow)       //�洢�������ۻ�ˮ��
{
  union flow_union *Water;
  
  Water = (union flow_union *)(SDCF12_ADDR); 
  WriteRom (SDCF13_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF11_ADDR); 
  WriteRom (SDCF12_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF10_ADDR); 
  WriteRom (SDCF11_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF9_ADDR); 
  WriteRom (SDCF10_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF8_ADDR); 
  WriteRom (SDCF9_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF7_ADDR); 
  WriteRom (SDCF8_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF6_ADDR); 
  WriteRom (SDCF7_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF5_ADDR); 
  WriteRom (SDCF6_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF4_ADDR); 
  WriteRom (SDCF5_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF3_ADDR); 
  WriteRom (SDCF4_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF2_ADDR); 
  WriteRom (SDCF3_ADDR,Water->flow8,4);      //д�ۻ�����
  
  Water = (union flow_union *)(SDCF1_ADDR); 
  WriteRom (SDCF2_ADDR,Water->flow8,4);      //д�ۻ�����
  
  WriteRom (SDCF1_ADDR,Flow->flow8,4);      //д�ۻ�����
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
void Save_Cal(enum Cal_State_En *Cal)       //�洢����״̬
{
    WriteRom (ADD_FLOW_ADD,Cal,1);      //д����״̬
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Read_BAT_Alarm_Value(void)     //��ȡ��ѹ�澯ֵ
{ 
  BAT_Alarm_Vol = *((const unsigned short *)(BAT_ALARM_ADD));
  if(BAT_Alarm_Vol == 0)        //Ĭ�ϸ澯��ѹ3.10V
  {
    BAT_Alarm_Vol = 310;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_BAT_Alarm_Value(void)     //�����ѹ�澯ֵ
{
  WriteRom (BAT_ALARM_ADD,&BAT_Alarm_Vol,2);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Read_Settle_Date(void)         //��ȡ��������
{
  Settle_Date = *((const unsigned char *)(SETTLEMENT_DATE_ADD));
  if(Settle_Date == 0)//Ĭ�Ͻ�������1��
  {
    Settle_Date = 1;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_Settle_Date(void)         //�����������
{
  WriteRom (SETTLEMENT_DATE_ADD,&Settle_Date,1);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Read_Settle_Time(void)   //��ȡ�ս���ʱ��
{
  Settlement_Time.RTC_Hours = *((const unsigned char *)(SETTLEMENT_TIME_ADD));
  Settlement_Time.RTC_Minutes = *((const unsigned char *)(SETTLEMENT_TIME_ADD+1));
  Settlement_Time.RTC_Seconds = *((const unsigned char *)(SETTLEMENT_TIME_ADD+2));
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_Settle_Time(void)   //�������ʱ��
{
  unsigned char buff[3] = {0};
  buff[0] = Settlement_Time.RTC_Hours;
  buff[1] = Settlement_Time.RTC_Minutes;
  buff[2] = Settlement_Time.RTC_Seconds;
  
  WriteRom (SETTLEMENT_TIME_ADD,buff,3);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Read_Report_Cycle(void)        //��ȡ�ϱ�����
{
  Report_Cycle = *((const unsigned short *)(REPORT_CYCLE_ADDR));
  if(Report_Cycle == 0) //Ĭ���ϱ�����24Сʱ
  {
    Report_Cycle = 24;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_Report_Cycle(void)        //�����ϱ�����
{
  WriteRom (REPORT_CYCLE_ADDR,&Report_Cycle,2);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Read_Meter_Number(void)           //��ȡ���
{
  Meter_Number[0] = *((const unsigned char *)(CJT_188_ADD));
  Meter_Number[1] = *((const unsigned char *)(CJT_188_ADD+1));
  Meter_Number[2] = *((const unsigned char *)(CJT_188_ADD+2));
  Meter_Number[3] = *((const unsigned char *)(CJT_188_ADD+3));
  Meter_Number[4] = *((const unsigned char *)(CJT_188_ADD+4));
  Meter_Number[5] = *((const unsigned char *)(CJT_188_ADD+5));
  Meter_Number[6] = *((const unsigned char *)(CJT_188_ADD+6));
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
void Save_Meter_Number(void)           //������
{
  WriteRom (CJT_188_ADD,Meter_Number,7);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
unsigned char Sum_Check(unsigned char *sdata,unsigned short NUM)                //�����У��
{
  unsigned char rdata = 0;
  unsigned short i = 0;
  if(NUM>1000)
    NUM = 10;
  for(i=0;i<NUM;i++)
  {
    rdata += sdata[i];
  }
  return rdata;
}
/******************************************END********************************************************/

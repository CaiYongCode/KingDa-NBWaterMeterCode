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
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
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
void Save_Add_Flow(u16 addr,union flow_union *Flow)       //�洢�ۻ�ˮ��
{
    WriteRom (addr,Flow->flow8,4);      //д�ۻ�����
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
///*********************************************************************************
// Function:      //
// Description:   //��ȡ��������
// Input:         //
//                //
// Output:        //
// Return:      	//
// Others:        //
//*********************************************************************************/
//enum Hall_Error_EN Read_Cal_Error(void)       
//{
//  return (enum Hall_Error_EN)(*((const unsigned short *)(HALL_ERROR_ADD)));   
//}
///*********************************************************************************
// Function:      //
// Description:   ////�洢��������
// Input:         //
//                //
// Output:        //
// Return:      	//
// Others:        //
//*********************************************************************************/
//void Save_Cal_Error(void)       
//{
//    WriteRom (HALL_ERROR_ADD,&Cal.Error,1);      
//}
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
    BAT_Alarm_Vol = 320;
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
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
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
    Report_Cycle = 1440;
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
void Read_BC95_ErrorRecord(void)           //��ȡBC95�����¼
{
  BC95.ErrorRecord = *((const unsigned char *)(BC95_ERROR_RECORD_ADD));
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
void Save_BC95_ErrorRecord(void)           //����BC95�����¼
{
  WriteRom(BC95_ERROR_RECORD_ADD,&BC95.ErrorRecord,1);
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

/*********************************************************************************
 Function:      //
 Description:   //��ȡ��ʷ����
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Read_History_Data(unsigned char* buff)
{
  unsigned char i = 0,j = 0;
  
  for(i = 0;i < 90;i++)
  {
    buff[0] = *((const unsigned char *)(HISTORYL_DATA_ADDR + i*14));
    if(buff[0] == 1)
    {
      for(j = 1;j < 14;j++)
      {
        buff[j] = *((const unsigned char *)(HISTORYL_DATA_ADDR + i*14+j));
      }
      HistoryDataIndex = i;
      return;
    }
  }
}
/*********************************************************************************
 Function:      //
 Description:   //������ʷ����
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Save_History_Data(void)
{
  unsigned char i = 0;
  unsigned char valid = 0;
  union flow_union LastMonthFlow;     //��һ�½������ۻ�����
  unsigned char buff[14] = {0};
  
  Read_ACUM_Flow(SDCF1_ADDR,&LastMonthFlow);
  RTC_GetDate(RTC_Format_BCD, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BCD, &RTC_TimeStr);
  
  buff[0] = 1;
  buff[1] = Cal.Water_Data.flow8[0];
  buff[2] = Cal.Water_Data.flow8[1];
  buff[3] = Cal.Water_Data.flow8[2];
  buff[4] = Cal.Water_Data.flow8[3];
  buff[5] = LastMonthFlow.flow8[0];
  buff[6] = LastMonthFlow.flow8[1];
  buff[7] = LastMonthFlow.flow8[2];
  buff[8] = LastMonthFlow.flow8[3];
  buff[9] = RTC_DateStr.RTC_Year;
  buff[10] = RTC_DateStr.RTC_Month;
  buff[11] = RTC_DateStr.RTC_Date;
  buff[12] = RTC_TimeStr.RTC_Hours;
  buff[13] = RTC_TimeStr.RTC_Minutes;
  
  for(i = 0;i < 90;i++)
  {
    valid = *((const unsigned char *)(HISTORYL_DATA_ADDR + i*14));
    if(valid != 1)
    {
      WriteRom((HISTORYL_DATA_ADDR + i*14),buff,14);
      return;
    }
  }
  
}
/*********************************************************************************
 Function:      //
 Description:   //�����ʷ����
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Clear_History_Data(unsigned char index)
{
  unsigned char buff[14] = {0};
  
  WriteRom((HISTORYL_DATA_ADDR + index*14),buff,14);
}
/******************************************END********************************************************/

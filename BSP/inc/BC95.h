#ifndef __BC95_H__
#define __BC95_H__
/*********************************************************************************************************
�ļ�������
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
�궨����
*********************************************************************************************************/
#define         RECV_BUFF_SIZE               256//���ջ�������С
#define         SEND_BUFF_SIZE               128//���ͻ�������С
#define         BC95_TIMEROUT_NUM            10  //��ʱ����
#define         BC95_TIMEROUT_TIME           2 //��ʱʱ�� ��λs

/*********************************************************************************************************
�������Ͷ���
*********************************************************************************************************/
enum Start_Process_En   //��������
{
  BC95_POWER_DOWN,      //����
  BC95_POWER_UP,        //�ϵ�
  BC95_RECONNECT,       //����
  
  NRB,                  //����
  AT,                   //ͬ��������
  CMEE,                 //�����ƶ��ն˴���
  CGSN,                 //��ѯIMEI 
  CCID,                 //��ѯCCID
  CFUN,                 //��ѯȫ����
  NBAND,                //��ѯƵ��
  CSQ,                  //��ѯ�ź�ǿ��
  CGATT,                //��ѯ����
  CEREG,                //��ѯ����ע��״̬
  CSCON,                //��ѯ��������״̬
  CCLK,                 //��ѯʵʱʱ��
  NCDP,                 //����CDP������
  NSMI,                 //���÷�����Ϣָʾ
  NNMI,                 //���ý�����Ϣָʾ
  NMGS,                 //������Ϣ
  BC95_CONNECT_ERROR,   //��������
};
  
struct BC95_Str//BC95 �ܽṹ��
{
  char R_Buffer[RECV_BUFF_SIZE];        //���ջ�����
  unsigned short Recv_Length;         //���ճ���
  enum Start_Process_En Start_Process;  //���ӽ���
  u8 Report_Bit;                        //����λ
  unsigned char TimeoutNum;         //��ʱ����
  unsigned char Rssi;                 //�ź�ǿ��
  bool Incident_Pend;                  //�¼������־
  unsigned char IPOpt;                //IPѡ��
  unsigned char Reconnect_Times;      //��������
  unsigned char FailTimes;            //ʧ�ܴ���
  unsigned char ICCID[20];
  unsigned char IMEI[15];
  unsigned char ErrorStep;        //���ϲ���
  unsigned char ErrorCode;        //���ϴ���
};
 
/*********************************************************************************************************
�ⲿ����������
*********************************************************************************************************/
extern struct BC95_Str BC95;//BC95 �õļĴ���
/*********************************************************************************************************
����������
*********************************************************************************************************/
void BC95_Power_On(void); 
void BC95_Power_Off(void);
void BC95_Reset(void);
void BC95_Process(void);
void BC95_Data_Send(unsigned char *Data,unsigned short Len);

void BC95_Start(void);
void BC95_Recv_Timeout_CallBack(void);
void BC95_Delay_CallBack(void);

void Recv_Data_Process(unsigned char* buff);
void Send_Data_Process(void);
void ACK(u8 messageId,u8 errcode,u8 mid[4]);
void Report_All_Parameters(void);
void Report_HC_Flow(void);

unsigned char Report_History_Data(void);

/********************************************************************************/
#endif

/******************************************END********************************************************/
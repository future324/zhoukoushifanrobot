#pragma once
#include"USART1.h"
Comm1 com;
BYTE Send_Buff1[10] = { "1234" };
int len = 6;
void ComInit(LPCTSTR portname, int rate_arg)
{
	com.openport(portname);
	com.setupdcb(rate_arg);
	com.setuptimeout(MAXDWORD, 500, 2000, 500, 2000);
	SetupComm(com.hComm, 1024, 1024);
	SetCommMask(com.hComm, EV_RXCHAR); //�����ַ���inbuf��ʱ��������¼�

									   //������ڵ����в���							   
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}
void open_MagneticNavigation()//�򿪴ŵ�����Դ
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x07;
	Send_Buff1[5] = 0x0C;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}
void close_MagneticNavigation()//�رմŵ�����Դ
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x08;
	Send_Buff1[5] = 0x0D;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}
void start_LinePatrol()//��ʼѲ��
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x09;
	Send_Buff1[5] = 0x0E;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}
void stop_LinePatrol()//����Ѳ�ߣ�ֹͣ�˶�  
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x0A;
	Send_Buff1[5] = 0x0F;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}
void Correct_MagneticNavigation()//�ŵ������У��
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x0B;
	Send_Buff1[5] = 0x10;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}
void Set_Sensitivity()
{
	Send_Buff1[0] = 0x5A;
	Send_Buff1[1] = 0x5A;
	Send_Buff1[2] = 0x03;
	Send_Buff1[3] = 0x02;
	Send_Buff1[4] = 0x0C;
	Send_Buff1[5] = 0x11;
	PurgeComm(com.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//����PurgeComm����������ֹ���ڽ��еĶ�д�������ú�������������������������е����ݡ�
	if (com.WriteChar(Send_Buff1, len)) {}
	else { MessageBox(NULL, L"����ʧ��", L"����", 1); }
}


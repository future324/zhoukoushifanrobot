#pragma once

#include"USART.h"
Comm m_Comm1;
BYTE Send_Buff[10] = { "1234" };
BYTE Get_Buff[10] = { "1234" };
void DipanSpeedSet(unsigned short m_TanslationSpeed, short m_Yaw, short m_RotationAngleSpeed)
{
	UCHAR sum = 0;
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x03;
	Send_Buff[3] = 0x08;
	Send_Buff[4] = 0x01;
	Send_Buff[5] = *(UCHAR*)(&m_TanslationSpeed);
	Send_Buff[6] = *((UCHAR*)(&m_TanslationSpeed) + 1);
	Send_Buff[7] = *(UCHAR*)(&m_Yaw);
	Send_Buff[8] = *((UCHAR*)(&m_Yaw) + 1);
	Send_Buff[9] = *(UCHAR*)(&m_RotationAngleSpeed);
	Send_Buff[10] = *((UCHAR*)(&m_RotationAngleSpeed) + 1);

	sum = 0x03 + 0x08 + 0x01 + *(UCHAR*)(&m_TanslationSpeed) + *((UCHAR*)(&m_TanslationSpeed) + 1)
		+ *(UCHAR*)(&m_Yaw) + *((UCHAR*)(&m_Yaw) + 1)
		+ *(UCHAR*)(&m_RotationAngleSpeed) + *((UCHAR*)(&m_RotationAngleSpeed) + 1);
	Send_Buff[11] = sum;
	//清除串口的所有操作							   
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 12)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

void encoder_get(unsigned short m_TanslationSpeed, short m_Yaw, short m_RotationAngleSpeed)
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x03;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x04;
	Send_Buff[5] = 0x09;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

void battery_get()
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x03;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x03;
	Send_Buff[5] = 0x08;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

void ladar_open()
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x03;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x05;
	Send_Buff[5] = 0x0a;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}


void ladar_close()
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x03;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x06;
	Send_Buff[5] = 0x0b;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}



void arm_motor_back()
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x05;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x01;
	Send_Buff[5] = 0x08;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

void arm_motor_close()
{
	UCHAR sum = 0;
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x05;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x02;
	Send_Buff[5] = 0x09;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

void arm_motor_recovery()
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x05;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = 0x03;
	Send_Buff[5] = 0x0a;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}


void arm_motion(BYTE dongzuo_n)
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x05;
	Send_Buff[3] = 0x03;
	Send_Buff[4] = 0x04;
	Send_Buff[5] = dongzuo_n;
	Send_Buff[6] = 0x0C + dongzuo_n;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 7)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}


void light(BYTE brightness)
{
	Send_Buff[0] = 0x5A;
	Send_Buff[1] = 0x5A;
	Send_Buff[2] = 0x07;
	Send_Buff[3] = 0x02;
	Send_Buff[4] = brightness;
	Send_Buff[5] = brightness + 0x09;
	PurgeComm(m_Comm1.hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//调用PurgeComm函数可以终止正在进行的读写操作，该函数还会清除输入或输出缓冲区中的内容。
	if (m_Comm1.WriteChar(Send_Buff, 6)) {}
	else { MessageBox(NULL, L"发送失败", L"错误", 1); }
}

int battery()
{
	battery_get();
	m_Comm1.ReceiveChar(Get_Buff,8);
	if (Get_Buff[0]==0xa5)
	{
		return int(Get_Buff[6]);
	}
	Sleep(500);
}

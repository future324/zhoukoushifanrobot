
#include <iostream>
#include "USART1.h"
#include"tts1.h"
using namespace std;
bool receiveValued = 1;
Comm1::Comm1()
{
	hComm = NULL;
	rev_byte_count = 0;
}
bool Comm1::openport(LPCTSTR portname)//打开串口
{
	hComm = CreateFile(portname, //串口号
		GENERIC_READ | GENERIC_WRITE, //允许读写
		0, //通讯设备必须以独占方式打开
		0, //无安全属性
		OPEN_EXISTING, //通讯设备已存在
		FILE_FLAG_OVERLAPPED, //异步I/O
		0); //通讯设备不能用模板打开
	if (hComm == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hComm);
		return FALSE;
	}
	else
		return true;
}

bool Comm1::setupdcb(int rate_arg)//设置DCB
{
	DCB dcb;
	int rate = rate_arg;
	memset(&dcb, 0, sizeof(dcb));
	if (!GetCommState(hComm, &dcb))//获取当前DCB配置
		return FALSE;
	// set DCB to configure the serial port
	dcb.DCBlength = sizeof(dcb);
	/* ---------- Serial Port Config ------- */

	dcb.BaudRate = rate;      //波特率
	dcb.Parity = NOPARITY;    //无奇偶校验
	dcb.fParity = 0;          //是否进行奇偶校验  不进行
	dcb.StopBits = ONESTOPBIT;//1位停止位
	dcb.ByteSize = 8;         //8位二进制
	dcb.fOutxCtsFlow = 0;
	dcb.fOutxDsrFlow = 0;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = 0;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fOutX = 0;
	dcb.fInX = 0;
	/* ----------------- misc parameters ----- */
	dcb.fErrorChar = 0;
	dcb.fBinary = 1;
	dcb.fNull = 0;
	dcb.fAbortOnError = 0;
	dcb.wReserved = 0;
	dcb.XonLim = 2;
	dcb.XoffLim = 4;
	dcb.XonChar = 0x13;
	dcb.XoffChar = 0x19;
	dcb.EvtChar = 0;
	// set DCB
	if (!SetCommState(hComm, &dcb))
		return false;
	else
		return true;
}

bool Comm1::setuptimeout(DWORD ReadInterval, DWORD ReadTotalMultiplier, DWORD ReadTotalconstant, DWORD WriteTotalMultiplier, DWORD WriteTotalconstant)
{
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = ReadInterval;
	timeouts.ReadTotalTimeoutConstant = ReadTotalconstant;
	timeouts.ReadTotalTimeoutMultiplier = ReadTotalMultiplier;
	timeouts.WriteTotalTimeoutConstant = WriteTotalconstant;
	timeouts.WriteTotalTimeoutMultiplier = WriteTotalMultiplier;
	if (!SetCommTimeouts(hComm, &timeouts))
		return false;
	else
		return true;
}
COMSTAT comstat;
OVERLAPPED m_ov;
char Buff[200] = { 0 };
DWORD WINAPI ttsThreadProc(LPVOID lpParameter)
{
	explain(stationindex);
	return 0;
}
bool Comm1::ReceiveChar()
{
	BOOL bRead = TRUE;
	BOOL bResult = TRUE;
	DWORD BytesRead = 0;
	DWORD dwError = 0;
	int m_Count = 0;
	receiveValued = 1;
	unsigned char RXBuff = 0;
	ttsThread = CreateThread(NULL, 0, ttsThreadProc, NULL, 0, NULL);
	CloseHandle(ttsThread);
	while(receiveValued)
	{
		Sleep(10);//延时的目的是为了降低CPU的使用率
		bResult = ClearCommError(hComm, &dwError, &comstat);
		if (comstat.cbInQue == 0)//输入缓冲区字节数为0
			continue;
		if (bRead)
		{
			bResult = ReadFile(hComm,  // Handle to COMM port
				&RXBuff,               // RX Buffer Pointer
				1,                     // Read one byte
				&BytesRead,            // Stores number of bytes read实际读出的字节个数
				&m_ov);                // pointer to the m_ov structure

									   // cout << (INT16)BytesRead << endl;  //实际读出的字节数为零的话，主要在于缓冲时间没有写对
			cout << "0x" << hex << (int)RXBuff << endl;
			//printf("%02X ", RXBuff);

			Buff[m_Count] = RXBuff;
			m_Count++;
			if (m_Count == 7 && Buff[6] == 0x57)
			{
				m_Count = 0;
				//cout << "到站点" << endl;
				//MessageBox(NULL, L"createdlg error", NULL, SW_SHOWNORMAL);
				stationindex++;
				 ttsThread = CreateThread(NULL, 0, ttsThreadProc, NULL, 0, NULL);
				CloseHandle(ttsThread);
				InvalidateRect(mydlg, NULL, FALSE);
			}
			if (m_Count == 6 && Buff[5] == 0x0E)
			{
				m_Count = 0;
				ttsValued1 = 0;
				if (ttsThread != NULL)
				{
					TerminateThread(ttsThread, 1);
				}
				ttsThread == NULL;
				//cout << "开始巡线" << endl;

			}
			if (m_Count == 6 && Buff[5] == 0x0F)
			{
				m_Count = 0;
				ttsValued1 = 0;
				if (ttsThread!=NULL)
				{
					TerminateThread(ttsThread, 1);
				}
				ttsThread == NULL;
				//cout << "停止" << endl;
			}

			if (!bResult)
			{
				switch (dwError = GetLastError())
				{
				case ERROR_IO_PENDING:
				{
					bRead = FALSE;
					break;
				}
				default:
				{
					break;
				}
				}
			}
			else
			{
				bRead = TRUE;

			}
		} // close if (bRead)
		if (!bRead)
		{
			bRead = TRUE;
			bResult = GetOverlappedResult(hComm,  // Handle to COMM port
				&m_ov,  // Overlapped structure
				&BytesRead,     // Stores number of bytes read
				TRUE);          // Wait flag
		}
	}
	return 0;
}

bool Comm1::WriteChar(BYTE* m_szWriteBuffer, DWORD m_nToSend)
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;
	DWORD BytesSent = 0;
	//HANDLE m_hWriteEvent;
	//ResetEvent(m_hWriteEvent);
	if (bWrite)
	{
		m_ov.Offset = 0;
		m_ov.OffsetHigh = 0;
		// Clear buffer
		bResult = WriteFile(hComm, // Handle to COMM Port
			m_szWriteBuffer, // Pointer to message buffer in calling finction
			m_nToSend,      // Length of message to send
			&BytesSent,     // Where to store the number of bytes sent
			&m_ov);        // Overlapped structure
		if (!bResult)
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
			case ERROR_IO_PENDING:
			{
				// continue to GetOverlappedResults()
				BytesSent = 0;
				bWrite = FALSE;
				break;
			}
			default:
			{
				// all other error codes
				break;
			}
			}
		}
	} // end if(bWrite)
	if (!bWrite)
	{
		bWrite = TRUE;
		bResult = GetOverlappedResult(hComm,   // Handle to COMM port
			&m_ov,     // Overlapped structure
			&BytesSent,    // Stores number of bytes sent
			TRUE);         // Wait flag

						   // deal with the error code
		if (!bResult)
		{
			printf("GetOverlappedResults() in WriteFile()");
		}
	} // end if (!bWrite)

	  // Verify that the data size send equals what we tried to send
	if (BytesSent != m_nToSend)
	{
		printf("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, strlen((char*)m_szWriteBuffer));
	}
	return true;
}





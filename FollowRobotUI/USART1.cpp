
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
bool Comm1::openport(LPCTSTR portname)//�򿪴���
{
	hComm = CreateFile(portname, //���ں�
		GENERIC_READ | GENERIC_WRITE, //�����д
		0, //ͨѶ�豸�����Զ�ռ��ʽ��
		0, //�ް�ȫ����
		OPEN_EXISTING, //ͨѶ�豸�Ѵ���
		FILE_FLAG_OVERLAPPED, //�첽I/O
		0); //ͨѶ�豸������ģ���
	if (hComm == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hComm);
		return FALSE;
	}
	else
		return true;
}

bool Comm1::setupdcb(int rate_arg)//����DCB
{
	DCB dcb;
	int rate = rate_arg;
	memset(&dcb, 0, sizeof(dcb));
	if (!GetCommState(hComm, &dcb))//��ȡ��ǰDCB����
		return FALSE;
	// set DCB to configure the serial port
	dcb.DCBlength = sizeof(dcb);
	/* ---------- Serial Port Config ------- */

	dcb.BaudRate = rate;      //������
	dcb.Parity = NOPARITY;    //����żУ��
	dcb.fParity = 0;          //�Ƿ������żУ��  ������
	dcb.StopBits = ONESTOPBIT;//1λֹͣλ
	dcb.ByteSize = 8;         //8λ������
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
		Sleep(10);//��ʱ��Ŀ����Ϊ�˽���CPU��ʹ����
		bResult = ClearCommError(hComm, &dwError, &comstat);
		if (comstat.cbInQue == 0)//���뻺�����ֽ���Ϊ0
			continue;
		if (bRead)
		{
			bResult = ReadFile(hComm,  // Handle to COMM port
				&RXBuff,               // RX Buffer Pointer
				1,                     // Read one byte
				&BytesRead,            // Stores number of bytes readʵ�ʶ������ֽڸ���
				&m_ov);                // pointer to the m_ov structure

									   // cout << (INT16)BytesRead << endl;  //ʵ�ʶ������ֽ���Ϊ��Ļ�����Ҫ���ڻ���ʱ��û��д��
			cout << "0x" << hex << (int)RXBuff << endl;
			//printf("%02X ", RXBuff);

			Buff[m_Count] = RXBuff;
			m_Count++;
			if (m_Count == 7 && Buff[6] == 0x57)
			{
				m_Count = 0;
				//cout << "��վ��" << endl;
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
				//cout << "��ʼѲ��" << endl;

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
				//cout << "ֹͣ" << endl;
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





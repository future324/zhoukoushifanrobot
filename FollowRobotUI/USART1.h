#pragma once
#include <windows.h>
#include<string>
using namespace std;
extern bool receiveValued;
class Comm1
{
public:

	HANDLE ttsThread;
	HANDLE hComm;
	COMSTAT comstat;
	OVERLAPPED m_ov;
	int rev_byte_count;
	Comm1();
	~Comm1() {
		CloseHandle(hComm);
	}
	bool openport(LPCTSTR portname);//打开串口

	bool setupdcb(int rate_arg);//设置DCB

	bool setuptimeout(DWORD ReadInterval, DWORD ReadTotalMultiplier, DWORD ReadTotalconstant, DWORD WriteTotalMultiplier, DWORD WriteTotalconstant);

	bool ReceiveChar();

	bool WriteChar(BYTE* m_szWriteBuffer, DWORD m_nToSend);

	

};

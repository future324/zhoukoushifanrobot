#pragma once
#pragma once
#include <windows.h>
#include<fstream>
#include <iostream>  
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include<gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
//���˵�����һ��ID
#pragma comment(lib, "winmm.lib")
#pragma  comment(lib,"Msimg32.lib")
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "psapi.h"
#include<Vfw.h>
#pragma comment (lib, "Vfw32.lib")
#pragma comment(lib, "psapi.lib") 
#include"resource.h"

#include "recongizer.h"
#include "access.h"
#include "tts.h"
#include "wave2txt.h"
#include"resource.h"
std::vector<string> search_ID;
std::ofstream fout;
std::string rihght_answer;
#include"termb.h"
#include"tools.hpp"
#define count1 6
#define  tuichu  "�˳�"
#define chatstart "����"

int cout_time_1 = 0;
int cout_time_2 = 0;
int cout_time_3 = 0;
#include <shlobj.h>
TCHAR path[255];

//const char* doctor = "D:/result/result_for_doc.doc";
string sickness = "";




DWORD PID;
#define WINDOW_WIDTH	GetSystemMetrics(SM_CXSCREEN)//1920							
#define WINDOW_HEIGHT	GetSystemMetrics(SM_CYSCREEN)//1080							
#define WINDOW_TITLE	L"���������С��"

Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
ULONG_PTR m_pGdiToken;


HDC				g_hdc = NULL, g_mdc = NULL;
HBITMAP		g_hBitmap, g_jqrmap, g_startmap = NULL;
BOOL						Windows_CleanUp(HWND hwnd);
HMENU hmenu;//�˵����
HFONT font;//������

LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  //���ڹ��̺���
WNDCLASSEX defaultwndclass =
{
	sizeof(WNDCLASSEX),
	CS_HREDRAW | CS_VREDRAW,
	WndProc,
	0,
	0,
	0 ,
	NULL,
	LoadCursor(NULL, IDC_ARROW),
	NULL,
	NULL,
	L"mywindow"
};
INT_PTR CALLBACK  yaofangDlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);  //�Ի�����̺���



#include <fstream>

#include"Robotmove.hpp"
void prompt(std::string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "��ʾ��   " << str << endl;
}

void robot(std::string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	cout << "O_o:   " << str << endl;
}

void robot_speak(std::string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	cout << "O_o:   " << str << endl;
	tts(str.c_str());
}

void man(std::string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "^_^:   " << str << endl << endl << endl << endl;
}



int writefile_data(std::string input_str, string name)//д�����ݺ���
{
	
	fout.open(name.c_str(), std::ios::app);
	fout << input_str ;
	fout << std::flush;
	fout.close();
	return 0;
}

std::string getallstr()
{
	std::string str;
	do
	{
		cout_time_1++;
		if (cout_time_1 == count1)
		{
			tts("��ⲻ���������룬�����˳���");
			return "null";
		}
		broadcast(L"start.wav");
		str = recong();
	} while (str.empty());
	cout_time_1 = 0;
	man(str);
	return str;
}
void SetImageFrame(HWND m_hWnd, TCHAR* FileName, int x, int y, int width, int height)
{

	Gdiplus::Image *m_pImageBack;

	m_pImageBack = Gdiplus::Image::FromFile(FileName);
	//int m_BakWidth = m_pImageBack->GetWidth(); 
	//int m_BakHeight = m_pImageBack->GetHeight();  
	HDC hdcTemp = GetDC(m_hWnd);//�õ�����DC 
	Gdiplus::Graphics graph(hdcTemp);//GDI��ͼ��DC 
	graph.DrawImage(m_pImageBack, x, y, width, height);
	graph.ReleaseHDC(hdcTemp);
	DeleteDC(hdcTemp);
	hdcTemp = NULL;
}
BOOL Windows_CleanUp(HWND hwnd)
{
	//�ͷ���Դ����
	DeleteObject(g_hBitmap);
	DeleteDC(g_mdc);
	return TRUE;
}
std::wstring stringToWstring(const std::string& str)
{
	LPCSTR pszSrc = str.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
	if (nLen == 0)
		return std::wstring(L"");

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring wstr(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;

	return wstr;
}
std::string TCHAR2STRING(TCHAR  *STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	return str;
}
void YesPaint(const wchar_t * que)
{
	FlushRect({ 1150,480,1500,540 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[512];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	RECT Rect = { 1150,480,1500,540 };
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(25, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"΢���ź�"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void NoPaint(const wchar_t * que)
{
	FlushRect({ 1150,540,1500,600 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[512];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	RECT Rect = { 1150,540,1500,600 };
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(25, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"΢���ź�"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void QuestionPaint(const wchar_t * que)
{
	FlushRect({ 1150,300,1550,450 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[512];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	RECT Rect = { 1150,300,1500,450 };
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(25, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"΢���ź�"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	DrawText(g_hdc, szText, size+ 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void shortPaint(const wchar_t * que, int x, int y)
{
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(20, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"����"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	TextOut(g_hdc, x, y, que, size);
}
void BigPaint(const wchar_t * que, int x, int y)
{
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(29, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"����"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	TextOut(g_hdc, x, y, que, size);
}

DWORD ProcessToPID(const wchar_t *InputProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	HANDLE hProcess = NULL;
	HMODULE hMod = NULL;
	TCHAR szProcessName[MAX_PATH] = L"UnknownProcess";



	// ����Ŀǰ�ж��ٽ���, aProcesses[]���������Ч�Ľ���PIDs
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 0;
	}

	cProcesses = cbNeeded / sizeof(DWORD);
	// ����Ч��PID�������еĽ���
	for (i = 0; i < cProcesses; i++)
	{
		// ���ض�PID�Ľ���
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, aProcesses[i]);
		// ȡ���ض�PID�Ľ�����
		if (hProcess)
		{
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod,
					szProcessName, sizeof(szProcessName));
				//��ȡ�õĽ�����������Ľ������Ƚϣ�����ͬ�򷵻ؽ���PID
				if (!_wcsicmp(szProcessName, InputProcessName))
				{
					CloseHandle(hProcess);
					return aProcesses[i];
				}
			}
		}//end of if ( hProcess )
	}//end of for
	 //û���ҵ���Ӧ�Ľ�����������0
	CloseHandle(hProcess);
	return 0;
}


void promptPaint(const char * que, int x, int y)
{
	const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(22, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"΢���ź�"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), question);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	//TextOut(g_hdc, x, y, szText, size+1);
}
void promptPaintYellow(const wchar_t * que, int x, int y)
{
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(22, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"΢���ź�"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	TextOut(g_hdc, x, y, szText, size + 1);
}


void yaofangpaint(const wchar_t* que, HWND hwnd)
{
	RECT Rect = { 100,110,850,500 };
	//FlushRect({ 100,200,500,400 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[600];
	//HWND hwnd = CreateDialog((HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_FORMVIEW), hwnd, (DLGPROC)DlgProc);

	//HWND hwnd = FindWindow(L"mywindow", L"���������С��");
	
	g_hdc = GetDC(hwnd);  //��ȡ�豸�������
	font = CreateFont(28, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		L"����"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(0, 0, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
	//Sleep(10);
	DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}
std::string inputstr;//�����ϳɺ�ľ���
int str_Que;//���������

AdoAccess dataBase;//��ʼ��,��ȡ���е��ֶ��������ݣ�����ʾ
_variant_t var_ques_ID, var_Que, var_questions, var_Y, var_N, var_answers;
std::string str_ques_ID, str_questions, str_Y, str_N, str_answers;

/*
@param:
File_Selected---Select from the specified from.
putstr---Input a sentence.
index_ID---The first to be selected.
*/
int dlgquit=1 ;
std::string access_out(_variant_t  File_Selected, std::string putstr, std::string index_ID)
{
	std::string inputstr;//�����ϳɺ�ľ���
	do
	{
		dataBase.OnInitADOConn();
		dataBase.HX_pRecordset.CreateInstance("ADODB.Recordset");
		dataBase.HX_pRecordset->Open(File_Selected, dataBase.HX_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);//ѡ����ΪTest�ı��  

		while (!dataBase.HX_pRecordset->adoEOF)//���δ����
		{
			var_ques_ID = dataBase.HX_pRecordset->GetCollect("ques_ID");//�����������ַ
			var_Que = dataBase.HX_pRecordset->GetCollect("Que");//���������
			var_questions = dataBase.HX_pRecordset->GetCollect("questions");//����
			var_Y = dataBase.HX_pRecordset->GetCollect("Y");//�϶��ش��������
			var_N = dataBase.HX_pRecordset->GetCollect("N");//�񶨻ش��������
			var_answers = dataBase.HX_pRecordset->GetCollect("answers");//�õ������յĴ�

			str_ques_ID = _com_util::ConvertBSTRToString((_bstr_t)var_ques_ID);//str_ques_ID��str_Que����Ϊ�գ����򱨴�
			str_Que = var_Que.intVal;


			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == -2)//������͡��������������������������д����,����������
			{

				str_questions = _com_util::ConvertBSTRToString((_bstr_t)var_questions);
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);
				str_answers = _com_util::ConvertBSTRToString((_bstr_t)var_answers);

				/*tts(str_questions.c_str());
				tts(str_Y.c_str());
				tts(str_N.c_str());*/

				robot_speak(str_questions);
				robot_speak(str_Y);
				robot_speak(str_N);
				robot(str_answers);

				dataBase.ExitConnect();


				robot_speak("���Ѿ�Ϊ���ƶ���ר�ŵ�������ʳ�����������ҩ������");
				/*writefile_data("��ϵĽ���� " + str_questions + "\n\n", doctor);
				writefile_data(str_Y + "\n\n", doctor);
				writefile_data(str_N + "\n\n", doctor);
				writefile_data(str_answers + "\n\n", doctor);*/

				//writefile_data(str_questions + "\n\n", sickness);
				//writefile_data(str_Y + "\n\n", sickness);
				//writefile_data(str_N + "\n\n", sickness);
				//writefile_data(str_answers + "\n\n", sickness);
				writefile_data("<p>", sickness);
				std::vector<std::string> resVec;
				str_answers = str_answers + "\n";
				int pos = str_answers.find("\n", 0);
				while (pos != string::npos)
				{
					string splitstring = str_answers.substr(0, pos);
					resVec.push_back("<br/></br></br>" + splitstring + "\n\n\n");
					str_answers = str_answers.substr(pos + 1, str_answers.size());
					//cout << srcstring.c_str();
					pos = str_answers.find("\n", 0);
				}
				for (size_t i = 0; i < resVec.size(); i++)
				{
					writefile_data(resVec[i], sickness);
					//cout << resVec[i];
				} 
				writefile_data("</p>", sickness);

				robot_speak("������ϱ����ҽ�����ߵ��ӱ��湩����ϸ�˽⣡");
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<pre>", sickness);
				writefile_data("									���ҽ���� ��ǩ����Ч��", sickness);
				writefile_data("</pre>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<pre>", sickness);
				writefile_data("									������ڣ�", sickness);
				writefile_data(people_time, sickness);
				writefile_data("</pre>", sickness);
				writefile_data("</body>", sickness);
				writefile_data("</html>", sickness);
				Sleep(500);
				ShellExecute(NULL, L"open", stringToWstring(sickness).c_str(), NULL, NULL, SW_SHOWNORMAL);
				return str_answers;
			}

			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == -1)//������͡�������������������������������
			{
				str_answers = _com_util::ConvertBSTRToString((_bstr_t)var_answers);
				dataBase.ExitConnect();
				return str_answers;
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 0)//������͡��������������������
			{
				str_answers = _com_util::ConvertBSTRToString((_bstr_t)var_answers);
				//tts(str_answers.c_str());
				robot_speak(str_answers);

				dataBase.ExitConnect();

				//writefile_data("��ϵĽ���� " + str_answers + "\n\n", doctor);
				//writefile_data(str_answers + "\n\n", sickness);
				return str_answers;
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 1)//�ж��Ƿ�����
			{
				str_questions = _com_util::ConvertBSTRToString((_bstr_t)var_questions);
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);

				prompt(str_Y);
				prompt(str_N);
				robot(str_questions);

				if (cout_time_2<1)   tts(str_questions.c_str());
				inputstr = getallstr();
				if (findstr_or(inputstr, { "�˳�","����","ֹͣ" }))
				{
					return tuichu;
				}
				if (inputstr == "null")
				{
					return "null";
				}

				if (decide_YN_or(str_N, inputstr) == true)
				{
					char last_in = index_ID[index_ID.length() - 1];//�ַ������һλ��һ
					index_ID = index_ID.substr(0, index_ID.length() - 1);
					last_in++;
					index_ID += last_in;

					//�����˵õ��Ľ����
					//writefile_data(str_questions, doctor);
					//writefile_data(inputstr + "\n\n", doctor);
					//writefile_data(str_questions, sickness);
					//writefile_data(inputstr + "\n\n", sickness);
				}
				else
				{
					if (decide_YN_or(str_Y, inputstr) == true)
					{
						index_ID += "a";//�ַ������һλ��a
										//�����˵õ��Ľ���϶�
						//writefile_data(str_questions, doctor);
						///writefile_data(inputstr + "\n\n", doctor);
						//writefile_data(str_questions, sickness);
						//writefile_data(inputstr + "\n\n", sickness);
					}
					else
					{
						cout_time_2++;
						if (cout_time_2 == 4)
						{
							cout_time_2 = 0;
							return "recycle";
						}
						cout_time_2>1 ? tts("�������ظ�һ�°ɣ��Ҹղ�û���壡") : tts("�������ظ�һ�飡");
						continue;
					}
				}
				cout_time_2 = 0;
			}

			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 2)//�������͵õ��ض��ĵ���
			{
				str_questions = _com_util::ConvertBSTRToString((_bstr_t)var_questions);
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);

				if (cout_time_2 < 1)
				{
					robot(str_questions);
					tts(str_questions.c_str());
				}
				inputstr = getallstr();
				if (inputstr == "null")
				{
					return "null";
				}
				if (findstr_or(inputstr, { "�˳�","����","ֹͣ" }))
				{
					return tuichu;
				}

				if (decide_YN_and(str_Y, inputstr) == true)
				{
					rihght_answer = decide_YN_and_getstr(str_Y, inputstr);//�õ�������Ҫ�Ĵ�
																		  //std::cout << rihght_answer << endl;

					/*writefile_data(str_questions, doctor);
					writefile_data(inputstr, doctor);
					writefile_data(rihght_answer + "\n\n", doctor);
					writefile_data(str_questions, sickness);
					writefile_data(inputstr + "\n\n", sickness);
					writefile_data(rihght_answer + "\n\n", sickness);*/
					index_ID += "a";
					//std::cout << "�϶��ش�" << std::endl;//�����˵õ��Ľ���϶�
					cout_time_2 = 0;
					return rihght_answer;
				}
				else
				{
					cout_time_2++;
					if (cout_time_2 == 4)
					{
						cout_time_2 = 0;
						return "recycle";
					}
					cout_time_2>1 ? tts("�������ظ�һ�°ɣ��Ҹղ�û���壡") : tts("�������ظ�һ�飡");
					continue;
				}
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 3)//ѡ������,�õ����յķ��Ͻ����ѡ��
			{
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);

				if (decide_YN_or(str_N, putstr) == true)
				{
					std::cout << str_N << std::endl;

					search_ID.push_back(index_ID);
					index_ID = index_ID.substr(0, index_ID.length() - 1);
					char last_in = index_ID[index_ID.length() - 1];
					last_in += 2;
					index_ID = last_in;
					index_ID += "a";

					//std::cout << "�񶨻ش�" << std::endl;//�����˵õ��Ľ����
				/*	writefile_data(str_questions, doctor);
					writefile_data(putstr, doctor);
					writefile_data(str_questions, sickness);
					writefile_data(inputstr + "\n\n", sickness);*/
				}
				else
				{//�ַ������һλ�Ӷ�
					index_ID = index_ID.substr(0, index_ID.length() - 1);
					char last_in = index_ID[index_ID.length() - 1];
					last_in += 2;
					index_ID = last_in;
					index_ID += "a";
				}
				if (index_ID == "{a")  return " ";
			}
			/*===========================================================================================================================================================================================*/



			/*===========================================================================================================================================================================================*/
			if (str_ques_ID == index_ID&&str_Que == 4)//ѡ������,�õ����յķ��Ͻ����ѡ��
			{
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);
				decide_YN_or_count(str_N, putstr);
				if (all_count >=1 )
				{
					//cout << "��⵽3�����ϵ��ֲ�������" << endl;
					return "over_three";
				}
				index_ID = index_ID.substr(0, index_ID.length() - 1);
				char last_in = index_ID[index_ID.length() - 1];
				last_in += 2;
				index_ID = last_in;
				index_ID += "a";
				if (index_ID == "{a")  return " ";
			}
			/*===========================================================================================================================================================================================*/
			dataBase.HX_pRecordset->MoveNext();
		}

		index_ID = index_ID.substr(0, index_ID.length() - 1);
		char last = index_ID[index_ID.length() - 1];
		index_ID = index_ID.substr(0, index_ID.length() - 1);
		last++;
		index_ID += last;
	} while (index_ID != "m");

	dataBase.ExitConnect();//ж��com���  
	return NULL;
}


std::string talk_robot()
{
	int count_1 = 0;
	while (1)//ͼ������˵Ľ���
	{
		broadcast(L"start.wav");
		std::string strstr = recong();
		//cout << strstr.length() << endl;
		if (strstr.empty() || strstr.length()<6)
		{
			count_1++;
			if (count_1 == 5)
			{
				robot_speak("�������𣬿��Գ��Ժ������찡��");
			}
			if (count_1 == 8)
			{
				//tts("��ⲻ���������룬�����˳���");
				return "null";
			}
			continue;
		}
		count_1 = 0;
		man(strstr);
		if (findstr_or(strstr, { "���뿴��","��Ҫ����","����Ҫ����","�����","����","��ѯ����","��ѯ����" ,"���","��ʼ����","������ʼ","����","������","��������","ʹ","��" }))
		{
			arm_motion(0x0a);
			Sleep(800);
			arm_motion(0x07);
			Sleep(200);
			return "kanbing";
		}
		if (findstr_or(strstr, { "����","�����ж�" }))
		{
			return "tizhipanduan";
		}
		if (findstr_or(strstr, { "�˳�","ֹͣ","����" }))
		{
			return "tuichu";
		}
		if (findstr_or(strstr, { "���" }))
		{
			arm_motion(0x06);
			Sleep(200);
			tts("���,�ܸ���Ϊ������");
			continue;
		}
		if (findstr_or(strstr, { "����","�ո���","��һ����" }))
		{
			arm_motion(0x01);
			Sleep(200);
			tts("�õģ����������ְɣ�");
			continue;
		}
		if (findstr_or(strstr, { "ӵ��","��һ��","��һ��","����" }))
		{
			arm_motion(0x04);
			Sleep(200);
			tts("��������һ�°ɣ�");
			continue;
		}
		if (findstr_or(strstr, { "̧ͷ","��ͷ","̧��ͷ" }))
		{
			arm_motion(0x07);
			Sleep(200);
			tts("�õģ����Ѿ��������ˣ�");
			continue;
		}
		if (findstr_or(strstr, { "ҡͷ", "ҡ��ͷ","ҡһ��ͷ" }))
		{
			arm_motion(0x02);
			Sleep(200);
			tts("��ҡ�Ҿ����ˣ���");
			continue;
		}
		if (findstr_or(strstr, { "��ͷ","���ͷ","��һ��ͷ" }))
		{
			arm_motion(0x0a);
			Sleep(800);
			arm_motion(0x07);
			Sleep(200);
			continue;
		}
		std::string strstr1 = tuling(strstr);
		if (findstr_or(strstr, { "��Ȼ����" }))
		{
			arm_motion(0x0a);
			Sleep(800);
			arm_motion(0x07);
			Sleep(200);
		}
		robot_speak(strstr1);
	}
	return "null";
}

bool situation(std::string str)
{
	if (str == "null")
	{
		return true;
	}
	if (str == "recycle")
	{
		robot_speak("��Ǹ������ⲻ������˵ʲô������ϵͳ�����˳����ټ���");
		return true;
	}
	if (str == tuichu)
	{
		std::string str1 = access_out("select *  from start", "l", "f");
		if (str1 == "null")
		{
			return true;
		}
		if (str1 == "recycle")
		{
			return true;
		}
		if (str1 == "Y")
		{
			robot_speak("�õģ������Ǽ�����!");
			return false;
		}
		if (str1 == "N")
		{
			robot_speak("ϣ�������彡���������´����İ�");
			arm_motion(0x0a);
			Sleep(200);
			light(0x02);
			Sleep(200);
			return true;
		}
		if (str1 == tuichu)
		{
			robot_speak("ϣ�������彡���������´����İ�");
			arm_motion(0x0a);
			Sleep(200);
			light(0x02);
			Sleep(200);
			return true;
		}
		/*robot_speak("ϣ�������彡���������´����İ�");
		return true;*/
	}
	return false;
}

bool situation_noasktuichu(std::string str)
{
	if (str == "null")
	{
		return true;
	}
	if (str == "recycle")
	{
		robot_speak("��Ǹ������ⲻ������˵ʲô������ϵͳ�����˳����ټ���");
		return true;
	}
	if (str == tuichu)
	{
		/*std::string str1= access_out("select *  from start", "l", "f");
		if (str1 == "null")
		{
		return true;
		}
		if (str1 == "recycle")
		{
		return true;
		}
		if (str1 == "Y")
		{
		robot_speak("�õģ������Ǽ�����!");
		return false;
		}
		if (str1 == "N")
		{
		robot_speak("ϣ�������彡���������´����İ�");
		return true;
		}*/
		robot_speak("ϣ�������彡���������´����İ�");
		return true;
	}
	return false;
}
INT_PTR yaofangDlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT queding_rect = { 300 ,700,410,755 };
	RECT tuichu_rect = { 700,700,810,755 };
	switch (message)
	{
	case WM_CREATE:
		SetWindowLong(hdlg, GWL_EXSTYLE, GetWindowLong(hdlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hdlg, RGB(255, 255, 255), 200, LWA_ALPHA);
		return 0;
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			int quedingvalue = (x > 200 && x < 300 && y>450 && y < 505);
			int tuichuvalue = (x > 600 && x < 700 && y>450 && y < 505);
			if (quedingvalue)
			{

			}
			if (tuichuvalue)
			{
				dlgquit = 0;
				DestroyWindow(hdlg);
			}
		}
	   break;
	case WM_PAINT:
		SetImageFrame(hdlg, L"img//bg2.jpg", 0, 0, 1000, 700);
		SetImageFrame(hdlg, L"img//queding.png", 200, 450, 100, 55);
		SetImageFrame(hdlg, L"img//tuichu.png", 600,450, 100, 55);
		yaofangpaint(stringToWstring(str_answers.c_str()).c_str(), hdlg);
		break;

	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			// ���ִ���˹ر�  
			// ���ٶԻ��򣬽��յ�WM_DESTROY��Ϣ  
			dlgquit = 0;
			DestroyWindow(hdlg);
		}
		return 0;
	
	}

	return (INT_PTR)FALSE;

}
bool ID_card()
{
	char chCode = 0x0;
	int nPort = 0;
	int nTickCount = 0;
	int nRet = 0;
	FILE* pFile = NULL;
	errno_t err;
	unsigned char cardData[256] = { 0x0 };
	setlocale(LC_ALL, "chs");
	int cout_all = 0;
	MSG msg = { 0 };		//���岢��ʼ��msg
	while (cout_all<10&& msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			//QuestionPaint(stringToWstring(to_string(battery())).c_str());
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);			//�ַ�һ����Ϣ�����ڳ���
		}
		cout_all++;
		if (0 >= (nPort = InitCommExt()))
		{
			printf("open reader success, port=%d\n", nPort);
			//	return 0;
		}
		printf("***************************************\n");
		if (1 == Authenticate())
		{
			nTickCount = GetTickCount();
			while (1 != (nRet = Read_Content(1)) && GetTickCount() - nTickCount <= 1000)
			{
				Sleep(50);
			}
			if (nRet != 1)
			{
				printf("����ʧ�ܣ������ԣ�\n");
			}
			else
			{
				if (1 == GetBmpPhoto("xp.wlt"))
				{
					printf("��Ƭ�����ɹ�,�ļ�����zp.bmp��\n");
				}
				if (err = (fopen_s(&pFile, "wz.txt", "rb")) == 0)
				{
					memset(cardData, 0x0, 256);
					fread(cardData, 1, 256, pFile);
					fclose(pFile);
					pFile = NULL;
					analyzeCardData(cardData);
					printf("��������\n");
					broadcast(L"ding.wav");
					break;
				}
				else
				{
					printf("���ļ�ʧ��\n");
				}

			}
		}
		else
		{
			printf("Ѱ��ʧ�ܣ���ſ���\n");
		}
		if (cout_all % 2 == 0)
		{
			robot_speak("δ��⵽���֤���������·���");
			//broadcast(L"ding.wav");
		}
		Sleep(2000);
	}
	CloseComm();
	
	if (cout_all == 10)
	{
		cout_all = 0;
		return false;
	}
	cout_all = 0;
	return true;
}

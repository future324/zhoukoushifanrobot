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
//给菜单定义一个ID
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
#define  tuichu  "退出"
#define chatstart "聊天"

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
#define WINDOW_TITLE	L"服务机器人小周"

Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
ULONG_PTR m_pGdiToken;


HDC				g_hdc = NULL, g_mdc = NULL;
HBITMAP		g_hBitmap, g_jqrmap, g_startmap = NULL;
BOOL						Windows_CleanUp(HWND hwnd);
HMENU hmenu;//菜单句柄
HFONT font;//字体句柄

LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  //窗口过程函数
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
INT_PTR CALLBACK  yaofangDlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);  //对话框过程函数



#include <fstream>

#include"Robotmove.hpp"
void prompt(std::string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "提示：   " << str << endl;
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



int writefile_data(std::string input_str, string name)//写入数据函数
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
			tts("检测不到语音输入，即将退出！");
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
	HDC hdcTemp = GetDC(m_hWnd);//得到窗体DC 
	Gdiplus::Graphics graph(hdcTemp);//GDI画图的DC 
	graph.DrawImage(m_pImageBack, x, y, width, height);
	graph.ReleaseHDC(hdcTemp);
	DeleteDC(hdcTemp);
	hdcTemp = NULL;
}
BOOL Windows_CleanUp(HWND hwnd)
{
	//释放资源对象
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
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	RECT Rect = { 1150,480,1500,540 };
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"微软雅黑"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	//DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void NoPaint(const wchar_t * que)
{
	FlushRect({ 1150,540,1500,600 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[512];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	RECT Rect = { 1150,540,1500,600 };
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"微软雅黑"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	//DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void QuestionPaint(const wchar_t * que)
{
	FlushRect({ 1150,300,1550,450 });
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[512];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	RECT Rect = { 1150,300,1500,450 };
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"微软雅黑"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	DrawText(g_hdc, szText, size+ 1, &Rect, DT_LEFT | DT_WORDBREAK);
}

void shortPaint(const wchar_t * que, int x, int y)
{
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"宋体"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	TextOut(g_hdc, x, y, que, size);
}
void BigPaint(const wchar_t * que, int x, int y)
{
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"宋体"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
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



	// 计算目前有多少进程, aProcesses[]用来存放有效的进程PIDs
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 0;
	}

	cProcesses = cbNeeded / sizeof(DWORD);
	// 按有效的PID遍历所有的进程
	for (i = 0; i < cProcesses; i++)
	{
		// 打开特定PID的进程
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, aProcesses[i]);
		// 取得特定PID的进程名
		if (hProcess)
		{
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod,
					szProcessName, sizeof(szProcessName));
				//将取得的进程名与输入的进程名比较，如相同则返回进程PID
				if (!_wcsicmp(szProcessName, InputProcessName))
				{
					CloseHandle(hProcess);
					return aProcesses[i];
				}
			}
		}//end of if ( hProcess )
	}//end of for
	 //没有找到相应的进程名，返回0
	CloseHandle(hProcess);
	return 0;
}


void promptPaint(const char * que, int x, int y)
{
	const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"微软雅黑"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 255));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), question);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	//DrawText(g_hdc, question, size, &Rect, DT_LEFT | DT_WORDBREAK);
	//TextOut(g_hdc, x, y, szText, size+1);
}
void promptPaintYellow(const wchar_t * que, int x, int y)
{
	//const wchar_t *question = stringToWstring(que).c_str();
	int size;
	TCHAR szText[1024];
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"微软雅黑"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(255, 255, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
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

	//HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	
	g_hdc = GetDC(hwnd);  //获取设备环境句柄
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
		L"宋体"); // lpszFac
	SelectObject(g_hdc, font);
	SetTextColor(g_hdc, RGB(0, 0, 0));
	SetBkMode(g_hdc, TRANSPARENT);
	//SetBkColor(g_hdc, RGB(0, 0, 0));
	size = wsprintf(szText, TEXT("%s\n"), que);
	//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
	//Sleep(10);
	DrawText(g_hdc, szText, size + 1, &Rect, DT_LEFT | DT_WORDBREAK);
}
std::string inputstr;//语音合成后的句子
int str_Que;//问题的类型

AdoAccess dataBase;//初始化,读取其中的字段所有数据，并显示
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
	std::string inputstr;//语音合成后的句子
	do
	{
		dataBase.OnInitADOConn();
		dataBase.HX_pRecordset.CreateInstance("ADODB.Recordset");
		dataBase.HX_pRecordset->Open(File_Selected, dataBase.HX_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);//选择名为Test的表格  

		while (!dataBase.HX_pRecordset->adoEOF)//查表未结束
		{
			var_ques_ID = dataBase.HX_pRecordset->GetCollect("ques_ID");//问题的索引地址
			var_Que = dataBase.HX_pRecordset->GetCollect("Que");//问题的类型
			var_questions = dataBase.HX_pRecordset->GetCollect("questions");//问题
			var_Y = dataBase.HX_pRecordset->GetCollect("Y");//肯定回答的特征词
			var_N = dataBase.HX_pRecordset->GetCollect("N");//否定回答的特征词
			var_answers = dataBase.HX_pRecordset->GetCollect("answers");//得到的最终的答案

			str_ques_ID = _com_util::ConvertBSTRToString((_bstr_t)var_ques_ID);//str_ques_ID和str_Que不能为空，否则报错
			str_Que = var_Que.intVal;


			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == -2)//结果类型—————问题语音读出，结果写出来,起到链接作用
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


				robot_speak("我已经为您制定了专门的生活饮食调理意见及中药处方。");
				/*writefile_data("诊断的结果： " + str_questions + "\n\n", doctor);
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

				robot_speak("您的诊断报告我将会出具电子报告供您详细了解！");
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<pre>", sickness);
				writefile_data("									审核医生： （签字有效）", sickness);
				writefile_data("</pre>", sickness);
				writefile_data("<br/>", sickness);	
				writefile_data("<br/>", sickness);
				writefile_data("<pre>", sickness);
				writefile_data("									诊断日期：", sickness);
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

			if (str_ques_ID == index_ID&&str_Que == -1)//结果类型—————语音不读出，起到链接作用
			{
				str_answers = _com_util::ConvertBSTRToString((_bstr_t)var_answers);
				dataBase.ExitConnect();
				return str_answers;
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 0)//结果类型—————语音读出结果
			{
				str_answers = _com_util::ConvertBSTRToString((_bstr_t)var_answers);
				//tts(str_answers.c_str());
				robot_speak(str_answers);

				dataBase.ExitConnect();

				//writefile_data("诊断的结果： " + str_answers + "\n\n", doctor);
				//writefile_data(str_answers + "\n\n", sickness);
				return str_answers;
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 1)//判断是否类型
			{
				str_questions = _com_util::ConvertBSTRToString((_bstr_t)var_questions);
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);

				prompt(str_Y);
				prompt(str_N);
				robot(str_questions);

				if (cout_time_2<1)   tts(str_questions.c_str());
				inputstr = getallstr();
				if (findstr_or(inputstr, { "退出","结束","停止" }))
				{
					return tuichu;
				}
				if (inputstr == "null")
				{
					return "null";
				}

				if (decide_YN_or(str_N, inputstr) == true)
				{
					char last_in = index_ID[index_ID.length() - 1];//字符串最后一位加一
					index_ID = index_ID.substr(0, index_ID.length() - 1);
					last_in++;
					index_ID += last_in;

					//机器人得到的结果否定
					//writefile_data(str_questions, doctor);
					//writefile_data(inputstr + "\n\n", doctor);
					//writefile_data(str_questions, sickness);
					//writefile_data(inputstr + "\n\n", sickness);
				}
				else
				{
					if (decide_YN_or(str_Y, inputstr) == true)
					{
						index_ID += "a";//字符串最后一位加a
										//机器人得到的结果肯定
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
						cout_time_2>1 ? tts("请您再重复一下吧，我刚才没听清！") : tts("请您再重复一遍！");
						continue;
					}
				}
				cout_time_2 = 0;
			}

			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 2)//问题类型得到特定的单词
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
				if (findstr_or(inputstr, { "退出","结束","停止" }))
				{
					return tuichu;
				}

				if (decide_YN_and(str_Y, inputstr) == true)
				{
					rihght_answer = decide_YN_and_getstr(str_Y, inputstr);//得到最终想要的答案
																		  //std::cout << rihght_answer << endl;

					/*writefile_data(str_questions, doctor);
					writefile_data(inputstr, doctor);
					writefile_data(rihght_answer + "\n\n", doctor);
					writefile_data(str_questions, sickness);
					writefile_data(inputstr + "\n\n", sickness);
					writefile_data(rihght_answer + "\n\n", sickness);*/
					index_ID += "a";
					//std::cout << "肯定回答！" << std::endl;//机器人得到的结果肯定
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
					cout_time_2>1 ? tts("请您再重复一下吧，我刚才没听清！") : tts("请您再重复一遍！");
					continue;
				}
			}
			/*===========================================================================================================================================================================================*/

			/*===========================================================================================================================================================================================*/

			if (str_ques_ID == index_ID&&str_Que == 3)//选择类型,得到最终的符合结果的选项
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

					//std::cout << "否定回答" << std::endl;//机器人得到的结果否定
				/*	writefile_data(str_questions, doctor);
					writefile_data(putstr, doctor);
					writefile_data(str_questions, sickness);
					writefile_data(inputstr + "\n\n", sickness);*/
				}
				else
				{//字符串最后一位加二
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
			if (str_ques_ID == index_ID&&str_Que == 4)//选择类型,得到最终的符合结果的选项
			{
				str_Y = _com_util::ConvertBSTRToString((_bstr_t)var_Y);
				str_N = _com_util::ConvertBSTRToString((_bstr_t)var_N);
				decide_YN_or_count(str_N, putstr);
				if (all_count >=1 )
				{
					//cout << "检测到3及以上的种病！！！" << endl;
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

	dataBase.ExitConnect();//卸载com组件  
	return NULL;
}


std::string talk_robot()
{
	int count_1 = 0;
	while (1)//图灵机器人的接入
	{
		broadcast(L"start.wav");
		std::string strstr = recong();
		//cout << strstr.length() << endl;
		if (strstr.empty() || strstr.length()<6)
		{
			count_1++;
			if (count_1 == 5)
			{
				robot_speak("您还在吗，可以尝试和我聊天啊！");
			}
			if (count_1 == 8)
			{
				//tts("检测不到语音输入，即将退出！");
				return "null";
			}
			continue;
		}
		count_1 = 0;
		man(strstr);
		if (findstr_or(strstr, { "我想看病","我要看病","我想要看病","不舒服","问诊","咨询病情","咨询问题" ,"诊断","开始看病","看病开始","难受","不好受","身体难受","痛","疼" }))
		{
			arm_motion(0x0a);
			Sleep(800);
			arm_motion(0x07);
			Sleep(200);
			return "kanbing";
		}
		if (findstr_or(strstr, { "体质","体质判断" }))
		{
			return "tizhipanduan";
		}
		if (findstr_or(strstr, { "退出","停止","结束" }))
		{
			return "tuichu";
		}
		if (findstr_or(strstr, { "你好" }))
		{
			arm_motion(0x06);
			Sleep(200);
			tts("你好,很高兴为您服务");
			continue;
		}
		if (findstr_or(strstr, { "握手","握个手","握一下手" }))
		{
			arm_motion(0x01);
			Sleep(200);
			tts("好的，我们来握手吧！");
			continue;
		}
		if (findstr_or(strstr, { "拥抱","抱一抱","抱一下","抱抱" }))
		{
			arm_motion(0x04);
			Sleep(200);
			tts("我们来抱一下吧！");
			continue;
		}
		if (findstr_or(strstr, { "抬头","仰头","抬个头" }))
		{
			arm_motion(0x07);
			Sleep(200);
			tts("好的，我已经看见你了！");
			continue;
		}
		if (findstr_or(strstr, { "摇头", "摇个头","摇一下头" }))
		{
			arm_motion(0x02);
			Sleep(200);
			tts("再摇我就晕了！！");
			continue;
		}
		if (findstr_or(strstr, { "点头","点个头","点一下头" }))
		{
			arm_motion(0x0a);
			Sleep(800);
			arm_motion(0x07);
			Sleep(200);
			continue;
		}
		std::string strstr1 = tuling(strstr);
		if (findstr_or(strstr, { "当然能了" }))
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
		robot_speak("抱歉，我理解不了您在说什么，语音系统即将退出，再见！");
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
			robot_speak("好的，那我们继续吧!");
			return false;
		}
		if (str1 == "N")
		{
			robot_speak("希望您身体健康，我们下次再聊吧");
			arm_motion(0x0a);
			Sleep(200);
			light(0x02);
			Sleep(200);
			return true;
		}
		if (str1 == tuichu)
		{
			robot_speak("希望您身体健康，我们下次再聊吧");
			arm_motion(0x0a);
			Sleep(200);
			light(0x02);
			Sleep(200);
			return true;
		}
		/*robot_speak("希望您身体健康，我们下次再聊吧");
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
		robot_speak("抱歉，我理解不了您在说什么，语音系统即将退出，再见！");
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
		robot_speak("好的，那我们继续吧!");
		return false;
		}
		if (str1 == "N")
		{
		robot_speak("希望您身体健康，我们下次再聊吧");
		return true;
		}*/
		robot_speak("希望您身体健康，我们下次再聊吧");
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
			// 如果执行了关闭  
			// 销毁对话框，将收到WM_DESTROY消息  
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
	MSG msg = { 0 };		//定义并初始化msg
	while (cout_all<10&& msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			//QuestionPaint(stringToWstring(to_string(battery())).c_str());
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
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
				printf("读卡失败，请重试！\n");
			}
			else
			{
				if (1 == GetBmpPhoto("xp.wlt"))
				{
					printf("照片解析成功,文件名：zp.bmp！\n");
				}
				if (err = (fopen_s(&pFile, "wz.txt", "rb")) == 0)
				{
					memset(cardData, 0x0, 256);
					fread(cardData, 1, 256, pFile);
					fclose(pFile);
					pFile = NULL;
					analyzeCardData(cardData);
					printf("读卡结束\n");
					broadcast(L"ding.wav");
					break;
				}
				else
				{
					printf("打开文件失败\n");
				}

			}
		}
		else
		{
			printf("寻卡失败，请放卡！\n");
		}
		if (cout_all % 2 == 0)
		{
			robot_speak("未检测到身份证，请您重新放置");
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

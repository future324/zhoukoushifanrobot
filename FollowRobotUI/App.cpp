#include"Mywindows.hpp"
#include"Robotmove.hpp"
#include <regex>
#include"cidaohang.h"
#include"tts1.h"
#include<process.h>
DWORD WINAPI DoctorProc(LPVOID lpParameter);
DWORD WINAPI MoveProc(LPVOID lpParameter);
DWORD WINAPI DlgThreadProc(LPVOID lpParameter); //线程对话框函数入口  
DWORD WINAPI jiangjieThreadProc(LPVOID lpParameter);
INT_PTR CALLBACK  DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);  //对话框过程函数


HANDLE  DoctorThread, MoveThread, DanceThread;//线程
bool Doctorstage, Movestage, Dancestage, Jiangjiestage,Followstage = 0;//线程状态
string  patientname, patientbirthday, patientAdress, patientsex;//患者信息
HANDLE dlg_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
HWND hwnd;
HWND mydlg;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

	WNDCLASSEX wndClass = defaultwndclass;
	wndClass.hInstance = hInstance;
	//wndClass.hbrBackground = CreateSolidBrush(RGB(180, 200, 200));
	wndClass.hIcon = (HICON)LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (!RegisterClassEx(&wndClass))
		return -1;
	HWND hwnd = CreateWindow(wndClass.lpszClassName, WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, hmenu, hInstance, NULL);

	//SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);    //调用ShowWindow函数来显示窗口
	UpdateWindow(hwnd);						//对窗口进行更新，就像我们买了新房子要装修一样
	MSG msg = { 0 };		//定义并初始化msg

	while (msg.message != WM_QUIT)			//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			//QuestionPaint(stringToWstring(to_string(battery())).c_str());
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
		}

	}
	Gdiplus::GdiplusShutdown(m_pGdiToken);
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static  int jiangjieclick,doctorclick, moveclick, danceclick, followclick;
	SHELLEXECUTEINFO ShExecInfo;
	HANDLE jiangjieThread=NULL;
	HANDLE DlgThread=NULL;
	switch (message)						//switch语句开始
	{

	case WM_CREATE:
		SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 250, LWA_ALPHA);
		break;
	case WM_COMMAND:

		break;

	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//按钮的范围，直接在这里改就好了。
		RECT Jiangjierect = { 150,700,220,770 };
		RECT Doctorrect = { 420,700,490,770 };
		RECT Moverect = { 690,700,780,770 };
		RECT Dancerect = { 975,700,1045,770 };
		RECT Followrect = { 1220,700,1290,770 };
		//
		int Jiangjievalue = (x > Jiangjierect.left&&x < Jiangjierect.right&&y<Jiangjierect.bottom&&y>Jiangjierect.top);
		int doctorValue = (x > Doctorrect.left && x < Doctorrect.right && y > Doctorrect.top && y < Doctorrect.bottom);
		int moveValue = (x > Moverect.left && x < Moverect.right && y > Moverect.top && y < Moverect.bottom);
		int danceValue = (x > Dancerect.left && x < Dancerect.right && y > Dancerect.top && y < Dancerect.bottom);
		int followValue = (x > Followrect.left && x < Followrect.right && y > Followrect.top && y < Followrect.bottom);

		if (Jiangjievalue&& moveclick % 2 != 1 && danceclick % 2 != 1 && followclick % 2 != 1&& doctorclick!=1)   jiangjieclick++;
		if (doctorValue&& moveclick % 2 != 1 && danceclick % 2 != 1 && followclick % 2 != 1&& jiangjieclick!=1)   doctorclick++;
		if (moveValue&& doctorclick % 2 != 1 && danceclick % 2 != 1 && followclick % 2 != 1 && jiangjieclick != 1) moveclick++;
		if (danceValue&&doctorclick % 2 != 1 && moveclick % 2 != 1 && followclick % 2 != 1 && jiangjieclick != 1) danceclick++;
		if (followValue&& doctorclick % 2 != 1 && moveclick % 2 != 1 && danceclick % 2 != 1 && jiangjieclick != 1)    followclick++;

		SetImageFrame(hwnd, L"img//shutdown2.png", 1300, 100, 70, 70);

		if (x>1300 && x<1370 && y>100 && y<170)
		{
			SendMessage(mydlg, WM_SYSCOMMAND, SC_CLOSE, 0);
			if (DlgThread != NULL)
			{
				TerminateThread(DlgThread, 1);
			}
			DlgThread = NULL;
			if (IDYES == MessageBox(hwnd, L"您是否要退出程序", L"提示！！！", MB_YESNO | MB_ICONQUESTION))
			{
				
				HANDLE dancehandle;
				close_MagneticNavigation();
				dancehandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"dance.exe"));
				if (dancehandle)
				{
					TerminateProcess(dancehandle, 0);
				}
				HANDLE followhandle;
				followhandle= OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"follow.exe"));
				if (followhandle)
				{
					TerminateProcess(followhandle, 0);
					Sleep(200);
				}
				arm_motion(0x0a);
				Sleep(200);
				light(0x02);
				Sleep(200);
				m_Comm1.~Comm();
				m_Comm1.openport(L"COM3", 115200);
				Sleep(100);
				DipanSpeedSet(0, 0, 0);
				Sleep(300);
				arm_motion(0x0a);
				Sleep(200);
				light(0x02);
				Sleep(200);
				ladar_close();
				Sleep(200);
				m_Comm1.~Comm();
				MSPLogout();
				ExitProcess(0);
				light(0x02);

			}
			else
			{

			}
			arm_motion(0x10);
		}

		if (jiangjieclick%2==1&&Jiangjievalue)
		{
			Jiangjiestage = 1;
			InvalidateRect(hwnd, &Jiangjierect, true);
			UpdateWindow(hwnd);
			ComInit(L"COM3", 115200);
			Sleep(100);

			open_MagneticNavigation();
			Sleep(100);
			open_eyes();
			Sleep(100);
			char* login_params = "appid = 59c066c4, work_dir = .";
			if (MSP_SUCCESS != MSPLogin(NULL, NULL, login_params))
			{
				MessageBox(NULL, L"login error", NULL, SW_SHOWNORMAL);
			}
			jiangjieThread = CreateThread(NULL, 0, jiangjieThreadProc, NULL, 0, NULL);
			CloseHandle(jiangjieThread);
			DlgThread = CreateThread(NULL, 0, DlgThreadProc, NULL, 0, NULL);
			CloseHandle(DlgThread);

		//WaitForSingleObject(dlg_handle, -1);
		}
		if (jiangjieclick % 2 == 0 && Jiangjievalue)
		{

			Jiangjiestage = 0;
			stationindex = 0;
			close_MagneticNavigation();
			Sleep(100);
			close_eyes();
			Sleep(100);

			ttsValued1 = 0;
			receiveValued = 0;
			InvalidateRect(hwnd, &Doctorrect, true);
			UpdateWindow(hwnd);
			if (jiangjieThread!=NULL)
			{
				TerminateThread(jiangjieThread, 1);
			}
			jiangjieThread = NULL;
			SendMessage(mydlg, WM_SYSCOMMAND, SC_CLOSE, 0);
			if (DlgThread!=NULL)
			{
				TerminateThread(DlgThread, 1);
			}
			DlgThread =NULL; 
			MSPLogout();
			com.~Comm1();
		}
		if (doctorclick % 2 == 1 && doctorValue)
		{
			bool open;
			open = m_Comm1.openport(L"COM3", 115200);
			if (open)
			{
				//MessageBox(NULL, L"串口打开成功",L"",1);
			}
			else
			{
				MessageBox(NULL, L"串口打开失败", L"", 1);

			}
			Doctorstage = 1;
			InvalidateRect(hwnd, &Doctorrect, true);
			UpdateWindow(hwnd);
			DoctorThread = CreateThread(NULL, 0, DoctorProc, NULL, 0, NULL); //第一个参数，使用默认的安全性；第二个参数，使用与调用函数的线程相同的栈大小
			CloseHandle(DoctorThread);
			/*arm_motion(0x07);
			Sleep(100);
			light(0x03);
			Sleep(100);*/

		}
		if (doctorclick % 2 == 0 && doctorValue&&doctorclick  != 0)
		{
			arm_motion(0x0a);
			Sleep(200);

			light(0x02);
			Sleep(200);

			Doctorstage = 0;
			ttsValued = 0;
			m_Comm1.~Comm();
			FlushRect({ 10,35,1200,235 });
			FlushRect({ 1100,500,1500,650 });
			InvalidateRect(hwnd, &Doctorrect, true);
			UpdateWindow(hwnd);
			MSPLogout();
			waveInClose(hWaveIn);
			TerminateThread(DoctorThread, 1);
		
		}
		if (moveclick % 2 == 1 && moveValue)
		{

			Movestage = 1;
			InvalidateRect(hwnd, &Moverect, true);
			UpdateWindow(hwnd);
			bool open;
			open = m_Comm1.openport(L"COM3", 115200);
			if (open)
			{
				//MessageBox(NULL, L"串口打开成功",L"",1);
			}
			else
			{
				MessageBox(NULL, L"串口打开失败", L"", 1);

			}
			Sleep(100);
			ladar_open();
			Sleep(100);
			light(0x01);
			Sleep(100);
			MoveThread = CreateThread(NULL, 0, MoveProc, NULL, 0, NULL);
			CloseHandle(MoveThread);
			

		}
		if (moveclick % 2 == 0 && moveValue&&moveclick!=0)
		{
			ladar_close();
			Sleep(100);

			light(0x02);
			Sleep(100);
			arm_motion(0x0a);
			Sleep(100);

			Movestage = 0;
			ttsValued = 0;
			InvalidateRect(hwnd, &Moverect, true);
			UpdateWindow(hwnd);
			MSPLogout();
			//broadcast(NULL);
			TerminateThread(MoveThread, EXIT_FAILURE);
			HANDLE musichandle;
			musichandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"musicplay.exe"));
			if (musichandle)
			{
				TerminateProcess(musichandle, 0);

			}
			m_Comm1.~Comm();
		}
		if (danceclick % 2 == 1 && danceValue)
		{
			Dancestage = 1;
			InvalidateRect(hwnd, &Dancerect, true);
			UpdateWindow(hwnd);
			ShellExecute(NULL, L"open", L"dance.exe", NULL, NULL, 1);


		}
		if (danceclick % 2 == 0 && danceValue&&danceclick!=0)
		{
			
			Dancestage = 0;
			InvalidateRect(hwnd, &Dancerect, true);
			UpdateWindow(hwnd);
			MSPLogout();

			HANDLE dancehandle;
			dancehandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"dance.exe"));
			if (dancehandle)
			{
				TerminateProcess(dancehandle, 0);

			}
			Sleep(200);
			m_Comm1.openport(L"COM3", 115200);
			Sleep(200);
			DipanSpeedSet(0, 0, 0);
			Sleep(200);

			light(0x02);
			Sleep(200);
			m_Comm1.~Comm();
		}
		if (followclick % 2 == 1 && followValue)
		{
			bool open;
			open = m_Comm1.openport(L"COM3", 115200);
			if (open)
			{
				//MessageBox(NULL, L"串口打开成功",L"",1);
			}
			else
			{
				MessageBox(NULL, L"串口打开失败", L"", 1);

			}
			Sleep(100);
			ladar_open();
			Sleep(100);
			light(0x01);
			Sleep(100);
			m_Comm1.~Comm();

			Followstage = 1;
			InvalidateRect(hwnd, &Followrect, true);
			UpdateWindow(hwnd);
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = NULL;
			ShExecInfo.lpVerb = NULL;
			ShExecInfo.lpFile = L"follow.exe"; //can be a file as well
			ShExecInfo.lpParameters = L"";
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.nShow = SW_SHOW;
			ShExecInfo.hInstApp = NULL;
			ShellExecuteEx(&ShExecInfo);
			

		}
		if (followclick % 2 == 0 && followValue&&followclick!=0)
		{
			Followstage = 0;
			
			InvalidateRect(hwnd, &Followrect, true);
			UpdateWindow(hwnd);
			HWND followhwnd = FindWindow(L"ConsoleWindowClass", NULL);
			PostMessage(followhwnd, WM_CLOSE, 0, 0);

			Sleep(500);
			m_Comm1.openport(L"COM3", 115200);
			Sleep(200);
			light(0x02);
			Sleep(100);
			ladar_close();
			Sleep(100);
			DipanSpeedSet(0, 0, 0);
			Sleep(200);
			m_Comm1.~Comm();

		}
		else
		{
			//
		}
	}
	break;

	case WM_PAINT:						// 若是客户区重绘消息
	{
		SetImageFrame(hwnd, L"img//bg.bmp", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		SetImageFrame(hwnd, L"img//shutdown2.png", 1300, 100, 70, 70);
		BigPaint(L"退出", 1380, 122);
		shortPaint(L"自动讲解", 240, 730);
		shortPaint(L"语音交互", 510, 730);
		shortPaint(L"运动控制", 780, 730);
		shortPaint(L"动作展示", 1065, 730);
		shortPaint(L"人机跟随", 1310, 730);
		if (Jiangjiestage==0)
		{
			SetImageFrame(hwnd, L"img//blue.png", 150, 700, 70, 70);

		}
		if (Jiangjiestage == 1)
		{
			SetImageFrame(hwnd, L"img//red.png", 150, 700, 70, 70);

		}
		if (Doctorstage == 0)
		{
			SetImageFrame(hwnd, L"img//blue.png", 420, 700, 70, 70);

		}
		if (Doctorstage == 1)
		{
			//MessageBox(NULL, L"", L"", 1);
			SetImageFrame(hwnd, L"img//red.png", 420, 700, 70, 70);
		}


		if (Movestage == 0)
		{
			SetImageFrame(hwnd, L"img//blue.png", 690, 700, 70, 70);

		}
		else
		{
			SetImageFrame(hwnd, L"img//red.png", 690, 700, 70, 70);
		}


		if (Dancestage == 0)
		{
			SetImageFrame(hwnd, L"img//blue.png", 975, 700, 70, 70);

		}
		else
		{
			SetImageFrame(hwnd, L"img//red.png", 975, 700, 70, 70);
		}

		if (Followstage == 0)
		{
			SetImageFrame(hwnd, L"img//blue.png", 1220, 700, 70, 70);
		}
		else
		{
			SetImageFrame(hwnd, L"img//red.png", 1220, 700, 70, 70);
		}

		ValidateRect(hwnd, false);		// 更新客户区的显示
	}
	break;									//跳出该switch语句

	case WM_KEYDOWN:                // 若是键盘按下消息
		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
			ExitProcess(0);		// 销毁窗口, 并发送一条WM_DESTROY消息
		break;									//跳出该switch语句

	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, L"您是否要退出程序", L"提示！！！", MB_YESNO | MB_ICONQUESTION))
		{
			close_MagneticNavigation();

			HANDLE dancehandle;
			dancehandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"dance.exe"));
			if (dancehandle)
			{
				TerminateProcess(dancehandle, 0);
			}
			HANDLE followhandle;
			followhandle = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, ProcessToPID(L"follow.exe"));
			if (followhandle)
			{
				TerminateProcess(followhandle, 0);
				Sleep(200);
			}
			m_Comm1.~Comm();
			m_Comm1.openport(L"COM3", 115200);
			Sleep(200);
			DipanSpeedSet(0, 0, 0);
			Sleep(300);
			arm_motion(0x0a);
			Sleep(200);
			light(0x02);
			Sleep(200);
			ladar_close();
			Sleep(200);

			m_Comm1.~Comm();
			MSPLogout();
			ExitProcess(0);
		}
		else
		{
			//

		}
		break;
	default:									//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
		break;
	}
	return 0;			//正常退出
}

DWORD WINAPI MoveProc(LPVOID lpParameter)
{
	char* login_params = "appid = 59c066c4, work_dir = .";
	if (MSP_SUCCESS != MSPLogin(NULL, NULL, login_params))
	{

	}
	
	robot_speak("您好，我是服务机器人小周，很高兴认识您");
	robot_speak("下面您可以通过语音控制我的运动");
	while (1)
	{
		broadcast(L"start.wav");
		std::string strstr =recong();
		if (strstr.empty())
		{
			continue;
		}
		//man(strstr);
		if (findstr_or(strstr, { "左" }) == true)
		{
			tts("请让一让");
			Sleep(1000);
			DipanSpeedSet(100, -90, 0); 
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";
		}
		if (findstr_or(strstr, { "右" }) == true)
		{
			tts("请让一让");
			Sleep(1000);
			DipanSpeedSet(100, 90, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		if (findstr_or(strstr, { "前","进" }) == true)
		{
			tts("请让一让");
			Sleep(1000);
			DipanSpeedSet(100, 0, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		if (findstr_or(strstr, { "后","退" }) == true)
		{
			tts("请让一让");
			Sleep(1000);
			DipanSpeedSet(100, 180, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		
		if (findstr_or(strstr, { "握","手"}) == true)
		{
			arm_motion(0x01);
			strstr = "";
			tts("好的，很高兴认识你");
			
		}
		if (findstr_or(strstr, { "抬","仰"}) == true)
		{
			arm_motion(0x07);
			strstr = "";
			tts("好的");
		}
		if (findstr_or(strstr, { "点","低" }) == true)
		{
			arm_motion(0x03);	
			strstr = "";
			tts("好的");
		}
		if (findstr_or(strstr, { "摇" }) == true)
		{
			arm_motion(0x02);
			strstr = "";
			tts("好的");
		}
		if (findstr_or(strstr, { "抱" }) == true)
		{
			arm_motion(0x04);
			strstr = "";
			tts("来，让我们抱一抱");
		}
		if (findstr_or(strstr, { "你好","您好","欢迎" }) == true)
		{
			arm_motion(0x06);
			strstr = "";
			tts("您好");

		}
		
		if (findstr_or(strstr, {"睁"}) == true)
		{
			light(0x01);
			strstr = "";
			tts("我看见你了，见到你很高兴");

		}
		if (findstr_or(strstr, {"闭"}) == true)
		{
			light(0x02);
			tts("好的，那我休息下");
			strstr = "";
		}
		

	}
	return 0;

}
DWORD DoctorProc(LPVOID lpParameter)
{
		char* login_params = "appid = 59c066c4, work_dir = .";
		std::string putstr;
		std::string get_ans_name, get_ans, ans_xuetang;
		bool decide_tangniao = false;
		bool decide_complication = false;
		/*bool decide_sex = false;*/
		bool decide_complicordebets = false;
		bool decide_heart_disease = false;
		bool decide_Breast_disease = false;
		bool chat_continue = false;
		bool decide_tizhi = false;
		bool tizhipanduan = false;
		std::string strstr;
		MSPLogout(); //退出登录
					 //第一个参数是用户名，第二个参数是密码，均传NULL即可，第三个参数是登录参数
		if (MSP_SUCCESS != MSPLogin(NULL, NULL, login_params))
		{
			std::cout << "========================" << std::endl;
			std::cout << "Login failed!" << std::endl;
			std::cout << "========================" << std::endl;
		}

		


	start_first:

		 //remove(doctor);
		 //remove(sickness);
		 decide_sex = false;
		 chat_continue = false;

		 decide_tangniao = false;
		 decide_complication = false;
		 decide_complicordebets = false;
		 decide_heart_disease = false;
		 decide_Breast_disease = false;
		 decide_tizhi = false;
		 tizhipanduan = false;

		 Sleep(300);
		 arm_motion(0x0a);
		 Sleep(200);

		 arm_motion(0x0a);

		 Sleep(200);
		 light(0x02);
		 Sleep(200);

		 while (1)//图灵机器人的接入
		 {
		 	std::string strstr = recong();
		 	if (strstr.empty())
		 	{continue;}
		 	man(strstr);

		 	if (findstr_or(strstr, { "你好","您好" }))
		 	{
				arm_motion(0x07);//仰头
				Sleep(300);
				light(0x01);//亮灯
				Sleep(100);

		 		robot_speak("您好，我是服务机器人小周！来自周口师范学院");
		 		robot_speak("请问您需要什么帮助呢？");
		 	chat:
		 		std::string str=talk_robot();
		 		if (str =="kanbing")
		 		{
		 			robot_speak("好的，那我帮您看看！");
		 			break;
		 		}
		 		if (str == "tizhipanduan")
		 		{
		 			tizhipanduan = true;
		 			break;
		 		}
		 		if (str == "null")
		 		{
		 			goto start_first;
		 		}
		 		if (str == "tuichu")
		 		{
		 			std::string str1 = access_out("select *  from start", "l", "f");
		 			if (str1 == "null")
		 			{
						//robot_speak("抱歉，没有检测到语音输入，再见！");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
		 				goto start_first;
		 			}
		 			if (str1 == "recycle")
		 			{
		 				robot_speak("抱歉，我理解不了您在说什么，语音系统即将退出，再见！");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);

		 				goto start_first;
		 			}
		 			if (str1 == "Y")
		 			{
		 				robot_speak("好的，那我们继续聊天吧!");
		 				goto chat;
		 			}
		 			if (str1 == "N")
		 			{
						robot_speak("希望您身体健康，我们下次再聊吧");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
		 				goto start_first;
		 			}
					if (str1 == tuichu)
					{
						robot_speak("希望您身体健康，我们下次再聊吧");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
						goto start_first;
					}
		 		}
		 	}
		 }




		//开始问题
		//开始问题
		 light(0x04);
		 Sleep(200);
		 if (chat_continue == false)//记录信息不能重复！！！！！！
		 {
			 std::string str = access_out("select *  from start2", "l", "a");
			 if (situation(str) == true) { goto start_first; }
			 if (str == "Y")//刷身份证
			 {
				 robot_speak("请您把身份证放在我的左肩上，我将读取您的基本信息。");
				 Sleep(1000);
				 //broadcast(L"ding.wav");
				 bool redult_ID = ID_card();
				 if (redult_ID == false)
				 {
					 robot_speak("您的身份证我识别不了，请您检查一下再来继续问诊吧！");
					 goto start_first;
				 }
				 else
				 {

					 int filecount=0;
					 HANDLE hFile;
					 LPCTSTR lpFileName = L"C://Users//ROBOT//Desktop//result//*.html"; //指定搜索目录和文件类型，如搜索d盘的音频文件可以是"D:\\*.mp3"  
					 WIN32_FIND_DATA pNextInfo;  //搜索得到的文件信息将储存在pNextInfo中;  
					 hFile = FindFirstFile(lpFileName, &pNextInfo);//请注意是 &pNextInfo , 不是 pNextInfo;  
					 
					 while (FindNextFile(hFile, &pNextInfo))
					 {
						 if (pNextInfo.cFileName[0] == '.')//过滤.和..  
							 continue;
						 else
							 filecount++;
					 }
					 string count;
					 if (filecount<10)
					 {
						 count = "00"+to_string(filecount);
					 }
					 if (filecount >= 10 && filecount < 100)
					 {
						 count="0"+ to_string(filecount);
					 }
					 string filepath = "C://Users//Administrator//Desktop//result//" + people_name + "诊断证书"+ count +".html";
					 sickness = filepath;
					 writefile_data("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"\" xml:lang=\"\"><head></head>\<body>\<p><img src = \"C:\\Users\\Administrator\\Desktop\\result\\logo.jpg\"/></p>\<center>\<title>诊断报告</title>\<font color = grey size = 5><strong>诊断报告</strong></font></center>", sickness);
					 writefile_data("<p align=\"right\">", sickness);
					 writefile_data("编号：", sickness);
					 writefile_data(people_num, sickness);
					 writefile_data(count, sickness);
					 writefile_data("</p>", sickness);

					 writefile_data("<hr/>", sickness);
					 writefile_data("<p>姓名：", sickness);
					 writefile_data(people_name, sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 writefile_data("性别：", sickness);
					 if (decide_sex == false)
					 {
						 writefile_data("男", sickness);
						 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
						 robot_speak("好了," + people_name + "先生，我已经读取了您的基本信息。请您收好您的身份证。");
						 robot_speak("接下来我还会问您一些生活方面的问题，请您继续配合。");
					 }
					 else
					 {
						 writefile_data("女", sickness);
						 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
						 robot_speak("好了," + people_name + "女士，您的身份信息已经成功的进行读取。请您收好您的身份证。");
						 robot_speak("接下来我还会问您一些生活方面的问题，请您继续配合。");
					 }
					 writefile_data("出生日期：", sickness);
					 writefile_data(people_birthday, sickness);
					 writefile_data("</p>", sickness);
					 writefile_data("<p>地址：", sickness);
					 writefile_data(people_address, sickness);
					 //writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					// writefile_data("诊断日期：", sickness);
					// writefile_data(people_time, sickness);
					 writefile_data("</p>", sickness);
					 writefile_data("<hr/>", sickness);


				 }
			 }
			 if (str == "N")
			 {
				 people_address = " ";
				 people_birthday = " ";
				 people_name = "未知";
				 robot_speak("好的，那我需要问一些问题，以便我对您的身体状况做出初步判断，希望您耐心配合！");
				 std::string str_little = access_out("select *  from start", "l", "r");
				 if (situation(str_little) == true) { goto start_first; }
				 str_little = access_out("select *  from start", "l", "ra");
				 if (situation(str_little) == true) { goto start_first; }
				 if (str_little == "Y")
				 {
					 //cout << "男性" << endl;
					 decide_sex = false;
				 }
				 if (str_little == "N")
				 {
					 //cout << "女性" << endl;
					 decide_sex = true;
				 }
				 str_little = access_out("select *  from start", "l", "taaa");
				 if (situation(str_little) == true) { goto start_first; }
				 str_little = access_out("select *  from start", "l", "taa");
				 if (situation(str_little) == true) { goto start_first; }
				 int filecount = 0;
				 HANDLE hFile;
				 LPCTSTR lpFileName = L"C://Users//ROBOT//Desktop//result//*.html"; //指定搜索目录和文件类型，如搜索d盘的音频文件可以是"D:\\*.mp3"  
				 WIN32_FIND_DATA pNextInfo;  //搜索得到的文件信息将储存在pNextInfo中;  
				 hFile = FindFirstFile(lpFileName, &pNextInfo);//请注意是 &pNextInfo , 不是 pNextInfo;  

				 while (FindNextFile(hFile, &pNextInfo))
				 {
					 if (pNextInfo.cFileName[0] == '.')//过滤.和..  
						 continue;
					 else
						 filecount++;
				 }
				 string count;
				 if (filecount<10)
				 {
					 count = "00" + to_string(filecount);
				 }
				 if (filecount >= 10 && filecount < 100)
				 {
					 count = "0" + to_string(filecount);
				 }
				 SYSTEMTIME systime = { 0 };
				 GetLocalTime(&systime);
				 string peoplemonth, peopleday = "";
				 peoplemonth= to_string(systime.wMonth);
				 peopleday= to_string(systime.wDay);
				 if (systime.wMonth < 10)
				 {
					 peoplemonth = "0" + to_string(systime.wMonth);
				 }
				 if (systime.wDay<10)
				 {
					 peopleday="0"+ to_string(systime.wDay);
				 }
				 people_num = to_string(systime.wYear) + peoplemonth + peopleday;
				 people_time = to_string(systime.wYear) + "年" + to_string(systime.wMonth) + "月" + to_string(systime.wDay) + "日";
				 string filepath = "C://Users//Administrator//Desktop//result//" + people_name + "诊断证书" + count + ".html";
				 sickness = filepath;
				 writefile_data("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"\" xml:lang=\"\"><head></head>\<body>\<p><img src = \"C:\\Users\\Administrator\\Desktop\\result\\logo.jpg\"/></p>\<center>\<title>诊断报告</title>\<font color = grey size = 5><strong>诊断报告</strong></font></center>", sickness);
				 writefile_data("<p align=\"right\">", sickness);
				 writefile_data("编号：", sickness);
				 writefile_data(people_num, sickness);
				 writefile_data(count, sickness);
				 writefile_data("</p>", sickness);

				 writefile_data("<hr/>", sickness);
				 writefile_data("<p>姓名：", sickness);
				 writefile_data(" ", sickness);
				 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
				 writefile_data("性别：", sickness);
				 if (decide_sex == false)
				 {
					 writefile_data(" ", sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 robot_speak("接下来我还会问您一些生活方面的问题，请您继续配合。");
				 }
				 else
				 {
					 writefile_data(" ", sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 robot_speak("接下来我还会问您一些生活方面的问题，请您继续配合。");
				 }
				 writefile_data("出生日期：", sickness);
				 writefile_data(people_birthday, sickness);
				 writefile_data("</p>", sickness);
				 writefile_data("<p>地址：", sickness);
				 writefile_data(people_address, sickness);
				 //writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
				 // writefile_data("诊断日期：", sickness);
				 // writefile_data(people_time, sickness);
				 writefile_data("</p>", sickness);
				 writefile_data("<hr/>", sickness);


			 }
			 chat_continue = true;
		 }

		 std::string str;
		 Sleep(800);
		 str = access_out("select *  from start", "l", "taaaa");
		 if (situation(str) == true) { goto start_first; }
		 str = access_out("select *  from start", "l", "t");
		 if (situation(str) == true) { goto start_first; }
		 str = access_out("select *  from start", "l", "ta");
		 if (situation(str) == true) { goto start_first; }
		 str = access_out("select *  from start", "l", "taaaaa");
		 if (situation(str) == true) { goto start_first; }



		 if (tizhipanduan == true)
		 {
			 robot_speak("你的基本情况我大概掌握了。");
			 //robot_speak("好的，那我们现在就进入体质判断，之后会给您一个调理身体的方案，请您按照方案来保养身体！那我们就开始吧！");
			 std::string str = access_out("select *  from Institution_judg", "l", "a");
			 if (situation_noasktuichu(str) == true)
			 {
				 tizhipanduan = false;
				 goto start_first;
			 }
			 tizhipanduan = false;
			 goto last;
		 }

		 robot_speak("好的，接下来的问题将根据八纲辨证、六经辨证和气血津液辨证等中医经典理论对您做出综合诊断。");
		 robot_speak("您的回答至关重要，请耐心回答！");
		 str = access_out("select *  from start2", "l", "c");
		 if (situation(str) == true) { goto start_first; }
		 str = access_out("select *  from start2", "l", "d");
		 if (situation(str) == true) { goto start_first; }
	wenzhen:
		//选择问题
		 search_ID.clear();
		 light(0x05);
		 Sleep(200);
		FlushRect({ 100,200,500,400 });
		robot_speak("那么您身体哪里不舒服呢？有哪些症状？");
		promptPaint("心脏病|心肌梗塞|心绞痛|心力衰竭|心律失常|胸痛|胸闷|心跳过快|心脏不舒服|心脏难受|", 10, 35);
		promptPaint("麻木疼痛|身体麻木疼痛|麻木|容易出汗|常出汗|汗多|多汗|性功能异常|性功能障碍|糖尿病|", 10, 60);
		promptPaint("腰膝酸痛|全身无力|身体酸痛|浑身无力|腰膝酸痛|浑身乏力|身体酸疼|全身乏力|腰部疼痛|膝盖疼痛|", 10, 85);
		promptPaint("双脚异常|双脚不正常|双脚不舒服|双脚麻木疼痛|双脚疼痛麻木|双脚发红|双脚发紫|脚疼|脚麻|腿脚疼痛|", 10, 110);
		promptPaint("肠胃不舒服|肠胃不适|胃肠不舒服|胃肠不适|胃部疼痛|胃疼|肠部不适|胸闷腹胀|腹胀胸闷|肚子胀|", 10, 135);
		promptPaint("多饮多食|多饮多尿|多食多尿|喝的多|喝水多|多食|吃的多|小便多|经常小便|多尿多食|尿多|尿频|", 10, 160);
		promptPaint("小便不利|小便不畅|尿不出|小便浑浊|尿浊|尿频|尿多|小便多|上厕所频繁|小便频繁|肢体软弱|四肢软弱|腿脚不利索|无力|乏力|没劲|起不来|", 10, 185);
		promptPaint("乳腺不舒服|乳房不舒服|胸部不舒服|乳头有溢液|乳头内陷|乳汁不通|乳腺肿瘤|乳腺炎|乳腺结节|乳腺增生|乳腺癌|乳腺不适|乳房不适|", 10, 210);
		promptPaint("视物模糊|眼睛干涩|模糊|眼睛模糊|看不清|胸闷气短|胸闷胸痛|胸痛气短|气短胸痛|胸闷胸痛|胸痛|胸部疼痛|皮肤瘙痒|皮肤难受|皮肤痒|皮肤异常|", 10, 235);

		decide_tangniao = false;
		decide_complication = false;
		decide_complicordebets = false;
		decide_heart_disease = false;
		decide_Breast_disease = false;
		decide_tizhi = false;
		tizhipanduan = false;
	puts:
		int count_time_3 = 0;
		do
		{
			count_time_3++;
			if (count_time_3 == 6)
			{
				goto start_first;
			}
			broadcast(L"start.wav");
			putstr = recong1();
			man(putstr);
		} while (putstr.empty());
		//writefile_data(putstr, doctor);//将大段的回答填入报告
		FlushRect({ 10,35,1200,265 });

		light(0x06);
		Sleep(200);
		if (findstr_or(putstr, { "退出","停止","结束" }))
		{
			robot_speak("希望您身体健康，我们下次再聊吧!");
			goto start_first;
		}

		if (findstr_or(putstr, { "体质","体质判断" }) == true)
		{
			//robot_speak("好的，那我们现在就进入体质判断，之后会给您一个调理身体的方案，请您按照方案来保养身体！那我们就开始吧！");
			std::string str = access_out("select *  from Institution_judg", "l", "a");
			if (situation_noasktuichu(str) == true) { goto start_first; }
			goto last;
		}


		str = access_out("select *  from start", "l", "u");//持续了多久？以前有没有类似的症状出现过？看过医生了吗？
		if (situation(str) == true) { goto start_first; }

		get_ans = access_out("select *  from choose_sickness", putstr, "aa");
		if (findstr_or(putstr, { tuichu }))
		{
			robot_speak("希望您身体健康，我们下次再聊吧!");
			goto start_first;
		}


		if (search_ID.size() != 0)//家族里面有遗传病吗？
		{
			str = access_out("select *  from start", "l", "v");
			if (situation(str) == true) { goto start_first; }
			str = access_out("select *  from start", "l", "va");
			if (situation(str) == true) { goto start_first; }
		}



		{//接下来我将会对您的症状问一些具体的问题，根据脏腑症候、经络症候、卫气营血症候对您的疾病进行精确的判断，请您配合一下。
			get_ans = access_out("select *  from choose_sickness_2", putstr, "aa");
			if (situation_noasktuichu(get_ans) == true) { goto start_first; }

			get_ans = access_out("select *  from choose_complication_2", putstr, "aa");
			if (situation_noasktuichu(get_ans) == true) { goto start_first; }

			if (get_ans == "over_three")
			{
				str = access_out("select *  from start2", "l", "e");
				if (situation(str) == true) { goto start_first; }
			}
			all_count = 0;
		}


		


		/****************************************心脏病************************************************************/

		for (int i = 0; i < search_ID.size(); i++)
		{
			if (search_ID[i] == "aa")//@心脏病
			{
				//std::cout << "@心脏病" << std::endl;
				//robot_speak("根据您的状况描述，您可能是患有心脏病，那我帮您进行心脏病的相关疾病诊断吧！");
				std::string str = access_out("select *  from heart_disease", "l", "a");
				if (situation_noasktuichu(str) == true) { goto start_first; }
				if (str == "Y")
				{
					search_ID.clear();
					goto wenzhen;
				}
				if (str == "N")
				{
					std::string str1 = access_out("select *  from start", "l", "f");//判断是否退出
					if (situation_noasktuichu(str1) == true) { goto start_first; }
					if (str1 == "Y")
					{
						robot_speak("好的，那我们继续吧!");
						goto wenzhen;
					}
					if (str1 == "N")
					{
						robot_speak("希望您身体健康，我们下次再聊吧!");
						goto start_first;
					}
				}
				decide_complication = true;
				decide_heart_disease = true;
			}


			/****************************************乳腺病**************************************************************/
			if (search_ID[i] == "ca")//@乳腺病，女性病
			{
				//robot_speak("嗯，您可能是有乳腺相关的疾病，我帮您进行乳腺疾病的医疗问答吧！");
				//std::cout << "@乳腺病" << std::endl;
				std::string str;

				str = access_out("select *  from start", "l", "y");
				if (situation_noasktuichu(str) == true) { goto start_first; }

				if (decide_sex == true)
				{
					str = access_out("select *  from Breast_disease_woman", "l", "a");
				}
				else
				{
					str = access_out("select *  from Breast_disease_man", "l", "a");
				}
				if (situation_noasktuichu(str) == true) { goto start_first; }

				if (str == "Y")
				{
					search_ID.clear();
					goto wenzhen;
				}
				if (str == "N")
				{
					std::string str1 = access_out("select *  from start", "l", "f");
					if (situation_noasktuichu(str1) == true) { goto start_first; }

					if (str1 == "Y")
					{
						search_ID.clear();
						robot_speak("好的，那我们继续吧!");
						goto wenzhen;
					}
					if (str1 == "N")
					{
						robot_speak("希望您身体健康，我们下次再聊吧!");
						goto start_first;
					}
				}
				decide_complication = true;
				decide_Breast_disease = true;
			}

			/****************************************糖尿病**************************************************************/
			if (search_ID[i] == "ea")//"@糖尿病
			{
				//std::cout << "@糖尿病" << std::endl;
				decide_tangniao = true;
				decide_complication = false;
				//robot_speak("刚才您的描述中说到您有糖尿病，那我们就直接进行糖尿病的诊断吧！");
			}

			/****************************************多饮多食**************************************************************/

			if (search_ID[i] == "ga"&&decide_tangniao == false)//@多饮多食
			{
				ans_xuetang = access_out("select *  from diabetes_ask", "l", "a");
				if (situation_noasktuichu(ans_xuetang) == true) { goto start_first; }
				if (ans_xuetang == "N")
				{
					//robot_speak("好的，稍后让我们的护士给您测一下血糖吧");
					robot_speak("请您测完血糖再来继续问诊！");
					goto start_first;
					decide_tizhi = true;
					break;
				}

				//			float c = atof(ans_xuetang.c_str());
				//cexuetang:
				//			while (c == 0)
				//			{
				//				ans_xuetang = access_out("select *  from diabetes_ask", "l", "aa");
				//				if (situation(ans_xuetang) == true) { goto start_first; }
				//
				//				c = atof(ans_xuetang.c_str());
				//				if (c>30.0 || c<2.0)
				//				{
				//					robot_speak("您可能在跟我开玩笑！好像没有这样的血糖值。。。请问：");
				//					c = 0;
				//				}
				//			}
				//			if (c > 30.0 || c<2.0)
				//			{
				//				robot_speak("您可能在跟我开玩笑！好像没有这样的血糖值。。。请问：");
				//				c = 0;
				//				goto cexuetang;
				//			}
				//			if (c <= 6.1&&c >= 2.0)
				//			{
				//				robot_speak("好的，您的血糖处于正常水平，我帮您进行体制判断吧！");
				//				decide_tangniao = false;
				//			}
				//			if (c>6.1)
				//			{
				//				//robot_speak("据银陀判断您可能处于高血糖状态！");
				//				decide_tangniao = true;
				//			}//在外围进行调理方案

				decide_tangniao = true;
				decide_complication = false;
			}
		}

		/************************************************并发症问答****************************************************/
		search_ID.clear();
		if (decide_complication == false)//决定是否进行并发症问答
		{
			get_ans = access_out("select *  from choose_complication", putstr, "aa");
			if (get_ans == tuichu)
			{
				robot_speak("希望您身体健康，我们下次再聊吧!");
				goto start_first;
			}

			//与上一个相连接，到特定的并发症进行问答
			if (!search_ID.empty())
			{
				//cout << "search_ID.empty()" << endl;
				decide_complicordebets = true;
			}

			for (int i = 0; i < search_ID.size(); i++)
			{
				if (decide_sex = false)
				{
					std::string str_man = access_out("select *  from get_complication_man", "1", search_ID[i]);
					if (situation_noasktuichu(str_man) == true) { goto start_first; }

					std::string str_man1 = access_out("select *  from complication_perscription", "1", str_man);
					if (situation_noasktuichu(str_man1) == true) { goto start_first; }
				}
				else
				{
					std::string str_woman = access_out("select *  from get_complication_woman", "1", search_ID[i]);
					if (situation_noasktuichu(str_woman) == true) { goto start_first; }

					std::string str_woman1 = access_out("select *  from complication_perscription", "1", str_woman);
					if (situation_noasktuichu(str_woman1) == true) { goto start_first; }
				}
			}
		}

		/************************************糖尿病主证问答***************************************************************/
		if (decide_complicordebets == false && decide_tangniao == true)
		{
			//tts("那么下面我们将要进入糖尿病的主证问答了！");
			//robot_speak("那么下面我们将要进入糖尿病的主证问答了！");
			std::string str = access_out("select *  from diabetes", "l", "a");
			if (situation_noasktuichu(str) == true) { goto start_first; }

			if (str == "Y")
			{
				search_ID.clear();
				robot_speak("好的，那我们继续问诊吧");
				goto wenzhen;
			}
			if (str == "N")
			{
				std::string str1 = access_out("select *  from start", "l", "f");
				if (situation_noasktuichu(str1) == true) { goto start_first; }
				if (str1 == "Y")
				{
					search_ID.clear();
					robot_speak("好的，那我们继续吧!");
					goto wenzhen;
				}
				if (str1 == "N")
				{
					robot_speak("希望您身体健康，我们下次再聊吧!");
					goto start_first;
				}
			}
		}

		/****************************************体制判断**************************************************************/
		if (decide_tangniao == false && search_ID.empty() && decide_heart_disease == false && decide_Breast_disease == false)
		{
			//std::cout << "进行体制判断，给出调理方案！" << endl;
			string str1;
			if (decide_tizhi == true)
			{
				str1 = access_out("select *  from start", "l", "n");
				robot_speak("那我来帮您看看吧！");
			}
			else
			{
				str1 = access_out("select *  from Institution_judg", "l", "j");
			}
			decide_tizhi = false;
			if (situation_noasktuichu(str1) == true) { goto start_first; }
			if (str1 == "Y")
			{
				//robot_speak("好的，那我们现在就进入体制判断，之后会给您一个调理身体的方案，请您按照方案来保养身体！那我们就开始吧！");
				std::string str = access_out("select *  from Institution_judg", "l", "a");
				if (situation_noasktuichu(str) == true) { goto start_first; }
			}

			if (str1 == "N")
			{
				std::string str1 = access_out("select *  from start", "l", "f");
				if (situation_noasktuichu(str1) == true) { goto start_first; }

				if (str1 == "Y")
				{
					robot_speak("好的，那我们继续吧!");
					goto wenzhen;
				}
				if (str1 == "N")
				{
					robot_speak("希望您身体健康，我们下次再聊吧!");
					goto start_first;
				}
			}
		}

	last:
		/*std::string str1 = access_out("select *  from start", "l", "w");
		if (situation_noasktuichu(str1) == true) { goto start_first; }

		if (str1 == "N")
		{
			search_ID.clear();
			robot_speak("希望您身体健康!");
			goto start_first;
		}
		if (str1 == "Y")
		{
			search_ID.clear();
			robot_speak("好的，那我们继续吧!");
			goto wenzhen;
		}*/


		search_ID.clear();
		robot_speak("希望您身体健康!再见！");
		goto start_first;


		//退出
	logout:
		broadcast(L"start.wav");
		robot_speak("希望您身体健康，我们下次再聊吧！");
		MSPLogout(); //退出登录
		return 0;


}


DWORD WINAPI jiangjieThreadProc(LPVOID lpParameter)
{
	com.ReceiveChar();
	return 0;
}
DWORD WINAPI DlgThreadProc(LPVOID lpParameter)
{
	
	HWND hDlg = CreateDialog((HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_FORMVIEW), hwnd, (DLGPROC)DlgProc);
	//MoveWindow(hDlg, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200, 161, true);
	if (hDlg)
	{
		
		ShowWindow(hDlg, SW_SHOWNA);
	}
	else
	{
		MessageBox(NULL, L"createdlg error", NULL, SW_SHOWNORMAL);
		return 0;
	}
	//
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//MessageBox(NULL, L"Login error", NULL, SW_SHOWNORMAL);

}

INT_PTR CALLBACK  DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam) //对话框过程函数
{
	 mydlg = hdlg;
	 RECT button1rect = { 160,50,360,250 };
	 RECT button2rect = { 430,50,630,250 };

	HDC ghdc = GetDC(hdlg);  //获取设备环境句柄
	int size;
	TCHAR a[] = L"当前是第";
	TCHAR b[] = L"站";
	TCHAR szText[256];
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
		L"黑体"); // lpszFac
	SelectObject(ghdc, font);
	SetTextColor(ghdc, RGB(0, 0, 0));
	SetBkMode(ghdc, TRANSPARENT);

	switch (message)
	{
	case WM_CREATE:
	{
		
		SetWindowLong(hdlg, GWL_EXSTYLE, GetWindowLong(hdlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hdlg, RGB(255, 255, 255), 200, LWA_ALPHA);
		
	}
	break;
	case WM_PAINT:
		SetImageFrame(hdlg, L"img//bg2.jpg", 0, 0, 800, 800);
		SetImageFrame(hdlg, L"img//start.png", button1rect.left, button1rect.top, button1rect.right- button1rect.left, button1rect.bottom- button1rect.top);
		SetImageFrame(hdlg, L"img//pause.png", button2rect.left, button2rect.top, button2rect.right - button2rect.left, button2rect.bottom - button2rect.top);
		TextOut(ghdc, 222, 260, L"下一站", 4);
		TextOut(ghdc, 510, 260, L"停止", 4);
		size = wsprintf(szText, TEXT("%s%d%s"), a, stationindex, b);
		//函数wsprintf()将一系列的字符和数值输入到缓冲区，函数的返回值是写入的长度  
		TextOut(ghdc, 10, 100, szText, size);
		break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		
		if (x<button1rect.right&&x>button1rect.left&&y<button1rect.bottom&&y>button1rect.top)
		{

			ttsValued1 = 0;
			if (com.ttsThread != NULL)
			{
				TerminateThread(com.ttsThread, 1);
			}
			com.ttsThread = NULL;
			broadcast(L"dong.wav");

			start_LinePatrol();
		}
		if (x<button2rect.right&&x>button2rect.left&&y<button2rect.bottom&&y>button2rect.top)
		{

			ttsValued1 = 0;
			if (com.ttsThread != NULL)
			{
				TerminateThread(com.ttsThread, 1);
			}
			com.ttsThread = NULL;
			broadcast(L"dong.wav");

			stop_LinePatrol();
		}
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON3:
			{
				//explain(0);
				//stationindex++;
				Correct_MagneticNavigation();
				Sleep(100);
				broadcast(L"dong.wav");

			}
			break;
			case IDC_BUTTON4:
			{
				Set_Sensitivity();
				Sleep(100);
				broadcast(L"dong.wav");

			}
			break;
		}

	}
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			// 如果执行了关闭  
			// 销毁对话框，将收到WM_DESTROY消息  
			DestroyWindow(hdlg);
			ttsValued1 = 0;

		}
		return 0;
	}
	return (INT_PTR)FALSE;
}
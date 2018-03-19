#include"Mywindows.hpp"
#include"Robotmove.hpp"
#include <regex>
#include"cidaohang.h"
#include"tts1.h"
#include<process.h>
DWORD WINAPI DoctorProc(LPVOID lpParameter);
DWORD WINAPI MoveProc(LPVOID lpParameter);
DWORD WINAPI DlgThreadProc(LPVOID lpParameter); //�̶߳Ի��������  
DWORD WINAPI jiangjieThreadProc(LPVOID lpParameter);
INT_PTR CALLBACK  DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);  //�Ի�����̺���


HANDLE  DoctorThread, MoveThread, DanceThread;//�߳�
bool Doctorstage, Movestage, Dancestage, Jiangjiestage,Followstage = 0;//�߳�״̬
string  patientname, patientbirthday, patientAdress, patientsex;//������Ϣ
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
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);    //����ShowWindow��������ʾ����
	UpdateWindow(hwnd);						//�Դ��ڽ��и��£��������������·���Ҫװ��һ��
	MSG msg = { 0 };		//���岢��ʼ��msg

	while (msg.message != WM_QUIT)			//ʹ��whileѭ���������Ϣ����WM_QUIT��Ϣ���ͼ���ѭ��
	{

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			//QuestionPaint(stringToWstring(to_string(battery())).c_str());
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);			//�ַ�һ����Ϣ�����ڳ���
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
	switch (message)						//switch��俪ʼ
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
		//��ť�ķ�Χ��ֱ��������ľͺ��ˡ�
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
			if (IDYES == MessageBox(hwnd, L"���Ƿ�Ҫ�˳�����", L"��ʾ������", MB_YESNO | MB_ICONQUESTION))
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
				//MessageBox(NULL, L"���ڴ򿪳ɹ�",L"",1);
			}
			else
			{
				MessageBox(NULL, L"���ڴ�ʧ��", L"", 1);

			}
			Doctorstage = 1;
			InvalidateRect(hwnd, &Doctorrect, true);
			UpdateWindow(hwnd);
			DoctorThread = CreateThread(NULL, 0, DoctorProc, NULL, 0, NULL); //��һ��������ʹ��Ĭ�ϵİ�ȫ�ԣ��ڶ���������ʹ������ú������߳���ͬ��ջ��С
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
				//MessageBox(NULL, L"���ڴ򿪳ɹ�",L"",1);
			}
			else
			{
				MessageBox(NULL, L"���ڴ�ʧ��", L"", 1);

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
				//MessageBox(NULL, L"���ڴ򿪳ɹ�",L"",1);
			}
			else
			{
				MessageBox(NULL, L"���ڴ�ʧ��", L"", 1);

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

	case WM_PAINT:						// ���ǿͻ����ػ���Ϣ
	{
		SetImageFrame(hwnd, L"img//bg.bmp", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		SetImageFrame(hwnd, L"img//shutdown2.png", 1300, 100, 70, 70);
		BigPaint(L"�˳�", 1380, 122);
		shortPaint(L"�Զ�����", 240, 730);
		shortPaint(L"��������", 510, 730);
		shortPaint(L"�˶�����", 780, 730);
		shortPaint(L"����չʾ", 1065, 730);
		shortPaint(L"�˻�����", 1310, 730);
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

		ValidateRect(hwnd, false);		// ���¿ͻ�������ʾ
	}
	break;									//������switch���

	case WM_KEYDOWN:                // ���Ǽ��̰�����Ϣ
		if (wParam == VK_ESCAPE)    // ��������µļ���ESC
			ExitProcess(0);		// ���ٴ���, ������һ��WM_DESTROY��Ϣ
		break;									//������switch���

	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, L"���Ƿ�Ҫ�˳�����", L"��ʾ������", MB_YESNO | MB_ICONQUESTION))
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
	default:									//������case�����������ϣ���ִ�и�default���
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ���
		break;
	}
	return 0;			//�����˳�
}

DWORD WINAPI MoveProc(LPVOID lpParameter)
{
	char* login_params = "appid = 59c066c4, work_dir = .";
	if (MSP_SUCCESS != MSPLogin(NULL, NULL, login_params))
	{

	}
	
	robot_speak("���ã����Ƿ��������С�ܣ��ܸ�����ʶ��");
	robot_speak("����������ͨ�����������ҵ��˶�");
	while (1)
	{
		broadcast(L"start.wav");
		std::string strstr =recong();
		if (strstr.empty())
		{
			continue;
		}
		//man(strstr);
		if (findstr_or(strstr, { "��" }) == true)
		{
			tts("����һ��");
			Sleep(1000);
			DipanSpeedSet(100, -90, 0); 
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";
		}
		if (findstr_or(strstr, { "��" }) == true)
		{
			tts("����һ��");
			Sleep(1000);
			DipanSpeedSet(100, 90, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		if (findstr_or(strstr, { "ǰ","��" }) == true)
		{
			tts("����һ��");
			Sleep(1000);
			DipanSpeedSet(100, 0, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		if (findstr_or(strstr, { "��","��" }) == true)
		{
			tts("����һ��");
			Sleep(1000);
			DipanSpeedSet(100, 180, 0);
			Sleep(2000);
			DipanSpeedSet(0, 0, 0);
			strstr = "";

		}
		
		if (findstr_or(strstr, { "��","��"}) == true)
		{
			arm_motion(0x01);
			strstr = "";
			tts("�õģ��ܸ�����ʶ��");
			
		}
		if (findstr_or(strstr, { "̧","��"}) == true)
		{
			arm_motion(0x07);
			strstr = "";
			tts("�õ�");
		}
		if (findstr_or(strstr, { "��","��" }) == true)
		{
			arm_motion(0x03);	
			strstr = "";
			tts("�õ�");
		}
		if (findstr_or(strstr, { "ҡ" }) == true)
		{
			arm_motion(0x02);
			strstr = "";
			tts("�õ�");
		}
		if (findstr_or(strstr, { "��" }) == true)
		{
			arm_motion(0x04);
			strstr = "";
			tts("���������Ǳ�һ��");
		}
		if (findstr_or(strstr, { "���","����","��ӭ" }) == true)
		{
			arm_motion(0x06);
			strstr = "";
			tts("����");

		}
		
		if (findstr_or(strstr, {"��"}) == true)
		{
			light(0x01);
			strstr = "";
			tts("�ҿ������ˣ�������ܸ���");

		}
		if (findstr_or(strstr, {"��"}) == true)
		{
			light(0x02);
			tts("�õģ�������Ϣ��");
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
		MSPLogout(); //�˳���¼
					 //��һ���������û������ڶ������������룬����NULL���ɣ������������ǵ�¼����
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

		 while (1)//ͼ������˵Ľ���
		 {
		 	std::string strstr = recong();
		 	if (strstr.empty())
		 	{continue;}
		 	man(strstr);

		 	if (findstr_or(strstr, { "���","����" }))
		 	{
				arm_motion(0x07);//��ͷ
				Sleep(300);
				light(0x01);//����
				Sleep(100);

		 		robot_speak("���ã����Ƿ��������С�ܣ������ܿ�ʦ��ѧԺ");
		 		robot_speak("��������Ҫʲô�����أ�");
		 	chat:
		 		std::string str=talk_robot();
		 		if (str =="kanbing")
		 		{
		 			robot_speak("�õģ����Ұ���������");
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
						//robot_speak("��Ǹ��û�м�⵽�������룬�ټ���");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
		 				goto start_first;
		 			}
		 			if (str1 == "recycle")
		 			{
		 				robot_speak("��Ǹ������ⲻ������˵ʲô������ϵͳ�����˳����ټ���");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);

		 				goto start_first;
		 			}
		 			if (str1 == "Y")
		 			{
		 				robot_speak("�õģ������Ǽ��������!");
		 				goto chat;
		 			}
		 			if (str1 == "N")
		 			{
						robot_speak("ϣ�������彡���������´����İ�");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
		 				goto start_first;
		 			}
					if (str1 == tuichu)
					{
						robot_speak("ϣ�������彡���������´����İ�");
						arm_motion(0x0a);
						Sleep(200);
						light(0x02);
						Sleep(200);
						goto start_first;
					}
		 		}
		 	}
		 }




		//��ʼ����
		//��ʼ����
		 light(0x04);
		 Sleep(200);
		 if (chat_continue == false)//��¼��Ϣ�����ظ�������������
		 {
			 std::string str = access_out("select *  from start2", "l", "a");
			 if (situation(str) == true) { goto start_first; }
			 if (str == "Y")//ˢ���֤
			 {
				 robot_speak("���������֤�����ҵ�����ϣ��ҽ���ȡ���Ļ�����Ϣ��");
				 Sleep(1000);
				 //broadcast(L"ding.wav");
				 bool redult_ID = ID_card();
				 if (redult_ID == false)
				 {
					 robot_speak("�������֤��ʶ���ˣ��������һ��������������ɣ�");
					 goto start_first;
				 }
				 else
				 {

					 int filecount=0;
					 HANDLE hFile;
					 LPCTSTR lpFileName = L"C://Users//ROBOT//Desktop//result//*.html"; //ָ������Ŀ¼���ļ����ͣ�������d�̵���Ƶ�ļ�������"D:\\*.mp3"  
					 WIN32_FIND_DATA pNextInfo;  //�����õ����ļ���Ϣ��������pNextInfo��;  
					 hFile = FindFirstFile(lpFileName, &pNextInfo);//��ע���� &pNextInfo , ���� pNextInfo;  
					 
					 while (FindNextFile(hFile, &pNextInfo))
					 {
						 if (pNextInfo.cFileName[0] == '.')//����.��..  
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
					 string filepath = "C://Users//Administrator//Desktop//result//" + people_name + "���֤��"+ count +".html";
					 sickness = filepath;
					 writefile_data("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"\" xml:lang=\"\"><head></head>\<body>\<p><img src = \"C:\\Users\\Administrator\\Desktop\\result\\logo.jpg\"/></p>\<center>\<title>��ϱ���</title>\<font color = grey size = 5><strong>��ϱ���</strong></font></center>", sickness);
					 writefile_data("<p align=\"right\">", sickness);
					 writefile_data("��ţ�", sickness);
					 writefile_data(people_num, sickness);
					 writefile_data(count, sickness);
					 writefile_data("</p>", sickness);

					 writefile_data("<hr/>", sickness);
					 writefile_data("<p>������", sickness);
					 writefile_data(people_name, sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 writefile_data("�Ա�", sickness);
					 if (decide_sex == false)
					 {
						 writefile_data("��", sickness);
						 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
						 robot_speak("����," + people_name + "���������Ѿ���ȡ�����Ļ�����Ϣ�������պ��������֤��");
						 robot_speak("�������һ�������һЩ���������⣬����������ϡ�");
					 }
					 else
					 {
						 writefile_data("Ů", sickness);
						 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
						 robot_speak("����," + people_name + "Ůʿ�����������Ϣ�Ѿ��ɹ��Ľ��ж�ȡ�������պ��������֤��");
						 robot_speak("�������һ�������һЩ���������⣬����������ϡ�");
					 }
					 writefile_data("�������ڣ�", sickness);
					 writefile_data(people_birthday, sickness);
					 writefile_data("</p>", sickness);
					 writefile_data("<p>��ַ��", sickness);
					 writefile_data(people_address, sickness);
					 //writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					// writefile_data("������ڣ�", sickness);
					// writefile_data(people_time, sickness);
					 writefile_data("</p>", sickness);
					 writefile_data("<hr/>", sickness);


				 }
			 }
			 if (str == "N")
			 {
				 people_address = " ";
				 people_birthday = " ";
				 people_name = "δ֪";
				 robot_speak("�õģ�������Ҫ��һЩ���⣬�Ա��Ҷ���������״�����������жϣ�ϣ����������ϣ�");
				 std::string str_little = access_out("select *  from start", "l", "r");
				 if (situation(str_little) == true) { goto start_first; }
				 str_little = access_out("select *  from start", "l", "ra");
				 if (situation(str_little) == true) { goto start_first; }
				 if (str_little == "Y")
				 {
					 //cout << "����" << endl;
					 decide_sex = false;
				 }
				 if (str_little == "N")
				 {
					 //cout << "Ů��" << endl;
					 decide_sex = true;
				 }
				 str_little = access_out("select *  from start", "l", "taaa");
				 if (situation(str_little) == true) { goto start_first; }
				 str_little = access_out("select *  from start", "l", "taa");
				 if (situation(str_little) == true) { goto start_first; }
				 int filecount = 0;
				 HANDLE hFile;
				 LPCTSTR lpFileName = L"C://Users//ROBOT//Desktop//result//*.html"; //ָ������Ŀ¼���ļ����ͣ�������d�̵���Ƶ�ļ�������"D:\\*.mp3"  
				 WIN32_FIND_DATA pNextInfo;  //�����õ����ļ���Ϣ��������pNextInfo��;  
				 hFile = FindFirstFile(lpFileName, &pNextInfo);//��ע���� &pNextInfo , ���� pNextInfo;  

				 while (FindNextFile(hFile, &pNextInfo))
				 {
					 if (pNextInfo.cFileName[0] == '.')//����.��..  
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
				 people_time = to_string(systime.wYear) + "��" + to_string(systime.wMonth) + "��" + to_string(systime.wDay) + "��";
				 string filepath = "C://Users//Administrator//Desktop//result//" + people_name + "���֤��" + count + ".html";
				 sickness = filepath;
				 writefile_data("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"\" xml:lang=\"\"><head></head>\<body>\<p><img src = \"C:\\Users\\Administrator\\Desktop\\result\\logo.jpg\"/></p>\<center>\<title>��ϱ���</title>\<font color = grey size = 5><strong>��ϱ���</strong></font></center>", sickness);
				 writefile_data("<p align=\"right\">", sickness);
				 writefile_data("��ţ�", sickness);
				 writefile_data(people_num, sickness);
				 writefile_data(count, sickness);
				 writefile_data("</p>", sickness);

				 writefile_data("<hr/>", sickness);
				 writefile_data("<p>������", sickness);
				 writefile_data(" ", sickness);
				 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
				 writefile_data("�Ա�", sickness);
				 if (decide_sex == false)
				 {
					 writefile_data(" ", sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 robot_speak("�������һ�������һЩ���������⣬����������ϡ�");
				 }
				 else
				 {
					 writefile_data(" ", sickness);
					 writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
					 robot_speak("�������һ�������һЩ���������⣬����������ϡ�");
				 }
				 writefile_data("�������ڣ�", sickness);
				 writefile_data(people_birthday, sickness);
				 writefile_data("</p>", sickness);
				 writefile_data("<p>��ַ��", sickness);
				 writefile_data(people_address, sickness);
				 //writefile_data("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;", sickness);
				 // writefile_data("������ڣ�", sickness);
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
			 robot_speak("��Ļ�������Ҵ�������ˡ�");
			 //robot_speak("�õģ����������ھͽ��������жϣ�֮������һ����������ķ������������շ������������壡�����ǾͿ�ʼ�ɣ�");
			 std::string str = access_out("select *  from Institution_judg", "l", "a");
			 if (situation_noasktuichu(str) == true)
			 {
				 tizhipanduan = false;
				 goto start_first;
			 }
			 tizhipanduan = false;
			 goto last;
		 }

		 robot_speak("�õģ������������⽫���ݰ˸ٱ�֤��������֤����Ѫ��Һ��֤����ҽ�������۶��������ۺ���ϡ�");
		 robot_speak("���Ļش�������Ҫ�������Ļش�");
		 str = access_out("select *  from start2", "l", "c");
		 if (situation(str) == true) { goto start_first; }
		 str = access_out("select *  from start2", "l", "d");
		 if (situation(str) == true) { goto start_first; }
	wenzhen:
		//ѡ������
		 search_ID.clear();
		 light(0x05);
		 Sleep(200);
		FlushRect({ 100,200,500,400 });
		robot_speak("��ô���������ﲻ����أ�����Щ֢״��");
		promptPaint("���ಡ|�ļ�����|�Ľ�ʹ|����˥��|����ʧ��|��ʹ|����|��������|���಻���|��������|", 10, 35);
		promptPaint("��ľ��ʹ|������ľ��ʹ|��ľ|���׳���|������|����|�ູ|�Թ����쳣|�Թ����ϰ�|����|", 10, 60);
		promptPaint("��ϥ��ʹ|ȫ������|������ʹ|��������|��ϥ��ʹ|������|��������|ȫ����|������ʹ|ϥ����ʹ|", 10, 85);
		promptPaint("˫���쳣|˫�Ų�����|˫�Ų����|˫����ľ��ʹ|˫����ʹ��ľ|˫�ŷ���|˫�ŷ���|����|����|�Ƚ���ʹ|", 10, 110);
		promptPaint("��θ�����|��θ����|θ�������|θ������|θ����ʹ|θ��|��������|���Ƹ���|��������|������|", 10, 135);
		promptPaint("������ʳ|��������|��ʳ����|�ȵĶ�|��ˮ��|��ʳ|�ԵĶ�|С���|����С��|�����ʳ|���|��Ƶ|", 10, 160);
		promptPaint("С�㲻��|С�㲻��|�򲻳�|С�����|����|��Ƶ|���|С���|�ϲ���Ƶ��|С��Ƶ��|֫������|��֫����|�ȽŲ�����|����|����|û��|����|", 10, 185);
		promptPaint("���ٲ����|�鷿�����|�ز������|��ͷ����Һ|��ͷ����|��֭��ͨ|��������|������|���ٽ��|��������|���ٰ�|���ٲ���|�鷿����|", 10, 210);
		promptPaint("����ģ��|�۾���ɬ|ģ��|�۾�ģ��|������|��������|������ʹ|��ʹ����|������ʹ|������ʹ|��ʹ|�ز���ʹ|Ƥ������|Ƥ������|Ƥ����|Ƥ���쳣|", 10, 235);

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
		//writefile_data(putstr, doctor);//����εĻش����뱨��
		FlushRect({ 10,35,1200,265 });

		light(0x06);
		Sleep(200);
		if (findstr_or(putstr, { "�˳�","ֹͣ","����" }))
		{
			robot_speak("ϣ�������彡���������´����İ�!");
			goto start_first;
		}

		if (findstr_or(putstr, { "����","�����ж�" }) == true)
		{
			//robot_speak("�õģ����������ھͽ��������жϣ�֮������һ����������ķ������������շ������������壡�����ǾͿ�ʼ�ɣ�");
			std::string str = access_out("select *  from Institution_judg", "l", "a");
			if (situation_noasktuichu(str) == true) { goto start_first; }
			goto last;
		}


		str = access_out("select *  from start", "l", "u");//�����˶�ã���ǰ��û�����Ƶ�֢״���ֹ�������ҽ������
		if (situation(str) == true) { goto start_first; }

		get_ans = access_out("select *  from choose_sickness", putstr, "aa");
		if (findstr_or(putstr, { tuichu }))
		{
			robot_speak("ϣ�������彡���������´����İ�!");
			goto start_first;
		}


		if (search_ID.size() != 0)//�����������Ŵ�����
		{
			str = access_out("select *  from start", "l", "v");
			if (situation(str) == true) { goto start_first; }
			str = access_out("select *  from start", "l", "va");
			if (situation(str) == true) { goto start_first; }
		}



		{//�������ҽ��������֢״��һЩ��������⣬�����อ֢�򡢾���֢������ӪѪ֢������ļ������о�ȷ���жϣ��������һ�¡�
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


		


		/****************************************���ಡ************************************************************/

		for (int i = 0; i < search_ID.size(); i++)
		{
			if (search_ID[i] == "aa")//@���ಡ
			{
				//std::cout << "@���ಡ" << std::endl;
				//robot_speak("��������״���������������ǻ������ಡ�����Ұ����������ಡ����ؼ�����ϰɣ�");
				std::string str = access_out("select *  from heart_disease", "l", "a");
				if (situation_noasktuichu(str) == true) { goto start_first; }
				if (str == "Y")
				{
					search_ID.clear();
					goto wenzhen;
				}
				if (str == "N")
				{
					std::string str1 = access_out("select *  from start", "l", "f");//�ж��Ƿ��˳�
					if (situation_noasktuichu(str1) == true) { goto start_first; }
					if (str1 == "Y")
					{
						robot_speak("�õģ������Ǽ�����!");
						goto wenzhen;
					}
					if (str1 == "N")
					{
						robot_speak("ϣ�������彡���������´����İ�!");
						goto start_first;
					}
				}
				decide_complication = true;
				decide_heart_disease = true;
			}


			/****************************************���ٲ�**************************************************************/
			if (search_ID[i] == "ca")//@���ٲ���Ů�Բ�
			{
				//robot_speak("�ţ�����������������صļ������Ұ����������ټ�����ҽ���ʴ�ɣ�");
				//std::cout << "@���ٲ�" << std::endl;
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
						robot_speak("�õģ������Ǽ�����!");
						goto wenzhen;
					}
					if (str1 == "N")
					{
						robot_speak("ϣ�������彡���������´����İ�!");
						goto start_first;
					}
				}
				decide_complication = true;
				decide_Breast_disease = true;
			}

			/****************************************����**************************************************************/
			if (search_ID[i] == "ea")//"@����
			{
				//std::cout << "@����" << std::endl;
				decide_tangniao = true;
				decide_complication = false;
				//robot_speak("�ղ�����������˵���������򲡣������Ǿ�ֱ�ӽ������򲡵���ϰɣ�");
			}

			/****************************************������ʳ**************************************************************/

			if (search_ID[i] == "ga"&&decide_tangniao == false)//@������ʳ
			{
				ans_xuetang = access_out("select *  from diabetes_ask", "l", "a");
				if (situation_noasktuichu(ans_xuetang) == true) { goto start_first; }
				if (ans_xuetang == "N")
				{
					//robot_speak("�õģ��Ժ������ǵĻ�ʿ������һ��Ѫ�ǰ�");
					robot_speak("��������Ѫ�������������");
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
				//					robot_speak("�������ڸ��ҿ���Ц������û��������Ѫ��ֵ���������ʣ�");
				//					c = 0;
				//				}
				//			}
				//			if (c > 30.0 || c<2.0)
				//			{
				//				robot_speak("�������ڸ��ҿ���Ц������û��������Ѫ��ֵ���������ʣ�");
				//				c = 0;
				//				goto cexuetang;
				//			}
				//			if (c <= 6.1&&c >= 2.0)
				//			{
				//				robot_speak("�õģ�����Ѫ�Ǵ�������ˮƽ���Ұ������������жϰɣ�");
				//				decide_tangniao = false;
				//			}
				//			if (c>6.1)
				//			{
				//				//robot_speak("�������ж������ܴ��ڸ�Ѫ��״̬��");
				//				decide_tangniao = true;
				//			}//����Χ���е�����

				decide_tangniao = true;
				decide_complication = false;
			}
		}

		/************************************************����֢�ʴ�****************************************************/
		search_ID.clear();
		if (decide_complication == false)//�����Ƿ���в���֢�ʴ�
		{
			get_ans = access_out("select *  from choose_complication", putstr, "aa");
			if (get_ans == tuichu)
			{
				robot_speak("ϣ�������彡���������´����İ�!");
				goto start_first;
			}

			//����һ�������ӣ����ض��Ĳ���֢�����ʴ�
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

		/************************************������֤�ʴ�***************************************************************/
		if (decide_complicordebets == false && decide_tangniao == true)
		{
			//tts("��ô�������ǽ�Ҫ�������򲡵���֤�ʴ��ˣ�");
			//robot_speak("��ô�������ǽ�Ҫ�������򲡵���֤�ʴ��ˣ�");
			std::string str = access_out("select *  from diabetes", "l", "a");
			if (situation_noasktuichu(str) == true) { goto start_first; }

			if (str == "Y")
			{
				search_ID.clear();
				robot_speak("�õģ������Ǽ��������");
				goto wenzhen;
			}
			if (str == "N")
			{
				std::string str1 = access_out("select *  from start", "l", "f");
				if (situation_noasktuichu(str1) == true) { goto start_first; }
				if (str1 == "Y")
				{
					search_ID.clear();
					robot_speak("�õģ������Ǽ�����!");
					goto wenzhen;
				}
				if (str1 == "N")
				{
					robot_speak("ϣ�������彡���������´����İ�!");
					goto start_first;
				}
			}
		}

		/****************************************�����ж�**************************************************************/
		if (decide_tangniao == false && search_ID.empty() && decide_heart_disease == false && decide_Breast_disease == false)
		{
			//std::cout << "���������жϣ�������������" << endl;
			string str1;
			if (decide_tizhi == true)
			{
				str1 = access_out("select *  from start", "l", "n");
				robot_speak("���������������ɣ�");
			}
			else
			{
				str1 = access_out("select *  from Institution_judg", "l", "j");
			}
			decide_tizhi = false;
			if (situation_noasktuichu(str1) == true) { goto start_first; }
			if (str1 == "Y")
			{
				//robot_speak("�õģ����������ھͽ��������жϣ�֮������һ����������ķ������������շ������������壡�����ǾͿ�ʼ�ɣ�");
				std::string str = access_out("select *  from Institution_judg", "l", "a");
				if (situation_noasktuichu(str) == true) { goto start_first; }
			}

			if (str1 == "N")
			{
				std::string str1 = access_out("select *  from start", "l", "f");
				if (situation_noasktuichu(str1) == true) { goto start_first; }

				if (str1 == "Y")
				{
					robot_speak("�õģ������Ǽ�����!");
					goto wenzhen;
				}
				if (str1 == "N")
				{
					robot_speak("ϣ�������彡���������´����İ�!");
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
			robot_speak("ϣ�������彡��!");
			goto start_first;
		}
		if (str1 == "Y")
		{
			search_ID.clear();
			robot_speak("�õģ������Ǽ�����!");
			goto wenzhen;
		}*/


		search_ID.clear();
		robot_speak("ϣ�������彡��!�ټ���");
		goto start_first;


		//�˳�
	logout:
		broadcast(L"start.wav");
		robot_speak("ϣ�������彡���������´����İɣ�");
		MSPLogout(); //�˳���¼
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

INT_PTR CALLBACK  DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam) //�Ի�����̺���
{
	 mydlg = hdlg;
	 RECT button1rect = { 160,50,360,250 };
	 RECT button2rect = { 430,50,630,250 };

	HDC ghdc = GetDC(hdlg);  //��ȡ�豸�������
	int size;
	TCHAR a[] = L"��ǰ�ǵ�";
	TCHAR b[] = L"վ";
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
		L"����"); // lpszFac
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
		TextOut(ghdc, 222, 260, L"��һվ", 4);
		TextOut(ghdc, 510, 260, L"ֹͣ", 4);
		size = wsprintf(szText, TEXT("%s%d%s"), a, stationindex, b);
		//����wsprintf()��һϵ�е��ַ�����ֵ���뵽�������������ķ���ֵ��д��ĳ���  
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
			// ���ִ���˹ر�  
			// ���ٶԻ��򣬽��յ�WM_DESTROY��Ϣ  
			DestroyWindow(hdlg);
			ttsValued1 = 0;

		}
		return 0;
	}
	return (INT_PTR)FALSE;
}
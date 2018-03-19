#include <conio.h>
#include "XAudio2.h"
#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"

#pragma comment(lib,"xaudio2.lib")
bool ttsValued=1;

IXAudio2 *pEngine = NULL;
IXAudio2MasteringVoice *pMasterVoice = NULL;
IXAudio2SourceVoice *pSourceVoice = NULL;


void broadcast(LPWSTR wave_name)
{
	PlaySound(wave_name, NULL, SND_FILENAME);
	
}


void warningall()
{
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!网络状态不太好!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int				size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int				fmt_size;				// = 下一个结构体的大小 : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = 通道数 : 1
	int				samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	int				avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	short int       bits_per_sample;        // = 量化比特数: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = 纯数据长度 : FileSize - 44 
} wave_pcm_hdr;

/* 默认wav音频头部数据 */
wave_pcm_hdr default_wav_hdr =
{
	{ 'R', 'I', 'F', 'F' },
	0,
	{ 'W', 'A', 'V', 'E' },
	{ 'f', 'm', 't', ' ' },
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{ 'd', 'a', 't', 'a' },
	0
};

//int text_to_speech(const char* src_text, const char* des_path, const char* params)
//{
//	int          ret = -1;
//	FILE*        fp = NULL;
//	const char*  sessionID = NULL;
//	unsigned int audio_len = 0;
//	wave_pcm_hdr wav_hdr = default_wav_hdr;
//	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;
//
//	if (NULL == src_text || NULL == des_path)
//	{
//		printf("params is error!\n");
//		return ret;
//	}
//	fopen_s(&fp,des_path, "wb");
//	if (NULL == fp)
//	{
//		printf("open %s error.\n", des_path);
//		return ret;
//	}
//	
//	sessionID = QTTSSessionBegin(params, &ret);
//	if (MSP_SUCCESS != ret)
//	{
//		warningall();
//		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
//		fclose(fp);
//		return ret;
//	}
//	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
//
//	if (MSP_SUCCESS != ret)
//	{
//		warningall();
//		printf("QTTSTextPut failed, error code: %d.\n", ret);
//		QTTSSessionEnd(sessionID, "TextPutError");
//		fclose(fp);
//		return ret;
//	}
//
//
//	//printf("正在合成 ,播放...\n");
//	fwrite(&wav_hdr, sizeof(wav_hdr), 1, fp); //添加wav音频头，使用采样率为16000
//	while (1)
//	{
//		/* 获取合成音频 */
//		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
//		if (MSP_SUCCESS != ret)
//			break;
//		if (NULL != data)
//		{
//			fwrite(data, audio_len, 1, fp);
//			wav_hdr.data_size += audio_len; //计算data_size大小
//		}
//		if (MSP_TTS_FLAG_DATA_END == synth_status)
//			break;
//		//printf(">");//输出
//		Sleep(150); //防止频繁占用CPU
//	}
//	//printf("\n");
//
//	if (MSP_SUCCESS != ret)
//	{
//		warningall();
//		printf("QTTSAudioGet failed, error code: %d.\n", ret);
//		QTTSSessionEnd(sessionID, "AudioGetError");
//		fclose(fp);
//		return ret;
//	}
//	/* 修正wav文件头数据的大小 */
//	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);
//
//	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
//	fseek(fp, 4, 0);
//	fwrite(&wav_hdr.size_8, sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
//	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
//	fwrite(&wav_hdr.data_size, sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
//	fclose(fp);
//	fp = NULL;
//	/* 合成完毕 */
//	ret = QTTSSessionEnd(sessionID, "Normal");
//	if (MSP_SUCCESS != ret)
//	{
//		warningall();
//		printf("QTTSSessionEnd failed, error code: %d.\n", ret);
//	}
//
//	return ret;
//}
void FlushRect(RECT Rect)
{
	HWND hwnd = FindWindow(L"mywindow", L"服务机器人小周");
	HDC g_hdc = GetDC(hwnd);
	HBITMAP g_hBit = (HBITMAP)LoadImage(NULL, L"img//bg.bmp", IMAGE_BITMAP, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), LR_LOADFROMFILE);
	HDC g_mdctemp = CreateCompatibleDC(g_hdc);
	SelectObject(g_mdctemp, g_hBit);
	BitBlt(g_hdc, Rect.left, Rect.top, Rect.right- Rect.left, Rect.bottom- Rect.top, g_mdctemp, Rect.left, Rect.top, SRCCOPY);    //采用BitBlt函数贴图，参数设置为窗口大小																																																														//InvalidateRect(hwnd, &Rect, false);
}
void FlushRect2(HWND hwnd ,RECT Rect)
{
	HDC g_hdc = GetDC(hwnd);
	HBITMAP g_hBit = (HBITMAP)LoadImage(NULL, L"img//bg2.bmp", IMAGE_BITMAP, 800,800, LR_LOADFROMFILE);
	HDC g_mdctemp = CreateCompatibleDC(g_hdc);
	SelectObject(g_mdctemp, g_hBit);
	BitBlt(g_hdc, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, g_mdctemp, Rect.left, Rect.top, SRCCOPY);    //采用BitBlt函数贴图，参数设置为窗口大小																																																														//InvalidateRect(hwnd, &Rect, false);
}

//int tts(const char* text)
//{
//	int  ret = MSP_SUCCESS;
//	//char* login_params = "appid = 59c066c4, work_dir = .";
//	char* session_begin_params = "voice_name = xiaofeng, text_encoding = gb2312, sample_rate = 16000, speed = 35, volume = 100, pitch = 50, rdn = 0";
//	//ret = MSPLogin(NULL, NULL, login_params); //第一个参数是用户名，第二个参数是密码，第三个参数是登录参数，用户名和密码可在http://www.xfyun.cn注册获取,此时不应该再登陆
//	char*filename = "tts_sample.wav";
//	if (*text=='\0')  return 0;
//	
//	ret = text_to_speech(text, filename, session_begin_params);
//	if (MSP_SUCCESS != ret)
//	{
//		warningall();
//	printf("text_to_speech failed, error code: %d.\n", ret);
//	return 0;
//	}
//	broadcast(L"tts_sample.wav");
//	//MSPLogout(); //退出登录
//	return 0;
//}
int tts(const char* src_text)
{
	const char* params = "voice_name = xiaofeng, text_encoding = gb2312, sample_rate = 16000, speed = 30, volume = 100, pitch = 50, rdn = 2";
	//MSPLogin(NULL, NULL, "appid = 59c066c4, work_dir = .");
	//MSPLogout(); //退出登录

	int ret = -1;
	int  synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	unsigned int audio_len = 0;
	unsigned int speech_len = 0;

	const char*sessionID = QTTSSessionBegin(params, &ret);
	const void* audio_data = NULL;
	char* synth_speech = new char[2 * 1024 * 1024];

	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);

	

	WAVEFORMATEX waveFormat = { 1,1,16000,32000,2,16,0 };//获取文件格式

	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))exit(0);
	if (FAILED(XAudio2Create(&pEngine)))exit(0);
	if (FAILED(pEngine->CreateMasteringVoice(&pMasterVoice)))exit(0);
	if (FAILED(pEngine->CreateSourceVoice(&pSourceVoice, &waveFormat)))exit(0);

	while (MSP_TTS_FLAG_DATA_END != synth_status)
	{
		audio_data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
		if (ret) break;
		if (NULL != audio_data && 0 != audio_len)
		{
			memcpy(synth_speech + speech_len, audio_data, audio_len);
			speech_len += audio_len;
		}
	}
	ret = QTTSSessionEnd(sessionID, "Normal");

	BYTE *pData = new BYTE[speech_len];//申请内存空间，用于保存数据
	pData = (BYTE*)synth_speech;

	XAUDIO2_BUFFER buffer = { 0 };//将读取的文件数据，赋值XAUDIO2_BUFFER
	buffer.AudioBytes = speech_len;
	buffer.pAudioData = pData;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	pSourceVoice->SubmitSourceBuffer(&buffer);//提交内存数据
	pSourceVoice->Start(0);//启动源声音
	XAUDIO2_VOICE_STATE state;
	pSourceVoice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);//获取状态
	ttsValued = 1;
	while (state.BuffersQueued&&ttsValued)
	{
			pSourceVoice->GetState(&state);
	}
	ttsValued =1;
	pMasterVoice->DestroyVoice();//释放资源
	pSourceVoice->DestroyVoice();//释放资源
	pEngine->Release();//释放资源

	CoUninitialize();//释放资源
	//cout << pData;
	delete[] pData;//释放资源
	pData = NULL;
	//MSPLogout(); //退出登录
	//MessageBox(NULL, L"", L"", 1);
	return 0;
}

//void tts(std::string stringall)
//{
//	stringall = stringall + "/";
//	while (1)
//	{
//		int x = stringall.find_first_of("/");
//		if (x <= 0) break;
//		std::string str_temp = stringall.substr(0, x);
//		cout << "o_O:" << str_temp << endl;
//		text_to_speech(str_temp.c_str());
//		std::string str_others = stringall.substr(str_temp.length() + 1);
//		stringall = str_others;
//	}
//}

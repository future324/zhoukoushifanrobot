#include"tts1.h"

bool ttsValued1 = 1;
int stationindex;

int tts1(const char* src_text)
{
	IXAudio2 *pEngine = NULL;
	IXAudio2MasteringVoice *pMasterVoice = NULL;
	IXAudio2SourceVoice *pSourceVoice = NULL;
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
	ttsValued1 = 1;

	while (MSP_TTS_FLAG_DATA_END != synth_status&& ttsValued1==1)
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
	while (state.BuffersQueued&&ttsValued1)
	{
		pSourceVoice->GetState(&state);
	}
	pMasterVoice->DestroyVoice();//释放资源
	pSourceVoice->DestroyVoice();//释放资源
	pEngine->Release();//释放资源

	CoUninitialize();//释放资源
					 //cout << pData;
	delete[] pData;//释放资源
	pData = NULL;

	return 0;
}

//
#include <string>
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace  rename ("EOF", "adoEOF")  

class AdoAccess2 {
public:
	::_ConnectionPtr   HX_pConnection; // 数据库指针  
	::_RecordsetPtr    HX_pRecordset; // 命令指针  
	::_CommandPtr      HX_pCommand; // 记录指针  
	void OnInitADOConn()
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		try
		{
			HX_pConnection.CreateInstance("ADODB.Connection");
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=讲解.accdb;Persist Security Info=False ";

			HX_pConnection->Open(strConnect, "", "", adModeUnknown);    //连接数据库  
																		//cout << "连接成功,并获得智能指针" << endl;
		}
		catch (_com_error e)
		{
			std::cout << e.Description() << std::endl;
		}

	}
	void ExitConnect()
	{
		if (HX_pRecordset != NULL)
			HX_pRecordset->Close();
		HX_pConnection->Close();
		::CoUninitialize();
	}
};
std::string  access2(_variant_t  File_Selected)
{
	AdoAccess2 dataBase;
	_variant_t  var_result;

	std::string result;
	dataBase.OnInitADOConn();
	dataBase.HX_pRecordset.CreateInstance("ADODB.Recordset");
	dataBase.HX_pRecordset->Open(File_Selected, dataBase.HX_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);//选择名为Test的表格  
	ttsValued1 = 1;
	while (!dataBase.HX_pRecordset->adoEOF&&ttsValued1 == 1)//查表未结束
	{
		var_result = dataBase.HX_pRecordset->GetCollect("result");
		result = _com_util::ConvertBSTRToString((_bstr_t)var_result);
		//cout << "result:" << result << endl;
		tts1(result.c_str());
		dataBase.HX_pRecordset->MoveNext();
	}
	dataBase.ExitConnect();//卸载com组件  
	return result;
}


void explain(int station)
{

	switch (station)
	{
	case 0:
		access2("select * from zero");
		//tts("大家好，我是机器人研究中心的服务机器人小周，欢迎莅临指导，下面请在我引导下参观建成的机器人平台。");
		break;
	case 1:
		access2("select * from one");

		//tts("现在大家面前的是由周口师范学院机器人研究中心自主研发的塔式全封闭立体车库模型。旨在解决日益严重的停车困难、现有立体车库智能化程度不高等问题。塔式全封闭立体车库模型包含1个进车口、1个出车口和10个停车位。在未来城市建设及规划中具有很大的应用前景。接下来，由我带领大家参观工业产品检测平台。");
		break;
	case 2:
		access2("select * from two");
		//tts("这是工业产品检测平台，其功能是将待检目标转换成数字信号，使用计算机系统代替人脑进行测量和判断，控制现场设备的动作，实现工业产品缺陷的检测和定位。中心工业产品检测平台采用机器视觉的方法进行物体缺陷和表面建模研究。通过加装红外和超声等传感器，平台可进行多模态数据的采集与融合，能够完成更加复杂和精确的检测任务。接下来，由我带领大家参观工业机械臂平台");
		break;
	case 3:
		access2("select * from three");
		//tts("现在您面前的是工业机械臂平台。该平台为五自由度机械臂，由五个独立且可联动的伺服电机组驱动，可以使机械臂末端达到空间内任意一点，或者沿着空间内任意曲线扫描。前端可以根据任务不同挂载不同的任务组件，可以完成喷涂、焊接、装配、码垛、打磨等多种繁琐的工业任务。机械臂是机器人技术领域中实际应用最广泛的自动化机械装置，现今已大量应用于工业制造、医学治疗、娱乐服务、军事、半导体制造以及太空探索等领域。");
		break;
	case 4:
		access2("select * from four");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break;
	case 5:
		access2("select * from five");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break; 
	case 6:
		access2("select * from six");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break; 
	case 7:
		access2("select * from seven");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break;
	case 8:
		access2("select * from eight");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break;
	case 9:
		access2("select * from nine");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break;
	case 10:
		access2("select * from ten");
		//tts("我的讲解就到此结束，非常感谢各位领导。");
		break;
	default:
		tts1("没有此站");
		break;
	}
}
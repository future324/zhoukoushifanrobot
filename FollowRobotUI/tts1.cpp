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
	//MSPLogout(); //�˳���¼

	int ret = -1;
	int  synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	unsigned int audio_len = 0;
	unsigned int speech_len = 0;

	const char*sessionID = QTTSSessionBegin(params, &ret);
	const void* audio_data = NULL;
	char* synth_speech = new char[2 * 1024 * 1024];

	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);



	WAVEFORMATEX waveFormat = { 1,1,16000,32000,2,16,0 };//��ȡ�ļ���ʽ

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

	BYTE *pData = new BYTE[speech_len];//�����ڴ�ռ䣬���ڱ�������
	pData = (BYTE*)synth_speech;

	XAUDIO2_BUFFER buffer = { 0 };//����ȡ���ļ����ݣ���ֵXAUDIO2_BUFFER
	buffer.AudioBytes = speech_len;
	buffer.pAudioData = pData;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	pSourceVoice->SubmitSourceBuffer(&buffer);//�ύ�ڴ�����
	pSourceVoice->Start(0);//����Դ����
	XAUDIO2_VOICE_STATE state;
	pSourceVoice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);//��ȡ״̬
	while (state.BuffersQueued&&ttsValued1)
	{
		pSourceVoice->GetState(&state);
	}
	pMasterVoice->DestroyVoice();//�ͷ���Դ
	pSourceVoice->DestroyVoice();//�ͷ���Դ
	pEngine->Release();//�ͷ���Դ

	CoUninitialize();//�ͷ���Դ
					 //cout << pData;
	delete[] pData;//�ͷ���Դ
	pData = NULL;

	return 0;
}

//
#include <string>
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace  rename ("EOF", "adoEOF")  

class AdoAccess2 {
public:
	::_ConnectionPtr   HX_pConnection; // ���ݿ�ָ��  
	::_RecordsetPtr    HX_pRecordset; // ����ָ��  
	::_CommandPtr      HX_pCommand; // ��¼ָ��  
	void OnInitADOConn()
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		try
		{
			HX_pConnection.CreateInstance("ADODB.Connection");
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=����.accdb;Persist Security Info=False ";

			HX_pConnection->Open(strConnect, "", "", adModeUnknown);    //�������ݿ�  
																		//cout << "���ӳɹ�,���������ָ��" << endl;
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
	dataBase.HX_pRecordset->Open(File_Selected, dataBase.HX_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);//ѡ����ΪTest�ı��  
	ttsValued1 = 1;
	while (!dataBase.HX_pRecordset->adoEOF&&ttsValued1 == 1)//���δ����
	{
		var_result = dataBase.HX_pRecordset->GetCollect("result");
		result = _com_util::ConvertBSTRToString((_bstr_t)var_result);
		//cout << "result:" << result << endl;
		tts1(result.c_str());
		dataBase.HX_pRecordset->MoveNext();
	}
	dataBase.ExitConnect();//ж��com���  
	return result;
}


void explain(int station)
{

	switch (station)
	{
	case 0:
		access2("select * from zero");
		//tts("��Һã����ǻ������о����ĵķ��������С�ܣ���ӭݰ��ָ�������������������²ι۽��ɵĻ�����ƽ̨��");
		break;
	case 1:
		access2("select * from one");

		//tts("���ڴ����ǰ�������ܿ�ʦ��ѧԺ�������о����������з�����ʽȫ������峵��ģ�͡�ּ�ڽ���������ص�ͣ�����ѡ��������峵�����ܻ��̶Ȳ��ߵ����⡣��ʽȫ������峵��ģ�Ͱ���1�������ڡ�1�������ں�10��ͣ��λ����δ�����н��輰�滮�о��кܴ��Ӧ��ǰ���������������Ҵ����Ҳι۹�ҵ��Ʒ���ƽ̨��");
		break;
	case 2:
		access2("select * from two");
		//tts("���ǹ�ҵ��Ʒ���ƽ̨���书���ǽ�����Ŀ��ת���������źţ�ʹ�ü����ϵͳ�������Խ��в������жϣ������ֳ��豸�Ķ�����ʵ�ֹ�ҵ��Ʒȱ�ݵļ��Ͷ�λ�����Ĺ�ҵ��Ʒ���ƽ̨���û����Ӿ��ķ�����������ȱ�ݺͱ��潨ģ�о���ͨ����װ����ͳ����ȴ�������ƽ̨�ɽ��ж�ģ̬���ݵĲɼ����ںϣ��ܹ���ɸ��Ӹ��Ӻ;�ȷ�ļ�����񡣽����������Ҵ����Ҳι۹�ҵ��е��ƽ̨");
		break;
	case 3:
		access2("select * from three");
		//tts("��������ǰ���ǹ�ҵ��е��ƽ̨����ƽ̨Ϊ�����ɶȻ�е�ۣ�����������ҿ��������ŷ����������������ʹ��е��ĩ�˴ﵽ�ռ�������һ�㣬�������ſռ�����������ɨ�衣ǰ�˿��Ը�������ͬ���ز�ͬ��������������������Ϳ�����ӡ�װ�䡢��⡢��ĥ�ȶ��ַ����Ĺ�ҵ���񡣻�е���ǻ����˼���������ʵ��Ӧ����㷺���Զ�����еװ�ã��ֽ��Ѵ���Ӧ���ڹ�ҵ���졢ҽѧ���ơ����ַ��񡢾��¡��뵼�������Լ�̫��̽��������");
		break;
	case 4:
		access2("select * from four");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break;
	case 5:
		access2("select * from five");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break; 
	case 6:
		access2("select * from six");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break; 
	case 7:
		access2("select * from seven");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break;
	case 8:
		access2("select * from eight");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break;
	case 9:
		access2("select * from nine");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break;
	case 10:
		access2("select * from ten");
		//tts("�ҵĽ���͵��˽������ǳ���л��λ�쵼��");
		break;
	default:
		tts1("û�д�վ");
		break;
	}
}
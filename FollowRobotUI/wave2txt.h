#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "tuling.h"


#define	BUFFER_SIZE	4096   //Decide the input character.
#define FRAME_LEN	640 
#define HINTS_SIZE  100

string run_iat()//wave to txt.
{
	char* session_begin_params = "sub = iat, domain = iat, language = zh_cn, accent = mandarin, sample_rate = 16000, result_type = plain, result_encoding = gb2312";
	const char*		session_id = NULL;
	char			rec_result[BUFFER_SIZE] = { NULL };
	char			hints[HINTS_SIZE] = { NULL }; //hintsΪ�������λỰ��ԭ�����������û��Զ���
	unsigned int	total_len = 0;
	int				aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;		//��Ƶ״̬
	int				ep_stat = MSP_EP_LOOKING_FOR_SPEECH;		//�˵���
	int				rec_stat = MSP_REC_STATUS_SUCCESS;			//ʶ��״̬
	int				errcode = MSP_SUCCESS;

	FILE*			f_pcm = NULL;
	char*			p_pcm = NULL;
	long			pcm_count = 0;
	long			pcm_size = 0;
	long			read_size = 0;
	string tts_str;
	string str1;

	fopen_s(&f_pcm,"test.wav", "rb");
	if (NULL == f_pcm)
	{
		cout << "Wav open error!!!" << endl;
		goto iat_exit;
	}

	fseek(f_pcm, 0, SEEK_END);
	pcm_size = ftell(f_pcm); //��ȡ��Ƶ�ļ���С 
	fseek(f_pcm, 0, SEEK_SET);

	p_pcm = (char *)malloc(pcm_size);
	if (NULL == p_pcm)
	{
		printf("\nout of memory! \n");
		goto iat_exit;
	}

	read_size = fread((void *)p_pcm, 1, pcm_size, f_pcm); //��ȡ��Ƶ�ļ�����
	if (read_size != pcm_size)
	{
		cout << "Read error!!!" << endl;
		goto iat_exit;
	}

	printf("\n��ʼ������д ...\n");
	session_id = QISRSessionBegin(NULL, session_begin_params, &errcode); //��д����Ҫ�﷨����һ������ΪNULL
	if (MSP_SUCCESS != errcode)
	{
		printf("\nQISRSessionBegin failed! error code:%d\n", errcode);
		goto iat_exit;
	}

	while (1)
	{
		unsigned int len = 10 * FRAME_LEN; // ÿ��д��200ms��Ƶ(16k��16bit)��1֡��Ƶ20ms��10֡=200ms��16k�����ʵ�16λ��Ƶ��һ֡�Ĵ�СΪ640Byte
		int ret = 0;

		if (pcm_size < 2 * len)
			len = pcm_size;
		if (len <= 0)
			break;

		aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;
		if (0 == pcm_count)
			aud_stat = MSP_AUDIO_SAMPLE_FIRST;

		printf(">");
		ret = QISRAudioWrite(session_id, (const void *)&p_pcm[pcm_count], len, aud_stat, &ep_stat, &rec_stat);
		if (MSP_SUCCESS != ret)
		{
			printf("\nQISRAudioWrite failed! error code:%d\n", ret);
			goto iat_exit;
		}

		pcm_count += (long)len;
		pcm_size -= (long)len;

		if (MSP_REC_STATUS_SUCCESS == rec_stat) //�Ѿ��в�����д���
		{
			const char *rslt = QISRGetResult(session_id, &rec_stat, 0, &errcode);
			if (MSP_SUCCESS != errcode)
			{
				printf("\nQISRGetResult failed! error code: %d\n", errcode);
				goto iat_exit;
			}
			if (NULL != rslt)
			{
				unsigned int rslt_len = strlen(rslt);
				total_len += rslt_len;
				if (total_len >= BUFFER_SIZE)
				{
					printf("\nno enough buffer for rec_result !\n");
					goto iat_exit;
				}
				strncat_s(rec_result, rslt, rslt_len);
			}
		}

		if (MSP_EP_AFTER_SPEECH == ep_stat)  break;

		//Sleep(200); //ģ����˵��ʱ���϶��200ms��Ӧ10֡����Ƶ
	}
	errcode = QISRAudioWrite(session_id, NULL, 0, MSP_AUDIO_SAMPLE_LAST, &ep_stat, &rec_stat);
	if (MSP_SUCCESS != errcode)
	{
		printf("\nQISRAudioWrite failed! error code:%d \n", errcode);
		goto iat_exit;
	}

	while (MSP_REC_STATUS_COMPLETE != rec_stat)
	{
		const char *rslt = QISRGetResult(session_id, &rec_stat, 0, &errcode);
		if (MSP_SUCCESS != errcode)
		{
			printf("\nQISRGetResult failed, error code: %d\n", errcode);
			goto iat_exit;
		}
		if (NULL != rslt)
		{
			unsigned int rslt_len = strlen(rslt);
			total_len += rslt_len;
			if (total_len >= BUFFER_SIZE)
			{
				printf("\nno enough buffer for rec_result !\n");
				goto iat_exit;
			}
			strncat_s(rec_result, rslt, rslt_len);
		}
		Sleep(150); //��ֹƵ��ռ��CPU
	}
	printf("\n=============================================================\n");
	printf("%s\n", rec_result);
	printf("=============================================================\n");

iat_exit:
	if (NULL != f_pcm)
	{
		fclose(f_pcm);
		f_pcm = NULL;
	}
	if (NULL != p_pcm)
	{
		free(p_pcm);
		p_pcm = NULL;
	}
	QISRSessionEnd(session_id, hints);
	return rec_result;
}
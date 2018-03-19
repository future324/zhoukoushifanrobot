#ifndef TERMB_H
#define TERMB_H

/**
*	@file		termb.h
*	@brief		���֤�Ķ������֤�Ķ��ӿں���
*	@author		scar chen
*	@date		2015-06-29
*	@version	2.0
*	@par	��Ȩ��
*				ZKTeco
*	@par	��ʷ�汾
*
*	@note		
*
*/

#ifndef ZKAPI
#define ZKAPI __stdcall
#endif

#ifndef ZKINTERFACE
#ifndef _USRDLL 
#ifdef _LIB
#define ZKINTERFACE
#else
#define ZKINTERFACE __declspec(dllimport)
#endif
#else	//_ZKDLL
#define ZKINTERFACE
#endif	//_ZKDLL
#endif


#ifdef __cplusplus
extern "C"
{
#endif


	/**
	*	@brief	�������֤�Ķ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	iPort			|	int			|	[in]				|	�˿ںţ�˵�����±�
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	>0				|	�ɹ����ض˿ں�
	*	0				|	ʧ��
	*	@note �����������豸
	*	�˿ں�˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1~16			|	�����豸
	*	1001~1016		|	USB�豸
	*/
	ZKINTERFACE int ZKAPI InitComm(int Port);

	/**
	*	@brief	�Զ��������֤�Ķ������������֤�Ķ���
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	>0				|	�ɹ����ض˿ں�
	*	0				|	ʧ��
	*	@note	�����������豸
	*/
	ZKINTERFACE int ZKAPI InitCommExt();



	/**
	*	@brief	�Ͽ������֤�Ķ�������
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*/
	ZKINTERFACE int ZKAPI CloseComm();
	
	
	
	/**
	*	@brief	����֤�����������ڶ������Ϳ�Ƭ֮��ĺϷ����ȷ��
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	-1				|	Ѱ��ʧ��
	*	-2				|	ѡ��ʧ��
	*	0				|	��������
	*	@note 
	*		ǰ��������InitComm/InitCommExt/ConnectIDRDev ���óɹ�
	*/
	ZKINTERFACE int ZKAPI Authenticate();


	/**
	*	@brief	��������,��Ϣ�ļ��洢��dll������
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	Active			|	int			|	[in]				|	���±�
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	-11				|	��Ч����
	*	0				|	��������
	*	@note 
	*		ǰ��������Authenticate ���óɹ�\n
	*	������ϸ˵������:
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	��������Ϣ���γ�������Ϣ�ļ�WZ.TXT����Ƭ�ļ�XP.WLT��ZP.BMP�������ָ����Ϣ�γ�ָ����Ϣ�ļ�FP.DAT
	*	2				|	ֻ��������Ϣ���γ�������Ϣ�ļ�WZ.TXT����Ƭ�ļ�XP.WLT
	*	3				|	������סַ��Ϣ���γ�����סַ�ļ�NEWADD.TXT
	*/
	ZKINTERFACE int ZKAPI Read_Content(int Active);



	/**
	*	@brief	��ȡSAMģ����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	SAMID			|	char*		|	[out]				|	SAMģ����
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*		ǰ��������InitComm/InitCommExt/ConnectIDRDev ���óɹ�
	*/
	ZKINTERFACE int ZKAPI GetSAMID(char *SAMID);

	/**
	*	@brief	��ȡSAMģ���ţ�10λ��ţ�
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	SAMID			|	char*		|	[out]				|	SAMģ����
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*		ǰ��������InitComm/InitCommExt/ConnectIDRDev ���óɹ�
	*/
	ZKINTERFACE int ZKAPI GetSAMIDEx(char *SAMID);



	/**
	*	@brief	�������֤��Ƭ
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	pszPath			|	char*		|	[in]				|	xp.wltͼƬ�ļ�ȫ·��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*		ǰ��������Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI GetBmpPhoto(const char* pszPath);

	/**
	*	@brief	�������֤��Ƭ
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*		ǰ��������Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI GetBmpPhotoExt();
	

	/**
	*	@brief	����Samģ��
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������InitComm/InitCommExt/ConnectIDRDev ���óɹ�
	*/
	ZKINTERFACE int ZKAPI Reset_SAM();

	/**
	*	@brief	��ȡSAMģ��״̬
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	״̬����
	*	0				|	״̬�쳣
	*	@note 
	*	ǰ��������InitComm/InitCommExt/ConnectIDRDev ���óɹ�
	*/
	ZKINTERFACE int ZKAPI GetSAMStatus();


	/**
	*	@brief	�������֤��Ϣ
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	index			|	int			|	[in]				|	����
	*	value			|	char*		|	[out]				|	����ֵ
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������Read_Content ���óɹ�\n
	*	��ϸ����˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	index(0)		|	��ȡ����
	*	index(1)		|	��ȡ�Ա�
	*	index(2)		|	��ȡ����
	*	index(3)		|	��ȡ��������(YYYYMMDD)
	*	index(4)		|	��ȡ��ַ
	*	index(5)		|	��ȡ���֤��
	*	index(6)		|	ǩ������
	*	index(7)		|	��Ч����ʼ����(YYYYMMDD)
	*	index(8)		|	��Ч�ڽ�ֹ����(YYYYMMDD)
	*/
	ZKINTERFACE int ZKAPI GetCardInfo(int index, char *value);

	
	/**
	*	@brief	�����������֤��������ͼƬ(���Ŀ¼��dll����Ŀ¼��cardv.jpg��SetCardJPGPathNameVָ��·��)
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������GetBmpPhoto/GetBmpPhotoExt ���óɹ�
	*/
	ZKINTERFACE int ZKAPI ExportCardImageV();


	
	/**
	*	@brief	���ɺ�����֤��������ͼƬ(���Ŀ¼��dll����Ŀ¼��cardh.jpg��SetCardJPGPathNameHָ��·��)
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������GetBmpPhoto/GetBmpPhotoExt ���óɹ�
	*/
	ZKINTERFACE int ZKAPI ExportCardImageH();

	/**
	*	@brief	�������֤����ͼƬ(���Ŀ¼��dll����Ŀ¼��cardf.jpgָ��·��)
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������GetBmpPhoto/GetBmpPhotoExt ���óɹ�
	*/
	ZKINTERFACE int ZKAPI ExportCardImageF();

	/**
	*	@brief	�������֤����ͼƬ(���Ŀ¼��dll����Ŀ¼��cardb.jpgָ��·��)
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	description of value
	*	----------------|-------------------------------
	*	1				|	�ɹ�
	*	0				|	ʧ��
	*	@note 
	*	ǰ��������GetBmpPhoto/GetBmpPhotoExt ���óɹ�
	*/
	ZKINTERFACE int ZKAPI ExportCardImageB();

	/*
	*	@brief	���������ļ���ʱĿ¼
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[in]				|	����ͼƬ��ʱĿ¼
	*	@return
	*		��
	*	@note 
	*		δ����Ĭ��Ϊ��dll����Ŀ¼
	*/
	ZKINTERFACE void ZKAPI SetTempDir(char *path);



	/**
	*	@brief	��ȡ�ļ�������ʱĿ¼
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ͼƬ��ʱĿ¼
	*	cbPath			|	int			|	[in]				|	���仺��������(����260Bytes)
	*	@return
	*		��
	*	@note 
	*		δ���÷��ص�ǰdll����Ŀ¼·��
	*/
	ZKINTERFACE void ZKAPI GetTempDir(char *path, int cbPath);


	/*
	*	@brief	����jpgͷ��ȫ·����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[in]				|	����jpgͼ���ļ�ȫ·����
	*	@return
	*		��
	*	@note 
	*		δ����Ĭ��Ϊ��dll����Ŀ¼��zp.jpg
	*/
	ZKINTERFACE void ZKAPI SetPhotoJPGPathName(char *path);



	/**
	*	@brief	��ȡjpgͷ��ȫ·����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ͼƬjpg�ļ�ȫ·��
	*	cbPath			|	int			|	[in]				|	���仺��������(����260Bytes)
	*	@return
	*		��
	*	@note 
	*		δ���÷��ر�dll����Ŀ¼��zp.jpg��ȫ·��
	*/
	ZKINTERFACE void ZKAPI GetPhotoJPGPathName(char *path, int cbPath);
	
	

	/*
	*	@brief	�����������֤��������ͼƬȫ·��
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[in]				|	����ͼƬjpg�ļ�ȫ·��
	*	@return
	*		��
	*	@note 
	*		δ����Ϊ��dll����Ŀ¼��cardv.jpg
	*/
	ZKINTERFACE void ZKAPI SetCardJPGPathNameV(char *path);

	/**
	*	@brief	��ȡ�������֤��������ͼƬȫ·��
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ͼƬjpg�ļ�ȫ·��
	*	cbPath			|	int			|	[in]				|	���仺��������(����260Bytes)
	*	@return
	*		��
	*	@note 
	*		δ���÷��ر�dll����Ŀ¼��cardv.jpg��ȫ·��
	*/
	ZKINTERFACE void ZKAPI GetCardJPGPathNameV(char *path, int cbpath);


	/*
	*	@brief	���ú�����֤��������ͼƬȫ·��
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[in]				|	����ͼƬjpg�ļ�ȫ·��
	*	@return
	*		��
	*	@note 
	*		δ����Ϊ��dll����Ŀ¼��cardh.jpg
	*/
	ZKINTERFACE void ZKAPI SetCardJPGPathNameH(char *path);

	/**
	*	@brief	��ȡ������֤��������ͼƬȫ·��
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ͼƬjpg�ļ�ȫ·��
	*	cbPath			|	int			|	[in]				|	���仺��������(����260Bytes)
	*	@return
	*		��
	*	@note 
	*		δ���÷��ر�dll����Ŀ¼��cardh.jpg��ȫ·��
	*/
	ZKINTERFACE void ZKAPI GetCardJPGPathNameH(char *path, int cbpath);


	//value

	/*
		���ƣ�getName
		��������ȡ����
		������
			data,����
			cbData,data��������С
		���أ�
			��
		ǰ�᣺Read_Content ���óɹ�
	*/

	/**
	*	@brief	��ȡ����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getName(char *data, int cbData);


	/**
	*	@brief	��ȡ�Ա�
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getSex(char *data, int cbData);

	/*
		���ƣ�getSexCode
		��������ȡ�Ա���
		������
			��
		���أ�
			�Ա���
		ǰ�᣺Read_Content ���óɹ�
	*/
	ZKINTERFACE int	 ZKAPI getSexCode();

	/**
	*	@brief	��ȡ����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void  ZKAPI getNation(char *data, int cbData);

	/*
		���ƣ�getNationCode
		��������ȡ������
		������
			��
		���أ�
			������
		ǰ�᣺Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI getNationCode();

	/**
	*	@brief	��ȡ����(YYYYMMDD)
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getBirthdate(char *data, int cbData);

	/*
		���ƣ�getBirthYear
		��������ȡ������
		������
			��
		���أ�
			������
		ǰ�᣺Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI getBirthYear();

	/*
		���ƣ�getBirthMon
		��������ȡ������
		������
			��
		���أ�
			������
		ǰ�᣺Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI getBirthMon();

	/*
		���ƣ�getBirthDay
		��������ȡ������
		������
			��
		���أ�
			������
		ǰ�᣺Read_Content ���óɹ�
	*/
	ZKINTERFACE int ZKAPI getBirthDay();

	/**
	*	@brief	��ȡ��ַ
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getAddress(char *data, int cbData);

	/**
	*	@brief	��ȡ���֤��
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getIDNum(char *data, int cbData);

	/**
	*	@brief	��ȡǩ������
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getIssue(char *data, int cbData);

	/**
	*	@brief	��ȡ��Ч����ʼ����(YYYYMMDD)
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getEffectedDate(char *data, int cbData);

	/**
	*	@brief	��ȡ��Ч�ڽ�ֹ����(YYYYMMDD)
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����64Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getExpiredDate(char *data, int cbData);

	/**
	*	@brief	��ȡBMPͷ��Base64����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺GetBmpPhoto/GetBmpPhotoExt ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getBMPPhotoBase64(char *data, int cbData);

	/**
	*	@brief	��ȡJPGͷ��Base64����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺GetBmpPhoto/GetBmpPhotoExt ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getJPGPhotoBase64(char *data, int cbData);

	/**
	*	@brief	��ȡ�������֤��������JPGͼ��base64�����ַ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺ExportCardImageV ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getJPGCardBase64V(char *data, int cbData);

	/**
	*	@brief	��ȡ������֤��������JPGͼ��base64�����ַ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺ExportCardImageH ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getJPGCardBase64H(char *data, int cbData);

	/**
	*	@brief	��ȡ���֤����JPGͼ��base64�����ַ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺ExportCardImageF ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getJPGCardBase64F(char *data, int cbData);

	/**
	*	@brief	��ȡ���֤����JPGͼ��base64�����ַ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺ExportCardImageB ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getJPGCardBase64B(char *data, int cbData);


	/**
	*	@brief	�������֤ͷ�񱳾�ɫ͸����ֵ
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	R				| unsigned char |	[in]				|	0~255,Ĭ��235
	*	G				| unsigned char |	[in]				|	0~255,Ĭ��235
	*	B				| unsigned char |	[in]				|	0~255,Ĭ��235
	*	@return
	*		��
	*	@note 
	*		RGB����ֵȫ���������ò��������Զ�����Ϊ͸��ɫ	
	*/
	ZKINTERFACE void ZKAPI SetTransparentThreshold(unsigned char R, unsigned char G, unsigned char B);

	/**
	*	@brief	��ȡָ������base64�����ַ���
	*	@param	:
	*	����˵�����±�
	*	name			|	type		|	param direction		|	description of param
	*	----------------|---------------|-----------------------|------------------------
	*	path			|	char*		|	[out]				|	����ֵ
	*	cbPath			|	int			|	[in]				|	���仺��������(����256*1024Bytes)
	*	@return
	*		��
	*	@note 
	*		ǰ�᣺Read_Content ���óɹ�	
	*/
	ZKINTERFACE void ZKAPI getFPDataBase64(char *data, int cbData);

#ifdef __cplusplus
}
#endif

#endif
#include"USART1.h"
extern Comm1 com;
extern BYTE Send_Buff1[12];
extern int len;
extern void ComInit(LPCTSTR portname, int rate_arg);

extern void open_MagneticNavigation();//�򿪴ŵ�����Դ
extern void close_MagneticNavigation();//�رմŵ�����Դ

extern void start_LinePatrol();//��ʼѲ��

extern void stop_LinePatrol();//����Ѳ�ߣ�ֹͣ�˶�  

extern void Correct_MagneticNavigation();//�ŵ������У��

extern void Set_Sensitivity();
extern void DipanSet(short m_RotationAngleSpeed);
extern void open_eyes();
extern void close_eyes();

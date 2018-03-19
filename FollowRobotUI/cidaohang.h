#include"USART1.h"
extern Comm1 com;
extern BYTE Send_Buff1[12];
extern int len;
extern void ComInit(LPCTSTR portname, int rate_arg);

extern void open_MagneticNavigation();//打开磁导航电源
extern void close_MagneticNavigation();//关闭磁导航电源

extern void start_LinePatrol();//开始巡线

extern void stop_LinePatrol();//结束巡线，停止运动  

extern void Correct_MagneticNavigation();//磁导航零点校正

extern void Set_Sensitivity();
extern void DipanSet(short m_RotationAngleSpeed);
extern void open_eyes();
extern void close_eyes();

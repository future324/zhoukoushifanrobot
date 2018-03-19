#pragma once
#pragma once
#include <conio.h>
#include "XAudio2.h"
#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include<iostream>
#pragma comment(lib,"xaudio2.lib")
void explain(int station);
int tts1(const char* src_text);
extern bool ttsValued1;
extern int stationindex;
extern HWND mydlg;


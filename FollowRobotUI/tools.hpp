#pragma once
#include <windows.h>
#include <stdio.h>
#include<iostream>
#include <locale.h>
#include "termb.h"
#pragma comment(lib, "termb.lib")
#include<stdlib.h>
bool decide_sex = false;
std::string people_name;
std::string people_address;
string people_birthday;
string people_time,people_num;
string ws2s(TCHAR  *STR)
{
int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
char* chRtn = new char[iLen * sizeof(char)];
WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
std::string str(chRtn);
return str;
}
void getNation(int nNation, char* nation)
{
	switch (nNation)
	{
	case 1:
	{
		strcpy_s(nation,6, "��");
		break;
	}
	case 2:
	{
		strcpy_s(nation, 6,"�ɹ�");
		break;
	}
	case 3:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 4:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 5:
	{
		strcpy_s(nation, 6,"ά���");
		break;
	}
	case 6:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 7:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 8:
	{
		strcpy_s(nation, 6,"׳");
		break;
	}
	case 9:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 10:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 11:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 12:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 13:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 14:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 15:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 16:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 17:
	{
		strcpy_s(nation, 6,"������");
		break;
	}
	case 18:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 19:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 20:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 21:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 22:
	{
		strcpy_s(nation, 6,"�");
		break;
	}
	case 23:
	{
		strcpy_s(nation, 6,"��ɽ");
		break;
	}
	case 24:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 25:
	{
		strcpy_s(nation, 6,"ˮ");
		break;
	}
	case 26:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 27:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 28:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 29:
	{
		strcpy_s(nation, 6,"�¶�����");
		break;
	}
	case 30:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 31:
	{
		strcpy_s(nation, 6,"���Ӷ�");
		break;
	}
	case 32:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 33:
	{
		strcpy_s(nation, 6,"Ǽ");
		break;
	}
	case 34:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 35:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 36:
	{
		strcpy_s(nation, 6,"ë��");
		break;
	}
	case 37:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 38:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 39:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 40:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 41:
	{
		strcpy_s(nation, 6,"������");
		break;
	}
	case 42:
	{
		strcpy_s(nation, 6,"ŭ");
		break;
	}
	case 43:
	{
		strcpy_s(nation, 6,"���α��");
		break;
	}
	case 44:
	{
		strcpy_s(nation, 6,"����˹");
		break;
	}
	case 45:
	{
		strcpy_s(nation, 6,"���¿�");
		break;
	}
	case 46:
	{
		strcpy_s(nation, 6,"�°�");
		break;
	}
	case 47:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 48:
	{
		strcpy_s(nation, 6,"ԣ��");
		break;
	}
	case 49:
	{
		strcpy_s(nation, 6,"��");
		break;
	}
	case 50:
	{
		strcpy_s(nation, 6,"������");
		break;
	}
	case 51:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 52:
	{
		strcpy_s(nation, 6,"���״�");
		break;
	}
	case 53:
	{
		strcpy_s(nation, 6,"����");
		break;
	}
	case 54:
	{
		strcpy_s(nation, 6,"�Ű�");
		break;
	}
	case 55:
	{
		strcpy_s(nation, 6,"���");
		break;
	}
	case 56:
	{
		strcpy_s(nation, 6,"��ŵ");
		break;
	}
	default:
	{
		strcpy_s(nation, 6,"δ֪");
	}
	break;
	}
}

void analyzeCardData(unsigned char* cardData)
{
	int nPos = 0;
	WCHAR szTemp[256] = { 0x0 };
	char szTempA[256] = { 0x0 };
	int nTemp1, nTemp2, nTemp3, nTemp4, nTemp5, nTemp6;
	memcpy(szTemp, cardData, 15 * sizeof(WCHAR));
	wprintf(L"������%ws\n", szTemp);
	people_name =ws2s(szTemp);
	people_name = people_name.erase(people_name.find_last_not_of(" ") + 1);

	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 15 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 1 * sizeof(WCHAR));
	if (wcscmp(szTemp, L"1") == 0)
	{
		wprintf(L"�Ա���\n");
		decide_sex = false;
	}
	else
	{
		wprintf(L"�Ա�Ů\n");
		decide_sex = true;
	}
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 1 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp1 = _wtoi(szTemp);
	getNation(nTemp1, szTempA);
	printf("����:%s\n", szTempA);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 4 * sizeof(WCHAR));
	nTemp1 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 4 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp2 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp3 = _wtoi(szTemp);
	printf("���գ�%d��%02d��%02d��\n", nTemp1, nTemp2, nTemp3);
	people_birthday = to_string(nTemp1) + "��" + to_string(nTemp2)+"��" + to_string(nTemp3)+"��";
	SYSTEMTIME systime = { 0 };
	GetLocalTime(&systime);
	people_time= to_string(systime.wYear) + "��" + to_string(systime.wMonth) + "��" + to_string(systime.wDay) + "��";
	string peoplemonth, peopleday = "";
	peoplemonth = to_string(systime.wMonth);
	peopleday = to_string(systime.wDay);
	if (systime.wMonth < 10)
	{
		peoplemonth = "0" + to_string(systime.wMonth);
	}
	if (systime.wDay<10)
	{
		peopleday = "0" + to_string(systime.wDay);
	}
	people_num = to_string(systime.wYear) + peoplemonth + peopleday;


	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 35 * sizeof(WCHAR));
	wprintf(L"��ַ��%ws\n", szTemp);
	wstring people_address_wide = szTemp;

	people_address=ws2s(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 35 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 18 * sizeof(WCHAR));
	wprintf(L"���֤�ţ�%ws\n", szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 18 * sizeof(WCHAR);

	memcpy(szTemp, cardData + nPos, 15 * sizeof(WCHAR));
	wprintf(L"ǩ��������%ws\n", szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 15 * sizeof(WCHAR);

	memcpy(szTemp, cardData + nPos, 4 * sizeof(WCHAR));
	nPos += 4 * sizeof(WCHAR);
	nTemp1 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp2 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp3 = _wtoi(szTemp);
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 4 * sizeof(WCHAR));
	nPos += 4 * sizeof(WCHAR);
	nTemp4 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp5 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 2 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp6 = _wtoi(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	printf("��Ч���ޣ�%d��%02d��%02d��-%d��%02d��%02d��\n", nTemp1, nTemp2, nTemp3, nTemp4, nTemp5, nTemp6);
}

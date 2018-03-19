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
		strcpy_s(nation,6, "汉");
		break;
	}
	case 2:
	{
		strcpy_s(nation, 6,"蒙古");
		break;
	}
	case 3:
	{
		strcpy_s(nation, 6,"回");
		break;
	}
	case 4:
	{
		strcpy_s(nation, 6,"藏");
		break;
	}
	case 5:
	{
		strcpy_s(nation, 6,"维吾尔");
		break;
	}
	case 6:
	{
		strcpy_s(nation, 6,"苗");
		break;
	}
	case 7:
	{
		strcpy_s(nation, 6,"彝");
		break;
	}
	case 8:
	{
		strcpy_s(nation, 6,"壮");
		break;
	}
	case 9:
	{
		strcpy_s(nation, 6,"布依");
		break;
	}
	case 10:
	{
		strcpy_s(nation, 6,"朝鲜");
		break;
	}
	case 11:
	{
		strcpy_s(nation, 6,"满");
		break;
	}
	case 12:
	{
		strcpy_s(nation, 6,"侗");
		break;
	}
	case 13:
	{
		strcpy_s(nation, 6,"瑶");
		break;
	}
	case 14:
	{
		strcpy_s(nation, 6,"白");
		break;
	}
	case 15:
	{
		strcpy_s(nation, 6,"土家");
		break;
	}
	case 16:
	{
		strcpy_s(nation, 6,"哈尼");
		break;
	}
	case 17:
	{
		strcpy_s(nation, 6,"哈萨克");
		break;
	}
	case 18:
	{
		strcpy_s(nation, 6,"傣");
		break;
	}
	case 19:
	{
		strcpy_s(nation, 6,"黎");
		break;
	}
	case 20:
	{
		strcpy_s(nation, 6,"傈僳");
		break;
	}
	case 21:
	{
		strcpy_s(nation, 6,"佤");
		break;
	}
	case 22:
	{
		strcpy_s(nation, 6,"畲");
		break;
	}
	case 23:
	{
		strcpy_s(nation, 6,"高山");
		break;
	}
	case 24:
	{
		strcpy_s(nation, 6,"拉祜");
		break;
	}
	case 25:
	{
		strcpy_s(nation, 6,"水");
		break;
	}
	case 26:
	{
		strcpy_s(nation, 6,"东乡");
		break;
	}
	case 27:
	{
		strcpy_s(nation, 6,"纳西");
		break;
	}
	case 28:
	{
		strcpy_s(nation, 6,"景颇");
		break;
	}
	case 29:
	{
		strcpy_s(nation, 6,"柯尔克孜");
		break;
	}
	case 30:
	{
		strcpy_s(nation, 6,"土");
		break;
	}
	case 31:
	{
		strcpy_s(nation, 6,"达斡尔");
		break;
	}
	case 32:
	{
		strcpy_s(nation, 6,"仫佬");
		break;
	}
	case 33:
	{
		strcpy_s(nation, 6,"羌");
		break;
	}
	case 34:
	{
		strcpy_s(nation, 6,"布朗");
		break;
	}
	case 35:
	{
		strcpy_s(nation, 6,"撒拉");
		break;
	}
	case 36:
	{
		strcpy_s(nation, 6,"毛南");
		break;
	}
	case 37:
	{
		strcpy_s(nation, 6,"仡佬");
		break;
	}
	case 38:
	{
		strcpy_s(nation, 6,"锡伯");
		break;
	}
	case 39:
	{
		strcpy_s(nation, 6,"阿昌");
		break;
	}
	case 40:
	{
		strcpy_s(nation, 6,"普米");
		break;
	}
	case 41:
	{
		strcpy_s(nation, 6,"塔吉克");
		break;
	}
	case 42:
	{
		strcpy_s(nation, 6,"怒");
		break;
	}
	case 43:
	{
		strcpy_s(nation, 6,"乌孜别克");
		break;
	}
	case 44:
	{
		strcpy_s(nation, 6,"俄罗斯");
		break;
	}
	case 45:
	{
		strcpy_s(nation, 6,"鄂温克");
		break;
	}
	case 46:
	{
		strcpy_s(nation, 6,"德昂");
		break;
	}
	case 47:
	{
		strcpy_s(nation, 6,"保安");
		break;
	}
	case 48:
	{
		strcpy_s(nation, 6,"裕固");
		break;
	}
	case 49:
	{
		strcpy_s(nation, 6,"京");
		break;
	}
	case 50:
	{
		strcpy_s(nation, 6,"塔塔尔");
		break;
	}
	case 51:
	{
		strcpy_s(nation, 6,"独龙");
		break;
	}
	case 52:
	{
		strcpy_s(nation, 6,"鄂伦春");
		break;
	}
	case 53:
	{
		strcpy_s(nation, 6,"赫哲");
		break;
	}
	case 54:
	{
		strcpy_s(nation, 6,"门巴");
		break;
	}
	case 55:
	{
		strcpy_s(nation, 6,"珞巴");
		break;
	}
	case 56:
	{
		strcpy_s(nation, 6,"基诺");
		break;
	}
	default:
	{
		strcpy_s(nation, 6,"未知");
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
	wprintf(L"姓名：%ws\n", szTemp);
	people_name =ws2s(szTemp);
	people_name = people_name.erase(people_name.find_last_not_of(" ") + 1);

	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 15 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 1 * sizeof(WCHAR));
	if (wcscmp(szTemp, L"1") == 0)
	{
		wprintf(L"性别：男\n");
		decide_sex = false;
	}
	else
	{
		wprintf(L"性别：女\n");
		decide_sex = true;
	}
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 1 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 2 * sizeof(WCHAR));
	nTemp1 = _wtoi(szTemp);
	getNation(nTemp1, szTempA);
	printf("民族:%s\n", szTempA);
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
	printf("生日：%d年%02d月%02d日\n", nTemp1, nTemp2, nTemp3);
	people_birthday = to_string(nTemp1) + "年" + to_string(nTemp2)+"月" + to_string(nTemp3)+"日";
	SYSTEMTIME systime = { 0 };
	GetLocalTime(&systime);
	people_time= to_string(systime.wYear) + "年" + to_string(systime.wMonth) + "月" + to_string(systime.wDay) + "日";
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
	wprintf(L"地址：%ws\n", szTemp);
	wstring people_address_wide = szTemp;

	people_address=ws2s(szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 35 * sizeof(WCHAR);
	memcpy(szTemp, cardData + nPos, 18 * sizeof(WCHAR));
	wprintf(L"身份证号：%ws\n", szTemp);
	memset(szTemp, 0x0, 256 * sizeof(WCHAR));
	nPos += 18 * sizeof(WCHAR);

	memcpy(szTemp, cardData + nPos, 15 * sizeof(WCHAR));
	wprintf(L"签发机构：%ws\n", szTemp);
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
	printf("有效期限：%d年%02d月%02d日-%d年%02d月%02d日\n", nTemp1, nTemp2, nTemp3, nTemp4, nTemp5, nTemp6);
}

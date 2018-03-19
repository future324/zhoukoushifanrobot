#include <string>

#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace  rename ("EOF", "adoEOF")  

class AdoAccess {
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
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=医疗问答0.accdb;Persist Security Info=False ";

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


bool decide_YN_and_one(std::string characteristic_words, std::string inputstr)//检测到所有的才终止
{
	int x = characteristic_words.find("&", 0);
	//cout << characteristic_words.length() << endl;
	int str_int = 0;
	int i = 0, j = 0;
	while (x != -1)
	{
		//cout << "x=" << x << endl;
		i++;
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("&", x + 1);
		//cout << str_temp << endl;
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			j++;//break;
		}
	}
	if (i == j)
	{
		return true;
	}
	return false;
}


bool decide_YN_or(std::string characteristic_words, std::string inputstr)
{
	int x = characteristic_words.find("|", 0);
	//cout << characteristic_words.length() << endl;
	int str_int = 0;
	while (x != -1)
	{
		//cout << "x=" << x << endl;
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("|", x + 1);
		//std::cout << str_temp << std::endl;
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			return true;
			//break;
		}
	}
	return false;
}

int all_count = 0;

int decide_YN_or_count(std::string characteristic_words, std::string inputstr)
{
	int x = characteristic_words.find("|", 0);
	int str_int = 0;
	while (x != -1)
	{
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("|", x + 1);
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			all_count++;
			//cout << "all_count:" << all_count << endl;
		}
	}
	return all_count;
}


bool decide_YN_and(std::string characteristic_words, std::string inputstr)//检测到所有的才终止
{
	int x = characteristic_words.find("|", 0);
	//cout << characteristic_words.length() << endl;
	int str_int = 0;
	int i=0,j=0;
	while (x != -1)
	{
		//cout << "x=" << x << endl;
		i++;
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("|", x + 1);
		//cout << str_temp << endl;
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			j++;//break;
		}
	}
	if (i==j)
	{
		return true;
	}
	return false;
}


std::string decide_YN_or_getstr(std::string characteristic_words, std::string inputstr)
{
	int x = characteristic_words.find("|", 0);
	//cout << characteristic_words.length() << endl;
	int str_int = 0;
	while (x != -1)
	{
		//cout << "x=" << x << endl;
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("|", x + 1);
		//cout << str_temp << endl;
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			return str_temp;
			//break;
		}
	}
	return NULL;
}


std::string decide_YN_and_getstr(std::string characteristic_words, std::string inputstr)//检测到所有的才终止
{
	int x = characteristic_words.find("|", 0);
	//cout << characteristic_words.length() << endl;
	int str_int = 0;
	int i = 0, j = 0;
	std::string str_temp_sum;
	while (x != -1)
	{
		//cout << "x=" << x << endl;
		i++;
		std::string  str_temp = characteristic_words.substr(str_int, x - str_int);
		str_int = x + 1;
		x = characteristic_words.find("|", x + 1);
		//cout << str_temp << endl;
		size_t fi = inputstr.find(str_temp, 0);
		if (fi != inputstr.npos)
		{
			str_temp_sum=inputstr.erase(fi, str_temp.length());
			//str_temp_sum += str_temp;
			j++;//break;
		}
	}
	if (i == j)
	{
		return str_temp_sum;
	}
	return NULL;
}



bool findstr_and(std::string str_org, std::initializer_list<string> lst)
{

	for (auto i = lst.begin(); i != lst.end(); i++)
	{
		if (str_org.find(*i) == str_org.npos)
		{
			return false;
		}
	}
	return true;
}


bool findstr_or(std::string str_org, std::initializer_list<string> lst)
{

	for (auto i = lst.begin(); i != lst.end(); i++)
	{
		if (str_org.find(*i) != str_org.npos)
		{
			return true;
		}
	}
	return false;
}
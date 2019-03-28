#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <vector>
using namespace std;

class strArr
{
public:
	char str[255];
	int count = 1;
};

bool find_str(const string&str, strArr* splited, int recent_size)
{
	for (int i = 0; i < recent_size; i++)
	{
		if (!strcmp(splited[i].str, str.c_str()))
		{
			splited[i].count++;
			return true;
		}
	}
	return false;
}
int Tokenize(const string& str, strArr* splited, const string& delimiters = " ")
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	//첫 문자가 구분자 인 경우 무시하고 가기
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	//구분자가 아닌 첫 문자를 찾는다 
	int i = 0;
	for (i = 0; string::npos != pos || string::npos != lastPos; i++)
	{	
		if (!find_str(str.substr(lastPos, pos - lastPos), splited, i))
			std::strcpy(splited[i].str, str.substr(lastPos, pos - lastPos).c_str());
		else { i--; }
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return i;
}


void shellSort(strArr* splited, const int n)
{
	int i, j, h; strArr v;
	h = 1;  do h = 3 * h + 1; while (h < n);
	do {
		h = h / 3;
		for (i = h; i < n; i++)
		{
			v = splited[i];	j = i;
			while (	j>0 && splited[j - 1].count < v.count||
				(splited[j - 1].count == v.count && strcmp(splited[j - 1].str, v.str)>0))
			{
				splited[j] = splited[j - h]; j -= h;
				if (j <= h - 1) break;
			}splited[j] = v;
		}
	} while (h > 1);
}

int main()
{
	int size = 0;
	strArr text[256];
	stringstream infstream;
	string inStr;
	infstream << ifstream("paragraph.txt").rdbuf();
	inStr = infstream.str();
	size = Tokenize(inStr, text, " .,\n/");
	shellSort(text, size);
	for (int j = 0; j < size; j++)
		cout << text[j].str << " : " << text[j].count << endl;
}
#include <iostream>
#include <string>


using namespace std;
//
//int bruteSearch(string str, string bomb)
//{
//	int i, j, m = str.size(), n = bomb.size();
//	for (i = 0; i < m - n; i++)
//	{
//		for (j = 0; j < n; j++)
//		{
//			if (str[i + j] != bomb[j])break;
//		}
//		return i;
//	}
//	return -1;
//}
//
//
//string chec(string str, string bomb)
//{
//	string rt_str = "";
//	int index = bruteSearch(str, bomb);
//	if (index != -1)
//		rt_str = str.substr(0, index) + str.substr(index + bomb.size());
//
//	return rt_str;
//	
//
//}

int main()
{

	string str;
	cout << "입력하세요:";

	getline(cin, str);

	cout << str << endl;

	string bomb;
	cout << "입력하세요:";


	cin >> bomb;
	cout << bomb << endl;



}
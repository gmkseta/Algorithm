//#include <iostream>
//#include <string>
//#include <cstring>
//
//using namespace std;
//
//class StringSearch
//{
//private:
//	const int q = 33554393;
//	const int d = 26;
//public:
//	int *SP;
//	char *p;
//	char *a;
//	int compare = 0;
//	StringSearch(char *Pattern, char *Text)
//	{
//		p = Pattern;
//		a = Text;
//	};
//
//	void brutesearch()
//	{  //p : Pattern String, a : Text String
//		int i, j, m = strlen(p), n = strlen(a);
//		for (i = 0; i <= n - m; i++) {
//			for (j = 0; j < m; j++) {
//				if (++compare && a[i + j] != p[j]) break;
//			}
//			if (j == m) {
//				cout << i << " , ";
//			}
//		}
//		cout << compare << endl;
//		compare = 0;
//	}
//
//	void initSP() {
//		int i, j, m = strlen(p);
//		SP = new int[strlen(p)];
//		SP[0] = -1;
//		for (i = 1, j = -1; i <= m - 1; i++) {
//			while ((j >= 0) && (p[j + 1] != p[i])) j = SP[j];
//			if (p[j + 1] == p[i]) j++;
//			SP[i] = j;
//		}
//	}
//
//	void kmpsearch() {
//		int i, j, m = strlen(p), n = strlen(a);
//		initSP();
//		for (i = 0, j = -1; i <= n - 1; i++) {
//			while ((j >= 0) && (p[j + 1] != a[i])) j = SP[j];
//			if (++compare && p[j + 1] == a[i]) j++;
//			if (j == m - 1) {
//				// 결과값 출력
//				cout << (i - m + 1) << " , ";
//				j = SP[j];
//			}
//		}
//		cout << compare << endl;
//		compare = 0;
//	}
//
//	void rksearch()
//	{
//		int i, j, s, dM = 1, h1 = 0, h2 = 0;
//		int m = strlen(p), n = strlen(a);
//		for (i = 0; i < m - 1; i++)
//			dM = (d*dM) % q;
//		for (i = 0; i < m; i++)
//		{
//			h1 = (h1*d + p[i]) % q;
//			h2 = (h2*d + a[i]) % q;
//		}
//		for (i = 0; i <= n - m; i++)
//		{
//			if (h1 == h2)
//			{
//				for (j = 0; j < m; j++)
//				{
//					if (++compare && a[i + j] != p[j])
//						break;
//				}
//				if (j == m)
//				{
//					cout << i << " , ";// 결과값 출력
//				}
//			}
//			if (++compare && i < n - m)
//			{
//				h2 = (d*(h2 - a[i] * dM) + a[i + m]) % q;
//				if (h2 < 0)
//					h2 = (h2 + q);
//			}
//		}
//		cout << compare << endl;
//		compare = 0;
//	}
//};
//
//int main()
//{
//	string Text_String;
//	string Pattern_String;
//
//	cout << "Text String >>";
//
//	getline(cin, Text_String);
//
//	cout << endl;
//
//	cout << "Pattern String >>";
//
//	getline(cin, Pattern_String);
//
//	cout << endl;
//
//	char* Text_S = new char[Text_String.size() + 1];
//	char* Pattern_S = new char[Pattern_String.size() + 1];
//
//	strcpy_s(Text_S, Text_String.size() + 1, Text_String.c_str());
//	strcpy_s(Pattern_S, Pattern_String.size() + 1, Pattern_String.c_str());
//
//	cout << Text_S << " //  " << Pattern_S << endl;
//
//	StringSearch Search(Pattern_S, Text_S);
//
//	Search.brutesearch();
//	Search.kmpsearch();
//	Search.rksearch();
//	system("pause");
//}
//
#include <iostream>
#include <cstdlib>
#include <string>

class StringSearch {
private :
	std::string p;
	std::string a;
	int *SP;  // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
	const int q = 33554393;
	const int d = 26;
public :
	StringSearch()
	{
		using namespace std;
		getline(cin, p);
		cout << "다" << endl;
		getline(cin, a);
	}


	void brutesearch(char *p, char *a) {  //p : Pattern String, a : Text String
		int i, j, m = strlen(p), n = strlen(a);
		for (i = 0; i <= n - m; i++) {
			for (j = 0; j<m; j++) {
				if (a[i + j] != p[j]) break;
			}
			if (j == m) {
				//결과값 출력 
			}
		}
	}
	void kmpsearch(char *p, char *a) {
		int i, j, m = strlen(p), n = strlen(a);
		//	initSP(p);
		for (i = 0, j = -1; i <= n - 1; i++) {
			while ((j >= 0) && (p[j + 1] != a[i])) j = SP[j];
			if (p[j + 1] == a[i]) j++;
			if (j == m - 1) {
				// 결과값 출력
				j = SP[j];
			}
		}
	}

	void initSP(char *p) {
		int i, j, m = strlen(p);
		SP[0] = -1;
		for (i = 1, j = -1; i <= m - 1; i++) {
			while ((j >= 0) && (p[j + 1] != p[i])) j = SP[j];
			if (p[j + 1] == p[i]) j++;
			SP[i] = j;
		}
	}



};

//
//void rksearch(char *p, char *a) {
//	int i, j, dM = 1, h1 = 0, h2 = 0, flag;
//	int m = strlen(p), n = strlen(a);
//	for (i = 1; i < m; i++) dM = (d*dM) % q;
//	for (i = 0; i < m; i++) {
//		h1 = (h1*d + index(p[i])) % q;
//		h2 = (h2*d + index(a[i])) % q;
//	}
//	for (i = 0; i< n - m + 1; i++) {
//		if (h1 == h2) {
//			flag = 1;
//			for (j = i; j<m; j++)  if (a[j] != p[j - i]) { flag = 0; break; }
//		}
//		if (flag) // 결과값 출력
//			if (s<n - m) {
//				h2 = (h2 - index(a[i])*dM) % q;
//				h2 = (h2*d + index(a[i + m])) % q;
//			}
//	}
//}



int main()
{
	StringSearch str;
}
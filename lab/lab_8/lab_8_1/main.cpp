#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>

class StringInfo {
private :
	char* p;
	char* a;
public :
	StringInfo()
	{
		using namespace std;
		string tmp;

		cout << "Text String 을 입력하세요 >>";
		getline(cin, tmp);
		a = new char[tmp.size() + 1];
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
		strcpy_s(a, tmp.size() + 1,tmp.c_str());

		cout << "Pattern String 을 입력하세요 >>";
		getline(cin, tmp);
		p = new char[tmp.size() + 1];
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
		strcpy_s(p, tmp.size() + 1, tmp.c_str());		
	}
	char* get_p() {return p;}
	char* get_a(){return a;}


};


class Search {
private:
	int *SP;  // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
	static const int q = 33554393;
	static const int d = 26;
public:
	static void brutesearch(char *p, char *a) {  //p : Pattern String, a : Text String
		int i, j, m = strlen(p), n = strlen(a);
		int cmp = 0;
		for (i = 0; i <= n - m; i++) {
			for (j = 0; j<m; j++) {
				if (++cmp&&a[i + j] != p[j]) break;
			}
			if (j == m) {
				std::cout << i << ",";//결과값 출력 
			}
		}
		std::cout << cmp << std::endl;
	}
	void kmpsearch(char *p, char *a) {
		int i, j, m = strlen(p), n = strlen(a);
		initSP(p);
		int cmp = 0;
		for (i = 0, j = -1; i <= n - 1; i++) {
			while ((j >= 0) && (p[j + 1] != a[i])) j = SP[j];
			if (++cmp&&p[j + 1] == a[i]) j++;
			if (j == m - 1) {
				std::cout << i-m+1 << ",";
				j = SP[j];
			}
		}
		std::cout << cmp << std::endl;
	}

	void initSP(char *p) {
		
		int i, j, m = strlen(p);
		SP = new int[m];
		SP[0] = -1;
		for (i = 1, j = -1; i <= m - 1; i++) {
			while ((j >= 0) && (p[j + 1] != p[i])) j = SP[j];
			if (p[j + 1] == p[i]) j++;
			SP[i] = j;
		}
	}
	
	static void rksearch(char *p, char *a) {
		int i, j, dM = 1, h1 = 0, h2 = 0, flag,cmp=0;
		int m = strlen(p), n = strlen(a);
		for (i = 0; i < m-1; i++) dM = (d*dM) % q;

		for (i = 0; i < m; i++) {
			h1 = (h1*d + p[i]-65) % q;
			h2 = (h2*d + a[i]-65) % q;
		}

		for (i = 0; i< n - m + 1; i++) {
			flag = 0;
			if (++cmp&&h1 == h2) {
				flag = 1;
				for (j = i; j<m+i; j++)  
					if (++cmp&&a[j] != p[j - i])
					{ flag = 0; break; }
			}
			if (flag) {std::cout<<i<<","; } // 결과값 출력
			if (i<n - m+1) {
					h2 = (h2 - (a[i]-65)*dM);
					h2 = (h2*d + a[i + m]-65) % q;
				}
		}
		std::cout << cmp << std::endl;
	}



};




int main()
{
	
	
	StringInfo str;
	Search::brutesearch(str.get_p(), str.get_a());
	Search srch;
	srch.kmpsearch(str.get_p(), str.get_a());
	Search::rksearch(str.get_p(), str.get_a());

}
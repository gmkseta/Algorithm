#include<iostream>
#include<string>
#include<algorithm>

class StringInfo {
private:
	char* p;
	char* a;
public:
	StringInfo()
	{
		using namespace std;
		string tmp;

		cout << "Text String 을 입력하세요 >>";
		getline(cin, tmp);
		a = new char[tmp.size() + 1];
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
		strcpy_s(a, tmp.size() + 1, tmp.c_str());

		cout << "Pattern String 을 입력하세요 >>";
		getline(cin, tmp);
		p = new char[tmp.size() + 1];
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
		strcpy_s(p, tmp.size() + 1, tmp.c_str());
	}
	char* get_p() { return p; }
	char* get_a() { return a; }
	~StringInfo() { delete a; delete p; }


};



class BruteSearch {
public:
	
	static void brutesearch(char *p, char *a) {  //p : Pattern String, a : Text String
		int cmp = 0;
		int i, j, m = strlen(p), n = strlen(a);
		for (i = 0; i <= n - m; i++) {
			for (j = 0; j<m; j++) {
				if (++cmp&&a[i + j] != p[j]) break;
			}
			if (j == m) {
				std::cout << i << " ,";//결과값 출력 
			}
		}
		std::cout << cmp << std::endl;
	}
};

class KMPSearch{
private:
	int *SP;  // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
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
public:
	void kmpsearch(char *p, char *a) {
		int i, j, m = strlen(p), n = strlen(a);
		int cmp = 0;
		initSP(p);
		for (i = 0, j = -1; i <= n - 1; i++) {
			while ((j >= 0) && (p[j + 1] != a[i])) j = SP[j];
			if (++cmp&&p[j + 1] == a[i]) j++;
			if (j == m - 1) {
				std::cout << i - m + 1 << ", ";// 결과값 출력
				j = SP[j];
			}
		}
		std::cout << cmp << std::endl;
	}
	~KMPSearch() { delete SP; }
};

class BoyerMoore{
private:
	int *skip;
	int *SP;
	const int alphabet_count = 26;
	int lp[26];
	int index[100];

	void initindex() {
		for (int i = 0; i < 100; i++) {
			index[i] = 0;
			if (i >= 65 && i <= 90)index[i] = i - 64;
		}
	}
	
	void initSP(char *p) {
		int i, j, m = strlen(p);
		SP = new int[m];
		skip = new int[m];
		SP[0] = -1;
		for (i = 1, j = -1; i <= m - 1; i++) {
			while ((j >= 0) && (p[j + 1] != p[i])) j = SP[j];
			if (p[j + 1] == p[i]) j++;
			SP[i] = j;
		}
	}

public:
	~BoyerMoore() {  }

	void boyerMoore(char *p, char *a) {
		int cmp = 0;
		int i, j, m = strlen(p), n = strlen(a);
		initindex();
		LastPos(p);
		GoodSuffix(p);
		j = 0;
		while (++cmp&&j <= n - m) {
			for (i = m - 1; i >= 0 && p[i] == a[j + i]; i--);
			if (i == -1) {//i가 -1 이면 다맞는거이므로 위치 출력
				printf("%d, ", j);
				j = j + skip[-1];
			}
			else { j = j + std::max(skip[i], i - lp[index[a[j + i]]]); }
		}
		std::cout << cmp << std::endl;
	}

	void LastPos(char *p) {//알파벳이 마지막으로 나타난 위치를  index를 넣어줌
		for (int i = 0; i < alphabet_count; i++) lp[i] = -1;
		for (unsigned int i = 0; i < strlen(p); i++) lp[index[p[i]]] = i;
	}
	
	void GoodSuffix(char *p) {
		int i, k, m = strlen(p);
		char *r_p = new char[m];
		for (i = 0; i<m; i++) {
			r_p[m - i - 1] = p[i];
		}
		initSP(r_p);
		for (i = -1; i <= m - 1; i++) skip[i] = m - 1 - SP[m - 1];
		for (k = 0; k <= m - 1; k++) {
			i = m - 1 - SP[k] - 1;
			if (skip[i]>k - SP[k]) skip[i] = k - SP[k];
		}

		delete r_p;
	}
	
};

int main() {
	using namespace std;

	StringInfo str;
	
	BruteSearch::brutesearch(str.get_p(), str.get_a());

	KMPSearch kmp;
	kmp.kmpsearch(str.get_p(), str.get_a());
	
	BoyerMoore boyer;
	boyer.boyerMoore(str.get_p(), str.get_a());
	
	return 0;
}

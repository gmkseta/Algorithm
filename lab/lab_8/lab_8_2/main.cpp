#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>

class StringInfo {
private:
	char** p;
	char** a;
public:
	StringInfo()
	{
		a = new char*[100];
		p = new char*[10];
		for (int i = 0; i < 100; i++)
		{
			a[i] = new char[100];
			for (int j = 0; j < 100; j++)
				a[i][j] = 'A';
		}
		for (int i = 0; i < 10; i++)
		{
			p[i] = new char[10];
			for (int j = 0; j < 10; j++)
				p[i][j] = 'A';
		}
		p[9][9] = 'B';
		
	}
	char* get_p(int i) { return p[i]; }
	char* get_a(int i) { return a[i]; }
	char** get_dp() { return p; }
	char** get_da() { return a; }


};


class Search {
private:
	int *SP;  // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
	static const int q = 33554393;
	static const int d = 26;

public:
	static int brutesearch(char *p, char *a) {  //p : Pattern String, a : Text String
		int i, j, m = 10, n = 100;
		int cmp = 0;
		for (i = 0; i <= n - m; i++) {
			for (j = 0; j<m; j++) {
 				if (++cmp&&a[i + j] != p[j]) 
					break;
			}
			if (j == m) {}//결과}
		}
			return cmp;
	}
	

	static int rksearch(char **p, char **a) {
		int i, j, x, y;
		int dM = 1, h1 = 0, h2 = 0, flag, cmp = 0;
		int m = 10, n = 100;


		for (i = 0; i < m - 1; i++)
			for (j = 0; j < m - 1; j++)
				dM = (d*dM) % q;

		for (i = 0; i < m; i++) {
			for (x = 0; x < m; x++) {
				h1 = (h1*d + p[i][x] - 65) % q;
				h2 = (h2*d + a[i][x] - 65) % q;
			}
		}


		

		for (i = 0; i < n - m + 1; i++) {
			for (j = 0; j < n - m + 1; j++) {
				flag = 0;
				if (++cmp&&h1 == h2) {
					flag = 1;
					for (x = i; x < m + i; x++)
						for(y=j;y<m+i;y++)
							if (++cmp&&a[i][j] != p[i][j - i])
							{	
							flag = 0; break;
							}
				}
				if (flag) {}//std::cout << i << ",";} // 결과값 출력
	
				if (j < n - m + 1) {
					for (x = 0; x < m; x++)
					{
							h2 = (h2 - (a[x+i][j] - 65)*dM);
							h2 = (h2*d + a[x+i][m+j] - 65) % q;
					
					}
				}
			}
		}
		return cmp;
	}
};
int main()
{


	StringInfo str;
	int sum = 0;
	for (int i = 0; i <= 90; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sum+=Search::brutesearch(str.get_p(j), str.get_a(j+i));
		}
	}
	std::cout << sum << std::endl;
	sum = 0;
	sum += Search::rksearch(str.get_dp(), str.get_da());
	
	std::cout << sum << std::endl;
}
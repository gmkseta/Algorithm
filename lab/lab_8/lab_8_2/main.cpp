#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Search
{
private:
	const int q = 33554393;
	const int d = 2;
public:
	char **p;
	char **a;
	int compare = 0;

	Search()
	{
		a = new char*[100];
		for (int i = 0; i < 100; i++)
		{
			a[i] = new char[100];
			for (int j = 0; j < 100; j++)
			{
				a[i][j] = 'A';
			}
		}

		p = new char*[10];
		for (int i = 0; i < 10; i++)
		{
			p[i] = new char[10];
			for (int j = 0; j < 10; j++)
			{
				p[i][j] = 'A';
			}
		}
		p[9][9] = 'B';
	}

	void brutesearch()
	{  //p : Pattern String, a : Text String
		int i, j, u, r;
		int m_x = 100;
		int m_y = 100;
		int n_x = 10;
		int n_y = 10;
		int flag = 0;
		int temp = 0;
		for (u = 0; u <= m_y - n_y; u++) // 큰 배열의 y 축
		{
			for (r = 0; r <= m_x - n_x; r++) // 큰 배열의 x 축
			{
				if (temp == n_x*n_y) // temp값이 배열의 x축 곱하기 y축 값과 일치한다면, 그 곳이 바로 일치하는 부분.
				{
					// cout << "시작점" << " : " << u << " , " << r - 1 << endl;
				}
				temp = 0;
				for (i = 0; i < n_y; i++) // 작은 배열의 y 축
				{
					for (j = 0; j < n_x; j++) // 작은 배열의 x 축
					{
						if (++compare && p[i][j] != a[i + u][j + r]) // 만약 같지 않다면 
						{
							flag = 1; // 해당 배열 x,y 에서 나가기 위한 flag 값 지정.
							break;
						}
						temp++; // 만약에 문자가 하나씩 일치하면, temp값 증가
					}

					if (flag == 1) // y축의 for문에서도 나가기 위함.
					{
						flag = 0;
						break;
					}
				}
			}
		}
		cout << compare << endl;
	}

	void rksearch()
	{
		int i, j, u, r;
		int dM = 1, h2 = 0, h1 = 0;
		int m_x = 100;
		int m_y = 100;
		int n_x = 10;
		int n_y = 10;
		int flag = 0;
		int temp = 0;
		int compare = 0;

		for (i = 0; i < n_x - 1; i++)
			dM = (d*dM) % q;

		for (i = 0; i < n_y; i++)
		{
			for (j = 0; j < n_x; j++)
			{
				h1 = (h1*d + p[i][j]) % q; // 패턴 스트링이 더 작으므로, h1이 패턴스트링의 값을 기준으로 해쉬가 정해짐.
				h2 = (h2*d + a[i][j]) % q;
			}
		}

		for (u = 0; u <= m_y - n_y; u++) // TEXT String의 y축
		{
			for (r = 0; r <= m_x - n_x; r++) // TEXT String의 x축
			{
				if (++compare && r < m_x - n_x) // 새로운 h2를 할당한다.
				{
					h2 = 0;
					for (i = 0; i < n_y; i++)
					{
						for (j = 0; j < n_x; j++)
						{
							h2 = (h2*d + a[i + u][j + r]) % q;
						}
					}
				}

				if (h1 == h2) // 만약 해시값이 같으면, 그때 brutesearch를 활용하여 찾는다.
				{
					for (i = 0; i < n_y; i++)
					{
						for (j = 0; j < n_x; j++)
						{
							if (++compare && p[i][j] != a[i + u][j + r])
							{
								flag = 1;
								break;
							}
							temp++;
						}
						if (flag == 1)
						{
							flag = 0;
							break;
						}
					}
					if (temp == n_x*n_y)
					{
						// cout << "시작점" << " : " << u << " , " << r - 1 << endl;
					}
					temp = 0;
				}
			}
		}
		cout << compare << endl;
	}
};


int main()
{
	Search search;
	search.brutesearch();
	search.rksearch();

	system("pause");
}
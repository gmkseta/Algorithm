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
		for (u = 0; u <= m_y - n_y; u++) // ū �迭�� y ��
		{
			for (r = 0; r <= m_x - n_x; r++) // ū �迭�� x ��
			{
				if (temp == n_x*n_y) // temp���� �迭�� x�� ���ϱ� y�� ���� ��ġ�Ѵٸ�, �� ���� �ٷ� ��ġ�ϴ� �κ�.
				{
					// cout << "������" << " : " << u << " , " << r - 1 << endl;
				}
				temp = 0;
				for (i = 0; i < n_y; i++) // ���� �迭�� y ��
				{
					for (j = 0; j < n_x; j++) // ���� �迭�� x ��
					{
						if (++compare && p[i][j] != a[i + u][j + r]) // ���� ���� �ʴٸ� 
						{
							flag = 1; // �ش� �迭 x,y ���� ������ ���� flag �� ����.
							break;
						}
						temp++; // ���࿡ ���ڰ� �ϳ��� ��ġ�ϸ�, temp�� ����
					}

					if (flag == 1) // y���� for�������� ������ ����.
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
				h1 = (h1*d + p[i][j]) % q; // ���� ��Ʈ���� �� �����Ƿ�, h1�� ���Ͻ�Ʈ���� ���� �������� �ؽ��� ������.
				h2 = (h2*d + a[i][j]) % q;
			}
		}

		for (u = 0; u <= m_y - n_y; u++) // TEXT String�� y��
		{
			for (r = 0; r <= m_x - n_x; r++) // TEXT String�� x��
			{
				if (++compare && r < m_x - n_x) // ���ο� h2�� �Ҵ��Ѵ�.
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

				if (h1 == h2) // ���� �ؽð��� ������, �׶� brutesearch�� Ȱ���Ͽ� ã�´�.
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
						// cout << "������" << " : " << u << " , " << r - 1 << endl;
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
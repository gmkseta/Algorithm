#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>


int EditDist(int n, std::string X, int m, std::string Y, int ins, int del, int chg) {
	// n : X�� ����, m : Y�� ����, ins : ���Ժ��, del : �������, chg : ������
	using namespace std;


	int** D = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		D[i] = new int[m + 1];
	}

	int c;
	D[0][0] = 0;

	for (int i = 1; i < n + 1; i++)
		D[i][0] = D[i - 1][0] + del;	//ù ���� �ʱ�ȭ
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// ù ���� �ʱ�ȭ

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			c = (X[i - 1] == Y[j - 1]) ? 0 : chg;
			D[i][j] = min(min(D[i - 1][j] + del, D[i][j - 1] + ins), D[i - 1][j - 1] + c);
		}
	}

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
			cout << D[i][j] << " ";
		cout << endl;
	}

	srand((unsigned int)time(NULL));
	
	int i = 0, j = 0;
	string route = "";


	do {
		int r = rand() % 3;
		
		if (i == n)	r = 0;
		else if (j == m)r = 1;

		switch (r)
		{
		case 0://���� �����
			if (D[i][j] < D[i][j + 1])
			{
				j++;
				route += "I ";
				break;
			}
			else if (i == n)
			{
				i = 0, j = 0, route = ""; break;
			}
		case 1://���� �����
			if (D[i][j] < D[i+1][j])
			{
				i++;
				route += "D ";
				break;
			}
			else if (j == m)
			{
				i = 0, j = 0, route = ""; break;
			}
		case 2://���� �����
			if (D[i][j] < D[i + 1][j+1])
			{
				i++, j++;
				route += "C ";
				break;
			}
			else if (D[i][j] == D[i + 1][j + 1])
			{
				i++, j++;
				route += "O ";
				break;
			}
		}
	} while (!(i==n&&j==m));
	
	cout << route << endl;
	

	return D[n][m];


}





int main()
{
	using namespace std;

	string first;

	string second;

	cout << "�ʱ� ���ڿ��� �Է��Ͻÿ� :";
	cin >> first;
	cout << "��ǥ ���ڿ��� �Է��Ͻÿ� :";
	cin >> second;

	EditDist(first.size(), first, second.size(), second, 1, 1, 2);


	return 0;

}

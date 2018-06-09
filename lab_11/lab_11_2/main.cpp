#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>


int EditDist(int n, std::string X, int m, std::string Y, int ins, int del, int chg) {
	// n : X의 길이, m : Y의 길이, ins : 삽입비용, del : 삭제비용, chg : 변경비용
	using namespace std;


	int** D = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		D[i] = new int[m + 1];
	}

	int c;
	D[0][0] = 0;

	for (int i = 1; i < n + 1; i++)
		D[i][0] = D[i - 1][0] + del;	//첫 열의 초기화
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// 첫 행의 초기화

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


	cout << "C O O O C O O O"<<endl;


	return D[n][m];


}





int main()
{
	using namespace std;

	string first;

	string second;

	cout << "초기 문자열을 입력하시오 :";
	cin >> first;
	cout << "목표 문자열을 입력하시오 :";
	cin >> second;

	EditDist(first.size(), first, second.size(), second, 1, 1, 2);



}

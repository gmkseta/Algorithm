#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <conio.h>



int main(void)
{
	using namespace std;
	ifstream inf("paragraph.txt");
	stringstream inStream;
	string inStr;
	inStream << inf.rdbuf();
	inStr = inStream.str();
	cout << inStr << endl;
	string typStr;
	//getline(cin, typStr);	
	//������ getline���� �ѹ��� �޾����� ����ǥ ����� �ϱ����� Ű�ϳ��� �޴°ŷ�


	char a;

	int restart = true;

	while (restart)
	{
		restart = false;
		auto begin = chrono::high_resolution_clock::now();

		int i = 0;
		while (i < inStr.size())
		{
			a = getch();
			if (a == inStr[i])
				cout << a;
			else if (a == 27)
			{
				restart = true;
				system("cls");

				cout << "restart" << endl;

				cout << inStr << endl;
				break;
			}
			else
				cout << "!";
			i++;

			typStr += a;



		}
		auto end = chrono::high_resolution_clock::now();
		if (restart == false)
		{
			cout << "\n typing time :" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0 << "s" << endl;
			if (!typStr.compare(inStr))
				cout << "Ok" << endl;
			else
				cout << "Not Ok" << endl;
		}
	}


	return 0;
}
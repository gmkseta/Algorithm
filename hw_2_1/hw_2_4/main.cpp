#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>
#define MAX_NUM 55


using namespace std;


ostream& operator<<(ostream& strm, vector<int> arr)
{
	//setw(4)�� �������� ��� �ϱ� ����. 
	for (auto itr : arr)strm <<setw(4)<< itr << " ";
	strm << endl;
	return strm;
}

//���Ⱑ ������ 
vector<int> operator-(vector<int> arr1, vector<int> arr2)
{
	vector<int> ret_arr;//����� �־��ֱ����� �迭
	vector<int>::iterator itr1, itr2;//����� ���� iterator
	itr1 = arr1.begin();itr2 = arr2.begin();//��ó���� �� �迭�� ù ��ҷ� ����
	while (true)
	{
		if (itr1 == arr1.end())break;//���� ���̶�� ����
		if (itr2 == arr2.end())break;
		if (*itr1 < *itr2)itr1++;//itr2�� �� ũ�ٸ� itr1�� arr1 �� ���� ��ҷ� �̵�
		else if (*itr1 > *itr2)itr2++;//itr1�� �� ũ�ٸ� itr2�� arr2�� ���� ��ҷ� �̵�
		else
		{//�� �� ���� ���� ��� �̹Ƿ� �������� �̶� ret_arr�� �־��ְ� ������ ���� ��ҷ� �̵�
			ret_arr.push_back(*(itr2++));
			itr1++;
		}
	}//��ȯ
	return ret_arr;
}

vector<int> operator+(vector<int> arr1, vector<int> arr2)
{
	vector<int> ret_arr;
	vector<int>::iterator itr1, itr2;
	itr1 = arr1.begin();
	itr2 = arr2.begin();
	while (true)//�����հ� �����
	{
		if (itr1 == arr1.end()){ret_arr.insert(ret_arr.end(),  itr2, arr2.end());break;}//itr1�� ������ ���Ҵٸ� itr2~arr2.end()���� �׳� �� �־����
		if (itr2 == arr2.end())	{ret_arr.insert(ret_arr.end(), itr1, arr1.end());break;}//���������� itr2�� ������ ���Ҵٸ� itr1~arr1.end()���� �׳� �� �־����
		if (*itr1 < *itr2)ret_arr.push_back(*(itr1++));//itr1�� �� �۴ٸ� itr1�� �ְ� ������ҷ��̵�
		else if (*itr1 > *itr2)ret_arr.push_back(*(itr2++));//itr2�� ���۴ٸ� itr2�� �ְ� ���� ��ҷ� �̵�
		else {ret_arr.push_back(*(itr2++));itr1++;}//���ٸ� �ְ� �Ѵ� ������ҷ� �̵�
	}
	return ret_arr;//��ȯ
}

class  InputNum
{
public:
	vector <int>  arr[2];

	InputNum()
	{
		cout << "Enter number ";
		cin >> _num1;
		cin >> _num2;
		AddRandomNum();
	}

	void AddRandomNum()
	{
		int num = rand() % MAX_NUM + 1;	
		for (int i = 0; i < _num1; i++)
		{
			num = rand() % MAX_NUM + 1;
			bool flag = true;
			for (auto itr: arr[0]){
				if (num == itr){flag = false;break;}
			}
			if (flag == true) arr[0].push_back(num);
			else i--;
		}
		for (int i = 0; i < _num2; i++)
		{
			num = rand() % MAX_NUM + 1;
			bool flag = true;
			for (auto itr : arr[1]) {
				if (num == itr) { flag = false; break; }
			}
			if (flag == true) arr[1].push_back(num);
			else i--;
		}
		std::sort(arr[0].begin(), arr[0].end());
		std::sort(arr[1].begin(), arr[1].end());
	}

	void printArr()
	{
		cout << "���� A - " << arr[0];
		cout << "���� B - " << arr[1];
		cout << "������ - " << arr[0] - arr[1];
		cout << "������ - " << arr[0] + arr[1];
		
	}


private:
	int _num1;
	int _num2;
};

int main()
{
	srand((unsigned int)time(NULL));
	InputNum d;
	d.printArr();
	return 0;

}
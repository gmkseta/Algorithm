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
	//setw(4)는 보기좋게 출력 하기 위함. 
	for (auto itr : arr)strm <<setw(4)<< itr << " ";
	strm << endl;
	return strm;
}

//여기가 교집합 
vector<int> operator-(vector<int> arr1, vector<int> arr2)
{
	vector<int> ret_arr;//결과값 넣어주기위한 배열
	vector<int>::iterator itr1, itr2;//계산을 위한 iterator
	itr1 = arr1.begin();itr2 = arr2.begin();//맨처음엔 두 배열의 첫 요소로 시작
	while (true)
	{
		if (itr1 == arr1.end())break;//만약 끝이라면 멈춤
		if (itr2 == arr2.end())break;
		if (*itr1 < *itr2)itr1++;//itr2가 더 크다면 itr1는 arr1 의 다음 요소로 이동
		else if (*itr1 > *itr2)itr2++;//itr1이 더 크다면 itr2는 arr2의 다음 요소로 이동
		else
		{//그 외 경우는 같을 경우 이므로 교집합임 이때 ret_arr에 넣어주고 각각을 다음 요소로 이동
			ret_arr.push_back(*(itr2++));
			itr1++;
		}
	}//반환
	return ret_arr;
}

vector<int> operator+(vector<int> arr1, vector<int> arr2)
{
	vector<int> ret_arr;
	vector<int>::iterator itr1, itr2;
	itr1 = arr1.begin();
	itr2 = arr2.begin();
	while (true)//교집합과 비슷함
	{
		if (itr1 == arr1.end()){ret_arr.insert(ret_arr.end(),  itr2, arr2.end());break;}//itr1이 끝까지 돌았다면 itr2~arr2.end()까지 그냥 다 넣어버림
		if (itr2 == arr2.end())	{ret_arr.insert(ret_arr.end(), itr1, arr1.end());break;}//마찬가지로 itr2이 끝까지 돌았다면 itr1~arr1.end()까지 그냥 다 넣어버림
		if (*itr1 < *itr2)ret_arr.push_back(*(itr1++));//itr1이 더 작다면 itr1을 넣고 다음요소로이동
		else if (*itr1 > *itr2)ret_arr.push_back(*(itr2++));//itr2가 더작다면 itr2를 넣고 다음 요소로 이동
		else {ret_arr.push_back(*(itr2++));itr1++;}//같다면 넣고 둘다 다음요소로 이동
	}
	return ret_arr;//반환
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
		cout << "집합 A - " << arr[0];
		cout << "집합 B - " << arr[1];
		cout << "교집합 - " << arr[0] - arr[1];
		cout << "합집합 - " << arr[0] + arr[1];
		
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
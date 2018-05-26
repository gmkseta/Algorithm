#include <iostream>
#include <string>


using namespace std;

string dec_to_bi(int num, int n)
{
	string result;
	int hi = 1;
	for (int i = 0; i < n; i++)
	{

		if (num % 8 > 0)
		{
			result.insert(0, std::to_string(num % 8));
		}
		else
		{
			result.insert(0, "0");
		}
		num = num / 8;

		hi *= 10;
	}
	return result;

}

int mul(string str)
{

	int i = str.size() - 1;
	int num1 = 0, num2 = 0;
	int n = 1;
	while (true)
	{
		if (str[i] == 'x')
		{
			i--;
			break;
		}
		else
			num1 += n*(str[i] - '0');
		i--;
		n *= 10;
	}
	n = 1;
	while (true)
	{
		if (i < 0)
			break;
		else
			num2 += n*(str[i] - '0');
		i--;
		n *= 10;
	}

	return num1*num2;
}

int main()
{
	string oper;
	cout << "nxm 형태로 입력" << endl;
	cin >> oper;
	cout << mul(oper) << endl;

}
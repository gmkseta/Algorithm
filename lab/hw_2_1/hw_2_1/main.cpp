#include <iostream>

using namespace std;
class  InputNum
{
public:
	InputNum()
	{
		cout << "Enter number ";
		cin >> _num;
	}

	int GetValue() const { return _num; }

	void AddInput()
	{
		InputNum aNum;  // get a number from user
		_num = _num + aNum.GetValue();
	}

private:
	int _num;
};
int main()
{
	InputNum num;
	cout << "The value is " << num.GetValue() << "\n";
	num.AddInput();
	cout << "Now the value is " << num.GetValue() << "\n";
}

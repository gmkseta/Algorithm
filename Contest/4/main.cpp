#include<iostream>



int primeMax(int a, int b)
{
	return b ? primeMax(b, a%b) : a;
}


int main()
{
	using namespace std;
	cout << primeMax(12, 18) << endl;
	return 0;
}
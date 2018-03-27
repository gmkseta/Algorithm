#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

typedef int itemType;

void shuffle(itemType* arr,int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 1; i <= n; i++)
	{
		int a = rand()%n+1;

		itemType tmp = arr[a];
		arr[a] = arr[i];
		arr[i] = tmp;
	}
}


std::string insertion(itemType a[], int n)
{
	int i, j; itemType v;
	int Compare_Cnt = 0, DataMove_Cnt = 0;
	for (i = 2; i <= n; i++)
	{
		v = a[i]; j = i;

		
		while (++Compare_Cnt&&a[j - 1] > v)
		{
			a[j] = a[j - 1];
			j--;
			a[j] = v;

			DataMove_Cnt++;

		}
	}

	std::string result = "Compare_Cnt : "+std::to_string(Compare_Cnt) + " DataMove_Cnt : " + std::to_string(DataMove_Cnt);
	return result;
	

	
}

int main()
{

	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n+1];
	itemType *rand_ord = new itemType[n+1];

	for (int i = 1; i <=n; i++)
	{
		des_ord[i] = n-i+1;
		rand_ord[i] = n-i+1;
	}
	des_ord[0] = INT_MIN;
	rand_ord[0] = INT_MIN;

	shuffle(rand_ord, n);


	cout << "Descending Order Array" << endl;
	for (int i = 1; i <=20; i++)
		cout << des_ord[i] << " ";
	
	cout <<endl<< insertion(des_ord, n) << endl;

	

	cout << "Random Order Array" << endl;
	for (int i = 1; i <=20; i++)
		cout << rand_ord[i] << " ";
	cout << endl << insertion(rand_ord, n) << endl;



}
#include <iostream>
#include <cstdlib>
#include <ctime>


typedef int itemType;

void shuffle(itemType* arr,int n)
{
	//srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		int a = rand()%n;

		itemType tmp = arr[a];
		arr[a] = arr[i];
		arr[i] = tmp;
	}
}



int insertion(itemType a[], int n)
{
	int i, j; itemType v;
	int count = 0;
	for (i = 1; i < n; i++)
	{
		v = a[i]; j = i;
		while (++count&&a[j - 1] > v)
		{
			a[j] = a[j - 1];
			j--;
			a[j] = v;

		}
	}
	return count;
}

int main()
{

	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n];
	itemType *rand_ord = new itemType[n];

	for (int i = n; i > 0; i--)
	{
		des_ord[n - i] = i;
		rand_ord[n - i] = i;
	}
	shuffle(rand_ord, n);
	cout << insertion(des_ord, n) << endl;
	//for(int i = 0 ; i <n ; i ++)
	//	cout << des_ord[i] << endl;
	

}
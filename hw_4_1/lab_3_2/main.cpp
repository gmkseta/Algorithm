#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

typedef int itemType;

void shuffle(itemType* arr, int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		int a = rand() % n ;

		itemType tmp = arr[a];
		arr[a] = arr[i];
		arr[i] = tmp;
	}
}


void insertSort(itemType a[], int n)
{
	int i, j; itemType v;
	
	for (i = 2; i <= n; i++)
	{
		v = a[i]; j = i;


		while (a[j - 1] > v)
		{
			a[j] = a[j - 1];
			j--;
		}
			a[j] = v;
		
	}
}

std::string shellSort(itemType a[],int n)
{

	int i, j, h; itemType v;
	int Compare_Cnt = 0, DataMove_Cnt = 0;

	h = 1;  do h = 3 * h + 1; while (h < n);
	do {
		h = h / 3;
		for (i = h; i < n; i++)
		{
			v = a[i]; 
			++DataMove_Cnt;
			j = i;

			while (++Compare_Cnt&& a[j - h] > v)
			{
				a[j] = a[j - h]; j -= h; 
				++DataMove_Cnt;
				if (j < h - 1) break;
			}
			a[j] = v;
			++DataMove_Cnt;
		}
	} while (h > 1);


	std::string result = "\nCompare_Cnt : " + std::to_string(Compare_Cnt) + " DataMove_Cnt : " + std::to_string(DataMove_Cnt)+"\n";
	return result;

}


int main()
{

	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n];
	itemType *rand_ord = new itemType[n];

	for (int i = 0; i <n ; i++)
	{
		des_ord[i] = n - i ;
		rand_ord[i] = n - i;
	}
	
	shuffle(rand_ord, n);
	cout << endl << "━━━━━━━━━━━━━━━Shell Sort━━━━━━━━━━━━━━━" << endl;
	cout << "Descending Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";

	cout << endl << shellSort(des_ord, n) << endl<<endl;



	cout << "Random Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";
	cout << endl <<  shellSort(rand_ord, n) << endl;



}
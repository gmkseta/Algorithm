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



int Compare_Cnt = 0;
int DataMove_Cnt = 0;

int Bubble(int sorted, itemType *a, int n)
{
	int temp;
	if (++Compare_Cnt&&*(a - 1) > *a) {
		temp = *(a - 1);
		*(a - 1) = *a;
		*a = temp;
		DataMove_Cnt++;
		sorted = false;
	}
	return sorted;
}

std::string bubbleSort(itemType a[], int n)
{
	Compare_Cnt = 0;
	DataMove_Cnt = 0;
	int i, Sorted;
	//int j = 0;
	Sorted = false;
	while (!Sorted) {
		Sorted = true;
		//여기서 버블정렬 이런 코드면 대각선 상관없이 쭉 돌리는거아닌가;
		for (i = 1; i < n; i++)
		{
			Sorted = Bubble(Sorted, &a[i], n);
		}
		n--;
	}

	std::string result = "Compare_Cnt : " + std::to_string(Compare_Cnt) + " DataMove_Cnt : " + std::to_string(DataMove_Cnt);
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

	for (int i = 0; i <n; i++)
	{
		des_ord[i] = n - i;
		rand_ord[i] = n - i;
	}

	shuffle(rand_ord, n);

	cout << endl << "━━━━━━━━━━━━━━━Bubble Sort━━━━━━━━━━━━━━━" << endl;
	cout << "Descending Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";

	cout << endl << bubbleSort(des_ord, n) << endl<<endl;

	cout << "Random Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";
	cout << endl <<bubbleSort(rand_ord, n) << endl;



}
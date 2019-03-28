#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

typedef int itemType;

int compare = 0;
int data = 0;

inline void swap(itemType a[], int i, int j)
{
	itemType  t = a[i]; a[i] = a[j]; a[j] = t;
}

int partition(itemType a[], int l, int r) {
	int i, j; itemType v;
	if (r > l) {
		v = a[l]; i = l; j = r + 1;
		for (;;) {
			while (a[++i] < v)compare++;//컴페어
			while (a[--j] > v)compare++;//컴페어
			if (i >= j) break;
			swap(a, i, j); data++;//데이터
		}
		swap(a, j, l); data++;//데이터
	}
	return j;
}

void quicksort(itemType a[], int l, int r) {
	int  j;
	if (r > l) {
		j = partition(a, l, r);
		quicksort(a, l, j - 1);
		quicksort(a, j + 1, r);
	}
}


void shuffle(itemType* arr, int n)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		int a = rand() % n;
		itemType tmp = arr[a];
		arr[a] = arr[i];
		arr[i] = tmp;
	}
}




int main()
{
	extern int data;
	extern int compare;
	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n+1];
	itemType *rand_ord = new itemType[n+1];

	for (int i = 0; i < n; i++)
	{
		des_ord[i] = n - i;
		rand_ord[i] = n - i;
	}

	des_ord[n] = INT_MAX;
	rand_ord[n] = INT_MAX;

	shuffle(rand_ord, n);

	cout << endl << "━━━━━━━━━━━━━━━   Quick Sort   ━━━━━━━━━━━━━━━" << endl;
	cout << "Descending Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";


//	cout << endl << insertion(des_ord, n) << endl << endl;
	
	quicksort(des_ord, 0, n);

	cout << endl<< endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";

	cout << endl;


	cout << "datamove_cnt : " << data << "  compare_cnt : " << compare << endl;

	data = 0;
	compare = 0;

	cout <<endl<< "Random Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";
	
	cout << endl<<endl;

	quicksort(rand_ord, 0, n);

	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";


	cout<<endl << "datamove_cnt : " << data << "  compare_cnt : " << compare << endl;


}
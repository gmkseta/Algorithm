#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

typedef int itemType;

#define N 10000
itemType* sorted = new itemType[N];

int compare = 0;
int data = 0;

void merge(itemType a[], int l, int mid, int r) {
	int i, j, k, n;
	
	

	i = l; j = mid + 1; k = l;
	n = j - i;
	
	while (i <= mid && j <= r) {
		if (++compare&&a[i] <= a[j]) {//컴페어
			
			sorted[k++] = a[i++];
			//데이터
			data++;
		}
		else {
			sorted[k++] = a[j++];
			//데이터
			data++;
		}
	}
	if (i > mid)
		for (n = j; n <= r; n++) { sorted[k++] = a[n];	data++; }
	else
		for (n = i; n <= mid; n++) { sorted[k++] = a[n];	data++; }
	for (n = l; n <= r; n++) a[n] = sorted[n];

	//delete sorted 
}
void mergesort(itemType a[], int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		mergesort(a, l, mid);
		mergesort(a, mid + 1, r);
		merge(a, l, mid, r);
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
	extern int compare;
	extern int data;
	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n];
	itemType *rand_ord = new itemType[n];

	for (int i = 0; i < n; i++)
	{
		des_ord[i] = n - i;
		rand_ord[i] = n - i;
	}

	shuffle(rand_ord, n);

	cout << endl << "━━━━━━━━━━━━━━━Merge Sort━━━━━━━━━━━━━━━" << endl;
	cout << "Descending Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";


	//	cout << endl << insertion(des_ord, n) << endl << endl;

	mergesort(des_ord, 0, n-1);

	cout << endl << endl;
	for (int i = 0; i < 20; i++)
		cout << des_ord[i] << " ";

	cout << endl;

	cout << "datamove_cnt : " << data << "  compare_cnt : " << compare << endl;

	data = 0;
	compare = 0;



	cout << "Random Order Array" << endl;
	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";

	cout << endl << endl;

	mergesort(rand_ord, 0, n-1);

	for (int i = 0; i < 20; i++)
		cout << rand_ord[i] << " ";


	cout <<endl <<"datamove_cnt : " << data << "  compare_cnt : " << compare << endl;

	data = 0;
	compare = 0;



}
#include <iostream>

#include <string>

typedef int itemType;

int Ins_w = 0;
int Bub_w = 0;
int She_w = 0;

void insertSort(itemType a[], int n)
{
	int i, j; itemType v;

	for (i = 2; i <= n; i++)
	{
		v = a[i]; j = i;
		Ins_w += v;

		while (a[j - 1] > v)
		{

			a[j] = a[j - 1];
			Ins_w += a[j - 1];
			j--;

			
		}
			a[j] = v;

			Ins_w += v;


		
	} 
}

void shellSort(itemType a[], int n)
{

	int i, j, h; itemType v;


	h = 1;  do h = 3 * h + 1; while (h < n);
	do {
		h = h / 3;
		for (i = h+1; i <= n; i++)
		{
			v = a[i]; j = i;
			if(a[i-h]>v)She_w += v;

			while (a[j - h] > v)
			{
				a[j] = a[j - h]; j -= h;
				She_w += a[j];

				if (j - h <= 0 || a[j - h] <= v)She_w += v;
				if (j <= h - 1) break;
			}
			a[j] = v;
		//	She_w += v;

		}
	} while (h > 1);



}




int Bubble(int sorted, itemType *a, int n)
{
	int temp;
	if (*(a - 1) > *a) {
		if (*(a - 1) < *a) {
			
			temp = *(a - 1);
			Bub_w += temp;
			*(a - 1) = *a;
			Bub_w += *(a - 1);

			*a = temp;
			Bub_w += temp;
		}
		else  {
			temp = *a;
			Bub_w += temp;
			*a= *(a - 1);
			Bub_w += *a;

			*(a - 1) = temp;
			Bub_w += temp;
		}
		
		sorted = false;
	}
	return sorted;
}

void bubbleSort(itemType a[], int n)
{

	int i, Sorted;
	int j = 0;
	Sorted = false;
	while (!Sorted) {
		Sorted = true;
		//여기서 버블정렬 이런 코드면 대각선 상관없이 쭉 돌리는거아닌가;
		for (i = 2; i <= n - j; i++)
		{
			Sorted = Bubble(Sorted, &a[i], n);
		}
		j++;
	}

}



int main()
{

	using namespace std;
	int n;

	cout << "배열의 크기를 입력하세요 (500이상) >>";
	cin >> n;

	itemType *des_ord = new itemType[n + 1];
	itemType *des_ord1 = new itemType[n + 1];
	itemType *des_ord2 = new itemType[n + 1];

	for (int i = 1; i <=n; i++)
	{
		des_ord[i] = n - i + 1;
		des_ord1[i] = n - i + 1;
		des_ord2[i] = n - i + 1;
	}
	des_ord[0] = INT_MIN;
	des_ord1[0] = INT_MIN;
	des_ord2[0] = INT_MIN;



	//cout << "Descending Order Array" << endl;
	//for (int i = 1; i <= 20; i++)
	//	cout << des_ord[i] << " ";
	cout << endl;
	insertSort(des_ord1, n);
	shellSort(des_ord2, n);
	bubbleSort(des_ord, n);


	cout << "Insertion Sort : " << Ins_w << endl;

	cout << "Bubble Sort : " << Bub_w << endl;


	cout << "Shell Sort : " << She_w << endl;



}
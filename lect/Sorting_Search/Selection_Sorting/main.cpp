#include "makeArr.h"
#include <iostream>


class SORT
{	
private:
	int com_cnt, datamove_cnt;

public:
	SORT() :com_cnt(0), datamove_cnt(0) {};
	void SelectionSort(itemType a[], int n)
	{
		int i, j;
		itemType v;
		for (i = 2; i <= n; i++)
		{
			v = a[i];
			datamove_cnt++;
			j = i;

			while (++com_cnt&&a[j - 1] > v)
			{
				a[j] = a[j - 1];
				datamove_cnt++;
				j--;
			}
			a[j] = v;
			datamove_cnt++;
		}
		
	}

};




int main()
{
	using namespace std;
	cout << "배열 크기 입력 >>";
	int n;
	cin >> n;

	makeArr arr(n,true);
	SORT cnt;



	arr.make_des_arr();
	arr.print_arr();
	cnt.SelectionSort(arr.arr, n);
	arr.print_arr();



	arr.make_rand_arr();

	arr.print_arr();

	cnt.SelectionSort(arr.arr, n);










}
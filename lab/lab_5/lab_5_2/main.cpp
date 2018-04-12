#include <iostream>
#include <ctime>
#include <cstdlib>


typedef int itemType;

int compare = 0, datamove = 0;
class MAKE_ARR {
private:
	itemType *a, *b, *N;
	int size;
public:
	MAKE_ARR(int max) { 
		a = new itemType[max+1]; 
		b = new itemType[max+1]; 
		N = new itemType[max+1]; 
		size = max;
	}
	~MAKE_ARR() { delete a; delete b; delete N; }

	void CountSort( int n, int k) {
		int i, j;
		compare = 0; datamove = 0;
		for (i = 1; i <= k; i++) N[i] = 0;

		for (i = 1; i <= n; i++) N[a[i]] = N[a[i]] + 1; 

		for (i = 2; i <= k; i++) N[i] = N[i] + N[i - 1];

		for (j = n; j >= 1; j--) {
			datamove++;
			b[N[a[j]]] = a[j];
			N[a[j]] = N[a[j]] - 1;
		}
	}


	void make_rand_arr()
	{
		make_des_arr();
		for (int i = 1; i <= size; i++)
		{
			int c = rand() % size+1;
			itemType tmp = a[c];
			a[c] = a[i];
			a[i] = tmp;
		}
	}

	void make_des_arr()
	{
		for (int i = 1; i <= size; i++)
			a[i] = size - i+1;
	}

	void make_overlap_arr()
	{
		for (int i = 1; i <=size; i++)
		{
			a[i] = rand() % size + 1;
		}
	}

	void print_a_arr()
	{
		for (int i = 1; i <= 20; i++)
			std::cout << a[i] << " ";
		std::cout << std::endl << std::endl;
	}
	void print_b_arr()
	{
		for (int i = 1; i <= 20; i++)
			std::cout << b[i] << " ";
		std::cout << std::endl << std::endl;
	}
};


int main() {
	using namespace std;
	srand((unsigned int)time(NULL));
	int n;
	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	MAKE_ARR hello(n);

	

	cout << endl << "━━━━━━━━━━━━━━━━━━ Count Sort ━━━━━━━━━━━━━━━━━━━" << endl;
	cout << endl << "━━━━━━━━━━━━ Descending Order Array ━━━━━━━━━━━━" << endl;

	hello.make_des_arr();
	hello.print_a_arr();
	hello.CountSort(n,n);
	hello.print_b_arr();
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;

	cout << endl << "━━━━━━━━━━━━━━ Random Order Array ━━━━━━━━━━━━━" << endl;

	hello.make_rand_arr();
	hello.print_a_arr();
	hello.CountSort(n, n);
	hello.print_b_arr();
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;

	cout << endl << "━━━━━━━━━━━━ (Overlap) Random Order Array ━━━━━━━━━━━━" << endl;

	hello.make_overlap_arr();
	hello.print_a_arr();
	hello.CountSort(n, n);
	hello.print_b_arr();
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;



}
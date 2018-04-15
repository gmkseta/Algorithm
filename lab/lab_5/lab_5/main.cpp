#include <iostream>
#include <ctime>
#include <cstdlib>


typedef int itemType;

int compare = 0, datamove = 0;
class MAKE_HEAP {
private:
	itemType *a;
	int N;
public:
	MAKE_HEAP(int max) { a = new itemType[max]; N = max; }
	~MAKE_HEAP() { delete a; }
	void swap(itemType a[], int i, int j) {
		int temp;
		temp = a[j]; a[j] = a[i]; a[i] = temp;
		datamove++;
	}

	void MakeHeap(itemType a[], int Root, int LastNode) {
		int Parent, LeftSon, RightSon, Son; itemType RootValue;
		Parent = Root;
		RootValue = a[Root];
		LeftSon = 2 * Parent + 1;
		RightSon = LeftSon + 1;
		while (++compare&&LeftSon <= LastNode){
			if (++compare&&RightSon <= LastNode && a[LeftSon] < a[RightSon]) {
				Son = RightSon;
			}
			else Son = LeftSon;
			datamove++;
			if (++compare&&RootValue < a[Son]) {
				datamove++;
				a[Parent] = a[Son];
				Parent = Son;
				LeftSon = Parent * 2 + 1;
				RightSon = LeftSon + 1;
				
			}
			else break;
		}
		a[Parent] = RootValue;
		datamove++;
	}
	void heapsort() {
		int i;
		compare = 0; datamove = 0;
		
		for (i = N / 2; i >= 1; i--)  MakeHeap(a, i - 1, N - 1);
		for (i = N - 1; i >= 1; i--) { swap(a, 0, i); MakeHeap(a, 0, i - 1); }
	}

	void make_rand_arr() 
	{
		make_des_arr();
		for (int i = 0; i < N; i++)
		{
			int c = rand() % N ;
			itemType tmp = a[c];
			a[c] = a[i];
			a[i] = tmp;
		}
	}
	void make_des_arr()
	{
		for (int i = 0; i < N; i++)
			a[i] = N - i;
	}

	void make_overlap_arr()
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = rand() % N+1;
		}
	}

	void print_arr()
	{
		for (int i = 0; i < 20; i++)
			std::cout << a[i] << " ";
		std::cout << std::endl << std::endl;
	}

};


int main() {
	using namespace std;
	srand((unsigned int)time(NULL));
	int n;
	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	MAKE_HEAP hello(n);


	cout << endl << "━━━━━━━━━━━━━━━━━━ Heap Sort ━━━━━━━━━━━━━━━━━━━" << endl;
	cout << endl << "━━━━━━━━━━━━ Descending Order Array ━━━━━━━━━━━━" << endl;
	
	hello.make_des_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();

	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;
	cout << endl << "━━━━━━━━━━━━━━ Random Order Array ━━━━━━━━━━━━━" << endl;
	
	hello.make_rand_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();

	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;
	cout << endl << "━━━━━━━━━━━━ (Overlap) Random Order Array ━━━━━━━━━━━━" << endl;
	
	hello.make_overlap_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;



}
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
		LeftSon = 2 * Parent + 1;//이런방식으로 하면 root가 0이여도 자식 잘 갈수있
		RightSon = LeftSon + 1;//원래는 2*Parent 가 Left , Right 2*Parent+1 자나
		while (LeftSon <= LastNode){
			//반목문이 LastNode 와 LeftSon을 비교하면서 돈다.
			//LeftSon이 더 커지는순간 나와짐. 즉 다돌면..
			if (++compare&&RightSon <= LastNode && a[LeftSon] < a[RightSon]) {
				Son = RightSon;//Right 가 더크면 Right 넣고
			}
			else Son = LeftSon;//left가 더 크면 left 를 넣음 즉 더 큰것을 넣음
			if (++compare&&RootValue < a[Son]) {//Root가 더 작으면? (바꿔줘야지!)
				datamove++;
				a[Parent] = a[Son];//Root에 넣어주고 더 큰 값인 Son을 넣어주고
				Parent = Son;//Parent index를 Son으로 바꾸고
				LeftSon = Parent * 2 + 1;//그녀석의 왼쪽자식
				RightSon = LeftSon + 1;	//오른쪽 자식하고 비교
			}//DownHeap 삭제 연산을 하는과정임.
			else break;
		}//이거로 힙을 다 바꾸고 . 
		a[Parent] = RootValue; //루트벨류의 최종위치에 넣어줌.
		datamove++;
	}
	void heapsort() {
		int i;
		compare = 0; datamove = 0;
		for (i = N / 2; i >= 1; i--) 
			MakeHeap(a, i - 1, N - 1);
		for (i = N - 1; i >= 1; i--) 
		{ 
			swap(a, 0, i); 
			MakeHeap(a, 0, i - 1); 
		}
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
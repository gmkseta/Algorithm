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
		LeftSon = 2 * Parent + 1;//�̷�������� �ϸ� root�� 0�̿��� �ڽ� �� ������
		RightSon = LeftSon + 1;//������ 2*Parent �� Left , Right 2*Parent+1 �ڳ�
		while (LeftSon <= LastNode){
			//�ݸ��� LastNode �� LeftSon�� ���ϸ鼭 ����.
			//LeftSon�� �� Ŀ���¼��� ������. �� �ٵ���..
			if (++compare&&RightSon <= LastNode && a[LeftSon] < a[RightSon]) {
				Son = RightSon;//Right �� ��ũ�� Right �ְ�
			}
			else Son = LeftSon;//left�� �� ũ�� left �� ���� �� �� ū���� ����
			if (++compare&&RootValue < a[Son]) {//Root�� �� ������? (�ٲ������!)
				datamove++;
				a[Parent] = a[Son];//Root�� �־��ְ� �� ū ���� Son�� �־��ְ�
				Parent = Son;//Parent index�� Son���� �ٲٰ�
				LeftSon = Parent * 2 + 1;//�׳༮�� �����ڽ�
				RightSon = LeftSon + 1;	//������ �ڽ��ϰ� ��
			}//DownHeap ���� ������ �ϴ°�����.
			else break;
		}//�̰ŷ� ���� �� �ٲٰ� . 
		a[Parent] = RootValue; //��Ʈ������ ������ġ�� �־���.
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
	cout << "�迭�� ũ�⸦ �Է��ϼ��� (10000�̻�) >>";
	cin >> n;

	MAKE_HEAP hello(n);


	cout << endl << "������������������������������������ Heap Sort ��������������������������������������" << endl;
	cout << endl << "������������������������ Descending Order Array ������������������������" << endl;
	
	hello.make_des_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();

	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;
	cout << endl << "���������������������������� Random Order Array ��������������������������" << endl;
	
	hello.make_rand_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();

	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;
	cout << endl << "������������������������ (Overlap) Random Order Array ������������������������" << endl;
	
	hello.make_overlap_arr();
	hello.print_arr();
	hello.heapsort();
	hello.print_arr();
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;



}
#include <iostream>
#include <ctime>
#include <cstdlib>


typedef int itemType;
int compare = 0, datamove = 0;
typedef struct node *node_pointer;
typedef struct node {
	itemType value;
	node_pointer next;
};

node_pointer TABLE[10], x, z, temp;


void make_des_arr(int *a, int size)
{
	for (int i = 0; i < size; i++)
		a[i] = size - i;
}

void make_rand_arr(int *a ,int size)
{
	make_des_arr(a,size);
	for (int i = 0; i < size; i++)
	{
		int c = rand() % size + 1;
		itemType tmp = a[c];
		a[c] = a[i];
		a[i] = tmp;
	}
}

void make_overlap_arr(int *a , int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % size + 1;
	}
}

void print_arr(int *a)
{
	for (int i = 0; i < 20; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl << std::endl;
}

void radixSort(itemType *a, int n) {
	int i, j, cnt, radix, radix_mod = 10, cipher = 0;
	i = n;
	compare = 0; datamove = 0;
	while (i>0) { i = i / 10; cipher++; } // cipher : 입력 데이터의 자리수 (ex. 450 -> 3)
	for (i = 0; i<cipher; i++) {
		for (j = 0; j<n; j++) {
			cnt = 0; radix = (a[j] % radix_mod) / (radix_mod / 10);
			/* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
			radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
			temp = new node; temp->value = a[j]; temp->next = z;
			if (TABLE[radix] == z) {
				// z는 list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
				TABLE[radix] = temp; datamove++;
			}
			else {
				x = TABLE[radix];
				while (x->next != z) {
					x = x->next;
				}
				datamove++;
				x->next = temp;
			}
		}

		for (j = 0; j<10; j++) {
			if (TABLE[j] != z) {
				x = TABLE[j];
				while (x != z) {
					datamove++;
					a[cnt++] = x->value;
					temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
					x = x->next;
					delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
				}
			}
			TABLE[j] = z;
		}
		radix_mod *= 10;
	}
}


int main() {
	using namespace std;
	srand((unsigned int)time(NULL));
	int n;
	cout << "배열의 크기를 입력하세요 (10000이상) >>";
	cin >> n;

	int* a = new int[n];

	



	cout << endl << "━━━━━━━━━━━━━━━━━━ Radix Sort ━━━━━━━━━━━━━━━━━━━" << endl;
	cout << endl << "━━━━━━━━━━━━ Descending Order Array ━━━━━━━━━━━━" << endl;
	make_des_arr(a, n);
	print_arr(a);
	radixSort(a, n);
	print_arr(a);
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;
	
	cout << endl << "━━━━━━━━━━━━━━ Random Order Array ━━━━━━━━━━━━━" << endl;

	make_rand_arr(a, n);
	print_arr(a);
	radixSort(a, n);
	print_arr(a);
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;

	cout << endl << "━━━━━━━━━━━━ (Overlap) Random Order Array ━━━━━━━━━━━━" << endl;

	make_overlap_arr(a, n);
	print_arr(a);
	radixSort(a, n);
	print_arr(a);
	cout << "DataMove:" << datamove << "  Compare : " << compare << endl;


}
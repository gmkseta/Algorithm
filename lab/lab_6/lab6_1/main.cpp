#include <iostream>
#include <ctime>

#define infoNIL 0
#define itemMIN -1
typedef int itemType;
typedef double infoType;
int compare;

class BST {
private:
	struct node {
		itemType key; infoType info;
		struct node *l, *r;
		node(itemType k, infoType i, struct node *ll, struct node *rr)  // node 생성시 초기값 부여 가능 
		{
			key = k; info = i; l = ll; r = rr;
		};
	};
	struct node *head, *z; // z : List의 끝을 대표하는 node pointer – NULL에 해당
public:
	BST(int max) {
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST(){};

	infoType BSTsearch(itemType v) {
		struct node *x = head->r;
		z->key = v;  // 아래 반복문을 간결히 만들기 위함
		while (v != x->key)
		{
			x = (++compare&&v < x->key) ? x->l : x->r;
		}
		return x->info;
	}
	void BSTinsert(itemType v, infoType info) {
		struct node *p=head, *x = head->r;
		while (x != z) 
		{
			p = x; x = (v < x->key) ? x->l : x->r;
		}
		x = new node(v, info, z, z);
		if (v < p->key) p->l = x; else p->r = x;
	}
};


class makeArr
{
private:
	itemType* arr;
	int N;
public : 
	
	makeArr(int n)
	{
		N = n;
		arr = new itemType[n];
	}

	void make_des_arr(){for (int i = 0; i < N; i++) arr[i] = N - i;}
	void make_rand_arr() 
	{
		srand((unsigned int)time(NULL));
		make_des_arr(); 
		for (int i = 0; i < N; i++)
		{
			int c = rand() % N;
			itemType tmp = arr[c];
			arr[c] = arr[i]; arr[i] = tmp;
		}
	}
	itemType get(int n) { return arr[n]; }
};

int main()
{
	using namespace std;
	extern int compare;
	compare = 0;
	int n;
	cout << "배열의 크기를 입력하세요 (10000>= n >=100)" << endl;
	cin >> n;

	makeArr arr(n);
	BST tree(n);

	arr.make_rand_arr();

	for (int i = 0; i < n; i++)
		tree.BSTinsert(arr.get(i), infoNIL);

	for (int i = 0; i < n; i++)
		tree.BSTsearch(i);

	cout << ((double)compare/n) << endl;

	
	return 0;
}


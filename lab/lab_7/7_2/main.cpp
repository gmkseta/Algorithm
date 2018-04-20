#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

#include <iostream>
#include <ctime>
typedef int itemType;
typedef double infoType;

using namespace std;

class RandomArray {
public:
	itemType *a;
	int size, n;

	RandomArray(int max)
	{
		a = new itemType[max]; size = max;
	}
	~RandomArray() { delete[] a; }
	void sort(itemType **a, int n)
	{
		int i, j; itemType v, v2;
		for (i = 1; i < n; i++)
		{
			v = a[i][0]; j = i;
			v2 = a[i][1];
			while (a[j - 1][0] > v) { a[j][0] = a[j - 1][0]; a[j][1] = a[j - 1][1]; j--; }
			a[j][0] = v;
			a[j][1] = v2;
		}
	}
	void create_arr()
	{
		itemType **temp = new itemType *[size + 1];
		temp[0] = new itemType[2];
		temp[0][0] = INT_MIN;
		temp[0][1] = INT_MIN;
		srand((unsigned)time(NULL));         // ����ð��� �̿��� �����߻��� rand()�� �ʱⰪ�� �缳��
		for (int i = 1; i <= size; i++) {
			temp[i] = new itemType[2];
			temp[i][0] = (1 + rand() % size);            // 1~n ������ ���� n���� �����ϰ� ����
			temp[i][1] = i;
		} // ������ ������� ������ 1�� �������Ѱ��� �� ������ ���� �ε����� ����
		sort(temp, size);            // ���� a[i][0]���� ������ �� �� ������� �ε��� a[i][1]���� ������Ű�� B�� ����

		for (int i = 1; i <= size; i++)
		{
			a[i - 1] = temp[i][1];
		}
		for (int i = 0; i < size + 1; i++) { delete[] temp[i]; }
		delete[] temp;
	}
};
class RBtree {
private:
	struct node {
		itemType key, tag;
		infoType Info;
		struct node *l, *r;
		node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
			key = k; Info = i; tag = t; l = ll; r = rr;
		}
	};
	struct node *head, *tail, *x, *p, *g, *gg, *z;
public:
	double compare_cnt1;
	double compare_cnt2;
	RBtree(int max) {
		z = new node(0, infoNIL, black, 0, 0);
		z->l = z; z->r = z;
		head = new node(itemMIN, infoNIL, black, z, z);
		compare_cnt1 = 0;
		compare_cnt2 = 0;
	}
	~RBtree() {}
	void insert(itemType k, infoType info);
	struct node *rotate(itemType k, struct node *y);
	void split(itemType k);
	infoType search(itemType k);
};
void RBtree::insert(itemType k, infoType info)
{
	x = head; p = head; g = head;
	while (x != z) {
		gg = g; g = p; p = x; //gg:�θ��� �θ��� �θ�, g:�θ��� �θ�, p : �θ�
		x = (k < x->key) ? x->l : x->r;
		if (x->l->tag && x->r->tag)split(k); //�� �ڽ��� ��� ��������� �� ����
		compare_cnt1++;
	}
	x = new node(k, info, red, z, z);
	if (k < p->key)p->l = x; else p->r = x;
	split(k); head->r->tag = black;
}
struct RBtree::node  *RBtree::rotate(itemType k, struct RBtree::node *y)
{
	struct RBtree::node *high, *low;
	high = (k < y->key) ? y->l : y->r;
	//right ȸ��
	if (k < high->key) { low = high->l; high->l = low->r; low->r = high; }
	//left ȸ��
	else { low = high->r; high->r = low->l; low->l = high; }
	if (k < y->key) y->l = low; else y->r = low;
	return low;
}
void RBtree::split(itemType k)
{
	x->tag = red; x->l->tag = black; x->r->tag = black;
	if (p->tag) {
		g->tag = red;
		if (k < g->key != k < p->key)p = rotate(k, g);
		x = rotate(k, gg);
		x->tag = black;
	}
}

infoType RBtree::search(itemType k)
{
	struct RBtree::node *x = head->r;
	z->key = k;  // �Ʒ� �ݺ����� ������ ����� ����
	while (k != x->key) { x = (k < x->key) ? x = x->l : x = x->r; compare_cnt2++; }
	return x->Info;
}

class HashTable {
private:
	struct Node
	{
		itemType id;
		infoType info;
		Node* hashNext;
		Node(itemType key, infoType inf) { id = key; info = inf; hashNext = NULL; }
	};
	Node** hashTable;
	int size;
public:
	double compare_cnt1, compare_cnt2;
	HashTable(int max) {
		hashTable = new Node*[max];   size = max;
		compare_cnt1 = 0; compare_cnt2 = 0;
	}
	void insert(itemType key, infoType info)
	{
		Node *node = new Node(key, info);
		int hash_key = key % size;
		if (hashTable[hash_key] == NULL) { hashTable[hash_key] = node; compare_cnt1++; }
		else {
			node->hashNext = hashTable[hash_key];
			hashTable[hash_key] = node;
			compare_cnt1++;
		}
	}
	infoType search(itemType key)
	{
		int hash_key = key%size;
		if (hashTable[hash_key] == NULL) {
			compare_cnt2++; return NULL;
		}
		if (hashTable[hash_key]->id == key) {
			compare_cnt2++; return hashTable[hash_key]->info;
		}
		else {
			Node* temp = hashTable[hash_key];
			while (temp) {
				if (++compare_cnt2&& temp->id == key) return temp->info;
				temp = temp->hashNext;
			}
		}
		return NULL;
	}

};

int main()
{
	int size;
	cin >> size;
	RandomArray arr(size);
	arr.create_arr();
	RBtree T3(size);
	HashTable h1(11), h2(101), h3(1009);

	for (int i = 0; i < size; i++)
	{
		T3.insert(arr.a[i], i);
		h1.insert(arr.a[i], i);
		h2.insert(arr.a[i], i);
		h3.insert(arr.a[i], i);
	}
	for (int i = 1; i <= size; i++)
	{
		T3.search(i);
		h1.search(i); h2.search(i); h3.search(i);
	}
	cout << T3.compare_cnt1 / size << "(T3�� ���� �� ��� �� ȸ��)" << endl;
	cout << h1.compare_cnt1 / size << "(h1�� ���� �� ��� �� ȸ��)" << endl;
	cout << h2.compare_cnt1 / size << "(h2�� ���� �� ��� �� ȸ��)" << endl;
	cout << h3.compare_cnt1 / size << "(h3�� ���� �� ��� �� ȸ��)" << endl << endl;
	cout << T3.compare_cnt2 / size << "(T3�� ��� �� ȸ��)" << endl;
	cout << h1.compare_cnt2 / size << "(h1�� ��� �� ȸ��)" << endl;
	cout << h2.compare_cnt2 / size << "(h2�� ��� �� ȸ��)" << endl;
	cout << h3.compare_cnt2 / size << "(h3�� ��� �� ȸ��)" << endl;
}
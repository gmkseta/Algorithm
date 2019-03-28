#include<iostream>
#include<ctime>
#include<cstdlib>
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

typedef int itemType;
typedef int infoType;

class makeArr
{
private:
	itemType* arr;int N;
public:
	makeArr(int n) :N(n) { arr = new itemType[n]; }
	void make_des_arr() { for (int i = 0; i < N; i++) arr[i] = N - i; }
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
	void print_arr()
	{
		for (int i = 0; i < 20; i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
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
	double comp_cnt, srch_cnt;
	RBtree(int max):comp_cnt(0.0), srch_cnt(0.0){
		z = new node(0, infoNIL, black, 0, 0);
		z->l = z; z->r = z;
		head = new node(itemMIN, infoNIL, black, z, z);
	}

	void insert(itemType k, infoType info) {
		x = head; p = head; g = head;
		while (++comp_cnt&&x != z) {
			gg = g; g = p; p = x;
			
			x = (k < x->key) ? x->l : x->r;
			if (x->l->tag && x->r->tag) split(k);
		}
		x = new node(k, info, red, z, z);
		if (k < p->key) p->l = x; else p->r = x;
		split(k); head->r->tag = black;
	}

	struct node *rotate(itemType k, struct node *y) {
		struct node *high, *low;
		high = (k < y->key) ? y->l : y->r;
		if (k < high->key) { low = high->l; high->l = low->r; low->r = high; }
		else { low = high->r; high->r = low->l; low->l = high; }
		if (k < y->key) y->l = low; else y->r = low;
		return low;
	}
	void split(itemType k) {
		x->tag = red; x->l->tag = black; x->r->tag = black;
		if (p->tag) {
			g->tag = red;
			if (k < g->key != k < p->key) p = rotate(k, g);
			x = rotate(k, gg);
			x->tag = black;
		}
	}
	infoType search(itemType k) {
		struct node *x = head->r;
		z->key = k;
		while (++srch_cnt&&k != x->key)x = (k < x->key) ? x->l : x->r;
		return x->key;
	}

	void RBtraversal(node* t)
	{
		if (t != z) {
			RBtraversal(t->l);
			std::cout << t->key << " ";
			RBtraversal(t->r);
		}
	}
	node* getHead()
	{
		return head;
	}
};

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
	double comp_cnt, srch_cnt;
	BST(int max):comp_cnt(0.0), srch_cnt(0.0){
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST() {};

	infoType BSTsearch(itemType v) {
		struct node *x = head->r;
		z->key = v;  // 아래 반복문을 간결히 만들기 위함
		while (++srch_cnt&&v != x->key)  x = (v < x->key) ? x->l : x->r;
		return x->info;
	}

	void BSTinsert(itemType v, infoType info) {
		struct node *p, *x;
		p = head; x = head->r;
		
		while (++comp_cnt&&x != z) {
			p = x; 
			x = (v < x->key) ? x->l : x->r; }
		x = new node(v, info, z, z);
		if (v < p->key) p->l = x; else p->r = x;
		
	}

	void BSTdelete(itemType v) {
		struct node *x = head->r, *p, *t, *c;
		p = head;
		while (x->key != v && x != z) {
			p = x;
			x = (v < x->key) ? x->l : x->r;
		}
		if (x == z) return;
		else t = x;
		if (t->r == z) x = t->l;
		else if (t->r->l == z) {
			x = t->r; x->l = t->l;
		}
		else {
			c = x->r; while (c->l->l != z) c = c->l;
			x = c->l; c->l = x->r;
			x->l = t->l; x->r = t->r;
		}
		free(t);
		if (v<p->key) p->l = x; else p->r = x;
	}

	void BSTtraversal(node* t, BST* bst)
	{
		if (t != z) {
			BSTtraversal(t->l, bst);
			bst->BSTinsert(t->key, t->info);
			BSTtraversal(t->r, bst);
		}
	}
	void RBtraversal(node* t, RBtree* rbt)
	{
		if (t != z) {
			RBtraversal(t->l, rbt);
			rbt->insert(t->key, t->info);
			RBtraversal(t->r, rbt);
		}
	}
	node* getHead()
	{
		return head;
	}
	void trb(node* t)
	{
		if (t != z) {
			trb(t->l);
			std::cout << t->key << " ";
			trb(t->r);
		}
	}

};


int main()
{
	using namespace std;
	
	int n;
	cout << "배열의 크기를 입력하세요 (20000>= n >=100)" << endl;
	cin >> n;
	srand((unsigned int)time(NULL));
	makeArr arr(n);
	BST T1(n);
	BST T2(n);
	RBtree T3(n);
	
	arr.make_rand_arr();
	
	for (int i = 0; i < n; i++)
		T1.BSTinsert(arr.get(i), infoNIL);
	T1.BSTtraversal(T1.getHead(), &T2);
	T1.RBtraversal(T1.getHead(), &T3);
	
	
	
	for (int i = 0; i < n; i++)
	{
		T1.BSTsearch(i);
		T2.BSTsearch(i);
		T3.search(i);
	}

	cout << "T1의 구축 시 평균 비교 횟수:" << (T1.comp_cnt / n) << endl;
	cout << "T2의 구축 시 평균 비교 횟수:" << (T2.comp_cnt / n) << endl;
	cout << "T3의 구축 시 평균 비교 횟수:" << (T3.comp_cnt / n) << endl;



	cout << "T1의 평균 탐색 비교 횟수:" << (T1.srch_cnt / n) << endl;
	cout << "T2의 평균 탐색 비교 횟수:" << (T2.srch_cnt / n) << endl;
	cout << "T3의 평균 탐색 비교 횟수:" << (T3.srch_cnt / n) << endl;




	return 0;
}
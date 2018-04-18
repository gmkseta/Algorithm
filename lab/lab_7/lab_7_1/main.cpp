#include<iostream>
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

typedef int itemType;
typedef int infoType;

struct node {
	itemType key, tag;
	infoType Info;
	struct node *l, *r;
	node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
		key = k; Info = i; tag = t; l = ll; r = rr;
	}
};
struct node *head, *tail, *x, *p, *g, *gg, *z;
void RBtree(int max) {
	z = new node(0, infoNIL, black, 0, 0);
	z->l = z; z->r = z;
	head = new node(itemMIN, infoNIL, black, z, z);
}
void insert(itemType k, infoType info) {
	x = head; p = head; g = head;
	while (x != z) {
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
	high = (k< y->key) ? y->l : y->r;
	if (k < high->key) { low = high->l; high->l = low->r; low->r = high; }
	else { low = high->r; high->r = low->l; low->l = high; }
	if (k < y->key) y->l = low; else y->r = low;
	return low;
}
void split(itemType k) {
	x->tag = red; x->l->tag = black; x->r->tag = black;
	if (p->tag) {
		g->tag = red;
		if (k<g->key != k<p->key) p = rotate(k, g);
		x = rotate(k, gg);
		x->tag = black;
	}
}
infoType search(itemType k) {
	// Red-Black Tree의 값을 탐색 기능 구현
}

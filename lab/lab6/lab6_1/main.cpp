#define infoNIL 0
#define itemMIN -1
typedef int itemType;
typedef double infoType;

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
	~BST();
	infoType  BSTsearch(itemType v);
	void BSTinsert(itemType v, infoType info);
};
infoType BST::BSTsearch(itemType v) {
	struct node *x = head->r;
	z->key = v;  // 아래 반복문을 간결히 만들기 위함
	while (v != x->key)  x = (v < x->key) ? x->l : x->r;
	return x->info;
}
void BST::BSTinsert(itemType v, infoType info) {
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) { p = x; x = (v < x->key) ? x->l : x->r; }
	x = new node(v, info, z, z);
	if (v < p->key) p->l = x; else p->r = x;
}

int main()
{
	return 0;
}
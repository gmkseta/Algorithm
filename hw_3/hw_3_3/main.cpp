#include <iostream>

struct treeNode { char info; struct treeNode *l, *r; int level=1; };

struct treeNode *x, *z;
//struct node *x, *z;

typedef treeNode *itemType;




class Stack
{
public:
	Stack(int max = 100) { stack = new itemType[max]; p = 0; };
	~Stack() {
		delete stack;
	};
	inline void push(itemType v) {
		stack[p++] = v;
	};
	inline itemType pop() {
		return stack[--p];
	};
	inline int empty() { return  !p; };
private:
	itemType *stack;
	int p;
};

class Queue
{
public:
	Queue(int max = 100) { queue = new itemType[max]; tail = 0; size = max; head = 0; };
	~Queue() {
		delete queue;
	};

	void put(itemType v)
	{
		queue[tail++] = v;
		if (tail > size) tail = 0;
	}
	itemType get()
	{
		itemType t = queue[head++];
		if (head > size) head = 0;
		return t;
	}
	int empty() { return head == tail; }

private:
	itemType *queue;
	int tail;
	int head;
	int size;
};
void visit(struct treeNode *t);
void traverse(struct treeNode *t);




Queue queue;
void visit(struct treeNode *t )
{
	//std::cout << t->info  << " ";
	std::cout << t->level << std::endl;
}
int traverse(struct treeNode *t ,char c)
{
	
	queue.put(t);
	while (!queue.empty())
	{
		t = queue.get();// visit(t);

		if (t->info == c)
		{
			visit(t);
			return 1;
		}


		if (t->l != z)
		{
			queue.put(t->l);
			t->l->level = t->level + 1;
		}
		if (t->r != z)
		{
			queue.put(t->r);
			t->r->level = t->level + 1;
		}
	}
	std::cout << "Not Found" << std::endl;
	return 0;
}




int main()
{

	char c; Stack stack(50);
	z = new treeNode; z->l = z; z->r = z;
	while ((c = std::cin.get()) != '\n')
	{
		while (c == ' ') std::cin.get(c);
		x = new treeNode;
		x->info = c; x->l = z; x->r = z;
		if (c == '+' || c == '*' || c == '-') { x->r = stack.pop(); x->l = stack.pop(); }		stack.push(x);
	}
	std::cout << " " << std::endl;

	c = std::cin.get();
	

	traverse(stack.pop(),c);

	std::cout << std::endl;
	return 0;
}
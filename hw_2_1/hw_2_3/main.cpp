#include <iostream>


typedef float itemType;


class Stack2
{
public:
	Stack2() {
		head = nullptr;
	}
	~Stack2()
	{
		while (!empty())
		{
			pop();
		}
		
	}
	void push(itemType v)
	{
		node* tempNode = new node;
		tempNode->key = v;
		tempNode->next = head;
		head = tempNode;

	}
	itemType pop()
	{
		if (head!=nullptr)
		{
			itemType value = head->key;
			node* tempNode = head;
			head = tempNode->next;
			delete tempNode;
			return value;
		}
		else
		{
			std::cout << "Empty Stack" << std::endl;
			return 0;
		}
	}
	bool empty()
	{
		return head == nullptr;
	}

private:
	struct node
	{
		itemType key; node *next;
	};
	node *head, *z;
};

int main()
{
	
	char c;
	Stack2 acc;
	itemType x;

	while ((c = std::cin.get()) != '\n')
	{
		x = 0;
		while (c == ' ') std::cin.get(c);
		if (c == '+') x = acc.pop() + acc.pop();
		if (c == '-')
		{
			itemType temp = acc.pop();
			x = acc.pop()-temp ;
		}
		if (c == '*') x = acc.pop() * acc.pop();
		if (c == '/')
		{
			itemType temp = acc.pop();
			x = acc.pop()/temp;
		}
		

		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - '0');  std::cin.get(c);
		}
		
		acc.push(x);

	}
	
	std::cout << acc.pop() << '\n';

}

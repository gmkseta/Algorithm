#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#define D_MAX_ARRAY_SIZE 512

using namespace std;

struct node
{
	struct node *l;
	int key;
	struct node *r;
};

void TreeInit()
{
	struct node *t, *head;
	head = (struct node *) malloc(sizeof *head);
	head->l = NULL;
	head->r = NULL;
	head->key = 0;
}

struct node *TreeSearch(struct node *head, int xkey)
{
	struct node *t;
	t =  head->r;
	while (t != NULL) {
		if (xkey == t->key)return(t);
		if (xkey < t->key)t = t->l;
		if (xkey > t->key)t = t->r;
	}
	return (NULL);
}

void TreeInsert(struct node *head , int xkey)
{
	struct node *p, *t;

}

void Tokenize(const string&str, vector<string>& tokens, const string& delimiters = " ")
{

	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

int main()
{
	ifstream inf("paragraph.txt");
	stringstream infstream;

	string inStr;
	vector <string> splited;	

	infstream<< inf.rdbuf();

	inStr = infstream.str();


	cout << inStr << endl;

	Tokenize(inStr,splited," .");


	for (auto itr : splited)
	{
		cout << itr << endl;
	}

	return 0;
}
#pragma once

typedef int itemType;


class makeArr
{
private:
	int N;
	bool dummy;
	void (makeArr::*fp)(void);
public:
	itemType* arr;
	makeArr(int n, bool dummy = false);
	
	void make_des_arr();
	void make_rand_arr();
	itemType get(int n);
	void print_arr();
	int getN() { return N; }
	
	void changePF(void (makeArr::*fp_)(void))
	{
		fp = fp_;
	}
	void usePF()
	{
		(this->*fp)();
	}
};


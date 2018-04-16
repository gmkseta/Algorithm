#include "makeArr.h"
#include<iostream>
#include<ctime>
#include<cstdlib>

makeArr::makeArr(int n,bool dummy)
{
	this->dummy = dummy;
	if (dummy == true)
	{
		N = n+1;
		arr = new itemType[n+1];
	}
	else
	{
		N = n;
		arr = new itemType[n];
	}
}

void makeArr::make_des_arr()
{
	if (dummy == true)
	{
		arr[0] = INT_MIN;
		for (int i = 1; i < N; i++)
			arr[i] = N - i;
	}
	else
	{
		for (int i = 0; i < N; i++)
			arr[i] = N - i;
	}
	
}

void makeArr::make_rand_arr()
{
	srand((unsigned int)time(NULL));
	make_des_arr();
	if (dummy == true)
	{
		for (int i = 1; i < N; i++)
		{
			int c = rand() % (N-1)+1;
			itemType tmp = arr[c];
			arr[c] = arr[i]; arr[i] = tmp;
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			int c = rand() % N;
			itemType tmp = arr[c];
			arr[c] = arr[i]; arr[i] = tmp;
		}
	}
}

itemType makeArr::get(int n)
{
	return arr[n]; 
}

void makeArr::print_arr()
{
	if (dummy == true)
	{
		for (int i = 1; i < 21; i++)
			std::cout << arr[i] << " ";
	}
	else
	{
		for (int i = 0; i < 20; i++)
			std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

}
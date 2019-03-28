#include <iostream>
#include <ostream>
#include <iomanip>
class VectorND
{
public:
	float* value;
	int size;
	VectorND(int n) :size(n)
	{
		value = new float[n];
		for (int i = 0; i < n; i++)
		{
			value[i] = i*0.1f;
		}
	}
	VectorND() {}
	void init(int n) {
		size = n;
		value = new float[n];
		for (int i = 0; i < n; i++)
		{
			value[i] = i*0.2f;
		}
	}
	void assignValue(int x, float v)
	{
		value[x] = v;
	}
	float& assignValue(int x)
	{
		return value[x];
	}
	float getValue(int x)
	{
		return value[x];
	}
	float operator()(int x)
	{
		return value[x];
	}
};

class MatrixMN
{
public:
	VectorND* value;
	int x_size, y_size;
	MatrixMN(int x, int y) :x_size(x), y_size(y)
	{
		value = new VectorND[y];
		for (int i = 0; i < y; i++)
		{
			value[i].init(x);
		}

	}
	void assignValue(int x, int y, float v)
	{
		value[y].assignValue(x, v);
	}
	float getValue(int x, int y)
	{
		return value[y].getValue(x);
	}
	//step 3
	VectorND* operator*(VectorND vec)
	{
		VectorND* result = new VectorND(x_size);
		for (int x = 0; x < x_size; x++)
		{
			float sum = 0.0f;
			for (int y = 0; y < y_size; y++)
			{
				sum += getValue(x, y)*vec.getValue(y);
			}
			result->assignValue(x, sum);
		}
		return result;
	}

};
using namespace std;

ostream& operator<<(ostream& strm, VectorND vec)
{
	for (int i = 0; i < vec.size; i++)
		strm << setw(5) << vec.getValue(i);
	strm << endl;
	return strm;
}
ostream& operator<<(ostream& strm, MatrixMN mat)
{
	for (int i = 0; i < mat.y_size; i++)
		strm << mat.value[i];
	strm << endl;
	return strm;
}
ostream& operator<<(ostream& strm, VectorND* vec)
{
	for (int i = 0; i < vec->size; i++)
		strm << setw(5) << vec->getValue(i);
	strm << endl;
	return strm;
}


int main()
{
	VectorND my_vec(10);
	my_vec.assignValue(3) = 10.0f;
	std::cout << my_vec(3) << std::endl;
	
	my_vec.assignValue(3, 10.0f);
	std::cout << my_vec.getValue(3) << std::endl;

	MatrixMN my_mat(15, 10);
	my_mat.assignValue(4, 5, 3.14f);
	std::cout << my_mat.getValue(4, 5) << std::endl;

	
	cout << my_vec << endl;

	
	cout << my_mat << endl;

	cout << my_mat*my_vec << endl;

}
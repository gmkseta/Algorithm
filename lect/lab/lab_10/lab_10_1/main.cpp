#include<iostream>
using namespace std;

typedef struct point {
	char c; int x, y;
	float angle;
}point;
typedef point itemType;


typedef struct line { struct point p1, p2; }line;




class Polygon {
private:
	int cmp_cnt;
public:
	Polygon(point *poly, int N)
	{
		cmp_cnt = 0;
		for (int i = 0; i < N; i++)
		{
			insert(poly, i);
		}
		compute(poly, N);
	}
	int getCnt() { return cmp_cnt; }
	void insert(point *poly, int i)
	{
		int tmp;
		poly[i].c = i + 65;
		cout << poly[i].c << "의 값 >>";
		cin >> tmp;
		poly[i].x = tmp;
		cin >> tmp;
		poly[i].y = tmp;
	}
	void compute(point *poly, int N)
	{
		int i , k = 0; 
		for (int i = 1; i < N; i++)//기준점 계산 ( y가 가장 작은 점)
		{
			if (poly[k].y > poly[i].y)
				k = i;
		}

		for (int i = 0; i < N; i++)
		{
			if(k!=i)
				poly[i].angle = ComputeAngle(poly[k], poly[i]);
		}

	}
	
	float ComputeAngle(struct point p1, struct point p2) {
		int dx, dy, ax, ay;
		float t;
		cmp_cnt++;
		dx = p2.x - p1.x; ax = abs(dx);
		dy = p2.y - p1.y; ay = abs(dy);
		t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
		if (dx < 0) t = 2 - t; else if (dy < 0) t = 4 + t;
		return t * 90.0;
	}

	
};

class HEAP_SORT {
private:
	itemType * a;
	int N;
public:
	int cnt_comp = 0;
	
	HEAP_SORT(itemType* poly, int max) {
		a = poly; N = max; heapsort();
	}
	~HEAP_SORT() { }
	void swap(itemType a[], int i, int j) {
		itemType temp;
		temp = a[j]; a[j] = a[i]; a[i] = temp;
	}
	void MakeHeap(itemType a[], int Root, int LastNode) {
		int Parent, LeftSon, RightSon, Son; itemType RootValue;
		Parent = Root;
		RootValue = a[Root];
		LeftSon = 2 * Parent + 1;
		RightSon = LeftSon + 1;
		while (LeftSon <= LastNode) {
			if (++cnt_comp&&RightSon <= LastNode && a[LeftSon].angle < a[RightSon].angle) {
				Son = RightSon;
			}
			else Son = LeftSon;
			if (++cnt_comp&&RootValue.angle < a[Son].angle) {
				a[Parent] = a[Son];
				Parent = Son;
				LeftSon = Parent * 2 + 1;
				RightSon = LeftSon + 1;
			}
			else break;
		}
		a[Parent] = RootValue;
	}
	void heapsort() {
		int i;
		for (i = N / 2; i >= 0; i--)
			MakeHeap(a, i, N - 1);
		for (i = N - 1; i >= 1; i--) {
			swap(a, 0, i);
			MakeHeap(a, 0, i - 1);
		}
	}
	void view()
	{
		for (int i = 0; i < N; i++)
			cout << a[i].c << " - ";
		cout << a[0].c ;
		cout << endl;
	}
};



int main() {
	int Nmax;
	cout << "N의 값 : ";
	cin >> Nmax;
	point *polygon = new point[Nmax];

	Polygon poly(polygon,Nmax);

	HEAP_SORT heap(polygon, Nmax);
	cout << "다각형이 만들어지는 순서 :";
	heap.view();

	cout << "수평각 계산 횟수 : " << poly.getCnt() << endl;
	cout << "각의 비교 횟수 : " << heap.cnt_comp << endl;

}

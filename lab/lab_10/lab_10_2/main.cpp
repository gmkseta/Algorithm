#include<iostream>
using namespace std;

struct point {
	char c; int x, y;
	point() {};
	void initialize(char c, int x, int y)
	{
		this->c = c; this->x = x; this->y = y;
	}

};
typedef struct polygon {
	struct point pt;
	float angle;
}polygon;
typedef polygon itemType;
struct line { struct point p1, p2; };

class Polygon {
private:
	int Nmax;
	struct point crt_pt;
public:
	polygon * poly;
	int cnt_ang = 0;
	Polygon(int N) : Nmax(N) {
		poly = new polygon[Nmax];
	}
	~Polygon() {
		delete poly;
	}
	void insert_point() {
		int x, y;
		for (int i = 0; i < Nmax; i++) {
			cout << (char)(i + 65) << "점 입력>> ";
			cin >> x >> y;
			poly[i].pt.initialize((char)(i + 65), x, y);
			//cout << poly[i].pt.c << " " << poly[i].pt.x << " " << poly[i].pt.y << endl;
		}
	}
	void make_criteria_point() {
		//crt_pt = poly[0].pt;
		int min = 0, i = 0, j = i + 1;
		while (j<Nmax) {
			for (j = i + 1; j < Nmax; j++) {
				if (poly[i].pt.y > poly[j].pt.y) {
					min = j; i = j; break;
				}
			}
		}
		crt_pt = poly[min].pt;
		poly[min].angle = -1;
	}
	float ComputeAngle(struct point p1, struct point p2) {
		int dx, dy, ax, ay;
		float t;
		dx = p2.x - p1.x; ax = abs(dx);
		dy = p2.y - p1.y; ay = abs(dy);
		t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
		if (dx < 0) t = 2 - t; else if (dy < 0) t = 4 + t;
		return t * 90.0;
	}
	void make_angle() {
		make_criteria_point();
		//poly[0].angle = -1;
		for (int i = 0; i < Nmax; i++)
		{
			if (poly[i].angle != -1) {
				poly[i].angle = ComputeAngle(crt_pt, poly[i].pt);
				cnt_ang++;
			}
		}
	}
	void view() {
		for (int i = 0; i < Nmax; i++)
			cout << poly[i].pt.c << " ";
		cout << endl;
	}
};
class MAKE_HEAP {
private:
	itemType * a;
	int N;
public:
	int cnt_comp = 0;
	MAKE_HEAP(int max) { a = new itemType[max]; N = max; }
	MAKE_HEAP(itemType* poly, int max) { a = poly; N = max; }
	~MAKE_HEAP() { }
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
	itemType* heap_result() {
		return a;
	}
	void view()
	{
		for (int i = 0; i <= N; i++)
			cout << a[i].angle << " ";
		cout << endl;
	}
};
int direction(struct point A, struct point B, struct point C) {
	int dxAB, dxAC, dyAB, dyAC, dir;
	dxAB = B.x - A.x; dyAB = B.y - A.y;
	dxAC = C.x - A.x; dyAC = C.y - A.y;
	if (dxAB*dyAC < dxAC*dyAB)dir = 1;
	if (dxAB*dyAC > dxAC*dyAB)dir = -1;
	if (dxAB*dyAC == dxAC * dyAB) {
		if (dxAB*dxAC < 0 || dyAB * dyAC < 0) dir = -1;
		else if (dxAB*dxAB + dyAB * dyAB > dxAC*dxAC + dyAC * dyAC) dir = 0;
		else dir = 1;
	}
	return dir;
}

int intersection(struct line AB, struct line CD) {
	bool linecrossing;
	if (direction(AB.p1, AB.p2, CD.p1)*direction(AB.p1, AB.p2, CD.p2) < 0 &&
		direction(CD.p1, CD.p2, AB.p1)*direction(CD.p1, CD.p2, AB.p2) < 0)
		linecrossing = true;
	else linecrossing = false;
	return linecrossing;
}
int isPointInside(struct point A, polygon p[], int n) {
	int count, i, lastpoint; bool point_on_testline = false;
	struct line testline, polyline;
	count = lastpoint = 0;
	testline.p1 = A; testline.p2 = A;
	testline.p2.x = INT_MAX;
	for (int i = 1; i < n; i++) {
		polyline.p1 = polyline.p2 = p[i].pt;
		if (intersection(testline, polyline))
			point_on_testline = true;
		else {
			polyline.p2 = p[lastpoint].pt;
			lastpoint = i;
			if (!point_on_testline)
				if (intersection(polyline, testline)) count++;
				else {
					if (direction(testline.p1, testline.p2, polyline.p1)*direction(testline.p1, testline.p2, polyline.p2) < 0) {
						count++; point_on_testline = false;
					}
				}
		}
	}
	return (count % 2 == 1);
}


int main() {
	int Nmax;
	cout << "N의 값>> ";
	struct point z;
	cin >> Nmax;
	cout << "Z좌표>>";
	cin >> z.x >> z.y;
	z.c = 'Z';


	Polygon poly(Nmax);
	poly.insert_point();
	poly.make_angle();

	MAKE_HEAP heap(poly.poly, Nmax);
	heap.heapsort();
	poly.poly = heap.heap_result();

	cout << "다각형이 만들어지는 순서 :";
	poly.view();
	bool point_inside = isPointInside(z, poly.poly, Nmax);
	if (point_inside) cout << "True" << endl;
	else cout << "False" << endl;
}
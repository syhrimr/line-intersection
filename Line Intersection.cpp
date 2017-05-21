#include <iostream>
#include <time.h>
using namespace std;

struct Point {	
	float x;
	float y;
};

class Line {
public :
	Point p1, p2;
	float m, c;
	float lowX, lowY, highX, highY;

	Line(Point p1, Point p2);
	~Line();
	void gradient();
	void ce();
	void checkHighLowPoint();
};

Line::Line(Point p1, Point p2) {
	this->p1 = p1;
	this->p2 = p2;
}

void Line::gradient() {
	m = (p2.y - p1.y) / (p2.x - p1.x);
	
	// Check if perpendicular, gradien equal to 0
	if ((p2.x - p1.x) == 0)	m = 0;
}

void Line::ce() {
	// Formula y = mx + c (choose one point)
	c = p2.y - m * p2.x;
}

void Line::checkHighLowPoint() {
	if (p1.y > p2.y) {
		highY = p1.y;
		lowY = p2.y;
	} else {
		highY = p2.y;
		lowY = p1.y;
	}
	
	if (p1.x > p2.x) {
		highX = p1.x;
		lowX = p2.x;
	} else {
		highX = p2.x;
		lowX = p1.x;
	}
}

Line::~Line() {
	
}

int main () {
	// Init x-point intersection and y-point intersection variable
	float xInt, yInt;
	// Variable to give true value when instersected
	bool line1, line2;
	//Variable to sum number of intersection
	int sum = 0;
	// Running time variable
	clock_t t;
	t = clock();
	
	// Init points
	Point p[3] = {{3, 11}, {3, 0}, {1, 3}};
	Point q[3] = {{5, 2}, {5, 5}, {5, 9}};
	
	int square = sizeof(p) / sizeof(p[0]);
		
	for (int i = 0; i <= square - 1; i++) {
		for (int j = 1; j <= square - 1; j++) {
			if (i == j) j++;
			
			cout << i << " " << j << endl;
			
			Line l1(p[i], q[i]);
			Line l2(p[j], q[j]);
			
			l1.gradient(); l1.ce();
			l2.gradient(); l2.ce();
			
			cout  << l1.m << " " << l2.m << endl;
			cout  << l1.c << " " << l2.c << endl;
			
			// X-Line intersection	-->	Formula : m1x + c1 = m2x + c2
			xInt = (l2.c - l1.c) / (l1.m - l2.m);
			
			//if ((l1.m - l2.m) == 0) xInt = 0;
			
			// Y-Line intersection	-->	Formula : y = mx + c
			yInt = l1.m * xInt + l1.c;
			
			cout  << xInt << " " << yInt << endl;
			
			l1.checkHighLowPoint();
			l2.checkHighLowPoint();
			
			// Check Intersection
			if ((yInt <= l1.highY && yInt >= l1.lowY) || (xInt <= l1.highX && xInt >= l1.lowX)) {
				line1 = true;
			} else {
				line1 = false;
			} if ((yInt <= l2.highY && yInt >= l2.lowY) || (xInt <= l2.highX && xInt >= l1.lowX)) {
				line2 = true;
			} else {
				line2 = false;
			}
			
			if (line1 && line2) {
				sum++;
				cout << "Intersection \n\n";
			} else {
				cout << "No intersection \n\n";
			}			
		}
	}
	
	t = clock() - t;
	long double time_taken = ((long double)t) / CLOCKS_PER_SEC;
	
	cout << "Sum of intersection : " << sum << endl;
	cout << "Time taken : " << time_taken << "s";
	
	return 0;
}

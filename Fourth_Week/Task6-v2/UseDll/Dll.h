/*
4.Create libraries for points and segments in the plane. Types of point and segment represented as records:
type = entry point
	x, in really;
ER;
The segment = entry
	a, b: Point;
ER;
Implement operations on points:
1) to the point t;
2) put the point t equal to (x, y);
3) show the point t.
Implement actions of the segments:
1) to segment s;
2) show a segment s;
3) put the segment s equal to a, b;
4) the length of the segment s;
5) or point tna is a straight line with a segment s;
6) or is the point tvseredyni segment s;
7) area of ​​the triangle formed by point tta segment s.
The file recorded sequence of points. Using the module to work with points and segments on the plane to find:
a) triangle of largest area formed by points of order;
b) the smallest circle radius, within which lie all points of order;
c) segment, which is the highest number of points of order;
g) range, which is the highest number of points of order.
*/
#pragma once
struct Point
{
	double x,y;
};
struct Line
{
	Point a, b;
};

typedef void (*ShowL)(const Line& l);//Show Line
typedef double (*Len)(const Line& l);//The length of the line	
typedef int (*PPL)(const Line& l, const Point& p);//Point lies on one line //Point lies on the line
typedef double (*A)(const Line& l, const Point& p);//Area Point and the point
typedef Line* (*FreeL)(Line *L);//Line free

extern "C" Point* GetPoint();//Get the pointer
extern "C" void PutPoint(const double& x, const double& y, Point& p);//Put the pointer (x, y)
extern "C" void ShowPoint(const Point& p);//Show point
extern "C" Line* GetLine(void);//Get the line
extern "C" void PutLine(const Point& a, const Point& b, Line& p);//Put the Line a, b
extern "C" Point* DeletePoint(Point *P);//Point free

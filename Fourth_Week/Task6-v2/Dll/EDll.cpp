// EDll.cpp: определ€ет экспортированные функции дл€ приложени€ DLL.
//
#include "stdafx.h"
#include "Dll.h"
#include <iostream>
#define DllExport extern "C" __declspec(dllexport)
//Selects memory at the point
//No parameters
//Return pointer
DllExport Point* GetPoint()
{
	Point *P;
	try 
	{
		P = new Point;
		P->x = 0;
		P->y = 0;
		return P;
	}
	catch(std::bad_alloc& e)
	{
		std::cout << "CanТt allocate memory for Point";
		delete P;
		P = NULL;
		return P;
	}
}
//Put the pointer (x, y)
//Receives the coordinates and point
//Return void
DllExport void PutPoint(const double& x, const double& y, Point& p)
{
	p.x = x;
	p.y = y;
}
//Prints point
//Gets the point
//Return void
DllExport void ShowPoint(const Point& P)
{
	std::cout << '(' << P.x << ';' << P.y << ')';
}
//Point A.x is equal point B.x? 
//Point and point
//Return A.x == B.x?
bool EqualXPoint(const Point& a, const Point& b)
{
	return abs(a.x - b.x) < 0.01l;
}
//Point A.y is equal point B.y? 
//Point and point
//Return A.y == B.y?
bool EqualYPoint(const Point& a, const Point& b)
{
	return abs(a.y - b.y) < 0.01l;
}
//Selects memory at the line
//No parameters
//Return line
DllExport Line* GetLine()
{
	Line *L;
	try 
	{
		L = new Line;
		L->a.x = 0;
		L->a.y = 0;
		L->b.x = 0;
		L->b.y = 0;
		return L;
	}
	catch(std::bad_alloc& e)
	{
		std::cout << "CanТt allocate memory for Point";
		delete L;
		L = NULL;
		return L;
	}
}
//Put the Line a, b
//Gets the point and Line
//Return void
DllExport void PutLine(const Point& a, const Point& b, Line& p)
{
	p.a = a;
	p.b = b;
}
//Prints line
//Gets the line
//Return void
DllExport void ShowLine(const Line& L)
{
	std::cout<< '(' << L.a.x << ';' << L.a.y << ')' << '-'
		<< '(' << L.b.x << ';' << L.b.y << ')';
}
//Selecifies the length of the line
//Gets the line
//Returns the length of
DllExport double LengthLine(const Line& l)
{
	double zm1, zm2;
	zm1 = (double) ((l.a.x - l.b.x) * (l.a.x - l.b.x));
	zm2 = (double) ((l.a.y - l.b.y) * (l.a.y - l.b.y));
	return pow(zm1 + zm2, 0.5);
}
//Point lies on a line not parallel axes
//Gets a point and line
//Return (point Lies on aline)? 
bool Point_Line(const Line& l, const Point& p)
{
	double X,Y;
	X = (p.x - l.a.x) / (l.b.x - l.a.x);
	Y = (p.y - l.a.y) / (l.b.y - l.a.y);
	return (abs(X - Y)) < 0.01;
}
//Point lies on one line
//Gets a point and line
//Return (Point lies on one line)?
DllExport bool PointOnLine(const Line& l, const Point& p)
{
	if ((l.b.x - l.a.x) == 0)
	{
		return EqualXPoint(l.a, p);
	}
	else if ((l.b.y - l.a.y) == 0)
	{
		return EqualYPoint(l.a, p);
	}
	else 
	{
		return Point_Line(l, p);
	}
}
//Point lies on the line
//Gets a point and line
//Return (Point lies on the line)?
DllExport int PointInLine(const Line& l, const Point& p)//Point a,Point b,Point p)
{
	if( !(p.x > l.a.x && p.x > l.b.x) || !(p.y > l.a.y && p.y > l.b.y)) 
	{
		return PointOnLine(l, p);
	}
	return false;
}
//Area Point and the point
//Gets a point and line
//Return Area
DllExport double LineArea(const Line& l, const Point& p)
{
	double A, B, C;
	A = LengthLine(l);
	Line *L=GetLine();
	PutLine(l.b, p, *L);
	B = LengthLine(*L);
	PutLine(p, l.a, *L);
	C = LengthLine(*L);
	double Per = (A + B + C) / 2;
	return sqrt(Per * (Per - A) * (Per - B) * (Per - C));
}
//Point free
//Point 
//NULL
DllExport Point* DeletePoint(Point *P)
{
	if (P == NULL)
		return P;
	PutPoint(0, 0, *P);
	delete P;
	P = NULL;
	return P;
}
//Line free
//Line
//NUll
DllExport Line* DeleteLine(Line *L)
{
	Point P;
	PutPoint(0,0,P);
	if (L == NULL)
		return L;
	PutLine(P,P,*L);
	delete L;
	L = NULL;
	return L;
}
 
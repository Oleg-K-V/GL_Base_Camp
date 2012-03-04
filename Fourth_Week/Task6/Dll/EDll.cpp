// EDll.cpp: определяет экспортированные функции для приложения DLL.
//
#include "stdafx.h"
#include "Dll.h"
#include <iostream>
#define DllExport extern "C" __declspec(dllexport)
//Get the pointer
DllExport Point* PointGet()
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
		std::cout << "Unselected memry for Point";
		delete P;
		P = NULL;
		return P;
	}
}
//Put the pointer (x, y)
DllExport void PointPut(const double& x, const double& y, Point& p)
{
	p.x = x;
	p.y = y;//записуєм дані
}
//Show point
DllExport void PointShow(const Point& P)
{
	std::cout << '(' << P.x << ';' << P.y << ')';//виводим на екран
}
//Point A is equal point B?
//A.x = B.x?
int PointEqualX(const Point& a, const Point& b)
{
	if (abs(a.x - b.x) < 0.01l)
		return 1;
	return 0;//порівнюєм на рівність
}
//A.y = B.y?
int PointEqualY(const Point& a, const Point& b)
{
	if (abs(a.y - b.y) < 0.01l)
		return 1;
	return 0;//порівнюєм на рівність у
}
//Get the line
DllExport Line* LineGet()
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
		std::cout << "Unselected memry for Line";
		delete L;
		L = NULL;
		return L;
	}
}
//Put the Line a, b
DllExport void LinePut(const Point& a, const Point& b, Line& p)
{
	p.a = a;
	p.b = b;//записуєм лінію
}
//Show Line
DllExport void LineShow(const Line& L)
{
	std::cout<< '(' << L.a.x << ';' << L.a.y << ')' << '-'
		<< '(' << L.b.x << ';' << L.b.y << ')';//виводим на екран
}
//The distance detween two point
double Length(const Point& a, const Point& b)
{
	double zm1, zm2;
	zm1 = (double) ((a.x - b.x) * (a.x - b.x));
	zm2 = (double) ((a.y - b.y) * (a.y - b.y));
	return pow(zm1 + zm2, 0.5);//визначаєм довжину
}
//The length of the line
DllExport  double LineLength(const Line& l)
{
	return Length(l.a,l.b);//визначаєм довжину відрізка
}
//Point lies on one line
int Point_Line(const Line& l, const Point& p)
{
	double X,Y;
	X = (p.x - l.a.x) / (l.b.x - l.a.x);
	Y = (p.y - l.a.y) / (l.b.y - l.a.y);
	if ((abs(X - Y)) < 0.01)
		return 0;
	return 1;//перевіка чи лінія лежить на одній прямій з точкою
}
//Point lies on one line
DllExport int PointOnLine(const Line& l, const Point& p)
{
	if ((l.b.x - l.a.x) == 0)
	{
		if (PointEqualX(l.a, p))
			return 0;
	}
	else if ((l.b.y - l.a.y) == 0)
	{
		if (PointEqualY(l.a, p))
			return 0;
	}
	else 
	{
		return Point_Line(l, p);
	}
	return 1;//Перевіряєм всі варіанти попадання точки на пряму
}
//Point lies on the line
DllExport int PointInLine(const Line& l, const Point& p)//Point a,Point b,Point p)
{
	if ((l.b.x - l.a.x) == 0)
	{
		if (((l.a.y <= p.y && p.y <= l.b.y) || (l.a.y >= p.y && p.y >= l.b.y)) && (PointEqualX(l.a, p)))
			return 0;
	}
	else if ((l.b.y - l.a.y) == 0)
	{
		if (((l.a.x <= p.x && p.x <= l.b.x) || (l.a.x >= p.x && p.x >= l.b.x)) && (PointEqualY(l.a, p)))
			return 0;
	}
	else if( !(p.x > l.a.x && p.x > l.b.x) || !(p.y > l.a.y && p.y > l.b.y)) 
	{
		return Point_Line(l, p);
	}
	return 1;//перевіряєм всі варіанти попадання точки на відрізок
}
//Perimeter
double Perimeter(const double& A, const double& B, const double& C)
{
	return A + B + C;//шукаєм перимтр
}
//Area three point
double Area(const Point& a, const Point& b,const Point& p)
{
	double A, B, C;
	A = Length(a, b);
	B = Length(b, p);
	C = Length(p, a);	
	double Per = Perimeter(A, B, C) / 2;
	return sqrt(Per * (Per - A) * (Per - B) * (Per - C));//шукаєм площу
}
//Area Point and the point
DllExport double LineArea(const Line& l, const Point& p)
{
	return Area(l.a, l.b, p);//площа лінії і точки 
}
//Point free
DllExport Point* PointDelete(Point *P)
{
	if (P != NULL)
		PointPut(0, 0, *P);
	delete P;
	P = NULL;
	return P;
}
//Line free
DllExport Line* LineDelete(Line *L)
{
	Point P;
	PointPut(0,0,P);
	if (L != NULL)
		LinePut(P,P,*L);
	delete L;
	L = NULL;
	return L;
}
 
// USDll.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include "Dll.h"
#include "Stack.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#pragma comment (lib, "EDll")
using namespace std;
size_t Stack::size = 0;
typedef Stack* S;
//Fres memory training
//Gets a reference to the stack
//Return void
void ClearD(S& Mas)
{
	Point *P;
	int size = Mas->Size();
	for (int i = size - 1; i > -1; i --)
	{
		Mas = Mas->Pop(Mas, P);
		P = DeletePoint(P);
	}
}
//Reads the point of the file
//Array and file name
//Return 0 or 1  
int Cin_file(S& Mas, const string& name)
{
	ifstream ist(name.c_str());
	Point *P;
	char zm1, zm2, zm3;
	P = GetPoint();
	while (ist >> zm1 >> P->x >> zm2 >> P->y >> zm3)
	{
		if (zm1 != '(' || zm2 != ';' || zm3 != ')')
		{
			cout << "Failed to read data!\nCheck the file for correct\n";
			ClearD(Mas);
			return 1;
		}
		Mas = Mas->Push(Mas, P);
		zm1 = 0; zm2 = 0; zm3 = 0;
		P = GetPoint();
	}
	if (zm1 != 0)
	{
			cout << "Failed to read data!\nCheck the file for correct\n";
			ClearD(Mas);
			return 1;
	}
	P = DeletePoint(P);
	return 0;
}
//Search the biggest square triangle
//Array and two pointer function
//Return biggest area
double BigA(const S& Mas, const A& AreaLine, const FreeL& DeleteLine)
{
	Line *L;
	L = GetLine();
	if (Mas->Size() < 3)
		return 0;
	double Biggest = 0, zm;
	for (size_t i = 0; i < Mas->Size() - 2; i ++)
	{
		for (size_t j = i + 1; j < Mas->Size() - 1; j ++)
		{
			for (size_t k = j + 1; k < Mas->Size(); k ++)
			{
				type_n a, b, c;
				a = Mas->ReadS(Mas, i);
				b = Mas->ReadS(Mas, j); 
				c = Mas->ReadS(Mas, k); 
				PutLine(*a, *b, *L);
				zm = AreaLine(*L, *c);
				if (zm > Biggest)
					Biggest = zm;
			}
		}
	}
	L = DeleteLine(L);
	return Biggest;
}
//Find the smallest radius
//Array, and two pointer function
//Return smallest radius doscribed range
double SmalR(const S& Mas, const Len& LengthLine, const FreeL& DeleteLine)
{
	Line *L;
	L=GetLine();
	if (Mas->Size() < 2)
		return 0;
	double Smal = 0, zm;
	for (size_t i = 0; i < Mas->Size() - 1; i ++)
	{
		for (size_t j = i + 1; j < Mas->Size(); j ++)
		{
			type_n a, b;
			a = Mas->ReadS(Mas, i);
			b = Mas->ReadS(Mas, j); 
			PutLine(*a, *b, *L);
			zm = LengthLine(*L);
			if (zm > Smal)
				Smal = zm;
		}
	}
	L = DeleteLine(L);
	return Smal / 2;
}
//The segment thet contains the greatest number of point
//Array, and two pointer function
//Return the line with the most points on it
Line* GreatL(const S& Mas, const PPL& PointOnLine, const FreeL& DeleteLine)
{
	Line *Greatest = NULL, *zm;
	zm = GetLine();
	int lich, res = 0;
	for (size_t i = 0; i < Mas->Size() - 1; i ++)
		for (size_t j = i + 1; j < Mas->Size(); j ++)
		{
			type_n a, b;
			a = Mas->ReadS(Mas, i);
			b = Mas->ReadS(Mas, j);
			PutLine(*a, *b, *zm);
			lich = 0;
			for(size_t k = i + 1; k< Mas->Size(); k ++)
			{
				if (k != j)
				{
					type_n c;
					c = Mas->ReadS(Mas, k);
					if (PointOnLine(*zm, *c))
						lich ++;
				}
			}
			if (lich > res)
			{
				res = lich;
				Greatest = DeleteLine(Greatest);
				Greatest = zm;
				zm = NULL;
				zm = GetLine();
			}
		}
	zm = DeleteLine(zm);
	return Greatest;
}
//Main
int _tmain(int argc, _TCHAR* argv[])
{
	ShowL ShowLine;
	Len LengthLine;
	PPL PointOnLine;
	PPL PointInLine;
	A AreaLine;
	FreeL DeleteLine;

	HINSTANCE pdll;
	pdll = LoadLibrary(TEXT("EDll"));
	if (pdll)
	{
		(FARPROC&)ShowLine=GetProcAddress(pdll,LPCSTR(0xb));
		(FARPROC&)LengthLine=GetProcAddress(pdll,LPCSTR(0x5));
		(FARPROC&)PointOnLine=GetProcAddress(pdll,LPCSTR(0x8));
		(FARPROC&)PointInLine=GetProcAddress(pdll,LPCSTR(0x7));
		(FARPROC&)AreaLine=GetProcAddress(pdll,LPCSTR(0x6));
		(FARPROC&)DeleteLine=GetProcAddress(pdll,LPCSTR(0x1));
		
		S Mas = NULL;
		string name("Points.txt");
		double ar, rad;
		if (Cin_file(Mas, name))
		{
			getch();
			return 1;
		}
		ar = BigA(Mas, AreaLine, DeleteLine);
		rad = SmalR(Mas, LengthLine, DeleteLine);
		if (ar != 0)
			cout << "The greatest area of a triangle is " << ar << endl;
		else cout << "Points are too small to build a triangle " << endl;
		if (rad != 0)
			cout << "The smallest radius f the circumscribing all points " << rad << endl;// обраховуєм найменший радіус описаного кола
		else cout << "Points are too little to build a line " << endl;
		Line *L;
		L = GreatL(Mas, PointOnLine, DeleteLine);//знаходим лінію з найбільшою кількістю точок на ній
		if (L != NULL)
		{
			cout << "The segment thet contains the greatest number of point ";
			ShowLine(*L);
			L = DeleteLine(L);
			cout << endl;
		}
		else cout << "There is no line on which lay at least one point " << endl;
		cout << "Scanned following points" << endl;
		for (size_t i=(size_t)0;i<Mas->Size();i++)
		{//виводим вміст файлу
			type_n a;
			a = Mas->ReadS(Mas, i);
			ShowPoint(*a);
			cout << endl;
		}
		ClearD(Mas);
	}
	else cout<<"Can not open";//якщо бібліотека не відкрилась закінчуєм роботу
	getch();
	return 0;
}


// USDll.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include "Dll.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
//Fres memory training
void Clear_data(vector<Point *>& Mas, FreeP PointDelete)
{
	Point *P;
	int size = Mas.size();
	for (int i = size - 1; i > -1; i--)
	{
		P = Mas[i];//зчитуєм обєкт
		Mas.pop_back();//видаляєм обєкт з масиву
		P = PointDelete(P);//вивільняєм память
	}
}
//Reads the point of the file
int Cin_file(vector<Point *>& Mas, string name, GetP PointGet, FreeP PointDelete)
{
	ifstream ist(name.c_str());//відкриваєм потік зчитування з файлу
	Point *P;
	char zm1, zm2, zm3;
	P = PointGet();//виділяєм память
	while (ist >> zm1 >> P->x >> zm2 >> P->y >> zm3)
	{//читаєм з файлу
		if (zm1 != '(' || zm2 != ';' || zm3 != ')')
		{//перевіряєм на коректність
			cout << "Failed to read data!\nCheck the file for correct\n";
			Clear_data(Mas, PointDelete);//якщо зчитано некоректні зані видаляєм зчитані дані
			return 1;//закінчуєм роботу
		}
		Mas.push_back(P);//записуєм в вектор
		P = NULL;
		zm1 = 0; zm2 = 0; zm3 = 0;
		P = PointGet();//виділяєм нову память
	}
	P = PointDelete(P);//позбуваємся зайво виділеної памяті
	return 0;
}
//Get area
double GetArea(Point *a, Point *b, Point *c, A LineArea, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *L;
	L=LineGet();//виділяєм память під лінію
	LinePut(*a, *b, *L);//ініціалізуєм лінію
	double res = LineArea(*L,*c);//знаходим перимтр
	L = LineDelete(L);//видаляєм лінію
	return res; 
}
//Search the biggest square triangle
double BiggestArea(vector<Point *> Mas, A LineArea, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	double Biggest = 0, zm;
	for (size_t i = 0; i < Mas.size(); i++)
		for (size_t j = i+1; j < Mas.size(); j++)
			for (size_t k = j+1; k < Mas.size(); k++)
			{
				zm = GetArea(Mas[i], Mas[j], Mas[k], LineArea, LineGet, LinePut, LineDelete);//зчитуєм перимтр
				if (zm > Biggest) //перевіряєм чи він є самим найбільшим на даний момент
					Biggest = zm;
			}
	return Biggest;
}
//Find the Length f
double Length(Point *a, Point *b, Len LineLength, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *L;
	L=LineGet();//виділяєм память під лінію
	LinePut(*a, *b, *L);//ініціалізуєм лінію
	double res = LineLength(*L);//Знаходим довжину
	L = LineDelete(L);//видаляєм лінію
	return res;
}
//The smallest radius
double SmallestRadius(vector<Point *> Mas, Len LineLength, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	double Smallest = 0, zm;
	for (size_t i = 0; i < Mas.size()-1; i++)
		for (size_t j = i+1; j < Mas.size(); j++)
		{
			zm = Length(Mas[i], Mas[j], LineLength, LineGet, LinePut, LineDelete);//Визначаєм довжину
			if (zm > Smallest)//перевіряєм це найдовша відстань на даний момент
				Smallest = zm;
		}
		return Smallest;
}
//The segment thet contains the greatest number of point
Line* GreatestLine(vector<Point *> Mas, PPL PointOnLine, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *Greatest = NULL, *zm;
	zm=LineGet();//виділяєм память під лінію
	int lich, res = 0;
	for (size_t i = 0; i < Mas.size()-1; i++)
		for (size_t j = i+1; j < Mas.size(); j++)
		{
			LinePut(*Mas[i], *Mas[j], *zm);//ініціалізуєм лінію 
			lich = 0;
			for(size_t k = i+1; k< Mas.size(); k++)
			{
				if (k != j)//перевіряєм чи точка не збігається з одною з вершин лінії
				{
					if (!(PointOnLine(*zm, *Mas[k])))//перевіряєм чи точка лежить на лінії
						lich++;
				}
			}
			if (lich > res)
			{//перевіряєм чи ця лінія містить найбільше точок
				res = lich;
				Greatest = LineDelete(Greatest);
				Greatest = zm;
				zm = NULL;
				zm = LineGet();
			}//копіюєм дані
		}
	zm = LineDelete(zm);//видаляєм лінію
	return Greatest;
}
//Main
int _tmain(int argc, _TCHAR* argv[])
{
	//оголошення вказвникі на функції
	GetP PointGet;
	PutP PointPut;
	ShowP PointShow;
	GetL LineGet;
	PutL LinePut;
	ShowL LineShow;
	Len LineLength;
	PPL PointOnLine;
	PPL PointInLine;
	A LineArea;
	FreeP PointDelete;
	FreeL LineDelete;

	HINSTANCE pdll;
	pdll = LoadLibrary(TEXT("EDll"));
	if (pdll)
	{
		//Загружаємо змінні
		(FARPROC&)PointGet=GetProcAddress(pdll,LPCSTR(0x8));
		(FARPROC&)PointPut=GetProcAddress(pdll,LPCSTR(0xb));
		(FARPROC&)PointShow=GetProcAddress(pdll,LPCSTR(0xc));
		(FARPROC&)LineGet=GetProcAddress(pdll,LPCSTR(0x3));
		(FARPROC&)LinePut=GetProcAddress(pdll,LPCSTR(0x5));
		(FARPROC&)LineShow=GetProcAddress(pdll,LPCSTR(0x6));
		(FARPROC&)LineLength=GetProcAddress(pdll,LPCSTR(0x4));
		(FARPROC&)PointOnLine=GetProcAddress(pdll,LPCSTR(0xa));
		(FARPROC&)PointInLine=GetProcAddress(pdll,LPCSTR(0x9));
		(FARPROC&)LineArea=GetProcAddress(pdll,LPCSTR(0x1));
		(FARPROC&)PointDelete=GetProcAddress(pdll,LPCSTR(0x7));
		(FARPROC&)LineDelete=GetProcAddress(pdll,LPCSTR(0x2));
		//
		vector<Point *> Mas;
		string name("Points.txt");
		if (Cin_file(Mas, name, PointGet, PointDelete))//читаєм файл
		{//якщо не вдалось прочитати завершуєм роботу
			getch();
			return 1;
		}
		cout<< "The greatest area of a triangle is " << BiggestArea(Mas, LineArea, LineGet, LinePut, LineDelete) << endl// обраховуєм найбільший перимтр
			<< "The smallest radius f the circumscribing all points " << SmallestRadius(Mas, LineLength, LineGet, LinePut, LineDelete) << endl;// обраховуєм найменший радіус описаного кола
		Line *L;
		L=GreatestLine(Mas, PointOnLine, LineGet, LinePut, LineDelete);//знаходим лінію з найбільшою кількістю точок на ній
		cout<< "The segment thet contains the greatest number of point ";
		LineShow(*L);
		L=LineDelete(L);//видаляєм лінію
		cout<< endl << "Scanned following points" << endl;
		for (size_t i=(size_t)0;i<Mas.size();i++)
		{//виводим вміст файлу
			PointShow(*Mas[i]);
			cout << endl;
		}
		Clear_data(Mas, PointDelete);//видаляєм всі точки з памяті
	}
	else cout<<"Can not open";//якщо бібліотека не відкрилась закінчуєм роботу
	getch();
	return 0;
}


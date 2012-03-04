// USDll.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		P = Mas[i];//������ ����
		Mas.pop_back();//�������� ���� � ������
		P = PointDelete(P);//��������� ������
	}
}
//Reads the point of the file
int Cin_file(vector<Point *>& Mas, string name, GetP PointGet, FreeP PointDelete)
{
	ifstream ist(name.c_str());//�������� ���� ���������� � �����
	Point *P;
	char zm1, zm2, zm3;
	P = PointGet();//������� ������
	while (ist >> zm1 >> P->x >> zm2 >> P->y >> zm3)
	{//����� � �����
		if (zm1 != '(' || zm2 != ';' || zm3 != ')')
		{//��������� �� ����������
			cout << "Failed to read data!\nCheck the file for correct\n";
			Clear_data(Mas, PointDelete);//���� ������� ��������� ��� �������� ������ ���
			return 1;//������� ������
		}
		Mas.push_back(P);//������� � ������
		P = NULL;
		zm1 = 0; zm2 = 0; zm3 = 0;
		P = PointGet();//������� ���� ������
	}
	P = PointDelete(P);//���������� ����� ������� �����
	return 0;
}
//Get area
double GetArea(Point *a, Point *b, Point *c, A LineArea, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *L;
	L=LineGet();//������� ������ �� ���
	LinePut(*a, *b, *L);//��������� ���
	double res = LineArea(*L,*c);//�������� �������
	L = LineDelete(L);//�������� ���
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
				zm = GetArea(Mas[i], Mas[j], Mas[k], LineArea, LineGet, LinePut, LineDelete);//������ �������
				if (zm > Biggest) //��������� �� �� � ����� ��������� �� ����� ������
					Biggest = zm;
			}
	return Biggest;
}
//Find the Length f
double Length(Point *a, Point *b, Len LineLength, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *L;
	L=LineGet();//������� ������ �� ���
	LinePut(*a, *b, *L);//��������� ���
	double res = LineLength(*L);//�������� �������
	L = LineDelete(L);//�������� ���
	return res;
}
//The smallest radius
double SmallestRadius(vector<Point *> Mas, Len LineLength, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	double Smallest = 0, zm;
	for (size_t i = 0; i < Mas.size()-1; i++)
		for (size_t j = i+1; j < Mas.size(); j++)
		{
			zm = Length(Mas[i], Mas[j], LineLength, LineGet, LinePut, LineDelete);//�������� �������
			if (zm > Smallest)//��������� �� �������� ������� �� ����� ������
				Smallest = zm;
		}
		return Smallest;
}
//The segment thet contains the greatest number of point
Line* GreatestLine(vector<Point *> Mas, PPL PointOnLine, GetL LineGet, PutL LinePut, FreeL LineDelete)
{
	Line *Greatest = NULL, *zm;
	zm=LineGet();//������� ������ �� ���
	int lich, res = 0;
	for (size_t i = 0; i < Mas.size()-1; i++)
		for (size_t j = i+1; j < Mas.size(); j++)
		{
			LinePut(*Mas[i], *Mas[j], *zm);//��������� ��� 
			lich = 0;
			for(size_t k = i+1; k< Mas.size(); k++)
			{
				if (k != j)//��������� �� ����� �� �������� � ����� � ������ ��
				{
					if (!(PointOnLine(*zm, *Mas[k])))//��������� �� ����� ������ �� ��
						lich++;
				}
			}
			if (lich > res)
			{//��������� �� �� ��� ������ �������� �����
				res = lich;
				Greatest = LineDelete(Greatest);
				Greatest = zm;
				zm = NULL;
				zm = LineGet();
			}//������ ���
		}
	zm = LineDelete(zm);//�������� ���
	return Greatest;
}
//Main
int _tmain(int argc, _TCHAR* argv[])
{
	//���������� �������� �� �������
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
		//��������� ����
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
		if (Cin_file(Mas, name, PointGet, PointDelete))//����� ����
		{//���� �� ������� ��������� �������� ������
			getch();
			return 1;
		}
		cout<< "The greatest area of a triangle is " << BiggestArea(Mas, LineArea, LineGet, LinePut, LineDelete) << endl// ��������� ��������� �������
			<< "The smallest radius f the circumscribing all points " << SmallestRadius(Mas, LineLength, LineGet, LinePut, LineDelete) << endl;// ��������� ��������� ����� ��������� ����
		Line *L;
		L=GreatestLine(Mas, PointOnLine, LineGet, LinePut, LineDelete);//�������� ��� � ��������� ������� ����� �� ��
		cout<< "The segment thet contains the greatest number of point ";
		LineShow(*L);
		L=LineDelete(L);//�������� ���
		cout<< endl << "Scanned following points" << endl;
		for (size_t i=(size_t)0;i<Mas.size();i++)
		{//������� ���� �����
			PointShow(*Mas[i]);
			cout << endl;
		}
		Clear_data(Mas, PointDelete);//�������� �� ����� � �����
	}
	else cout<<"Can not open";//���� �������� �� ��������� ������� ������
	getch();
	return 0;
}


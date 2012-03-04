/*
10.	� ��������� ������ ���� ����� ��� �������� �� ������:  <�����>, <����� ���������>, <г� �������>, <�����>. 
������������ �������� ������ � ������ �������, ������������ ���� �� ������ ������� ��������� �� ������������ �� ����������. 
��������� � ����������� ��� ��� ������� ����� �� ����� � ����� ���������.
*/
//10 ��������
#include <iostream>
#include <conio.h>
using namespace std;
union Marka
{
	char marka[20];
	int slovo[5];
};
//---------------------------------------------------------
struct Avto
{
	Marka marka;
	char nomer[8];
	int vupusk, probig;
};
//---------------------------------------------------------
struct SerProb
{
	Marka marka;
	int probig, lich;
};
//�������� �� ������
unsigned equal(Marka a, Marka b)
{
	for (int i = (unsigned)0;i < 5; ++i)
	{
		if (a.slovo[i] != b.slovo[i])
			return 0;
	}
	return 1;
}
//�������� �� ��������
unsigned no_equal(Marka a, Marka b)
{
	for (unsigned  i = (unsigned)0;i < 5; ++i)
	{
		if (a.slovo[i] != b.slovo[i])
			return 1;
	}
	return 0;
}
//��������� ���������� �����
void start(unsigned s, SerProb* sp)
{
	for (unsigned i = (unsigned)0; i < s; ++i)
	{
		sp[i].marka.marka[0] = '\0';
		sp[i].probig = (int)0;
		sp[i].lich = (int)0;
	}
}
//������ �����
void my_sort(unsigned n, Avto*ap)
{
	for (unsigned i = (unsigned)0; i < n - (unsigned)1; ++i)
	{
		for(unsigned j = i + (unsigned)1; j < n; ++j)//� ���� ��������� �� ��������
		{
			if ( ap[i].vupusk > ap[j].vupusk)//���� ������� ����� �� ��������
			{
				Avto zm = ap[i];
				ap[i] = ap[j];
				ap[j] = zm;//����� ������
			}
		}
	}
}
//������ ������� �����
unsigned unique_car(unsigned n, SerProb* sp, Avto* ap)
{
	unsigned nom = (unsigned)0;
	sp[nom].marka = ap[nom].marka;//������ ���� ����� ������ 
	nom++;
	for (unsigned i = (unsigned)0; i < n; ++i)
	{//��������� ����� ����� ��������� 
		if (no_equal(sp[0].marka, ap[i].marka))
		{//���� ����� ������������ �� �����
			int zm = 0;
			for(unsigned j=(unsigned)1; j < nom; ++j)
			{//� ���� ��������� �� �� ����� �� �������� � ������� 2
				if (equal(ap[i].marka, sp[j].marka))
					zm = 1;
			}
			if (!zm)//���� �� ��������, �������
			{
				sp[nom].marka = ap[i].marka;
				nom++;
			}
		}
	}
	return nom;
}
//������� ������� �����
void average_mileage(unsigned n, unsigned nom, SerProb* sp, Avto* ap)
{
	for (unsigned i = (unsigned)0; i < (unsigned)nom; ++i)
	{
		for(unsigned j = (unsigned)0; j < (unsigned)n; ++j)
		{
			if(equal(sp[i].marka, ap[j].marka))
			{
				sp[i].probig += ap[j].probig;
				sp[i].lich++;
			}
		}
	}
}
//������� ������������ ����� �����
void cout_car(unsigned n, Avto* ap)
{
	for (unsigned i = (unsigned)0; i < n; ++i)
	{
		cout << ap[i].marka.marka << '\t';
		cout << ap[i].nomer << '\t';
		cout << ap[i].vupusk << '\t';
		cout << ap[i].probig << endl;
	}
}
//������� ����� ���������� ������ ���������
void cout_un_car(unsigned nom, SerProb* sp)
{
	for (unsigned i = (unsigned)0; i < nom; ++i)
	{
		cout << sp[i].marka.marka << '\t';
		cout << sp[i].probig/sp[i].lich << endl;
	}
}
int main()
{
	cout << "Enter array size\n";
	unsigned n;
	cin >> n;
	Avto* ap = (Avto*)calloc((size_t)n, sizeof(Avto));
	SerProb* sp = (SerProb*)calloc((size_t)n, sizeof(SerProb));
	start(n, sp);//��������� ����������
	cout << "Enter data in the format \"mark number year run\"\n" ;
	//������� ���
	for (unsigned i = (unsigned)0; i < n; ++i)
	{
		cin >> ap[i].marka.marka;
		cin >> ap[i].nomer;
		cin >> ap[i].vupusk;
		cin >> ap[i].probig;
	}
	my_sort(n, ap);//������ 
	unsigned nom = unique_car(n, sp, ap);
	average_mileage(nom, n, sp, ap);
	cout_car(n, ap);
	free(sp);
	free(ap);
	sp = NULL;
	ap = NULL;
	{
		cin.clear();
		char ch;
		cout<<"Wedit sumvol dla zavershena"<<endl;
		cin>>ch;
	}
	return 0;
}

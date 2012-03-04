/*
10.	З клавіатури ввести набір даних про автомобілі за формою:  <Марка>, <Номер автомобіля>, <Рік випуску>, <Пробіг>. 
Роздрукувати введений список у вигляді таблиці, відсортувавши його за роками випуску автомобілів від найсучасніших до найстаріших. 
Визначити і надрукувати дані про середній пробіг по кожній з марок автомобілів.
*/
//10 завдання
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
//Перевірка на рівність
unsigned equal(Marka a, Marka b)
{
	for (int i = (unsigned)0;i < 5; ++i)
	{
		if (a.slovo[i] != b.slovo[i])
			return 0;
	}
	return 1;
}
//Перевірка на нерівність
unsigned no_equal(Marka a, Marka b)
{
	for (unsigned  i = (unsigned)0;i < 5; ++i)
	{
		if (a.slovo[i] != b.slovo[i])
			return 1;
	}
	return 0;
}
//початкове заповнення нулем
void start(unsigned s, SerProb* sp)
{
	for (unsigned i = (unsigned)0; i < s; ++i)
	{
		sp[i].marka.marka[0] = '\0';
		sp[i].probig = (int)0;
		sp[i].lich = (int)0;
	}
}
//Сортуєм масив
void my_sort(unsigned n, Avto*ap)
{
	for (unsigned i = (unsigned)0; i < n - (unsigned)1; ++i)
	{
		for(unsigned j = i + (unsigned)1; j < n; ++j)//В циклі перевіряєм всі значення
		{
			if ( ap[i].vupusk > ap[j].vupusk)//якщо поточне більше за наступне
			{
				Avto zm = ap[i];
				ap[i] = ap[j];
				ap[j] = zm;//міняєм місцями
			}
		}
	}
}
//Зчитуєм унікальні марки
unsigned unique_car(unsigned n, SerProb* sp, Avto* ap)
{
	unsigned nom = (unsigned)0;
	sp[nom].marka = ap[nom].marka;//зчитуєм пешу марку машини 
	nom++;
	for (unsigned i = (unsigned)0; i < n; ++i)
	{//перевіряєм кожну марку автомобіля 
		if (no_equal(sp[0].marka, ap[i].marka))
		{//якщо марка відрязняється від першої
			int zm = 0;
			for(unsigned j=(unsigned)1; j < nom; ++j)
			{//в циклі перевіряєм чи ця марка не занесина в таблицю 2
				if (equal(ap[i].marka, sp[j].marka))
					zm = 1;
			}
			if (!zm)//якщо не занесина, заносим
			{
				sp[nom].marka = ap[i].marka;
				nom++;
			}
		}
	}
	return nom;
}
//Записуєм середній пробіг
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
//виводим відсортований масив машин
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
//виводим масив середнього пробігу автомобілів
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
	start(n, sp);//початкове заповнення
	cout << "Enter data in the format \"mark number year run\"\n" ;
	//зчитуємо дані
	for (unsigned i = (unsigned)0; i < n; ++i)
	{
		cin >> ap[i].marka.marka;
		cin >> ap[i].nomer;
		cin >> ap[i].vupusk;
		cin >> ap[i].probig;
	}
	my_sort(n, ap);//Сортуєм 
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

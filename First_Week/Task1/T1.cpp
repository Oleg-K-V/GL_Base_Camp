/*
6. Використовуючи тільки бітові операції, написати функцію, яка повертає беззнакове довге ціле число, 
у якому встановлений в 1 лише один біт - у позиції наймолодшого встановленого в 1 біта заданого беззнакового довгого цілого числа (параметра функції).
7. Використовуючи тільки бітові операції, написати функцію, яка міняє місцями усі сусідні біти у заданому беззнаковому довгому цілому числі.
8. Використовуючи тільки бітові операції, написати функцію, яка повертає беззнакове довге ціле число, 
у якому встановлений в 1 лише один біт - у позиції найстаршого очищеного (встановленого в 0) 
біта заданого беззнакового довгого цілого числа (параметра функції).
9. Використовуючи тільки бітові операції, написати функцію, яка встановлює в 1 наймолодший очищений (установлений в 0)
біт у заданому беззнаковому довгому цілому числі.
10. Використовуючи тільки бітові операції, написати функцію, яка очищує (встановлює в 0) найстарший установлений в 1 біт
у заданому беззнаковому довгому цілому числі.
11. Використовуючи тільки бітові та арифметичні операції, написати функцію, яка повертає номер позиції наймолодшого встановленого в 1 біта
у заданому беззнаковому довгому цілому числі (біти нумеруються від 0 справа наліво; можна використати умовний оператор).
12. Використовуючи тільки бітові операції, написати функцію, яка міняє місцями усі сусідні групи з 2-х бітів у заданому беззнаковому довгому
цілому числі.
13. Використовуючи тільки бітові та арифметичні операції, написати функцію, яка повертає кількість одиничних бітів у заданому беззнаковому
довгому цілому числі.
14. Використовуючи тільки бітові та арифметичні операції, написати функцію, яка для заданого беззнакового довгого цілого числа x
повертає значення k=[log2x], тобто 2^k<=x<=2^k+1 (можна використати оператор циклу).
*/
#include <iostream>
#include <bitset>
using namespace std;
//6
unsigned long int clear_first_bit(unsigned long int i)
{
	unsigned long int zm = i;
	i |= i << 1;
	i |= i << 2;
	i |= i << 4;
	i |= i << 8;
	i |= i << 16;
	i ^= i << 1;//дальше ми обнуляєм всі біти крім самого молодшого
	return i;
}
//7
unsigned long int obm_bit(unsigned long int i)
{
	unsigned long int x1, x2, res;
	x1 = (i & 0x55555555);//зчитуєм кожний наступний біт
	x2 = ((i >> 1) & 0x55555555);//зсуваєм на 1 біта в право і зчитуєм кожний наступний біт
	res= ((x1 << 1) | (x2));//обєднуєм результати
	return res;
}
//8
unsigned long int bit_set_first_zero(unsigned long int i)
{
	unsigned long int zm = i;
	i &= ((i >> 1) | 0x80000000);
	i &= ((i >> 2) | 0xC0000000);
	i &= ((i >> 4) | 0xF0000000);
	i &= ((i >> 8) | 0xFF000000);
	i &= ((i >> 16) | 0xFFFF0000);
	i ^= ((i >> 1) ^ 0x80000000);//дальше ми обнуляєм всі біти крім самого старшого
	return i |= zm;//встановлюєм самий старший біт
}
//9
unsigned long int first_bit_set(unsigned long int i)
{
	unsigned long int zm = i;
	i &= ((i << 1) | 1);
	i &= ((i << 2) | 3);
	i &= ((i << 4) | 0xF);
	i &= ((i << 8) | 0xFF);
	i &= ((i << 16) | 0xFFFF);
	i ^= ((i << 1) | 1);//дальше ми обнуляєм всі біти крім самого молодшого
	return i |= zm;//встановлюєм самий молодший біт
}
//10
unsigned long int lost_bit_clear(unsigned long int i)
{
	unsigned long int zm = i;
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
	i |= i >> 16;
	i ^= i >> 1;//дальше ми обнуляєм всі біти крім самого старшого
	i = ~ i;//інвертуємо результат
	return i &= zm;//очищаєм самий старший біт
}
//11
int Per1bit(unsigned long int i, int j)
{
	if (i & 0x00000001)//перевіряєм чи число не 0
		return 1 + j;//модифікуєм номер 0
	else return 2 + j;//модифікуєм номер 1
}
int Per2bit(unsigned long int i, int j)
{
	if (i & 0x00000003)//Перевіряєм чи в перших 2 біт становлено біт
		return Per1bit(i, j);//викликаєм функцію обробки молодших 2-ти біт і кажем що н цьому етапі номер не змінився
	else
	{	
		unsigned long int zm = i >> 2;//зсуваєм число на 2 біт 
		return Per1bit(zm, j + 2);;//викликаєм функцію обробки молодших 2-ти біт і кажем що на цьому етапі номер збільшився на 2
	}
}
int Per4bit(unsigned long int i, int j)
{
	if (i & 0x0000000F)//Перевіряєм чи в перших 4 біт становлено біт
		return Per2bit(i, j);//викликаєм функцію обробки молодших 4-ти біт і кажем що н цьому етапі номер не змінився
	else
	{
		unsigned long int zm = i >> 4;//зсуваєм число на 4 біт 
		return Per2bit(zm, j + 4);;//викликаєм функцію обробки молодших 4-ти біт і кажем що на цьому етапі номер збільшився на 4
	}
}
int Per8bit(unsigned long int i, int j)
{
	if (i & 0x000000FF)//Перевіряєм чи в перших 8 біт становлено біт
		return Per4bit(i, j);//викликаєм функцію обробки молодших 8-ти біт і кажем що н цьому етапі номер не змінився
	else
	{
		unsigned long int zm = i >> 8;//зсуваєм число на 8 біт 
		return Per4bit(zm, j + 8);//викликаєм функцію обробки молодших 8-ти біт і кажем що на цьому етапі номер збільшився на 8
	}
}
int Per16bit(unsigned long int i)
{
	if (i & 0x0000FFFF)//Перевіряєм чи в перших 16 біт становлено біт
		return Per8bit(i, 0);//викликаєм функцію обробки молодших 16-ти біт і кажем що н цьому етапі номер не змінився тобто рівний 0
	else if (( i >> 16) & 0x0000FFFF)//Перевіряєм чи в других 16 біт становлено біт
	{
		unsigned long int zm = i >> 16;//зсуваєм старший біт на 16
		return Per8bit(zm, 16);//викликаєм функцію обробки молодших 16-ти біт і кажем що на цьому етапі номер збільшився на 16
	}
	else return - 1;
}
//12
unsigned long int obm_par_bit(unsigned long int zm)
{
	unsigned long int x1, x2, res;
	x1 = (zm & 0x33333333);//зчитуєм перші пари біт
	x2 = ((zm >> 2) & 0x33333333);//зсуваєм на 2 біта в право і зчитуєм перші пари біт
	res = ((x1 << 2) | (x2));//обєднуєм результати
	return res;
}
//13
int Summa(unsigned long int i)
{
	return (i & 1) + (i >> 1);//сумуємо два молодших біта
}
int dil2(unsigned long int i)
{
	return Summa(i & 0x00000003) + Summa(i >> 2);//сумуємо 4 молодших біта
}
int dil4(unsigned long int i)
{
	return dil2(i & 0x0000000F) + dil2(i >> 4);//сумуємо 8 молодших бітів
}
int dil8(unsigned long int i)
{
	return dil4(i & 0x000000FF) + dil4(i >> 8);//сумуємо 16 молодших біта
}
int dil16(unsigned long int i)
{
	return dil8(i & 0x0000FFFF) + dil8(i >> 16);//сумуємо все слово
}
//14
int Klog(unsigned long int i)
{
	unsigned long int zm = i;
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
	i |= i >> 16;
	i ^= i >> 1;//дальше ми обнуляєм всі біти крім самого старшого
	int j = 0;
	for (; i != 0; i = i >> 1)//зміщаєм старший біт вправо і перевіряєм чи ми не досягли 0
	{
		j++;
	}
	return j;
}
int main()
{
	unsigned long int i = 0;
	bitset<32> chuslo, res;
	cout << "Wedit budlaska chuslo" << endl;
	while(cin >> i && i != 0)
	{
		chuslo = long int(i);
		cout << "10 zavdnja" << endl;
		//10
		res = long int(lost_bit_clear(i));
		cout << "Rezyltatom poshuky i ochushchena samogo starshogo vstanovlenogo chusla taki" << endl
			 << chuslo << " - pochatkoe znachena" << endl
			 << res << " - rezyltat" << endl << endl << endl << endl << "11 zavdnja" << endl;
		//11
		cout << "Rezyltatom poshuky samigo molodshogo vstanovlenogo bita v chusli" << endl
			 << chuslo << "\tje nastupne chuslo ("
			 << Per16bit(i) << ")" << endl << endl << endl << endl << "12 zavdnja" << endl;
		//12
		res = long int(obm_par_bit(i));
		cout << "Rezyltatom obminy par bitiv mischamu, bydyt nastypnumu" << endl
			 << chuslo <<" - pochatkove znachena" << endl
			 << res << " - rezultat" << endl << endl << endl << endl  << "13 zavdnja" << endl;
		//13
		cout << "Rezyltatom summuvanja vsih bit chusla x" << endl
			 << chuslo << "\tbyde nastupnum ("
			 << dil16(i) << ")" << endl << endl << endl << endl << "14 zavdnja" << endl;
		//14
		cout << "Rezyltatom znahodgjenja logarufma k=[log2(x)], chusla " << endl
			 << chuslo << endl
			 << "bude nomer stepeni dviiku zaykryglenoi do nuchogo znachenja ("
			 << Klog(i) << ")" << endl << endl//викликаєм функцію знаходження логарифму log2(i)
			 << "--------------------------------------------------------------------------------"
			 << "Wedit budlaska chuslo" << endl;
	}
	return 0;
}
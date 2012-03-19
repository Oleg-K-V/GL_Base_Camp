#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
//Read data from file, a task 1
//Links to unsigned n and m
//Return 1 if all is well fulfilled
char GetDT(unsigned& n, unsigned& m)
{
	string name("INPUT.TXT");
	ifstream ist(name.c_str());
	char ch = 0;
	n = 0; m = 0;
	ist >> n >>  m >> ch;
	ist.close();
	if (m > 32767 || m < 0 || n > 32767 || n < 0 || ch != 0)
	{
		cout << "Failed to read data\nCheck the "<< name <<" file for correctness";
		return 0;
	}
	return 1;
}
//Write the results to file, a task 1
//Gets const reference to the result
//Retunr void
void SetRes(const unsigned& res)
{
	string name("OUTPUT.TXT");
	ofstream ost(name.c_str());
	ost << res;
	ost.flush();
	if (!ost)
	{
		cout << "Failed to write data\nCheck the " << name << " file for correctness";
	}
	ost.close();
}
//Read data from file, a task 4
//Links to unsigned long res
//Return 1 if all is well fulfilled
char GetDT(unsigned long& res)
{
	string name("INPUT2.TXT");
	ifstream ist(name.c_str());
	char ch = 0;
	res = 0;
	while (ist >> ch)
	{
		if (ch < 48 || ch > 57)
			goto Fail;
		res += (ch - 48);
	}
	if (!res)
		goto Fail;
	return 1;
Fail:cout << "Failed to read data\nCheck the "<< name <<" file for correctness";
	res = 0;
	ist.close();
	return 0;
}
//Write the results to file, a task 4
//Gets const reference to the result and n
//Retunr void
void SetRes(const unsigned char& res, const unsigned char& n)
{
	string name("OUTPUT2.TXT");
	ofstream ost(name.c_str());
	if (res == 2)
		ost << (int)res;
	else ost << (int)res << (int)n;
	ost.flush();
	if (!ost)
	{
		cout << "Failed to write data\nCheck the " << name << " file for correctness";
	}
	ost.close();
}
int main1()
{
	unsigned m = 0, n = 0, res = 0;
	unsigned long num = 0;
	
	if (GetDT(n, m))
	{
		if (n <= m)
			res = n*2-2;
		else res = m*2-1;
		SetRes(res);
	}

	if (GetDT(num))
	{
		num = num%3;
		if (num == 0)
			res = 2;
		else res = 1;
		SetRes((unsigned char)res, (unsigned char)num);
	}
	system("PAUSE");
	return 0;
}


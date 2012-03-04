#include "Matr.h"

int Matr::MatrXYRead(unsigned x, unsigned y, int& p)
{//читаЇм дан≥ з матриц≥
	if (x < this->size && y < this->size)
	{//перев≥р€Їм чи ми не вил≥зли за меж≥ матриц≥
		p = this->matr[y * this->size + x];
		return 0;
	}
	else return 1;
}
//---------------------------------------------------------
unsigned Matr::SizeRead()
	{//читаЇм розм≥р
		return this->size;
	}
//---------------------------------------------------------
int Matr::MatrXYWrite(unsigned x, unsigned y, const int& p)
{//записуЇмо да н≥ в матрицю
	if (x < this->size && y < this->size)
	{//перев≥р€Їм чи не вил≥зли за меж≥ матриц≥
		matr[y * this->size + x] = p;
		return 0;
	}
	else return 1;
}
//---------------------------------------------------------
void Matr::MatrClear()
{
	for(unsigned i = (unsigned)0; i < this->size; ++i)
	{
		this->matr[i] = (unsigned)0;
	}
}
//---------------------------------------------------------
void Matr::Start()
{//‘ункц≥€ запису в матрицю випадеових числ в межах 0-100
	for (unsigned i = (unsigned)0; i < this->size; ++i)
	{
		for (unsigned j = (unsigned)0; j < this->size; ++j)
		{
			int random = rand() % 100;//генеруЇм випадкове число
			if (this->MatrXYWrite(i, j, random))
				goto start1;//в раз≥ помилки покидаЇм функц≥ю
		}
	}
	return;
start1:std::cout << "Error writing\n";
	return;
}
//---------------------------------------------------------
void Matr::End()
{//зчитуЇм дан≥ з матриц≥ в виводим на екран
	for (unsigned i = (unsigned)0;i < this->size; i++)
	{
		for (unsigned j = (unsigned)0; j < this->size; j++)
		{
			int XY;
			if(this->MatrXYRead(i, j, XY))
				goto end1;//в раз≥ помилки зак≥нчуЇм зчитуванн€
			std::cout << XY << '\t';
		}
		std::cout << std::endl;
	}
	return;
end1: std::cout << "Error reading\n";
	return;
}
//---------------------------------------------------------
int Matr::Z10(int n, int &res)
{
	res=0;//ќбнул€Їм результат 
	int Zm1, Zm2;
	for(unsigned i = (unsigned)0; i < this->size; ++i)
	{//¬ цикл≥ знаходим скал€рний добуток
		if (this->MatrXYRead (0, i, Zm1) || this->MatrXYRead(i, i, Zm2))
			goto Z10_1;//якщо виникла помилка зак≥нчуЇм роботу
		else res += (Zm1 * (Zm2 % n));
	}
		return 0;
Z10_1:std::cout << "Error reading\n";
	return 1;
}
//---------------------------------------------------------
int Matr::Z11(int n, int &res)
{
	res=0;//ќбнул€Їм результат
	int Zm1, Zm2;
	for(unsigned i = (unsigned)0; i < this->size; ++i)
	{
		if (this->MatrXYRead(0, i, Zm1) || this->MatrXYRead(i, 0, Zm2))
			goto Z11_1;//якщо виникла помилка зак≥нчуЇм роботу
		else res += (Zm1 * (Zm2 % n));
	}
	return 0;
Z11_1:std::cout << "Error reading\n";
	return 1;
}
//---------------------------------------------------------
int Matr::Z12(int n,int &res)
{
	res = 0;//ќбнул€Їм результат
	int Zm1, Zm2;
	for(unsigned i = (unsigned)0;i < this->size; ++i)
	{
		if (this->MatrXYRead(0, i, Zm1) || this->MatrXYRead(i, this->SizeRead() - 1,Zm2))
			goto Z12_1;//якщо виникла помилка зак≥нчуЇм роботу
		else res += (Zm1 * (Zm2 % n));
	}
	return 0;
Z12_1:std::cout << "Error reading\n";
	return 1;
}
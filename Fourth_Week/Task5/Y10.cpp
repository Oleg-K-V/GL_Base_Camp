/*
10 The specified square matrix of dimension m × 3. Matrix set in the class Matr.
Find the scalar product of the first row of the matrix of m-dimensional vector, each coordinate of which is a balance mod n
of various elements of the diagonal side.
Dimension set in the main program constant. The elements of the matrix are integers.
11 The specified square matrix of dimension m × 3. Matrix set in the class Matr.
Find the scalar product of the first row of the matrix of m-dimensional vector, each coordinate of which is a balance mod n
of various elements of the first column.
Dimension set in the main program constant. The elements of the matrix are integers.
12 The specified square matrix of dimension m × 3. Matrix set in the class Matr.
Find the scalar product of the first row of the matrix of m-dimensional vector, each coordinate of which is a balance mod n
of various elements of the last column.
Dimension set in the main program constant. The elements of the matrix are integers.
*/
#include "Matr.h"
#include <ctime>
#include <conio.h>

void task(Matr *Mas)
{
	std::cout << "Please, enter the number N\n";
	int n = 10;
	int res = 0;
	std::cin >> n;
	//Задача 10
	if(Mas->Z10(n, res))
		std::cout << "Error, calculations are not possible\n";
	else std::cout << "The result of computing tasks 10\n"
				   << res << "\n\n\n";
	//Задача 11
	if(Mas->Z11(n, res))
		std::cout << "Error, calculations are not possible\n";
	else std::cout << "The result of computing tasks 11\n"
				   << res << "\n\n\n";
	//Задача 12
	if(Mas->Z12(n, res))
		std::cout << "Error, calculations are not possible\n";
	else std::cout << "The result of computing tasks 12\n"
				   << res << "\n\n\n";
}

int main()
{
	srand((unsigned)time(0));
	const int size = rand()%10+1;
	Matr *Mas;
	try
	{
		Mas = new Matr(size);
	}
	catch(std::bad_alloc& e)
	{
		std::cout << "Unselected memry\n";
		delete Mas;
		Mas = NULL;
		getch();
		return 1;
	}
	Mas->Start();
	task(Mas);
	Mas->End();
	getch();
	return 0;
}
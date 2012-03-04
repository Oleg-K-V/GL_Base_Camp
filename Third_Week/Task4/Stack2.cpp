/*Используя стек, напечатать символы 
некоторой величины строкового типа в обратном порядке.*/
#include <iostream>
#include <conio.h>
#include <stdarg.h>//підключив для макросів звязаних з функцією з зміною кількістю параметрів
struct Stack
{
	char data;
	Stack *last;
};
struct StackInStack
{
	Stack *slovo;
	StackInStack *last;
};
typedef Stack* (*pS)(Stack*);//створюємо тип вказівник на функцію
//Перевірка на нуль вказівника типу Stack
inline int empty(Stack* stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}
//Перевірка на нуль вказівника типу StackInStack
inline int empty(StackInStack* SIS)
{
	if (SIS == NULL)
		return 1;
	return 0;
}
//очищення стеку типу Stack
inline void Stack_Clear(Stack* stack)
{
	stack->data = (char)'/0';
	stack->last = NULL;
}
//очищення стеку типу StackInStack
inline void StackInStack_Clear(StackInStack* SIS)
{
	SIS->slovo = NULL;
	SIS->last = NULL;
}
//Положити в стек типу Stack
Stack* Stack_push(Stack* stack, char ch)
{
	Stack* new_stack;
	try
	{
		new_stack = new Stack;//виділяєм памятьь під нову вершину стека
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_stack;
		new_stack = NULL;
		return NULL;
	}
	new_stack->last = stack;//кажем що вказівник last вказує на попередню вершину
	new_stack->data = ch;//записуєм дані в нову вершину
	stack = new_stack;//Присвоюю стеку нову вершину
	new_stack = NULL;
	return stack;
}
//Положити в стек типу StackInStack
StackInStack* StackInStack_push(StackInStack* SIS, Stack* stack)
{
	StackInStack* new_SIS;
	try
	{
		new_SIS = new StackInStack;//виділяєм память під новий елемент стеку
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_SIS;
		new_SIS = NULL;
		return NULL;
	}
	new_SIS -> last = SIS;//записуєм адресу попереднього елементу
	new_SIS -> slovo = stack;//зчитуєм адресу слова(стека)
	SIS = new_SIS;//записуєм нову вершину
	new_SIS = NULL;
	return SIS;
}
//Витягнути з стеку типу Stack
Stack* Stack_pop(Stack* stack, char& ch)
{
	if (empty(stack))
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	Stack* del_stack;
	del_stack = stack;//зчитуєм адресу памяті яку потрібно звільнити
	ch = stack->data;//Зчитуєм дані
	stack = stack->last;//кажем вказівнику вказувати на попередній елемент
	Stack_Clear(del_stack);
	delete del_stack;
	del_stack = NULL;
	return stack;
}
//Витягнути з стеку типу StackInStack
StackInStack* StackInStack_pop(StackInStack* SIS, Stack*& stack)
{ 
	if (empty(SIS))
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	StackInStack* del_SIS;
	del_SIS = SIS;//зчитуєм адресу памяті яку потрібно звільнити
	SIS = del_SIS->last;//кажем вказівнику вказувати на попередній елемент
	stack = del_SIS->slovo;//Зчитуєм дані
	StackInStack_Clear(del_SIS);
	delete del_SIS;
	del_SIS = NULL;
	return SIS;
}
//Очищення стека типу Stack
Stack* clear(Stack * stack)
{
	if (empty(stack))
		return NULL;//якщо стек уже пустий виходим
	Stack* del_stack;
	while(1)
	{
		if (!(empty(stack)))//перевіряєм чи не вивільнили весь стек
		{
			del_stack=stack;//зчитуєм адресу памяті яку потрібно звільнити
			stack=stack->last;//кажем вказівнику вказувати на попередній елемент
			Stack_Clear(del_stack);
			delete del_stack;
			del_stack = NULL;
		}
		else 
		{
			Stack_Clear(stack);
			delete stack;
			return NULL;
		}
	}
}
//Очищення стеку типа StackInStack
StackInStack* clear(StackInStack * SIS)
{
	if (empty(SIS))
		return NULL;//якщо стек уже пустий виходим
	StackInStack* del_SIS;
	while(1)
	{
		if (SIS->last != NULL)//перевіряєм чи не вивільнили весь стек
		{
			del_SIS = SIS;//зчитуєм адресу памяті яку потрібно звільнити
			SIS = SIS->last;//кажем вказівнику вказувати на попередній елемент
			del_SIS->slovo = clear(del_SIS->slovo);
			StackInStack_Clear(del_SIS);
			delete del_SIS;
			del_SIS = NULL;
		}
		else 
		{
			StackInStack_Clear(SIS);
			delete SIS;
			return NULL;
		}
	}
}
//Функція виведення результатів стеку типу Stack
Stack* Stack_End(Stack* stack)
{
	if (empty(stack))
		return NULL;//якщо стек уже пустий виходим
	char ch;
	while(1)
	{
		if (stack != NULL)
		{
			stack = Stack_pop(stack, ch);
			std::cout << ch;
		}
		else break;
	}
	return stack;
}
//Функція виведення результатів стеку типа StackInStack
StackInStack* SIS_End(StackInStack* SIS,pS p1)
{
	Stack *stack;
	while(1)
	{
		if (!(empty(SIS)))
		{
			SIS = StackInStack_pop(SIS, stack);
			stack = p1(stack);
			stack = NULL;
			std::cout << ' ';
		}
		else break;
	}
	return SIS;
}
//Видалити з стеку типу Stack
Stack* Stack_delete(Stack* stack)
{
	char ch;
	return Stack_pop(stack, ch);
}
//Видалити з стеку типу StackInStack
StackInStack* StackInStack_delete(StackInStack* SIS)
{
	Stack* stack;
	SIS=StackInStack_pop(SIS, stack);
	stack=clear(stack);
	return SIS;
}
//Записуєм слово в стек типу Stack
Stack* Stack_Plus_Slovo(int i,...)
{
	Stack* stack = NULL;
	va_list p;//оголошую вказівник на початок паретрів
	va_start(p, i);//перекидую вказівник на парамтр наступний після першого
	for(int j = (int)1; j <= i; j++)
	{//зчитую параметри
		char* ch = (char*)p;
		stack = Stack_push(stack, *ch);//парисую парамтр в стек
		va_arg(p, char);//іду до наступного параметра
	}
	va_end(p);//видаляєм вказівник
	return stack;
}
//Точка входу
int main()
{
	Stack* stack = NULL;
	StackInStack *SIS = NULL;//Обнуляєм вказвіники
	pS p1 = Stack_End;
	char ch;
	std::cout << "Please enter sentences\nFor complite enter '.'\n";
	while(std::cin.get(ch))//почергово зчитуєм всі введені символи
	{
		if (isalpha(ch))
		{//перевіряєм чи було введено букву верхнього або нижнього регістра крім ' '
			stack=Stack_push(stack, ch);//заносим символ в стек
		}
		else if (ch == ' ')//перевіряєм чи слово закінчилося
		{
			SIS=StackInStack_push(SIS, stack);//заносимо слово(стек) в стек
			stack = NULL;//зануляєм вказвіник, щоб він нам не спортив занесені дані
		}
		else if (ch == '.')
		{
			SIS = StackInStack_push(SIS, stack);//заносим остане зчитане слово в стек
			stack = Stack_Plus_Slovo(7,':','e','g','n','a','h','C');
			SIS = StackInStack_push(SIS, stack);
			stack = NULL;
			break;//закінчуєм зчитування
		}
	}
	//SIS = StackInStack_clear(SIS,p1);//звільняєм память
	SIS=SIS_End(SIS,p1);
	SIS=clear(SIS);
	std::cout<<std::endl;
	getch();//завершуєм роботу
	return 0;
}

/*
Написать программу, которая определяет, 
является ли введенная скобочная структура правильной. 
Примеры правильных скобочных выражений: 
(), (())(), ()(), ((())), 
неправильных — )(, ())((), (, )))), ((()).
*/
#include <iostream>
#include <conio.h>
struct Stack
{
	char data;
	Stack* last;
};
//Функція занулення
inline Stack* P_Clear()
{
	return NULL;
}
//Перевірка на нуль
inline int empty(Stack* stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}
//очищення стеку 
inline void Stack_Clear(Stack* stack)
{
	stack->data = (char)'/0';
	stack->last = NULL;
}
//Покласти в стак
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
	new_stack = NULL;//зануляє непотрібний вказвіник
	return stack;//повертаєм вказвіник на нову вершину
}
//Витягнути з стеку
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
//Видалити з стеку
inline Stack* Stack_delete(Stack* stack)
{
	char ch;
	return Stack_pop(stack, ch);
}
//очистити стек
Stack* clear(Stack * stack)
{
	if (empty(stack))
		return NULL;//якщо стек уже пустий виходим
	Stack* del_stack;
	while(1)
	{
		if (stack->last != NULL)//перевіряєм чи не вивільнили весь стек
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
//головна функція
int main()
{
	Stack *StackToken = P_Clear();
	std::cout << "To complete the input type 'Q'\n";
	char s;
	while(std::cin >> s)
	{//Зчитуємо дані поки не введуть 'Q'
		if (s == '(')
			StackToken = Stack_push(StackToken, s);//створюєм новий екземпляр стеку
		else if (s == ')')
		{
			if (StackToken == NULL)//перевіряєм чи стек не пустий
			{
				std::cout << "Put too much ')'\n";
				break;
			}
			StackToken = Stack_delete(StackToken);//видаляєм елемент стеку
		}
		else if (s == (char)'Q')//перевіряєм чи не закінчли введення
		{
			if (StackToken == NULL)//перевіряєм чи стек порожній
				std::cout << "All correct\n";
			else
				std::cout << "Put too much '('\n";
			break;
		}
	}
	StackToken = clear(StackToken);//очищаєм стек
	getch();
}

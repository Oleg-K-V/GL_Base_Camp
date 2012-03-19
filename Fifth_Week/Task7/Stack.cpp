#include <iostream>
#include "Stack.h"
size_t Stack::Size()
{
	return size;
}
//Chack in zero
//Takes a pointer to class Stack
//return 1 or 0 
inline int Stack::empty(Stack* stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}
//clear stack
//Takes a pointer to class Stack
//return void
inline void Stack::ClearS(Stack* stack)
{
	stack->P = NULL;
	stack->last = NULL;
	stack->nom = 0;
}
//Write the stack to another pointer
//Takes a pointer to object
//return pointer to the new top stack
Stack* Stack::Push(const type_n& push)
{
	Stack* new_stack;
	try
	{
		new_stack = new Stack();
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_stack;
		new_stack = NULL;
		return this;
	}
	new_stack->last = this;
	new_stack->P = push;
	if (this == NULL)
	{
	new_stack->nom = 0;
	new_stack->size = 1;
	}
	else
	{
	new_stack->nom = this->size;
	new_stack->size = this->size + 1;
	}
	return new_stack;
}
//Extract the stack to another pointer
//Takes a pointer to class Stack and a pointer to object
//return pointer to a new height minus one stack
Stack* Stack::Pop(type_n& pop)
{
	if (empty(this))
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	Stack* del_stack, *stack;
	del_stack = this;
	pop = this->P;
	stack = this->last;
	ClearS(del_stack);
	delete del_stack;
	return stack;
}
//Read item
//Takes a pointer to class Stack and item namber
//return a pointer to object
type_n Stack::ReadS(size_t s)
{
	Stack* stack = this;
	if (s >= size)
	{
		std::cout<< "canТt read " << s << " element" << std::endl;
		return NULL;
	}
	for (int i = (int)size - (int)1 ; i >=0 ; i --)
	{
		if (s == stack->nom)
		{
			return stack->P;
		}
		stack = stack->last;
	}
}
//Clear all Stack
//Takes a pointer to class Stack
//return NULL
Stack* Stack::Clear(Stack * stack)
{
	if (empty(stack))
		return NULL;//€кщо стек уже пустий виходим
	Stack* del_stack;
	while(1)
	{
		if (stack->last != NULL)//перев≥р€Їм чи не вив≥льнили весь стек
		{
			del_stack = stack;//зчитуЇм адресу пам€т≥ €ку потр≥бно зв≥льнити
			stack = stack->last;//кажем вказ≥внику вказувати на попередн≥й елемент
			ClearS(del_stack);
			delete del_stack;
			del_stack = NULL;
		}
		else 
		{
			ClearS(stack);
			stack->size = 0;
			delete stack;
			return NULL;
		}
	}
}

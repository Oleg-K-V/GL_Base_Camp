/*��������� ����, ���������� ������� 
��������� �������� ���������� ���� � �������� �������.*/
#include <iostream>
#include <conio.h>
#include <stdarg.h>//�������� ��� ������� �������� � �������� � ����� ������� ���������
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
typedef Stack* (*pS)(Stack*);//��������� ��� �������� �� �������
//�������� �� ���� ��������� ���� Stack
inline int empty(Stack* stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}
//�������� �� ���� ��������� ���� StackInStack
inline int empty(StackInStack* SIS)
{
	if (SIS == NULL)
		return 1;
	return 0;
}
//�������� ����� ���� Stack
inline void Stack_Clear(Stack* stack)
{
	stack->data = (char)'/0';
	stack->last = NULL;
}
//�������� ����� ���� StackInStack
inline void StackInStack_Clear(StackInStack* SIS)
{
	SIS->slovo = NULL;
	SIS->last = NULL;
}
//�������� � ���� ���� Stack
Stack* Stack_push(Stack* stack, char ch)
{
	Stack* new_stack;
	try
	{
		new_stack = new Stack;//������� ������� �� ���� ������� �����
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_stack;
		new_stack = NULL;
		return NULL;
	}
	new_stack->last = stack;//����� �� �������� last ����� �� ��������� �������
	new_stack->data = ch;//������� ��� � ���� �������
	stack = new_stack;//�������� ����� ���� �������
	new_stack = NULL;
	return stack;
}
//�������� � ���� ���� StackInStack
StackInStack* StackInStack_push(StackInStack* SIS, Stack* stack)
{
	StackInStack* new_SIS;
	try
	{
		new_SIS = new StackInStack;//������� ������ �� ����� ������� �����
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_SIS;
		new_SIS = NULL;
		return NULL;
	}
	new_SIS -> last = SIS;//������� ������ ������������ ��������
	new_SIS -> slovo = stack;//������ ������ �����(�����)
	SIS = new_SIS;//������� ���� �������
	new_SIS = NULL;
	return SIS;
}
//��������� � ����� ���� Stack
Stack* Stack_pop(Stack* stack, char& ch)
{
	if (empty(stack))
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	Stack* del_stack;
	del_stack = stack;//������ ������ ����� ��� ������� ��������
	ch = stack->data;//������ ���
	stack = stack->last;//����� ��������� ��������� �� ��������� �������
	Stack_Clear(del_stack);
	delete del_stack;
	del_stack = NULL;
	return stack;
}
//��������� � ����� ���� StackInStack
StackInStack* StackInStack_pop(StackInStack* SIS, Stack*& stack)
{ 
	if (empty(SIS))
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	StackInStack* del_SIS;
	del_SIS = SIS;//������ ������ ����� ��� ������� ��������
	SIS = del_SIS->last;//����� ��������� ��������� �� ��������� �������
	stack = del_SIS->slovo;//������ ���
	StackInStack_Clear(del_SIS);
	delete del_SIS;
	del_SIS = NULL;
	return SIS;
}
//�������� ����� ���� Stack
Stack* clear(Stack * stack)
{
	if (empty(stack))
		return NULL;//���� ���� ��� ������ �������
	Stack* del_stack;
	while(1)
	{
		if (!(empty(stack)))//��������� �� �� ��������� ���� ����
		{
			del_stack=stack;//������ ������ ����� ��� ������� ��������
			stack=stack->last;//����� ��������� ��������� �� ��������� �������
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
//�������� ����� ���� StackInStack
StackInStack* clear(StackInStack * SIS)
{
	if (empty(SIS))
		return NULL;//���� ���� ��� ������ �������
	StackInStack* del_SIS;
	while(1)
	{
		if (SIS->last != NULL)//��������� �� �� ��������� ���� ����
		{
			del_SIS = SIS;//������ ������ ����� ��� ������� ��������
			SIS = SIS->last;//����� ��������� ��������� �� ��������� �������
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
//������� ��������� ���������� ����� ���� Stack
Stack* Stack_End(Stack* stack)
{
	if (empty(stack))
		return NULL;//���� ���� ��� ������ �������
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
//������� ��������� ���������� ����� ���� StackInStack
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
//�������� � ����� ���� Stack
Stack* Stack_delete(Stack* stack)
{
	char ch;
	return Stack_pop(stack, ch);
}
//�������� � ����� ���� StackInStack
StackInStack* StackInStack_delete(StackInStack* SIS)
{
	Stack* stack;
	SIS=StackInStack_pop(SIS, stack);
	stack=clear(stack);
	return SIS;
}
//������� ����� � ���� ���� Stack
Stack* Stack_Plus_Slovo(int i,...)
{
	Stack* stack = NULL;
	va_list p;//�������� �������� �� ������� �������
	va_start(p, i);//��������� �������� �� ������� ��������� ���� �������
	for(int j = (int)1; j <= i; j++)
	{//������ ���������
		char* ch = (char*)p;
		stack = Stack_push(stack, *ch);//������� ������� � ����
		va_arg(p, char);//��� �� ���������� ���������
	}
	va_end(p);//�������� ��������
	return stack;
}
//����� �����
int main()
{
	Stack* stack = NULL;
	StackInStack *SIS = NULL;//�������� ���������
	pS p1 = Stack_End;
	char ch;
	std::cout << "Please enter sentences\nFor complite enter '.'\n";
	while(std::cin.get(ch))//��������� ������ �� ������ �������
	{
		if (isalpha(ch))
		{//��������� �� ���� ������� ����� ��������� ��� �������� ������� ��� ' '
			stack=Stack_push(stack, ch);//������� ������ � ����
		}
		else if (ch == ' ')//��������� �� ����� ����������
		{
			SIS=StackInStack_push(SIS, stack);//�������� �����(����) � ����
			stack = NULL;//�������� ��������, ��� �� ��� �� ������� ������� ���
		}
		else if (ch == '.')
		{
			SIS = StackInStack_push(SIS, stack);//������� ������ ������� ����� � ����
			stack = Stack_Plus_Slovo(7,':','e','g','n','a','h','C');
			SIS = StackInStack_push(SIS, stack);
			stack = NULL;
			break;//������� ����������
		}
	}
	//SIS = StackInStack_clear(SIS,p1);//�������� ������
	SIS=SIS_End(SIS,p1);
	SIS=clear(SIS);
	std::cout<<std::endl;
	getch();//�������� ������
	return 0;
}

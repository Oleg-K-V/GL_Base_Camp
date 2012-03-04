/*
�������� ���������, ������� ����������, 
�������� �� ��������� ��������� ��������� ����������. 
������� ���������� ��������� ���������: 
(), (())(), ()(), ((())), 
������������ � )(, ())((), (, )))), ((()).
*/
#include <iostream>
#include <conio.h>
struct Stack
{
	char data;
	Stack* last;
};
//������� ���������
inline Stack* P_Clear()
{
	return NULL;
}
//�������� �� ����
inline int empty(Stack* stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}
//�������� ����� 
inline void Stack_Clear(Stack* stack)
{
	stack->data = (char)'/0';
	stack->last = NULL;
}
//�������� � ����
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
	new_stack = NULL;//������� ���������� ��������
	return stack;//�������� �������� �� ���� �������
}
//��������� � �����
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
//�������� � �����
inline Stack* Stack_delete(Stack* stack)
{
	char ch;
	return Stack_pop(stack, ch);
}
//�������� ����
Stack* clear(Stack * stack)
{
	if (empty(stack))
		return NULL;//���� ���� ��� ������ �������
	Stack* del_stack;
	while(1)
	{
		if (stack->last != NULL)//��������� �� �� ��������� ���� ����
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
//������� �������
int main()
{
	Stack *StackToken = P_Clear();
	std::cout << "To complete the input type 'Q'\n";
	char s;
	while(std::cin >> s)
	{//������� ��� ���� �� ������� 'Q'
		if (s == '(')
			StackToken = Stack_push(StackToken, s);//�������� ����� ��������� �����
		else if (s == ')')
		{
			if (StackToken == NULL)//��������� �� ���� �� ������
			{
				std::cout << "Put too much ')'\n";
				break;
			}
			StackToken = Stack_delete(StackToken);//�������� ������� �����
		}
		else if (s == (char)'Q')//��������� �� �� ������� ��������
		{
			if (StackToken == NULL)//��������� �� ���� �������
				std::cout << "All correct\n";
			else
				std::cout << "Put too much '('\n";
			break;
		}
	}
	StackToken = clear(StackToken);//������ ����
	getch();
}

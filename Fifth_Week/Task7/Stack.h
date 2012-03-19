#pragma once
typedef char type_n;
class Stack
{
	type_n P;
	Stack *last;
	size_t nom;
	size_t size;
public:
	Stack():size(0)	{P = NULL;}
	size_t Size();
	inline static int empty(Stack* stack);
	inline void ClearS(Stack* stack);
	Stack* Push(const type_n& push);
	Stack* Pop(type_n& pop);
	type_n ReadS(size_t s);
	Stack* Clear(Stack * stack);
};
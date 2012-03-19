#pragma once 
#include <iostream>
#include "Dll.h"
typedef Point* type_n;
class Stack
{
	type_n P;
	Stack *last;
	size_t nom;
	static size_t size;
public:
	Stack()	{}
	size_t Size();
	inline int empty(Stack* stack);
	inline void ClearS(Stack* stack);
	Stack* Push(Stack* stack, const type_n& push);
	Stack* Pop(Stack* stack, type_n& pop);
	type_n ReadS(Stack* stack, size_t s);
	Stack* Clear(Stack * stack);
};
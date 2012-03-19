#pragma once
#include "Stack.h"
class WStack : private Stack
{
	Stack *stack;
	WStack *wlast;
	size_t wnom;
	size_t wsize;
	void print(int i);
	WStack* Clear();
public:
	WStack():wsize(0){stack = NULL;}
	void WordPlus(const char& ch);
	WStack* WSPlus();
	WStack* Res();
};
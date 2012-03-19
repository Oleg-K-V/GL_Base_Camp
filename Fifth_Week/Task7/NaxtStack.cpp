#include <iostream>
#include "NextStack.h"
//Printout results
//Gets value of nuvbe, or -1 case of errors
//Return void
void WStack::print(int i)
{
	if (i >= 0)
		std::cout << "Binary number equal " << i << std::endl ;
	else std::cout << "The word is not a binary number" << std::endl;
}
//Delete an instance of the WStack
//Gets void
//Return a new peak
WStack* WStack::Clear()
{
	if (this == NULL)
	{
		std::cout << "Yuo can\'t delete an item as the stacj is empty";
		return NULL;
	}
	WStack *del_ws, *WS;
	del_ws = this;
	WS = this->wlast;
	delete del_ws;
	return WS;
}
//Saves the symbol for word
//Gets referens to the symbol
//Return void
void WStack::WordPlus(const char& ch)
{
	this->stack = this->stack->Push(ch);
}
//Selects memory when a new word
//Gers void
//Return a new peak
WStack* WStack::WSPlus()
{
	WStack* new_wstack;
	try
	{
		new_wstack = new WStack();
	}
	catch(std::bad_alloc &e)
	{
		std::cout << "Unselected memry";
		delete new_wstack;
		new_wstack = NULL;
		return this;
	}
	new_wstack->wlast = this;
	new_wstack->stack = NULL;
	if (this == NULL)
	{
		new_wstack->wnom = 0;
		new_wstack->wsize = 1;
	}
	else 
	{
		new_wstack->wnom = this->wsize;
		new_wstack->wsize = this->wsize+1;
	}
	return new_wstack;
}
//Performs word verification, and release the entire WStack
//Gets void
//Return NULL
WStack* WStack::Res()
{
	if (this == NULL)
		return this;
	char ch = 0; int coef = 1, res = 0, WSsize, Ssize;
	WSsize = this->wsize - 1;
	WStack *word = this;
	for (int i = WSsize; i >= 0; i --)
	{	
		if (word->empty(word->stack))
		{
			word = word->Clear();
		}
		else
		{
			Ssize = word->stack->Size() - 1;
			for(int j = Ssize; j >= 0; j --)
			{
				word->stack=word->stack->Pop(ch);
				if (ch == 48 || ch == 49)
				{
					res += coef * (ch % 2);
					coef *= 2;
				}
				else 
				{
					res = - 1;
					break;
				}
			}
			print(res);
			res = 0;
			coef = 1;
			word = word->Clear();
		}
	}
	return word;	
}
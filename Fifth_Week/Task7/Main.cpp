#include <conio.h>
#include <iostream>
#include "NextStack.h"
int main()
{
	char ch;
	WStack *WS = NULL;
	WS = WS->WSPlus();
	while (std::cin.get(ch))
	{//Read teh word entered in the first Enter 
		if (ch == '\n')
			break;
		else if (ch == ' ')
			WS = WS->WSPlus();//Save the sumbol with the word
		else 
			WS->WordPlus(ch);//New word
	}
	WS = WS->Res();//Processing reads
	getch();
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include"FunctionalDLL.h"
#include <stdio.h>
#include <string.h>

extern DWORD __stdcall Dialog()
{
	DWORD i = 0;
	char* str = (char*)calloc(250, sizeof(char));
	printf("What you want to do ? \n");
	printf("(1)Load plugins \n");
	printf("(2)Unload plugins \n");
	printf("(3)Show list of plugins \n");
	printf("(4)Show information about plugins \n");
	printf("(5)Perform the action presented by the plugin \n");
	printf("(6)EXit \n");
	while (TRUE)
	{
		gets(str);
		i = atoi(str);
		if (i > 0 && i <= 6)
			return i;
		printf("Wrong data. Please try again \n");
	}
}
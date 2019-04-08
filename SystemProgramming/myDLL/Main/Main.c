#define _CRT_SECURE_NO_WARNINGS
#include"FunctionalDLL.h"
#include <stdio.h>
#include <string.h> 
#include <windows.h>
#include <tlhelp32.h>

DWORD PrintListOfModules(DWORD dwPID,char** names, int length)
{
	HANDLE hModuleSnap;
	MODULEENTRY32 entry;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of modules) failed with error code = %d \n", GetLastError());
		return 0;
	}
	entry.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &entry))
	{
		printf("Module32First failed with error code = %d \n", GetLastError());
		CloseHandle(hModuleSnap);
		return 0;
	}

	do
	{
		for (int i = 0; i < length; ++i)
		{
			if (strcmp(entry.szModule, names[i]) == 0)
			{
				printf("Name of DLL %s\n ", entry.szModule);
			}
		}
		
	} 
	while (Module32Next(hModuleSnap, &entry));

	CloseHandle(hModuleSnap);
}

VOID printList(char* name,char** names,int length)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 entry;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of processes) failed with error code = %d \n", GetLastError());
		return;
	}
	entry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &entry))
	{
		printf("Process32First failed with error code = %d \n ", GetLastError());
		CloseHandle(hProcessSnap);
		return;
	}
	printf("List of processes in system\n");
	do
	{
		if (strcmp(entry.szExeFile, name) == 0)
		{
			PrintListOfModules(entry.th32ProcessID,names,length);
			break;
		}
	}
	while (Process32Next(hProcessSnap, &entry));

	CloseHandle(hProcessSnap);
}

void main()
{
	int length = 2;
	char** list = (char**)calloc(2, sizeof(char*));
	list[0]= (char*)calloc(200, sizeof(char));
	list[1] = (char*)calloc(200, sizeof(char));
	strcpy(list[0], "FirstDLL.dll");
	strcpy(list[1], "SecondDLL.dll");
	HMODULE hFDLL=NULL;
	HMODULE hSDLL=NULL;
//	LPSTR str;
	DWORD read = 0;
	DWORD sizeBuffer = 250;
	DWORD temp;
	DWORD firstLoad = 0;
	DWORD secondLoad = 0;
	while (TRUE)
	{
		temp = Dialog();
		switch (temp)
		{
		case 1:
		{
			BOOLEAN flag = TRUE;
			DWORD i = 0;
			char* str = (char*)calloc(250, sizeof(char));
			printf("\nWhich libary do you want to load ? \n");
			printf("(1)First \n");
			printf("(2)Second \n");
			printf("(3)Both \n");
			while (flag)
			{
				gets(str);
				i = atoi(str);
				if (i > 0 && i <= 3)
					flag = FALSE;
				else		
					printf("Wrong data. Please try again \n");
			}
			free(str);
			switch (i)
			{
			case 1:
			{
				if (firstLoad == 0)
				{
					hFDLL= LoadLibrary("FirstDLL.dll");
					firstLoad = 1;
					printf("You have successfully loaded DLL\n");
				}
				else
					printf("This DLL already loaded \n");
				break;
			}
			case 2:
			{
				if (secondLoad == 0)
				{
					hSDLL = LoadLibrary("SecondDLL.dll");
					secondLoad = 1;
					printf("You have successfully loaded DLL\n");
				}
				else
					printf("This DLL already loaded \n");
				break;
			}
			case 3:
			{

				if (secondLoad == 0 && firstLoad == 0)
				{
					hFDLL = LoadLibrary("FirstDLL.dll");
					hSDLL = LoadLibrary("SecondDLL.dll");
					firstLoad = 1;
					secondLoad = 1;
					printf("You have successfully loaded DLLs\n");
				}
				else
					printf("One of this or both DLLs already loaded \n");
				break;
			}
			}
			system("pause");
			break;
		}
		case 2:
		{
			BOOLEAN flag = TRUE;
			DWORD i = 0;
			char* str = (char*)calloc(250, sizeof(char));
			printf("\nWhich libary do you want to unload ? \n");
			printf("(1)First \n");
			printf("(2)Second \n");
			printf("(3)Both \n");
			while (flag)
			{

				gets(str);
				i = atoi(str);
				if (i > 0 && i <= 3)
					flag = FALSE;
				else
					printf("Wrong data. Please try again \n");
			}
			free(str);
			switch (i)
			{
			case 1:
			{
				if (firstLoad == 1)
				{
					FreeLibrary(hFDLL);
					firstLoad = 0;
					printf("You have successfully unloaded DLL\n");
				}
				else
					printf("This DLL already unloaded \n");
				break;
			}
			case 2:
			{
				if (secondLoad == 1)
				{
					FreeLibrary(hSDLL);
					secondLoad = 0;
					printf("You have successfully unloaded DLL\n");
				}
				else
					printf("This DLL already unloaded \n");
				break;
			}
			case 3:
			{

				if (secondLoad == 1 && firstLoad == 1)
				{
					FreeLibrary(hFDLL);
					FreeLibrary(hSDLL);
					firstLoad = 0;
					secondLoad = 0;
					printf("You have successfully unloaded DLLs\n");
				}
				else
					printf("One of this or both DLLs already unloaded \n");
				break;
			}
			}
			system("pause");
			break;
		}
		case 3:
		{

			printList("Main.exe",list,length);
			system("pause");
			break;
		}
		case 4:
		{
			char* str = (char*)calloc(250, sizeof(char));
			printf("\nWhich information do you need ? \n");
			printf("(1)About FirtstDLL \n");
			printf("(2)About SecondDLL \n");
			gets(str);
			int d = atoi(str);
			free(str);
			switch (d)
			{
			case 1:
			{
				if (firstLoad == 1)
				{
					DWORD sizeBuffer = 250;
					LPSTR name = (LPSTR)calloc(sizeBuffer, sizeof(char));
					LPSTR description = (LPSTR)calloc(sizeBuffer, sizeof(char));
					DWORD lol = 0;
					BOOLEAN(*pFunctionF)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
					pFunctionF = (BOOLEAN(*) (LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)) GetProcAddress(hFDLL, "GetAuthor");
					pFunctionF(name, sizeBuffer, &lol);
					BOOLEAN(*pFunctionS)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
					pFunctionS = (BOOLEAN(*) (LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)) GetProcAddress(hFDLL, "GetDescription");
					pFunctionS(description, sizeBuffer, &lol);
					printf("Name of DLL %s \n", list[0]);
					printf("Name of author %s \n", name);
					printf("Descripton %s \n", description);
				}
				else
					printf("This DLL in unload\n");
				break;
			}
			case 2:
			{
				if (secondLoad == 1)
				{
					DWORD sizeBuffer = 250;
					LPSTR name = (LPSTR)calloc(sizeBuffer, sizeof(char));
					LPSTR description = (LPSTR)calloc(sizeBuffer, sizeof(char));
					DWORD lol = 0;
					BOOLEAN(*pFunctionF)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
					pFunctionF = (BOOLEAN(*) (LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)) GetProcAddress(hSDLL, "GetAuthor");
					pFunctionF(name,sizeBuffer,&lol);
					BOOLEAN(*pFunctionS)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
					pFunctionS = (BOOLEAN(*) (LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)) GetProcAddress(hSDLL, "GetDescription");
					pFunctionS(description, sizeBuffer,&lol);
					printf("Name of DLL %s \n", list[1]);
					printf("Name of author %s \n", name);
					printf("Descripton %s \n", description);
				}
				else
					printf("This DLL in unload\n");
				break;
			}
			default:
			{
				printf("There is no such option\n");
			}
			}
			system("pause");
			break;
		}
		case 5:
		{
			char* str = (char*)calloc(250, sizeof(char));
			printf("\nWhich action you want to perfom ? \n");
			printf("(1)From FirtstDLL \n");
			printf("(2)From SecondDLL \n");
			gets(str);
			int d = atoi(str);
			free(str);
			switch (d)
			{
			case 1:
			{
				if (firstLoad == 1)
				{
					void(*pFunctionF)();
					pFunctionF = (void(*) ()) GetProcAddress(hFDLL, "Execute");
					pFunctionF();
				}
				else
					printf("This DLL in unload\n");
				break;
			}
			case 2:
			{
				if (secondLoad == 1)
				{
					void(*pFunctionF)();
					pFunctionF = (void(*) ()) GetProcAddress(hSDLL, "Execute");
					pFunctionF();
				}
				else
					printf("This DLL in unload\n");
				break;
			}
			default:
			{
				printf("There is no such option\n");
			}
			}
			system("pause");
			break;
		}
		case 6:
		{
			return;
		}
		}
	}
	
}
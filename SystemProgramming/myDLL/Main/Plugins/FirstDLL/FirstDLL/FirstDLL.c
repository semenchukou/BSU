#include"FirstDLL.h"
#include <stdio.h>
#include <string.h> 
#include <tlhelp32.h>

extern BOOLEAN __cdecl GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	LPSTR name = "Alex";
	int i = 0;
	DWORD sizeName = (DWORD)strlen(name);
	while (i < sizeName && i < dwBufferSize)
	{
		buffer[i] = name[i];
		++i;
	}
	*pdwBytesWritten = i;
	if (i == sizeName)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

extern BOOLEAN __cdecl GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	LPSTR description = "Returns names of all processes in the system";
	int i = 0;
	DWORD sizeDName = (DWORD)strlen(description);
	while (i < sizeDName && i < dwBufferSize)
	{
		buffer[i] = description[i];
		++i;
	}
	*pdwBytesWritten = i;
	if (i == sizeDName)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

extern VOID __cdecl Execute()
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
		printf("PROCESS NAME:  %s \n", entry.szExeFile);
	}
	while (Process32Next(hProcessSnap, &entry));

	CloseHandle(hProcessSnap);
	return;
}
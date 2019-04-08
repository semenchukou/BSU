#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

#define MAXLENGTH 250													

HANDLE GetProcessHandle(char* process_name)
{
	DWORD processID = 0;
	HANDLE snapHandle;
	PROCESSENTRY32 processEntry;
	if ((snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of processes) failed with error code  %d \n", GetLastError());
		CloseHandle(snapHandle);
		return NULL;
	}

	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapHandle, &processEntry))
	{
		do 
		{
			if (strcmp(processEntry.szExeFile, process_name) == 0)
			{
				return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);
			}
		} 
		while (Process32Next(snapHandle, &processEntry));
	}
	else
	{
		printf("Process32First failed with error code  %d \n ", GetLastError());
		return NULL;
	}
	return NULL;
}

void SendAdress(DWORD szAdress)
{
	HANDLE hNamedPipe;
	DWORD dwBytesWritten;
	LPCWSTR pipeName = TEXT("\\\\.\\pipe\\mynamedpipe");
	hNamedPipe = CreateFile(pipeName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);//разрешение писать, разрешает тому читать,
	//открывате существующий

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed with error code  %d \n", GetLastError());
		return ;
	}
	

	printf("Wating for server read data...\n");
	if (!WriteFile(hNamedPipe, &szAdress, sizeof(szAdress), &dwBytesWritten, NULL))	
	{
		printf("Writing to the named pipe failed with error code %d\n", GetLastError());
		CloseHandle(hNamedPipe);
		return ;
	}
	CloseHandle(hNamedPipe);
	printf("Process_B read data.\n");
	return ;
}


void main()
{
	DWORD szSize = sizeof(char) * MAXLENGTH;
	char *a = (char*)malloc(szSize);
	printf("Input text: ");
	gets_s(a, MAXLENGTH - 1);
	HANDLE hProcess = GetProcessHandle("Process_B.exe");//указатель на процесс запущенный
	LPVOID szAddress = VirtualAllocEx(hProcess, NULL, szSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);//дальний указатель на что-угодно
	//изменение виртуальной памяти процессе, null - ф-я сама ищет где память изменять(первые попавшиеся ячейки), обьем памяти в байтах выделяется, мем ресерв
	//выделяет виртуальную память без изменения физической, комит распределяет по нескольким кускам памяти и гарантирует что туда не запишется мусор, ридрайт
	//для чтения и записи
	WriteProcessMemory(hProcess, szAddress, a, szSize, NULL);//в том процуссу, такая память, строка, макс размер
	SendAdress((DWORD)szAddress);
	free(a);
	VirtualFreeEx(hProcess, szAddress, 0, MEM_RELEASE);
	system("pause");
}
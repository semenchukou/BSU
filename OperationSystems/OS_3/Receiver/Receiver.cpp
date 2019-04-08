#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <mutex>

using namespace std;

#define CONSTS_SIZE 16
#define MESSAGE_SIZE 20

HANDLE hFullSemaphore, hEmptySemaphore;
HANDLE hMutex;

char* pop(FILE* file)
{
	int curr_size = 0;
	int max_size = 0;
	int front, rear;
	char* msg = (char*)malloc(sizeof(char) * MESSAGE_SIZE);

	fseek(file, 0, SEEK_SET);
	fread(&curr_size, sizeof(int), 1, file);
	fread(&max_size, sizeof(int), 1, file);
	fread(&front, sizeof(int), 1, file);
	fread(&rear, sizeof(int), 1, file);

	if (!curr_size) {
		printf("\nQueue is empty\n");
		free(msg);
		return NULL;
	}
	fseek(file, front, SEEK_SET);
	fread(msg, sizeof(char), MESSAGE_SIZE, file);

	if (front == (max_size - 1) * MESSAGE_SIZE + CONSTS_SIZE)
		front = CONSTS_SIZE;
	else
		front += MESSAGE_SIZE;
	curr_size--;

	fseek(file, 0, SEEK_SET);
	fwrite(&curr_size, sizeof(int), 1, file);
	fwrite(&max_size, sizeof(int), 1, file);
	fwrite(&front, sizeof(int), 1, file);
	fwrite(&rear, sizeof(int), 1, file);
	fflush(file);
	return msg;
	//free(msg);
}

//void read(FILE* file)
//{
//	while (true)
//	{
//		WaitForSingleObject(hFullSemaphore, INFINITE);
//		WaitForSingleObject(hMutex, INFINITE);
//		char* message = pop(file);
//		ReleaseMutex(hMutex);
//		ReleaseSemaphore(hEmptySemaphore, 1, NULL);
//		if (message == NULL)
//			Sleep(2000);
//		else 
//			cout << message << endl;
//	}
//}

int main(int argc, char *argv[])
{
	int amount = atoi(argv[2]);
	STARTUPINFO *si = new STARTUPINFO[amount];
	PROCESS_INFORMATION *piCom = new PROCESS_INFORMATION[amount];
	HANDLE *hInEvent = new HANDLE[amount];
	int curr_size = 0;
	int max_size = 5;
	FILE* file = fopen(argv[1], "wb+");
	int front = CONSTS_SIZE - 1, rear = CONSTS_SIZE;
	fwrite(&curr_size, sizeof(curr_size), 1, file);
	fwrite(&max_size, sizeof(max_size), 1, file);
	fwrite(&front, sizeof(front), 1, file);
	fwrite(&rear, sizeof(rear), 1, file);

	hFullSemaphore = CreateSemaphore(NULL, max_size, max_size, "fullSemaphore");
	hEmptySemaphore = CreateSemaphore(NULL, max_size, max_size, "emptySemaphore");
	hMutex = CreateMutex(NULL, FALSE, "mutex");
	for (int i = 0; i < amount; i++)
	{
		string name_event = to_string(i);
		char *lpEventName = _strdup(name_event.c_str());
		string path = "C:\\Users\\Alex\\source\\repos\\OS_3\\Debug\\Sender.exe " + string(argv[1]) + " " + name_event;
		char *lpszCommandLine = _strdup(path.c_str());
		ZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		hInEvent[i] = CreateEvent(NULL, FALSE, FALSE, lpEventName);
		CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si[i], &piCom[i]);
		if (hInEvent[i] == NULL)
			return GetLastError();
	}
	WaitForMultipleObjects(amount, hInEvent, TRUE, INFINITE);
	//read(file);
	while (true)
	{
		WaitForSingleObject(hFullSemaphore, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		char* message = pop(file);
		ReleaseMutex(hMutex);
		ReleaseSemaphore(hEmptySemaphore, 1, NULL);
		if (message != NULL)
			cout << message << endl;
		Sleep(100);
	}
	for (int i = 0; i < amount; i++)
	{
		CloseHandle(hInEvent[i]);
		CloseHandle(piCom[i].hThread);
		CloseHandle(piCom[i].hProcess);
	}
	fclose(file);
	system("pause");
	return 0;
}
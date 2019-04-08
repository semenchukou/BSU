#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <mutex>
#include <cstring>

using namespace std;

#define CONSTS_SIZE 16
#define MESSAGE_SIZE 20

HANDLE hInEvent;
HANDLE hFullSemaphore, hEmptySemaphore;
HANDLE hMutex;

void push(FILE* file, const char* msg)
{
	int curr_size = 0;
	int max_size = 0;
	int front, rear;

	fseek(file, 0, SEEK_SET);
	fread(&curr_size, sizeof(int), 1, file);
	fread(&max_size, sizeof(int), 1, file);
	fread(&front, sizeof(int), 1, file);
	fread(&rear, sizeof(int), 1, file);

	if ((curr_size == max_size))
	{
		//printf("\nQueue is full\n");
		return;
	}
	else if (front == CONSTS_SIZE - 1)
	{
		front = rear = CONSTS_SIZE;
		fseek(file, CONSTS_SIZE, SEEK_SET);
		fwrite(msg, sizeof(char), MESSAGE_SIZE, file);
		rear += MESSAGE_SIZE;
	}
	else if (rear + MESSAGE_SIZE == CONSTS_SIZE + MESSAGE_SIZE * max_size)
	{
		fseek(file, rear, SEEK_SET);
		fwrite(msg, sizeof(char), MESSAGE_SIZE, file);
		rear = CONSTS_SIZE;
	}
	else {
		fseek(file, rear, SEEK_SET);
		fwrite(msg, sizeof(char), MESSAGE_SIZE, file);
		rear += MESSAGE_SIZE;
	}
	curr_size++;
	printf("%s\t", msg);
	fseek(file, 0, SEEK_SET);
	fwrite(&curr_size, sizeof(int), 1, file);
	fwrite(&max_size, sizeof(int), 1, file);
	fwrite(&front, sizeof(int), 1, file);
	fwrite(&rear, sizeof(int), 1, file);
	fflush(file);
}

char* generateMessage(int number)
{
	srand(time(NULL));
	string temp;
	temp += "Sender";
	temp += to_string(number);
	return _strdup(temp.c_str());
}

//void write(FILE* file)
//{
//	while (true)
//	{
//		char* message = (char*)malloc(MESSAGE_SIZE);
//		message = generateMessage();
//		WaitForSingleObject(hEmptySemaphore, INFINITE);
//		WaitForSingleObject(hMutex, INFINITE);
//		int result = push(file, message);
//		
//		ReleaseMutex(hMutex);
//		ReleaseSemaphore(hFullSemaphore, 1, NULL);
//		if (result == 0)
//			Sleep(15);
//	}
//}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	hInEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, argv[2]);
	int event_number = atoi(argv[2]);
	//cout << event_number << endl;
	if (hInEvent == NULL)
	{
		cout << GetLastError() << "\n";
		return 1;
	}
	
	FILE* file = fopen(argv[1], "wb+");

	SetEvent(hInEvent);
	
	hFullSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "fullSemaphore");
	hEmptySemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "emptySemaphore");
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mutex");

	//write(file);
	while (true)
	{
		char* message = (char*)malloc(MESSAGE_SIZE);
		message = generateMessage(event_number);
		WaitForSingleObject(hEmptySemaphore, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		push(file, message);
		ReleaseMutex(hMutex);
		Sleep(1500);
		ReleaseSemaphore(hFullSemaphore, 1, NULL);
	}
	CloseHandle(hInEvent);
	fclose(file);
	return 0;
}
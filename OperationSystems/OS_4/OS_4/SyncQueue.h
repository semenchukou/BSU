#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h>

class SyncQueue
{
private:
	int size;
	int current_size;
	int *array;
	int front, rear;
	//HANDLE hWriteSemaphore;
	HANDLE hFullSemaphore, hEmptySemaphore;
	HANDLE hMutex;
	//int readerCount;
public:
	SyncQueue(int nSize);
	void insert(int nElement);
	int remove();
	void print();
	~SyncQueue();
};


#include "SyncQueue.h"

SyncQueue::SyncQueue(int nSize)
{
	size = nSize;
	current_size = 0;
	front = 0;
	rear = 0;
	//readerCount = 0;
	array = new int[size]();
	//hWriteSemaphore = CreateSemaphore(NULL, 1, 1, "writeSemaphore");
	hFullSemaphore = CreateSemaphore(NULL, size, size, "fullSemaphore");
	hEmptySemaphore = CreateSemaphore(NULL, size, size, "emptySemaphore");
	hMutex = CreateMutex(NULL, FALSE, "mutex");
}

SyncQueue::~SyncQueue()
{
}

//void SyncQueue::insert(int nElement)
//{
//	while (current_size == size)
//	{
//		Sleep(200);
//	}
//	WaitForSingleObject(hWriteSemaphore, INFINITE);
//	
//	if (current_size == 0)
//	{
//		array[0] = nElement;
//		rear = 1;
//	}
//	else if (rear + 1 == size)
//	{
//		array[size - 1] = nElement;
//		rear = 0;
//	}
//	else 
//	{
//		array[rear] = nElement;
//		rear++;
//	}
//	current_size++;
//	ReleaseSemaphore(hWriteSemaphore, 1, NULL);
//}
//
//int SyncQueue::remove()
//{
//	while (!current_size)
//	{
//		Sleep(200);
//	}
//	WaitForSingleObject(hMutex, INFINITE);
//	readerCount++;
//	if (readerCount == 1)
//	{
//		WaitForSingleObject(hWriteSemaphore, INFINITE);
//	}
//	ReleaseMutex(hMutex);
//	int msg = array[front];
//	if (front == size - 1)
//		front = 0;
//	else
//		front++;
//	current_size--;
//	WaitForSingleObject(hMutex, INFINITE);
//	readerCount--;
//	if (readerCount == 0)
//	{
//		ReleaseSemaphore(hWriteSemaphore, 1, NULL);
//	}
//	ReleaseMutex(hMutex);
//	return msg;
//}
void SyncQueue::insert(int nElement)
{
	while (current_size == size)
	{
		Sleep(200);
	}
	WaitForSingleObject(hEmptySemaphore, INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	if (current_size == 0)
	{
		array[0] = nElement;
		front = 0;
		rear = 1;
	}
	else if (rear + 1 == size)
	{
		array[size - 1] = nElement;
		rear = 0;
	}
	else
	{
		array[rear] = nElement;
		rear++;
	}
	current_size++;
	ReleaseMutex(hMutex);
	ReleaseSemaphore(hFullSemaphore, 1, NULL);
}

int SyncQueue::remove()
{
	while (!current_size)
	{
		Sleep(200);
	}
	WaitForSingleObject(hFullSemaphore, INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	int msg = array[front];
	if (front == size - 1)
		front = 0;
	else
		front++;
	current_size--;
	ReleaseMutex(hMutex);
	ReleaseSemaphore(hEmptySemaphore, 1, NULL);
	return msg;
}

void SyncQueue::print()
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
}
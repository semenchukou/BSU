#include "SyncQueue.h"

using namespace std;

HANDLE hAddEvent;
HANDLE *hInEventConsumer;
HANDLE *hInEventProducer;
SyncQueue *q;
CRITICAL_SECTION cs;

DWORD WINAPI Consumer(LPVOID lpParam)
{
	int id = *static_cast<int*>(lpParam);
	int amount;
	EnterCriticalSection(&cs);
	cout << "Enter the amount of numbers to execute for " << id << " consumer: ";
	cin >> amount;
	LeaveCriticalSection(&cs);
	SetEvent(hInEventConsumer[id]);
	WaitForSingleObject(hAddEvent, INFINITE);
	for (int i = 0; i < amount; i++)
	{
		int msg = q->remove();
		EnterCriticalSection(&cs);
		printf("\tDeleted msg = %d, consumer id %d\n", msg, id);
		LeaveCriticalSection(&cs);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI Producer(LPVOID lpParam)
{
	int id = *static_cast<int*>(lpParam);
	int amount;
	int number;
	EnterCriticalSection(&cs);
	cout << "Enter the amount of numbers to produce for " << id << " producer and the number: ";
	cin >> amount >> number;
	LeaveCriticalSection(&cs);
	SetEvent(hInEventProducer[id]);
	WaitForSingleObject(hAddEvent, INFINITE);
	for (int i = 0; i < amount; i++)
	{
		q->insert(number);
		EnterCriticalSection(&cs);
		printf("Producer %d, written msg = %d, iteration %d\n", id, number, i);
		//q->print();
		//printf("\n");
		LeaveCriticalSection(&cs);
		Sleep(500);
	}
	return 0;
}

int main()
{
	int amount_consumer, amount_producer, qSize;
	
	cout << "Enter the queue size: ";
	cin >> qSize;
	q = new SyncQueue(qSize);
	cout << "Enter the emount of consumers: ";
	cin >> amount_consumer;
	cout << "Enter the emount of producers: ";
	cin >> amount_producer;

	InitializeCriticalSection(&cs);
	HANDLE *hThreadConsumer = new HANDLE[amount_consumer];
	HANDLE *hThreadProducer = new HANDLE[amount_producer];
	DWORD *IDThreadConsumer = new DWORD[amount_consumer];
	DWORD *IDThreadProducer = new DWORD[amount_producer];
	hInEventConsumer = new HANDLE[amount_consumer];
	hInEventProducer = new HANDLE[amount_producer];
	
	for (int i = 0; i < amount_consumer; i++)
	{
		int* id = new int(i);
		hInEventConsumer[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hThreadConsumer[i] = CreateThread(NULL, 0, Consumer, id, 0, &IDThreadConsumer[i]);
		if (hInEventConsumer[i] == NULL)
			return GetLastError();
	}

	for (int i = 0; i < amount_producer; i++)
	{
		int* id = new int(i);
		hInEventProducer[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hThreadProducer[i] = CreateThread(NULL, 0, Producer, id, 0, &IDThreadProducer[i]);
		if (hInEventProducer[i] == NULL)
			return GetLastError();
	}

	WaitForMultipleObjects(amount_consumer, hInEventConsumer, TRUE, INFINITE);
	WaitForMultipleObjects(amount_producer, hInEventProducer, TRUE, INFINITE);
	
	hAddEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hAddEvent == NULL)
		return GetLastError();

	WaitForMultipleObjects(amount_consumer, hThreadConsumer, TRUE, INFINITE);
	WaitForMultipleObjects(amount_producer, hThreadProducer, TRUE, INFINITE);

	DeleteCriticalSection(&cs);
	for (int i = 0; i < amount_consumer; i++)
	{
		CloseHandle(hThreadConsumer[i]);
		CloseHandle(hInEventConsumer[i]);
	}
	for (int i = 0; i < amount_producer; i++)
	{
		CloseHandle(hThreadProducer[i]);
		CloseHandle(hInEventProducer[i]);
	}
	CloseHandle(hAddEvent);
	//q->print();
	system("pause");
}
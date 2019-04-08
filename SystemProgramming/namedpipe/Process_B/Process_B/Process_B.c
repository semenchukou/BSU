#include <stdio.h>
#include <windows.h> 

int main() 
{
	LPCWSTR pipeName = TEXT("\\\\.\\pipe\\mynamedpipe"); 
	HANDLE hNamedPipe;
	DWORD address;
	DWORD dwBytesRead;

	hNamedPipe = CreateNamedPipe(//пайп для передачи данных между параллельными
		pipeName,
		PIPE_ACCESS_INBOUND, //в одну сторону
		PIPE_TYPE_MESSAGE | // всообщении а не байтах
		PIPE_READMODE_MESSAGE | //читает
		PIPE_WAIT,//ждет пока не напишешь
		1,//колво сообщений
		sizeof(DWORD),
		sizeof(DWORD),
		1,//время ожидания для введения
		NULL);//нельзя унаслеовать
	
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		printf("Can't create name pipe.\n");
		return 1;
	}
	printf("Wating Process_A write data!\n");
	ConnectNamedPipe(hNamedPipe, NULL);//соединение со второй стороной

	ReadFile(hNamedPipe,//откуда
		&address, //куда
		sizeof(address),//сколько максимум
		&dwBytesRead,// сколько байт на самом деле
		NULL);
	
	printf("Text get: %s\n", (char*)address);
	CloseHandle(hNamedPipe);
	system("pause");
	return 0;
}
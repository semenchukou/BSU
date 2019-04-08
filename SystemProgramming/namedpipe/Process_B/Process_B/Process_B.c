#include <stdio.h>
#include <windows.h> 

int main() 
{
	LPCWSTR pipeName = TEXT("\\\\.\\pipe\\mynamedpipe"); 
	HANDLE hNamedPipe;
	DWORD address;
	DWORD dwBytesRead;

	hNamedPipe = CreateNamedPipe(//���� ��� �������� ������ ����� �������������
		pipeName,
		PIPE_ACCESS_INBOUND, //� ���� �������
		PIPE_TYPE_MESSAGE | // ���������� � �� ������
		PIPE_READMODE_MESSAGE | //������
		PIPE_WAIT,//���� ���� �� ��������
		1,//����� ���������
		sizeof(DWORD),
		sizeof(DWORD),
		1,//����� �������� ��� ��������
		NULL);//������ �����������
	
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		printf("Can't create name pipe.\n");
		return 1;
	}
	printf("Wating Process_A write data!\n");
	ConnectNamedPipe(hNamedPipe, NULL);//���������� �� ������ ��������

	ReadFile(hNamedPipe,//������
		&address, //����
		sizeof(address),//������� ��������
		&dwBytesRead,// ������� ���� �� ����� ����
		NULL);
	
	printf("Text get: %s\n", (char*)address);
	CloseHandle(hNamedPipe);
	system("pause");
	return 0;
}
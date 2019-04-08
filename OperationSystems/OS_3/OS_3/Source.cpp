#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define CONSTS_SIZE 16
#define MESSAGE_SIZE 20

void push(FILE* file, const char* msg);
char* pop(FILE* file);
void print(FILE* file);

int main(int argc, char* argv[])
{
	/*if (argc != 2) {
		printf("Invalid number of parameters");
		return -1;
	}*/

	const char* filename_str = "binary.bin";
	int curr_size = 0;
	int max_size = 3;
	int front = CONSTS_SIZE - 1, rear = CONSTS_SIZE;

	FILE* file = fopen(filename_str, "wb+");

	fwrite(&curr_size, sizeof(curr_size), 1, file);
	fwrite(&max_size, sizeof(max_size), 1, file);
	fwrite(&front, sizeof(front), 1, file);
	fwrite(&rear, sizeof(rear), 1, file);

	char push_test[10];
	for (int i = 0; i < 3; i++)
	{
		_itoa(i, push_test, 10);
		push(file, push_test);
		print(file);
		printf("\n");
	}
	for (int i = 0; i < 2; i++)
	{
		pop(file);
		print(file);
		printf("\n");
	}
	for (int i = 10; i < 12; i++)
	{
		_itoa(i, push_test, 10);
		push(file, push_test);
		print(file);
		printf("\n");
	}
	print(file);

	fclose(file);
	system("pause");
	return 0;
}

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
		printf("\nQueue is full");
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

	fseek(file, 0, SEEK_SET);
	fwrite(&curr_size, sizeof(int), 1, file);
	fwrite(&max_size, sizeof(int), 1, file);
	fwrite(&front, sizeof(int), 1, file);
	fwrite(&rear, sizeof(int), 1, file);

}

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
		printf("\nQueue is empty");
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
	return msg;
	//free(msg);
}

void print(FILE* file)
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

	printf("\nThe current number of elements is: %d", curr_size);
	printf("\nThe current number of elements is: %d", max_size);

	fseek(file, front, SEEK_SET);
	if (front < rear)
	{
		while (front < rear)
		{
			fread(msg, sizeof(char), MESSAGE_SIZE, file);
			printf("\n %s ", msg);
			front += MESSAGE_SIZE;
		}
	}
	else {
		while (front < CONSTS_SIZE + max_size * MESSAGE_SIZE) 
		{
			fread(msg, sizeof(char), MESSAGE_SIZE, file);
			printf("\n %s ", msg);
			front += MESSAGE_SIZE;
		}
		front = CONSTS_SIZE;
		fseek(file, front, SEEK_SET);
		while (front != rear)
		{
			fread(msg, sizeof(char), MESSAGE_SIZE, file);
			printf("\n %s ", msg);
			front += MESSAGE_SIZE;
		}
	}
	free(msg);
}

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>

struct Polynom
{
	int deg;
	float *numbers;
	float x;
	float sum;
};

DWORD WINAPI CountPolynom(LPVOID lpParam)
{
	struct Polynom* pol = (struct Polynom*)lpParam;
	float sum = 0;
	sum += pol->numbers[pol->deg];
	for (int i = pol -> deg - 1; i != -1; i--)
	{
		sum = sum * pol->x + pol->numbers[i];
		Sleep(15);
	}
	pol -> sum = sum;
	printf("p(%f) = %f\n", pol -> x, pol ->sum);
}

int main()
{
	setlocale(LC_ALL, "rus");
	HANDLE hThread1, hThread2;
	DWORD IDThread1, IDThread2;
	struct Polynom pol_num, pol_denum;
	int deg1, deg2;
	float x;
	printf("Введите степень числителя: ");
	scanf("%d", &deg1);
	pol_num.deg = deg1;
	float *Numbers1 = (float*)malloc((deg1 + 1) * sizeof(float));
	for (int i = 0; i < deg1 + 1; i++)
	{
		printf("%d коэффициент равен = ", i);
		scanf("%f", &Numbers1[i]);
	}
	pol_num.numbers = Numbers1;
	printf("Введите степень знаменателя: ");
	scanf("%d", &deg2);
	pol_denum.deg = deg2;
	float *Numbers2 = (float*)malloc((deg2 + 1) * sizeof(float));
	for (int i = 0; i < deg2 + 1; i++)
	{
		printf("%d коэффициент равен = ", i);
		scanf("%f", &Numbers2[i]);
	}
	pol_denum.numbers = Numbers2;
	printf("Введите x: ");
	scanf("%f", &x);
	pol_num.x = x;
	pol_denum.x = x;
	hThread1 = CreateThread(NULL, 0, CountPolynom, &pol_num, 0, &IDThread1);
	hThread2 = CreateThread(NULL, 0, CountPolynom, &pol_denum, 0, &IDThread2);
	if (hThread1 == NULL || hThread2 == NULL)
		return GetLastError();
	HANDLE mas[2] = { hThread1, hThread2 };
	WaitForMultipleObjects(2, mas, TRUE, INFINITE);
	printf("f(%f) = %f\n", x, pol_num.sum / pol_denum.sum);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	system("pause");
	return 0;
}
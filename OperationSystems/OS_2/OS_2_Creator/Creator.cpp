#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct tax_payment
{
	int num;			// идентификационный номер компании
	char name[10];		// название компании
	double sum;			// сумма налоговых платежей
};

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	int amount = atoi(argv[2]);
	tax_payment temp;
	ofstream out(argv[1], ios::binary);
	cout << "Файл " << argv[1] << endl;
	cout << "Введите " << amount << " значений: " << endl;
	for (int i = 0; i < amount; i++)
	{
		cout << "Компания номер " << i + 1 << " :" << endl << "Введите идентификационный номер: ";
		cin >> temp.num;
		cout << "Введите название компании: ";
		cin >> temp.name;
		cout << "Введите суммy налоговых платежей: ";
		cin >> temp.sum;
		out.write((char *)(&temp), sizeof(tax_payment));
	}
	out.close();
	return 0;
}
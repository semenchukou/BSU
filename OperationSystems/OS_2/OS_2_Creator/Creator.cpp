#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct tax_payment
{
	int num;			// ����������������� ����� ��������
	char name[10];		// �������� ��������
	double sum;			// ����� ��������� ��������
};

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	int amount = atoi(argv[2]);
	tax_payment temp;
	ofstream out(argv[1], ios::binary);
	cout << "���� " << argv[1] << endl;
	cout << "������� " << amount << " ��������: " << endl;
	for (int i = 0; i < amount; i++)
	{
		cout << "�������� ����� " << i + 1 << " :" << endl << "������� ����������������� �����: ";
		cin >> temp.num;
		cout << "������� �������� ��������: ";
		cin >> temp.name;
		cout << "������� ����y ��������� ��������: ";
		cin >> temp.sum;
		out.write((char *)(&temp), sizeof(tax_payment));
	}
	out.close();
	return 0;
}
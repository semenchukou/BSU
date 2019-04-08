#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct tax_payment
{
	int num;
	char name[10];
	double sum;
};

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	double payments = atof(argv[3]);
	int marker;
	if (argv[4][0] == '<')//< = 0, > = 1
		marker = 0;
	else
		marker = 1;
	ofstream out(argv[2]);
	ifstream in(argv[1], ios::binary);
	tax_payment temp;
	out << "Отчет по файлу " << argv[1] << endl;
	out << "Список компаний, налоговые платежи которых " << argv[4] << " " << payments << endl;
	while (in.read((char *)(&temp), sizeof(tax_payment)))
	{
		if (marker == 0)
		{
			if (temp.sum < payments)
			{
				out << temp.name;
				out << " с номером " << temp.num << " и суммой платежей " << temp.sum << endl;
			}
		}
		else
		{
			if (temp.sum > payments)
			{
				out << temp.name;
				out << " с номером " << temp.num << " и суммой платежей " << temp.sum << endl;
			}
		}
	}
	out.close();
	in.close();
	return 0;
}
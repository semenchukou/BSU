#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <locale.h>

using namespace std;

struct tax_payment
{
	int num;	
	char name[10];
	double sum;
};

int main()
{
	setlocale(LC_ALL, "rus");
	string file_bin;
	int amount;
	cout << "¬ведите им€ бинарного файла: ";
	cin >> file_bin;
	cout << "¬ведите колличество записей: ";
	cin >> amount;

	string path1 = "C:\\Users\\Alex\\source\\repos\\OS_2\\Debug\\OS_2_Creator.exe " 
		+ file_bin + " " + to_string(amount);

	char* lpszCommandLine = _strdup(path1.c_str());
	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// создаем новый консольный процесс
	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);
	WaitForSingleObject(piCom.hThread, INFINITE);
	// закрываем дескрипторы этого процесса
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	ifstream in(file_bin, ios::binary);
	tax_payment temp;
	cout << "—писок компаний: " << endl;
	while (in.read((char *)(&temp), sizeof(tax_payment)))
	{
		cout << temp.name;
		cout << " с номером " << temp.num << " и суммой платежей " << temp.sum << endl;
	}
	in.close();

	string file_txt;
	double payment;
	char symbol;
	cout << "¬ведите им€ текстового файла отчета: ";
	cin >> file_txt;
	cout << "¬ведите значение платежей: ";
	cin >> payment;
	cout << "¬ведите < или >: ";
	cin >> symbol;

	string path2 = "C:\\Users\\Alex\\source\\repos\\OS_2\\Debug\\OS_2_Reporter.exe "
		+ file_bin + " " + file_txt + " " + to_string(payment) + " " + symbol;

	char* lpszCommandLine2 = _strdup(path2.c_str());
	STARTUPINFO si2;
	PROCESS_INFORMATION piCom2;
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);
	// создаем новый консольный процесс
	CreateProcess(NULL, lpszCommandLine2, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si2, &piCom2);
	WaitForSingleObject(piCom2.hThread, INFINITE);
	// закрываем дескрипторы этого процесса
	CloseHandle(piCom2.hThread);
	CloseHandle(piCom2.hProcess);

	ifstream inn(file_txt);
	string line;
	while (!inn.eof())
	{
		getline(inn, line);
		cout << line << endl;
	}
	inn.close();
	system("pause");
	return 0;
}
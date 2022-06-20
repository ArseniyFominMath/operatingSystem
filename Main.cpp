#include<windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <codecvt>
#include <locale>
using namespace std;

struct Еmployee
{
	int num; 
	char name[10]; 
	double hours; 
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	STARTUPINFO sUpInfoCreator;
	PROCESS_INFORMATION processInfoCreator;
	ZeroMemory(&sUpInfoCreator, sizeof(STARTUPINFO));
	sUpInfoCreator.cb = sizeof(STARTUPINFO);
	string str1 = "Creator.exe ";

	char fileNameCreator[20];

	int recordsNum;
	cout << "Введите имя бинарного файла (имя.bin):\n";
	cin >> fileNameCreator;
	cout << "Введите количество записей:\n";
	cin >> recordsNum;
	CreateProcess(NULL, (LPWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(
		str1 + fileNameCreator + " " + to_string(recordsNum)).c_str(), 
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sUpInfoCreator, &processInfoCreator);

	WaitForSingleObject(processInfoCreator.hProcess, INFINITE);
	CloseHandle(processInfoCreator.hThread);
	CloseHandle(processInfoCreator.hProcess);

	ifstream finCreator(fileNameCreator, ios::binary | ios::in);
	Еmployee emp;
	while (!finCreator.eof()) {
		finCreator.read((char*)&emp, sizeof(emp));
		if (!finCreator.eof())
			cout << emp.num << ", " << emp.name << ", " << emp.hours << '\n';
	}
	finCreator.close();
	STARTUPINFO sUpInfoReporter;
	PROCESS_INFORMATION processInfoReporter;
	ZeroMemory(&sUpInfoReporter, sizeof(STARTUPINFO));
	sUpInfoReporter.cb = sizeof(STARTUPINFO);
	string str2 = "Reporter.exe ";

	char fileNameReporter[20];

	cout << "Введите имя файла отчёта (имя.bin):\n";
	cin >> fileNameReporter;
	int payment;
	cout << "Введите оплату за час работы в у.е. :\n";
	cin >> payment;

	CreateProcess(NULL, (LPWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(
		str2 + fileNameCreator + " " + fileNameReporter + " " + to_string(payment)).c_str(), 
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sUpInfoReporter, &processInfoReporter);

	WaitForSingleObject(processInfoReporter.hProcess, INFINITE);
	CloseHandle(processInfoReporter.hThread);
	CloseHandle(processInfoReporter.hProcess);
	
	ifstream finReporter(fileNameReporter);
	char ch; 
	while (!finReporter.eof()) {
		finReporter.read(&ch, 1);
		if (!finReporter.eof()) {
			cout << ch; 
		}
	}
	finReporter.close();
	return 0;
}


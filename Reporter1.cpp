#include <windows.h>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

struct employee
{
    int num; 
    char name[10]; 
    double hours; 
};

int main(int argC, char* argV[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream in(argV[1], ios::binary | ios::in);
    ofstream out(argV[2]);
    out << "Отчёт по файлу: «" << argV[1] << "»\n";
    out << "Номер сотрудника (id), имя сотрудника, часы, зарплата в у.е.\n";
    employee emp;
    while (!in.eof()) {
        in.read((char*)&emp, sizeof(emp));
        if(!in.eof())
            out << emp.num << ", " << emp.name << ", " << emp.hours << ", " << emp.hours * atoi(argV[3]) << '\n';
    }
    out.close();
    in.close();
    return 0;
}
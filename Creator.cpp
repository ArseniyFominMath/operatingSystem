#include <windows.h>
#include <fstream>
#include <iostream>
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
    ofstream out(argV[1], ios::binary | ios::out);
    employee emp;
    for (int i = 0; i < atoi(argV[2]); i++) {
        cout << "Введите индификационный номер сотрудника:\n";
        cin >> emp.num;
        cout << "Введите имя сотрудника:\n";
        cin >> emp.name;
        cout << "Введите количество отработанных часов в целых числах:\n";
        cin >> emp.hours;
        out.write((char*)&emp, sizeof(emp));
    }
    out.close();
    return 0;
}


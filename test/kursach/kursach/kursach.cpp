//статическая приоритетная очередь динамических стеков
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "airCompanyProcessing.hpp"
#include "file_IO.hpp"
using namespace std;
file_IO storage{"C:/VLAD/Programs/SAOD/kursach/kursach/Data.txt"};
airCompanyProcessing MyAirCompany{};
template<typename T>
T checkingInput() {
    T input;
    while (!(cin >> input) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nПроизошла ошибка. Попробуйте ввести снова. \n" << endl;
    }
    return input;
}
void postMenu() {
    int number;
    string temp;
    bool flag = true;
    cout << "1) Сохранить информацию об авиакомпании в файле\n";
    cout << "2) Завершить без сохранения\n";
    cout << "Введите номер команды: ";
    number = checkingInput<int>();
    switch (number)
    {
    case 1:
        if (storage.fileExists()) {
            storage.outputData(&MyAirCompany);
            cout << "Данные сохранены в файле по пути: C:/VLAD/Programs/SAOD/kursach/kursach/Data.txt";
        }
        else {
            storage.outputData(&MyAirCompany);
            cout << "Файла не существует. Данные сохранены в новом файле по пути: C:/VLAD/Programs/SAOD/kursach/kursach/Data.txt";
        }
        break;
    case 2:

        break;
    default:
        cout << "Ошибка ввода. Повторите ввод команды\n";
        break;
    }
}
void menu() {
    int number;
    bool flag = true;
    while (flag) {
        cout << "\nВыберите команду из списка:\n";
        cout << "1) Добавить новый аэропорт\n";
        cout << "2) Найти аэропорт по названию\n";
        cout << "3) Удалить аэропорт\n";
        cout << "4) Добавить новый самолет в аэропорт\n";
        cout << "5) Найти самолет\n";
        cout << "6) Удалить самолет\n";
        cout << "7) Вывести всю информацию об авиакомпании\n";
        cout << "8) Завершить работу программы\n";
        cout << "Введите номер команды: ";
        number = checkingInput<int>();
        switch (number)
        {
        case 1:
            MyAirCompany.addAirport();
            break;
        case 2:
            MyAirCompany.findAirport();
            break;
        case 3:
            MyAirCompany.deleteAirport();
            break;
        case 4:
            MyAirCompany.addAirplane();
            break;
        case 5:
            cout << "Введите 1, если хотите найти самолет по бренду.\nВведите 2, если хотите найти самолет по году выпуска.\nВаш выбор: ";  
            number = checkingInput<int>();
            while (flag) {
                switch (number) {
                case 1:
                    MyAirCompany.findAirplaneBrand();
                    break;
                case 2:
                    MyAirCompany.findAirplaneReleaseYear();
                    break;
                default:
                    cout << "Введите корректное значение: ";
                    number = checkingInput<int>();
                    flag = !flag;
                    break;
                }
                flag = !flag;
            }
            flag = true;
            break;
        case 6:
            MyAirCompany.deleteAirplane();
            break;
        case 7:
            MyAirCompany.showAllAirCompanyInformation();
            break;
        case 8:
            postMenu();
            flag = false;
            break;
        default:
            cout << "Ошибка ввода. Повторите ввод команды\n";
            break;
        }
    }
}
void predMenu() {
    int number;
    string temp;
    bool flag = true;
    cout << "1) Загрузить информацию об авиакомпании из файла\n";
    cout << "2) Создать новую авиакомпанию\n";
    cout << "Введите номер команды: ";
    number = checkingInput<int>();
    switch (number)
    {
        case 1:
            if (!storage.inputData(MyAirCompany.getAirCompany())) {
                cout << "Произошла ошибка чтения файла. Создайте новую авиакомпанию\n";
                goto case2;
            };
            break;
        case 2:
            case2:
            cout << "Введите название авиакомпании: ";
            temp = checkingInput<string>();
            MyAirCompany.getAirCompany()->setName(temp);
            break;
        default:
            cout << "Ошибка ввода. Повторите ввод команды\n";
            break;
    }
}
int main()
{
    predMenu();
    menu();
}


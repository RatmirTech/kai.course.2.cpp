#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "airCompanyProcessing.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class file_IO
{
private:
    string address;
public:
    file_IO(string _address) {
        address = _address;
    };
    bool inputData(airCompany* _airCompany) {
        airport* tempAirport = nullptr;
        string text, name;
        int releaseYear = 0;
        char buffer[100];
        char* f;

        ifstream file(address);

        if (!file.is_open())
            return false;

        if (!file.eof()) {
            file.getline(buffer, 100); // Берем одну строку
            text = buffer;
            _airCompany->setName(text);
        }
        else {
            cout << "Файл пуст.\n";
            return false;
        }
        while (!file.eof()) {
            file.getline(buffer, 100); // Берем одну строку
            f = strtok(buffer, " "); // Делим строку по пробелам
            if (f == NULL) continue; //если строка пустая, перейти на следующую итерацию цикла
            if (f)
                name = f;
            _airCompany->push(name); // создаем подменю
            f = strtok(NULL, " "); // Переходим к следующему элементу
            while (f) { // пока не пусто
                if (f)
                    text = f;
                f = strtok(NULL, " "); // Переходим к следующему элементу
                if (f)
                    releaseYear = stoi(f);
                else
                    return false;
                tempAirport = _airCompany->getAirport(name);
                tempAirport->push(text, releaseYear); //Создаем команду, если нашлись данные
                f = strtok(NULL, " "); // Переходим к следующему элементу
            }
        }
        file.close();
        return true;
    }
    bool fileExists() {
        std::ifstream file(address);
        return file.good();  // true если файл существует и доступен
    }
    bool outputData(airCompanyProcessing* _airCompany) {
        ofstream file(address);
        if (!file.is_open()) return false;
        file << _airCompany->GetStringForFile();
        file.close();
        return true;
    };

    ~file_IO() {};
};

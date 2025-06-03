#pragma once
#include <iostream>
#include <string>
#include "airCompany.hpp"
using namespace std;

class airCompanyProcessing {
private:
	airCompany MyAirCompany;
public:
	airCompanyProcessing() {}
	template <typename T>
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
	void addAirport() {
		string airportName = "";
		if (MyAirCompany.isFull()) {
			cout << "Достигнуто максимальное количество аэропортов. Дальнейшее создание невозможно.\n";
			return;
		}
		cout << "Введите название для аэропорта: ";
		airportName = checkingInput<string>();
		if (MyAirCompany.push(airportName)) {
			cout << "\nАэропорт успешно создан.\n";
		}
		else cout << "Не удалось создать новый аэропорт.\n";
	}
	void findAirport() {
		if (MyAirCompany.isEmpty()) {
			cout << "Список аэропортов пуст.\n";
			return;
		}
		string airportName = "";
		cout << "Введите название аэропорта для поиска: ";
		airportName = checkingInput<string>();
		cout << endl;
		if (MyAirCompany.findAirport(airportName)) {
			cout << "Аэропорт с названием " << airportName << " был найден.\n";
		}
		else cout << "Аэропорт с названием " << airportName << " не найден.\n";
	}
	void findAirplaneBrand() {
		string airplaneBrand = "";
		cout << "Введите название самолета для поиска: ";
		airplaneBrand = checkingInput<string>();
		cout << endl;
		if (MyAirCompany.findAirplane(airplaneBrand)) {
			cout << "Самолет под брендом " << airplaneBrand << " был найден.\n";
		}
		else cout << "под брендом\n";
	}
	void findAirplaneReleaseYear() {
		int releaseYear = 0;
		cout << "Введите год выпуска самолета для поиска: ";
		releaseYear = checkingInput<int>();
		cout << endl;
		if (MyAirCompany.findAirplane(releaseYear)) {
			cout << "Самолет, выпущенный в " << releaseYear << " году был найден.\n";
		}
		else cout << "Самолет, выпущенный в " << releaseYear << " не найден.\n";
	}
	void addAirplane() {
		string airportName = "";
		string airplaneBrand = "";
		int releaseYear = 0;
		cout << "Введите аэропорт, в который нужно добавить новый самолет: ";
		airportName = checkingInput<string>();
		airport* airport = MyAirCompany.getAirport(airportName);
		if (airport == nullptr) {
			cout << "Заданный аэропорт не найдет, добавление самолета невозможно";
			return;
		}
		cout << "Введите бренд нового самолета: ";
		airplaneBrand = checkingInput<string>();
		cout << "Введите год выпуска нового самолета: ";
		releaseYear = checkingInput<int>();
		if (airport->push(airplaneBrand, releaseYear)) {
			cout << "Самолет успешно добавлен в аэропорт " << airportName << ".\n";
		}
		else cout << "Самолет не был добавлен.\n";
	}
	void showAllAirCompanyInformation() {
		cout << "Название авиакомпании: " << MyAirCompany.getName() << ".\n";
		cout << "Аэропорты и самолеты под владением авиакомпании:\n";
		if (!MyAirCompany.showAirportsWithAirplanes()) {
			cout << "Нет ни аэропортов ни самолетов.\n";
		};
	}
	void deleteAirport() {
		if (!MyAirCompany.isEmpty()) {
			MyAirCompany.pop();
			cout << "Аэропорт успешно удален.\n";
		}
		else cout << "Список аэропортов пуст. Удаление невозможно.\n";
	}
	void deleteAirplane() {
		string airportName = "";
		cout << "Введите аэропорт, из которого нужно удалить самолет: ";
		airportName = checkingInput<string>();
		airport* findedAirport = MyAirCompany.getAirport(airportName);
		if (findedAirport) {
			if (findedAirport->isEmpty()) {
				cout << "Список самолетов в аэропорте " << airportName << " пуст. Удаление невозможно.\n";
				return;
			}
			if (findedAirport) {
				findedAirport->pop();
				cout << "Самолет успешно удален из аэропорта " << airportName << ".\n";
			}
			else cout << "Аэропорт не найден. Удаление самолета невозможно.\n";
		}
		else cout << "Аэропорт с таким названием не найден.\n"; return;
	}
	string GetStringForFile() // Формирование таблицы в виде строки
	{
		return MyAirCompany.getName() + '\n' + MyAirCompany.GetStringForFile();
	}
	airCompany* getAirCompany() {
		return &MyAirCompany;
	}
	~airCompanyProcessing() {}
};
#include <iostream>
#include <limits>
#include <locale>
#include <codecvt>
#include "GasCompany.h"
#include "Storage.h"

void displayMenu() {
	std::wcout << L"\nМеню управления бензиновой компанией:\n";
	std::wcout << L"1. Добавить автозаправку\n";
	std::wcout << L"2. Удалить автозаправку\n";
	std::wcout << L"3. Найти автозаправку\n";
	std::wcout << L"4. Добавить бензоколонку\n";
	std::wcout << L"5. Удалить бензоколонку\n";
	std::wcout << L"6. Найти бензоколонку\n";
	std::wcout << L"7. Изменить название компании\n";
	std::wcout << L"8. Показать все данные\n";
	std::wcout << L"9. Сохранить в файл\n";
	std::wcout << L"10. Загрузить из файла\n";
	std::wcout << L"0. Выход\n";
	std::wcout << L"Выберите действие: ";
}

int getIntInput(const std::wstring& prompt) {
	int value;
	while (true) {
		std::wcout << prompt;
		std::wcin >> value;
		if (std::wcin.fail()) {
			std::wcin.clear();
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
			std::wcout << L"Ошибка ввода. Пожалуйста, введите целое число.\n";
		}
		else {
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
			return value;
		}
	}
}

int main() {
	// Установка русской локали для корректного ввода/вывода
	std::locale ru("ru_RU.UTF-8");
	std::locale::global(ru);
	std::wcout.imbue(ru);
	std::wcin.imbue(ru);

	// ВАЖНО: Для корректного отображения русских символов в консоли Windows
	// перед запуском программы выполните команду:
	// chcp 65001
	// Это переключит кодировку консоли на UTF-8.

	GasCompany company(L"Моя Бензиновая Компания");
	Storage storage(L"data.txt");

	int choice;
	do {
		displayMenu();
		choice = getIntInput(L"");

		switch (choice) {
		case 1: {
			int number = getIntInput(L"Введите номер автозаправки: ");
			GasStation station(number);
			if (company.addStation(station)) {
				std::wcout << L"Автозаправка успешно добавлена.\n";
			}
			break;
		}
		case 2: {
			int number = getIntInput(L"Введите номер автозаправки для удаления: ");
			if (company.removeStation(number)) {
				std::wcout << L"Автозаправка успешно удалена.\n";
			}
			else {
				std::wcout << L"Автозаправка с таким номером не найдена.\n";
			}
			break;
		}
		case 3: {
			int number = getIntInput(L"Введите номер автозаправки для поиска: ");
			GasStation* station = company.findStation(number);
			if (station) {
				std::wcout << L"Автозаправка найдена:\n";
				station->display();
			}
			else {
				std::wcout << L"Автозаправка с таким номером не найдена.\n";
			}
			break;
		}
		case 4: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"Автозаправка с таким номером не найдена.\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки: ");
			std::wcout << L"Введите марку бензина: ";
			std::wstring fuelType;
			std::getline(std::wcin, fuelType);

			GasPump pump(pumpNumber, fuelType);
			if (station->addPump(pump)) {
				std::wcout << L"Бензоколонка успешно добавлена.\n";
			}
			break;
		}
		case 5: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"Автозаправка с таким номером не найдена.\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки для удаления: ");
			if (station->removePump(pumpNumber)) {
				std::wcout << L"Бензоколонка успешно удалена.\n";
			}
			else {
				std::wcout << L"Бензоколонка с таким номером не найдена.\n";
			}
			break;
		}
		case 6: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"Автозаправка с таким номером не найдена.\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки для поиска: ");
			GasPump* pump = station->findPump(pumpNumber);
			if (pump) {
				std::wcout << L"Бензоколонка найдена: ";
				pump->display();
				std::wcout << L"\n";
			}
			else {
				std::wcout << L"Бензоколонка с таким номером не найдена.\n";
			}
			break;
		}
		case 7: {
			std::wcout << L"Введите новое название компании: ";
			std::wstring newName;
			std::getline(std::wcin, newName);
			company.setName(newName);
			std::wcout << L"Название компании изменено.\n";
			break;
		}
		case 8: {
			company.display();
			break;
		}
		case 9: {
			if (storage.saveToFile(company)) {
				std::wcout << L"Данные успешно сохранены в файл.\n";
			}
			else {
				std::wcout << L"Ошибка при сохранении в файл.\n";
			}
			break;
		}
		case 10: {
			if (storage.loadFromFile(company)) {
				std::wcout << L"Данные успешно загружены из файла.\n";
			}
			else {
				std::wcout << L"Ошибка при загрузке из файла.\n";
			}
			break;
		}
		case 0: {
			std::wcout << L"Выход из программы.\n";
			break;
		}
		default: {
			std::wcout << L"Неверный выбор. Попробуйте снова.\n";
		}
		}
	} while (choice != 0);

	return 0;
}
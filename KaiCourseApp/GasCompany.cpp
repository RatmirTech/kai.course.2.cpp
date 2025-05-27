#include <iostream>
#include <limits>
#include <locale>
#include <codecvt>
#include "GasCompany.h"
#include "Storage.h"

using namespace std;

void displayMenu() {
	wcout << L"\nМеню управления бензиновой компанией:\n";
	wcout << L"1. Добавить автозаправку\n";
	wcout << L"2. Удалить автозаправку\n";
	wcout << L"3. Найти автозаправку\n";
	wcout << L"4. Добавить бензоколонку\n";
	wcout << L"5. Удалить бензоколонку\n";
	wcout << L"6. Найти бензоколонку\n";
	wcout << L"7. Изменить название компании\n";
	wcout << L"8. Показать все данные\n";
	wcout << L"9. Сохранить в файл\n";
	wcout << L"10. Загрузить из файла\n";
	wcout << L"0. Выход\n";
	wcout << L"Выберите действие: ";
}

int getIntInput(const wstring& prompt) {
	int value;
	while (true) {
		wcout << prompt;
		wcin >> value;
		if (wcin.fail()) {
			wcin.clear();
			wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
			wcout << L"Ошибка ввода. Пожалуйста, введите целое число.\n";
		}
		else {
			wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
			return value;
		}
	}
}

int main() {
	locale ru("ru_RU.UTF-8");
	locale::global(ru);
	wcout.imbue(ru);
	wcin.imbue(ru);

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
				wcout << L"Автозаправка с номером " << number << L" успешно добавлена.\\n";
			}
			break;
		}
		case 2: {
			int number = getIntInput(L"Введите номер автозаправки для удаления: ");
			if (company.removeStation(number)) {
				wcout << L"Автозаправка с номером " << number << L" успешно удалена.\\n";
			}
			else {
				wcout << L"Ошибка: не удалось удалить автозаправку с номером " << number << L". Возможно, она не существует.\\n";
			}
			break;
		}
		case 3: {
			int number = getIntInput(L"Введите номер автозаправки для поиска: ");
			GasStation* station = company.findStation(number);
			if (station) {
				wcout << L"Автозаправка с номером " << number << L" найдена:\\n";
				station->display();
			}
			else {
				wcout << L"Автозаправка с номером " << number << L" не найдена.\\n";
			}
			break;
		}
		case 4: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"Автозаправка с номером " << stationNumber << L" не найдена.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки: ");
			wcout << L"Введите марку бензина: ";
			wstring fuelType;
			getline(wcin, fuelType);

			GasPump pump(pumpNumber, fuelType);
			if (station->addPump(pump)) {
				wcout << L"Бензоколонка с номером " << pumpNumber << L" успешно добавлена на автозаправку " << stationNumber << L".\\n";
			}
			break;
		}
		case 5: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"Автозаправка с номером " << stationNumber << L" не найдена.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки для удаления: ");
			if (station->removePump(pumpNumber)) {
				wcout << L"Бензоколонка с номером " << pumpNumber << L" успешно удалена с автозаправки " << stationNumber << L".\\n";
			}
			else {
				wcout << L"Ошибка: не удалось удалить бензоколонку с номером " << pumpNumber << L" с автозаправки " << stationNumber << L". Возможно, она не существует.\\n";
			}
			break;
		}
		case 6: {
			int stationNumber = getIntInput(L"Введите номер автозаправки: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"Автозаправка с номером " << stationNumber << L" не найдена.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"Введите номер бензоколонки для поиска: ");
			GasPump* pump = station->findPump(pumpNumber);
			if (pump) {
				wcout << L"Бензоколонка с номером " << pumpNumber << L" найдена на автозаправке " << stationNumber << L":\\n";
				pump->display();
				wcout << endl;
			}
			else {
				wcout << L"Бензоколонка с номером " << pumpNumber << L" не найдена на автозаправке " << stationNumber << L".\\n";
			}
			break;
		}
		case 7: {
			wcout << L"Введите новое название компании: ";
			wstring newName;
			getline(wcin, newName);
			company.setName(newName);
			wcout << L"Название компании изменено на: " << newName << L"\n";
			break;
		}
		case 8: {
			company.display();
			break;
		}
		case 9: {
			if (storage.saveToFile(company)) {
				wcout << L"Данные успешно сохранены в файл " << storage.getFilePath() << L".\\n";
			}
			else {
				wcout << L"Ошибка: не удалось сохранить данные в файл.\\n";
			}
			break;
		}
		case 10: {
			if (storage.loadFromFile(company)) {
				wcout << L"Данные успешно загружены из файла " << storage.getFilePath() << L".\\n";
				wcout << L"Загруженная компания: " << company.getName() << endl;
				company.display();
			}
			else {
				wcout << L"Ошибка: не удалось загрузить данные из файла. Файл может не существовать или быть поврежден.\\n";
			}
			break;
		}
		case 0: {
			wcout << L"Выход из программы.\n";
			break;
		}
		default: {
			wcout << L"Неверный выбор. Попробуйте снова.\n";
		}
		}
	} while (choice != 0);

	return 0;
}
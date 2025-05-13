#include <iostream>
#include <limits>
#include <locale>
#include <codecvt>
#include "GasCompany.h"
#include "Storage.h"

void displayMenu() {
	std::wcout << L"\n���� ���������� ���������� ���������:\n";
	std::wcout << L"1. �������� ������������\n";
	std::wcout << L"2. ������� ������������\n";
	std::wcout << L"3. ����� ������������\n";
	std::wcout << L"4. �������� ������������\n";
	std::wcout << L"5. ������� ������������\n";
	std::wcout << L"6. ����� ������������\n";
	std::wcout << L"7. �������� �������� ��������\n";
	std::wcout << L"8. �������� ��� ������\n";
	std::wcout << L"9. ��������� � ����\n";
	std::wcout << L"10. ��������� �� �����\n";
	std::wcout << L"0. �����\n";
	std::wcout << L"�������� ��������: ";
}

int getIntInput(const std::wstring& prompt) {
	int value;
	while (true) {
		std::wcout << prompt;
		std::wcin >> value;
		if (std::wcin.fail()) {
			std::wcin.clear();
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
			std::wcout << L"������ �����. ����������, ������� ����� �����.\n";
		}
		else {
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
			return value;
		}
	}
}

int main() {
	// ��������� ������� ������ ��� ����������� �����/������
	std::locale ru("ru_RU.UTF-8");
	std::locale::global(ru);
	std::wcout.imbue(ru);
	std::wcin.imbue(ru);

	// �����: ��� ����������� ����������� ������� �������� � ������� Windows
	// ����� �������� ��������� ��������� �������:
	// chcp 65001
	// ��� ���������� ��������� ������� �� UTF-8.

	GasCompany company(L"��� ���������� ��������");
	Storage storage(L"data.txt");

	int choice;
	do {
		displayMenu();
		choice = getIntInput(L"");

		switch (choice) {
		case 1: {
			int number = getIntInput(L"������� ����� ������������: ");
			GasStation station(number);
			if (company.addStation(station)) {
				std::wcout << L"������������ ������� ���������.\n";
			}
			break;
		}
		case 2: {
			int number = getIntInput(L"������� ����� ������������ ��� ��������: ");
			if (company.removeStation(number)) {
				std::wcout << L"������������ ������� �������.\n";
			}
			else {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
			}
			break;
		}
		case 3: {
			int number = getIntInput(L"������� ����� ������������ ��� ������: ");
			GasStation* station = company.findStation(number);
			if (station) {
				std::wcout << L"������������ �������:\n";
				station->display();
			}
			else {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
			}
			break;
		}
		case 4: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������: ");
			std::wcout << L"������� ����� �������: ";
			std::wstring fuelType;
			std::getline(std::wcin, fuelType);

			GasPump pump(pumpNumber, fuelType);
			if (station->addPump(pump)) {
				std::wcout << L"������������ ������� ���������.\n";
			}
			break;
		}
		case 5: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������ ��� ��������: ");
			if (station->removePump(pumpNumber)) {
				std::wcout << L"������������ ������� �������.\n";
			}
			else {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
			}
			break;
		}
		case 6: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������ ��� ������: ");
			GasPump* pump = station->findPump(pumpNumber);
			if (pump) {
				std::wcout << L"������������ �������: ";
				pump->display();
				std::wcout << L"\n";
			}
			else {
				std::wcout << L"������������ � ����� ������� �� �������.\n";
			}
			break;
		}
		case 7: {
			std::wcout << L"������� ����� �������� ��������: ";
			std::wstring newName;
			std::getline(std::wcin, newName);
			company.setName(newName);
			std::wcout << L"�������� �������� ��������.\n";
			break;
		}
		case 8: {
			company.display();
			break;
		}
		case 9: {
			if (storage.saveToFile(company)) {
				std::wcout << L"������ ������� ��������� � ����.\n";
			}
			else {
				std::wcout << L"������ ��� ���������� � ����.\n";
			}
			break;
		}
		case 10: {
			if (storage.loadFromFile(company)) {
				std::wcout << L"������ ������� ��������� �� �����.\n";
			}
			else {
				std::wcout << L"������ ��� �������� �� �����.\n";
			}
			break;
		}
		case 0: {
			std::wcout << L"����� �� ���������.\n";
			break;
		}
		default: {
			std::wcout << L"�������� �����. ���������� �����.\n";
		}
		}
	} while (choice != 0);

	return 0;
}
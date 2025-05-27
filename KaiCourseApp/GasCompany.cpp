#include <iostream>
#include <limits>
#include <locale>
#include <codecvt>
#include "GasCompany.h"
#include "Storage.h"

using namespace std;

void displayMenu() {
	wcout << L"\n���� ���������� ���������� ���������:\n";
	wcout << L"1. �������� ������������\n";
	wcout << L"2. ������� ������������\n";
	wcout << L"3. ����� ������������\n";
	wcout << L"4. �������� ������������\n";
	wcout << L"5. ������� ������������\n";
	wcout << L"6. ����� ������������\n";
	wcout << L"7. �������� �������� ��������\n";
	wcout << L"8. �������� ��� ������\n";
	wcout << L"9. ��������� � ����\n";
	wcout << L"10. ��������� �� �����\n";
	wcout << L"0. �����\n";
	wcout << L"�������� ��������: ";
}

int getIntInput(const wstring& prompt) {
	int value;
	while (true) {
		wcout << prompt;
		wcin >> value;
		if (wcin.fail()) {
			wcin.clear();
			wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
			wcout << L"������ �����. ����������, ������� ����� �����.\n";
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
				wcout << L"������������ � ������� " << number << L" ������� ���������.\\n";
			}
			break;
		}
		case 2: {
			int number = getIntInput(L"������� ����� ������������ ��� ��������: ");
			if (company.removeStation(number)) {
				wcout << L"������������ � ������� " << number << L" ������� �������.\\n";
			}
			else {
				wcout << L"������: �� ������� ������� ������������ � ������� " << number << L". ��������, ��� �� ����������.\\n";
			}
			break;
		}
		case 3: {
			int number = getIntInput(L"������� ����� ������������ ��� ������: ");
			GasStation* station = company.findStation(number);
			if (station) {
				wcout << L"������������ � ������� " << number << L" �������:\\n";
				station->display();
			}
			else {
				wcout << L"������������ � ������� " << number << L" �� �������.\\n";
			}
			break;
		}
		case 4: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"������������ � ������� " << stationNumber << L" �� �������.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������: ");
			wcout << L"������� ����� �������: ";
			wstring fuelType;
			getline(wcin, fuelType);

			GasPump pump(pumpNumber, fuelType);
			if (station->addPump(pump)) {
				wcout << L"������������ � ������� " << pumpNumber << L" ������� ��������� �� ������������ " << stationNumber << L".\\n";
			}
			break;
		}
		case 5: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"������������ � ������� " << stationNumber << L" �� �������.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������ ��� ��������: ");
			if (station->removePump(pumpNumber)) {
				wcout << L"������������ � ������� " << pumpNumber << L" ������� ������� � ������������ " << stationNumber << L".\\n";
			}
			else {
				wcout << L"������: �� ������� ������� ������������ � ������� " << pumpNumber << L" � ������������ " << stationNumber << L". ��������, ��� �� ����������.\\n";
			}
			break;
		}
		case 6: {
			int stationNumber = getIntInput(L"������� ����� ������������: ");
			GasStation* station = company.findStation(stationNumber);
			if (!station) {
				wcout << L"������������ � ������� " << stationNumber << L" �� �������.\\n";
				break;
			}

			int pumpNumber = getIntInput(L"������� ����� ������������ ��� ������: ");
			GasPump* pump = station->findPump(pumpNumber);
			if (pump) {
				wcout << L"������������ � ������� " << pumpNumber << L" ������� �� ������������ " << stationNumber << L":\\n";
				pump->display();
				wcout << endl;
			}
			else {
				wcout << L"������������ � ������� " << pumpNumber << L" �� ������� �� ������������ " << stationNumber << L".\\n";
			}
			break;
		}
		case 7: {
			wcout << L"������� ����� �������� ��������: ";
			wstring newName;
			getline(wcin, newName);
			company.setName(newName);
			wcout << L"�������� �������� �������� ��: " << newName << L"\n";
			break;
		}
		case 8: {
			company.display();
			break;
		}
		case 9: {
			if (storage.saveToFile(company)) {
				wcout << L"������ ������� ��������� � ���� " << storage.getFilePath() << L".\\n";
			}
			else {
				wcout << L"������: �� ������� ��������� ������ � ����.\\n";
			}
			break;
		}
		case 10: {
			if (storage.loadFromFile(company)) {
				wcout << L"������ ������� ��������� �� ����� " << storage.getFilePath() << L".\\n";
				wcout << L"����������� ��������: " << company.getName() << endl;
				company.display();
			}
			else {
				wcout << L"������: �� ������� ��������� ������ �� �����. ���� ����� �� ������������ ��� ���� ���������.\\n";
			}
			break;
		}
		case 0: {
			wcout << L"����� �� ���������.\n";
			break;
		}
		default: {
			wcout << L"�������� �����. ���������� �����.\n";
		}
		}
	} while (choice != 0);

	return 0;
}
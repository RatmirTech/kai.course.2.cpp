#pragma once
#include "GasPump.h"
#include "PriorityQueue.h"
#include <iostream>

class GasStation {
private:
	int stationNumber;
	PriorityQueue<GasPump> pumps;

public:
	GasStation() : stationNumber(0) {}
	GasStation(int num) : stationNumber(num) {}

	int getNumber() const { return stationNumber; }
	void setNumber(int num) { stationNumber = num; }

	bool addPump(const GasPump& pump) {
		if (pumps.find(pump.getNumber()) != nullptr) {
			std::wcout << L"Ошибка: колонка с номером " << pump.getNumber() << L" уже существует\n";
			return false;
		}
		return pumps.enqueue(pump, pump.getNumber());
	}

	bool removePump(int pumpNumber) {
		return pumps.remove(pumpNumber);
	}

	GasPump* findPump(int pumpNumber) {
		return pumps.find(pumpNumber);
	}

	void display() const {
		std::wcout << L"Автозаправка №" << stationNumber << L":\n";
		pumps.display();
	}

	std::wstring toString() const {
		std::wstring result = std::to_wstring(stationNumber) + L"\n";
		result += pumps.toString();
		return result;
	}

	bool isEmpty() const {
		return pumps.isEmpty();
	}

	bool operator==(const GasStation& other) const {
		return stationNumber == other.stationNumber;
	}
};
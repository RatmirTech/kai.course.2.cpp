#pragma once
#include "GasStation.h"
#include "PriorityQueue.h"
#include <string>
#include <iostream>

class GasCompany {
private:
	std::wstring companyName;
	PriorityQueue<GasStation> stations;

public:
	GasCompany() : companyName(L"") {}
	GasCompany(const std::wstring& name) : companyName(name) {}

	std::wstring getName() const { return companyName; }
	void setName(const std::wstring& name) { companyName = name; }

	bool addStation(const GasStation& station) {
		bool res = stations.find(station.getNumber());
		if (res)
		{
			std::wcout << L"Ошибка: автозаправка с номером " << station.getNumber() << L" уже существует\n";
			return false;
		}
		return stations.enqueue(station, station.getNumber());
	}

	bool removeStation(int stationNumber) {
		return stations.remove(stationNumber);
	}

	GasStation* findStation(int stationNumber) {
		return stations.find(stationNumber);
	}

	void display() const {
		std::wcout << L"Бензиновая компания: " << companyName << L"\n";
		if (!stations.isEmpty()) {
			stations.display();
		}
		else {
			std::wcout << L"Нет данных об автозаправках.\n";
		}
	}

	std::wstring toString() const {
		return companyName + L"\n" + stations.toString();
	}

	bool isEmpty() const {
		return stations.isEmpty();
	}
};
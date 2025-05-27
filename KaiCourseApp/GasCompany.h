#pragma once
#include "GasStation.h"
#include "PriorityQueue.h"
#include <string>
#include <iostream>

using namespace std;

class GasCompany {
private:
	wstring companyName;
	PriorityQueue<GasStation> stations;

public:
	GasCompany() : companyName(L"") {}
	GasCompany(const wstring& name) : companyName(name) {}

	wstring getName() const { return companyName; }
	void setName(const wstring& name) { companyName = name; }

	bool addStation(const GasStation& station) {
		if (stations.find(station.getNumber()) != nullptr)
		{
			wcout << L"Ошибка: автозаправка с номером " << station.getNumber() << L" уже существует\n";
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
		wcout << L"Газовая компания: " << companyName << L"\n";
		if (!stations.isEmpty()) {
			stations.display();
		}
		else {
			wcout << L"Список автозаправок пуст.\n";
		}
	}

	wstring toString() const {
		return companyName + L"\n" + stations.toString();
	}

	bool isEmpty() const {
		return stations.isEmpty();
	}
};
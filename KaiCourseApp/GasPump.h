#pragma once
#include <string>
#include <iostream>

using namespace std;

class GasPump {
private:
	int pumpNumber;
	wstring fuelType;

public:
	GasPump() : pumpNumber(0), fuelType(L"") {}
	GasPump(int num, const wstring& type) : pumpNumber(num), fuelType(type) {}

	int getNumber() const { return pumpNumber; }
	wstring getFuelType() const { return fuelType; }

	void setNumber(int num) { pumpNumber = num; }
	void setFuelType(const wstring& type) { fuelType = type; }

	void display() const {
		wcout << L"Колонка #" << pumpNumber << L" (" << fuelType << L")";
	}

	wstring toString() const {
		return to_wstring(pumpNumber) + L" " + fuelType;
	}

	bool operator==(const GasPump& other) const {
		return pumpNumber == other.pumpNumber;
	}
};
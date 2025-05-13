#pragma once
#include <string>
#include <iostream>

class GasPump {
private:
	int pumpNumber;
	std::wstring fuelType;

public:
	GasPump() : pumpNumber(0), fuelType(L"") {}
	GasPump(int num, const std::wstring& type) : pumpNumber(num), fuelType(type) {}

	int getNumber() const { return pumpNumber; }
	std::wstring getFuelType() const { return fuelType; }

	void setNumber(int num) { pumpNumber = num; }
	void setFuelType(const std::wstring& type) { fuelType = type; }

	void display() const {
		std::wcout << L"Колонка №" << pumpNumber << L" (" << fuelType << L")";
	}

	std::wstring toString() const {
		return std::to_wstring(pumpNumber) + L" " + fuelType;
	}

	bool operator==(const GasPump& other) const {
		return pumpNumber == other.pumpNumber;
	}
};
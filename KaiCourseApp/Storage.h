#pragma once
#include "GasCompany.h"
#include <fstream>
#include <locale>
#include <codecvt>

class Storage {
private:
	std::wstring filePath;

public:
	Storage(const std::wstring& path) : filePath(path) {}

	bool saveToFile(const GasCompany& company) {
		std::wofstream file(filePath);
		if (!file.is_open()) return false;

		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
		file << company.toString();
		file.close();
		return true;
	}

	bool loadFromFile(GasCompany& company) {
		std::wifstream file(filePath);
		if (!file.is_open()) return false;

		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

		std::wstring line;
		getline(file, line); // Читаем название компании
		company.setName(line);

		while (getline(file, line)) {
			if (line.empty()) continue;

			int stationNumber = std::stoi(line);
			GasStation station(stationNumber);

			while (getline(file, line) && !line.empty()) {
				size_t spacePos = line.find(L' ');
				if (spacePos == std::wstring::npos) continue;

				int pumpNumber = std::stoi(line.substr(0, spacePos));
				std::wstring fuelType = line.substr(spacePos + 1);

				GasPump pump(pumpNumber, fuelType);
				station.addPump(pump);
			}

			company.addStation(station);
		}

		file.close();
		return true;
	}
};
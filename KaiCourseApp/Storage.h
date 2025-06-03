#pragma once
#include "GasCompany.h"
#include <fstream>
#include <locale>
#include <codecvt>

using namespace std;

class Storage {
private:
	wstring filePath;

public:
	Storage(const wstring& path) : filePath(path) {}

	wstring getFilePath() const { return filePath; }

	~Storage() = default;

	bool saveToFile(const GasCompany& company) {
		wofstream file(filePath);
		if (!file.is_open()) return false;

		file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
		file << company.toString();
		file.close();
		return true;
	}

	bool loadFromFile(GasCompany& company) {
		wifstream file(filePath);
		if (!file.is_open()) {
			return false;
		}

		file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));

		GasCompany tempCompany;
		wstring line;

		if (!getline(file, line)) {
			file.close();
			return false;
		}
		tempCompany.setName(line);

		int stationCount = 0;
		while (true) {
			streampos lineStartPos = file.tellg();
			if (!getline(file, line)) {
				if (file.eof()) {
				}
				else {
				}
				break;
			}

			if (line.empty()) {
				continue;
			}

			int stationNumber;
			try {
				stationNumber = stoi(line);
			}
			catch (const invalid_argument& ia) {
				continue;
			}
			catch (const out_of_range& oor) {
				continue;
			}
			GasStation station(stationNumber);
			stationCount++;

			int pumpCount = 0;
			while (true) {
				streampos pumpLineStartPos = file.tellg();
				if (!getline(file, line)) {
					if (file.eof()) {
					}
					else {
					}
					break;
				}

				if (line.empty()) {
					file.clear();
					file.seekg(pumpLineStartPos);
					break;
				}

				size_t spacePos = line.find(L' ');

				bool isPumpLine = false;
				int pumpNumber = 0;
				wstring fuelType;

				if (spacePos != wstring::npos && spacePos > 0) {
					wstring pumpNumStr = line.substr(0, spacePos);
					try {
						pumpNumber = stoi(pumpNumStr);
						fuelType = line.substr(spacePos + 1);
						isPumpLine = true;
					}
					catch (const invalid_argument& ia) {
						isPumpLine = false;
					}
					catch (const out_of_range& oor) {
						isPumpLine = false;
					}
				}

				if (isPumpLine) {
					GasPump pump(pumpNumber, fuelType);
					if (!station.addPump(pump)) {
					}
					else {
						pumpCount++;
					}
				}
				else {
					file.clear();
					file.seekg(pumpLineStartPos);
					break;
				}
			}
			tempCompany.addStation(station);
		}

		file.close();
		company = tempCompany;
		return true;
	}
};
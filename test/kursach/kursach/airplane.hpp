#pragma once
#include <iostream>
#include <string>
using namespace std;
class airplane {
private:
	struct airplaneInfo {
		string brand;
		short releaseYear;
	} Airplane;
	airplane* next;
public:
	airplane() {
		Airplane.brand = "";
		Airplane.releaseYear = 0;
		next = nullptr;
	}
	void setBrand(string name) {
		Airplane.brand = name;
	}
	void setReleaseYear(short year) {
		Airplane.releaseYear = year;
	}
	void setNext(airplane* nextPoint) {
		next = nextPoint;
	}
	string getBrand() {
		return Airplane.brand;
	}
	short getReleaseYear() {
		return Airplane.releaseYear;
	}
	airplane* getNext() {
		return next;
	}
	~airplane() {}
};
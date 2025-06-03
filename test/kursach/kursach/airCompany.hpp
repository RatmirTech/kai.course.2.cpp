#pragma once
#include <iostream>
#include <string>
#include "airport.hpp"
using namespace std;

class airCompany {
private:
    struct airCompanyInformation {
        string name;
    }airCompanyInfo;
    static constexpr int SIZE_ARRAY = 5;
    airport airports[SIZE_ARRAY];
    int Fullness;
public:
    airCompany() {
        airCompanyInfo.name = "";
        Fullness = 0;
    }
    int isEmpty() {
        if (Fullness == 0) return 1;
        else return 0;

    }
    int isFull() {
        if (Fullness >= SIZE_ARRAY) return 1;
        else return 0;
    }
    bool push(string airportName) {
        int currentPosition = 0;
        airport temp ;
        if (isEmpty()) {
            airports[0].setAirportName(airportName);
            Fullness++;
            return true;
        }
        if (!isFull()) {
            while (airports[currentPosition].getAirportName() < airportName) {
                if (airports[currentPosition].getAirportName() == "") {
                    break;
                }
                currentPosition++;
            }
            //temp = &airports[Fullness];
            for (int i = Fullness-1; i >= currentPosition; i--) {
                airports[i + 1] = airports[i];
            }
            airports[currentPosition] = temp;
            /*if (airports[currentPosition].getSp() != nullptr) {
                while (airports[currentPosition].pop());
            }*/
            airports[currentPosition].setAirportName(airportName);
            Fullness++;
        }
        else return false;
    }
    bool pop() {
        if (!isEmpty()) {
            airports[0].~airport();
            for (int i = 0; i < Fullness - 1; i++) {
                airports[i] = airports[i + 1];

            }
            airports[Fullness - 1].setSp(nullptr);
            Fullness--;
            return true;
        }
        else return false;
    }
    bool showAirports() {
        if (!isEmpty()) {
            for (int i = 0; i < Fullness; i++) {
                cout << i + 1 << ") " << airports[i].getAirportName() << "\n";
            }
            return true;
        }
        else return false;
    }
    bool showAirportsWithAirplanes() {
        airplane* current = nullptr;
        if (!isEmpty()) {
            for (int i = 0; i < Fullness; i++) {
                cout << i + 1 << ") Аэропорт " << airports[i].getAirportName() << "\n";
                airports[i].show();
            }
            return true;
        }
        else return false;
    }
    bool findAirport(string airportName) {
        for (int i = 0; i < Fullness; i++) {
            if (airports[i].getAirportName() == airportName) {
                return true;
            }
        }
        return false;
    }
    //для добавления нового самолета
    airport* getAirport(string airportName) {
        for (int i = 0; i < Fullness; i++) {
            if (airports[i].getAirportName() == airportName) {
                return &airports[i];
            }
        }
        return nullptr;
    }
    bool findAirplane(string airplaneBrand) {
        for (int i = 0; i < Fullness; i++) {
            if (airports[i].findAirplane(airplaneBrand)) {
                return true;
            }
        }
        return false;
    }
    bool findAirplane(int releaseYear) {
        for (int i = 0; i < Fullness; i++) {
            if (airports[i].findAirplane(releaseYear)) {
                return true;
            }
        }
        return false;
    }
    string GetStringForFile()
    {
        string str = "";
        for (int i = 0; i < Fullness; i++) {
            str += airports[i].getAirportName() + airports[i].GetStringForFile() + "\n";
        }
        return str;
    }
    void setName(string newName) {
        airCompanyInfo.name = newName;
    }
    string getName() {
        return airCompanyInfo.name;
    }
    ~airCompany() {
        airplane* current = nullptr;
        airplane* deleteElement = nullptr;
        for (int i = 0; i < Fullness; i++){
            current = airports[i].getSp();
            airports[i].setSp(nullptr);
            while (current != nullptr) {
                deleteElement = current;
                current = current->getNext();
                delete deleteElement;
                deleteElement = nullptr;
            }
        }
    }
};
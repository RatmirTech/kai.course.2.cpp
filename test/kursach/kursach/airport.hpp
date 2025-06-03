#pragma once
#include <iostream>
#include <string>
#include "airplane.hpp"
using namespace std;

class airport {
private:
    struct airportInformation {
        string name;
    }airportInf;
    airplane* sp;
public:
    airport() {
        airportInf.name = "";
        sp = nullptr;
    }
    bool isEmpty() {
        if (sp == nullptr) return 1;
        else return 0;
    }
    void show() {
        if (sp != nullptr) {
            airplane* current;
            current = sp;
            int i = 1;
            do {
                cout << "\t" << i << ") Самолет: " << current->getBrand() << ", год выпуска: " << current->getReleaseYear() << "\n";
                current = current->getNext();
                i++;
            } while (current != nullptr);
        }
        else {
            cout << "\tСписок самолетов пуст.\n";
        }
    }
    airplane* push(string value, int releaseYear) {
        airplane* item = new airplane();
        item->setBrand(value);
        item->setReleaseYear(releaseYear);
        item->setNext(sp);
        sp = item;
        return sp;
    }
    bool pop() {
        if (!isEmpty()) {
            airplane* current;
            current = sp;
            sp = sp->getNext();
            delete current;
            return true;
        }
        else
            return false;
    }
    bool findAirplane(string airplaneBrand) {
        airplane* current = sp;
        while (current != nullptr) {
            if (current->getBrand() == airplaneBrand) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }
    bool findAirplane(int releaseYear) {
        airplane* current = sp;
        while (current != nullptr) {
            if (current->getReleaseYear() == releaseYear) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }
    string getAirportName() {
        return airportInf.name;
    }
    void setAirportName(string newName) {
        airportInf.name = newName;
    }
    airplane* getSp() {
        return sp;
    }
    void setSp(airplane* _sp) {
        sp = _sp;
    }
    string GetStringForFile() {
        string str = "";
        airplane* current = sp;
        airport temp {};
        while (current != nullptr) {
            temp.push(current->getBrand(), current->getReleaseYear());
            current = current->getNext();
        }
        current = temp.getSp();
        while (current != nullptr) {
            str += " " + current->getBrand() + " " + to_string(current->getReleaseYear());
            current = current->getNext();
        }
        return str;
    };

    ~airport() {
        airplane* current = sp;
        airplane* ElementDelete = nullptr;
        while (current != nullptr) {
            ElementDelete = current;
            current = current->getNext();
            delete ElementDelete;
        }
    }

};

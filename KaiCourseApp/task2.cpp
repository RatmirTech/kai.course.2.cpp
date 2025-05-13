//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <cstdlib>
//
//using namespace std;
//
//// ��������� ��� ������������� ������������
//struct FuelPump {
//	int number;         // ����� ������������
//	string fuelType;    // ����� �������
//
//	FuelPump(int n, const string& fuel) : number(n), fuelType(fuel) {}
//};
//
//// ��������� ��� ����������� ������������ �������
//struct DynamicPriorityQueue {
//	struct Element {
//		string name;    // �������� �������� (��������, ������������)
//		int priority;   // ���������
//		Element* next;  // ��������� �� ��������� �������
//
//		Element(const string& n, int p) : name(n), priority(p), next(nullptr) {}
//	};
//
//	Element* head;  // ��������� �� ������ �������
//
//	DynamicPriorityQueue() : head(nullptr) {}
//
//	// ���������� �������� � ������� � �����������
//	void insert(const string& name, int priority) {
//		Element* newElement = new Element(name, priority);
//
//		if (!head || head->priority < priority) {
//			newElement->next = head;
//			head = newElement;
//			return;
//		}
//
//		Element* current = head;
//		while (current->next && current->next->priority >= priority) {
//			current = current->next;
//		}
//
//		newElement->next = current->next;
//		current->next = newElement;
//	}
//
//	// ���������� �������� � ������������ �����������
//	string pop() {
//		if (!head) {
//			return "Queue is empty!";
//		}
//
//		Element* temp = head;
//		string name = head->name;
//		head = head->next;
//		delete temp;
//		return name;
//	}
//
//	// ����������� ���� ��������� �������
//	void display() const {
//		if (!head) {
//			cout << "������� �����!" << endl;
//			return;
//		}
//
//		Element* current = head;
//		while (current) {
//			cout << "������������ �" << current->name << ", ���������: " << current->priority << endl;
//			current = current->next;
//		}
//	}
//
//	// ������������ ������
//	~DynamicPriorityQueue() {
//		while (head) {
//			Element* temp = head;
//			head = head->next;
//			delete temp;
//		}
//	}
//};
//
//// ��������� ��� ������������� ������������
//struct GasStation {
//	int number;                // ����� ������������
//	DynamicPriorityQueue fuelPumpsQueue;  // ������� ������������
//
//	GasStation(int num) : number(num) {}
//
//	// ���������� ������������ � �������
//	void addFuelPump(int number, const string& fuelType, int priority) {
//		fuelPumpsQueue.insert(to_string(number), priority);
//	}
//
//	// ����������� ���������� � ������������� �� ������������
//	void display() {
//		cout << "�������� �" << number << ":" << endl;
//		fuelPumpsQueue.display();
//	}
//};
//
//// ��������� ��� ������������� ���������� ��������
//struct GasCompany {
//	string name;               // �������� ��������
//	GasStation** gasStations;  // ������ ������������
//	int gasStationsCount;      // ���������� ������������
//
//	GasCompany(const string& name, int count) : name(name), gasStationsCount(count) {
//		gasStations = new GasStation * [gasStationsCount];
//	}
//
//	// ���������� ������������ � ��������
//	void addGasStation(int number, int index) {
//		gasStations[index] = new GasStation(number);
//	}
//
//	// ������������ ������
//	~GasCompany() {
//		for (int i = 0; i < gasStationsCount; i++) {
//			delete gasStations[i];
//		}
//		delete[] gasStations;
//	}
//
//	// ���������� ������ � �������� � ��������� ����
//	void saveToFile(const string& filename) {
//		ofstream file(filename);
//		if (file.is_open()) {
//			file << "��������: " << name << endl;
//			for (int i = 0; i < gasStationsCount; i++) {
//				file << "�������� �" << gasStations[i]->number << ":" << endl;
//				// ����� �� ��������� ������ ������ ������������ � �� ����������
//				file << "\t������������: " << endl;
//				gasStations[i]->fuelPumpsQueue.display();
//			}
//			file.close();
//			cout << "������ ��������� � ���� " << filename << endl;
//		}
//		else {
//			cout << "������ ��� �������� �����!" << endl;
//		}
//	}
//
//	// �������� ������ � �������� �� ���������� �����
//	void loadFromFile(const string& filename) {
//		ifstream file(filename);
//		if (file.is_open()) {
//			string line;
//			getline(file, line); // ������ �������� ��������
//			name = line.substr(9); // ������� "��������: "
//
//			int gasStationIndex = 0;
//			while (getline(file, line)) {
//				if (line.find("��������") != string::npos) {
//					int number = stoi(line.substr(10));
//					addGasStation(number, gasStationIndex++);
//				}
//			}
//
//			file.close();
//			cout << "������ ��������� �� ����� " << filename << endl;
//		}
//		else {
//			cout << "������ ��� �������� �����!" << endl;
//		}
//	}
//
//	// ����������� ���� ������������ � �� ������������
//	void display() {
//		cout << "��������: " << name << endl;
//		for (int i = 0; i < gasStationsCount; i++) {
//			gasStations[i]->display();
//		}
//	}
//};
//
//// ������������ ������ � ���������� ��������� � ��������������
//void menu() {
//	GasCompany company("��������", 2); // ������� ��������
//
//	// ��������� ������������ � ������������
//	company.addGasStation(1, 0);
//	company.addGasStation(2, 1);
//	company.gasStations[0]->addFuelPump(1, "��-92", 10);
//	company.gasStations[0]->addFuelPump(2, "��-95", 20);
//	company.gasStations[1]->addFuelPump(1, "������", 5);
//
//	int choice;
//	string filename;
//
//	while (true) {
//		cout << "\n������� ���������� ���������� ���������\n";
//		cout << "1. ���������� ��� ������ � ��������\n";
//		cout << "2. ��������� ������ � ����\n";
//		cout << "3. ��������� ������ �� �����\n";
//		cout << "0. �����\n";
//		cout << "������� ��� �����: ";
//		cin >> choice;
//
//		switch (choice) {
//		case 1:
//			company.display();
//			break;
//
//		case 2:
//			cout << "������� ��� ����� ��� ����������: ";
//			cin >> filename;
//			company.saveToFile(filename);
//			break;
//
//		case 3:
//			cout << "������� ��� ����� ��� ��������: ";
//			cin >> filename;
//			company.loadFromFile(filename);
//			break;
//
//		case 0:
//			return;
//
//		default:
//			cout << "�������� �����, ���������� �����.\n";
//		}
//	}
//}
//
//int main() {
//	setlocale(LC_ALL, "Ru");
//	menu();
//	return 0;
//}

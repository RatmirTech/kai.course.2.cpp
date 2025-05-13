//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <cstdlib>
//
//using namespace std;
//
//// Структура для представления сотрудника
//struct Employee {
//	string name;      // Имя сотрудника
//	string position;  // Должность
//	int priority;     // Приоритет
//
//	Employee* next;   // Указатель на следующий сотрудника
//
//	Employee(string n, string p, int pr) : name(n), position(p), priority(pr), next(nullptr) {}
//};
//
//// Структура для динамической очереди сотрудников
//struct EmployeeQueue {
//	Employee* head;  // Указатель на начало списка
//
//	EmployeeQueue() : head(nullptr) {}
//
//	// Добавление сотрудника в очередь по приоритету
//	void addEmployee(const string& name, const string& position, int priority) {
//		Employee* newEmployee = new Employee(name, position, priority);
//
//		if (!head || head->priority < priority) {
//			newEmployee->next = head;
//			head = newEmployee;
//			return;
//		}
//
//		Employee* current = head;
//		while (current->next && current->next->priority >= priority) {
//			current = current->next;
//		}
//
//		newEmployee->next = current->next;
//		current->next = newEmployee;
//	}
//
//	// Удаление сотрудника по имени
//	bool removeEmployee(const string& name) {
//		if (!head) return false;
//
//		if (head->name == name) {
//			Employee* temp = head;
//			head = head->next;
//			delete temp;
//			return true;
//		}
//
//		Employee* current = head;
//		while (current->next && current->next->name != name) {
//			current = current->next;
//		}
//
//		if (current->next) {
//			Employee* temp = current->next;
//			current->next = current->next->next;
//			delete temp;
//			return true;
//		}
//
//		return false;
//	}
//
//	// Поиск сотрудника по имени
//	Employee* findEmployee(const string& name) {
//		Employee* current = head;
//		while (current) {
//			if (current->name == name) {
//				return current;
//			}
//			current = current->next;
//		}
//		return nullptr;
//	}
//
//	// Сохранение данных в текстовый файл
//	void saveToFile(const string& filename) {
//		ofstream file(filename);
//		if (file.is_open()) {
//			Employee* current = head;
//			while (current) {
//				file << current->name << "," << current->position << "," << current->priority << endl;
//				current = current->next;
//			}
//			file.close();
//			cout << "Data saved to " << filename << endl;
//		}
//		else {
//			cout << "Error opening file!" << endl;
//		}
//	}
//
//	// Загрузка данных из текстового файла
//	void loadFromFile(const string& filename) {
//		ifstream file(filename);
//		if (file.is_open()) {
//			string line;
//			while (getline(file, line)) {
//				stringstream ss(line);
//				string name, position;
//				int priority;
//				getline(ss, name, ',');
//				getline(ss, position, ',');
//				ss >> priority;
//				addEmployee(name, position, priority);
//			}
//			file.close();
//			cout << "Data loaded from " << filename << endl;
//		}
//		else {
//			cout << "Error opening file!" << endl;
//		}
//	}
//
//	// Отображение всех сотрудников
//	void display() const {
//		if (!head) {
//			cout << "No employees in the queue." << endl;
//			return;
//		}
//
//		Employee* current = head;
//		while (current) {
//			cout << "Name: " << current->name << ", Position: " << current->position << ", Priority: " << current->priority << endl;
//			current = current->next;
//		}
//	}
//};
//
//// Демо-модуль с консольным интерфейсом
//void menu() {
//	EmployeeQueue queue;
//	int choice;
//	string name, position, filename;
//	int priority;
//
//	while (true) {
//		cout << "\nEmployee Queue System\n";
//		cout << "1. Add employee\n";
//		cout << "2. Remove employee\n";
//		cout << "3. Find employee\n";
//		cout << "4. Display all employees\n";
//		cout << "5. Save to text file\n";
//		cout << "6. Load from text file\n";
//		cout << "0. Exit\n";
//		cout << "Enter your choice: ";
//		cin >> choice;
//
//		switch (choice) {
//		case 1:
//			cout << "Enter name: ";
//			cin.ignore();
//			getline(cin, name);
//			cout << "Enter position: ";
//			getline(cin, position);
//			cout << "Enter priority: ";
//			cin >> priority;
//			queue.addEmployee(name, position, priority);
//			break;
//
//		case 2:
//			cout << "Enter name to remove: ";
//			cin.ignore();
//			getline(cin, name);
//			if (queue.removeEmployee(name)) {
//				cout << "Employee removed successfully.\n";
//			}
//			else {
//				cout << "Employee not found.\n";
//			}
//			break;
//
//		case 3:
//			cout << "Enter name to find: ";
//			cin.ignore();
//			getline(cin, name);
//			{
//				Employee* emp = queue.findEmployee(name);
//				if (emp) {
//					cout << "Employee found: Name: " << emp->name << ", Position: " << emp->position << ", Priority: " << emp->priority << endl;
//				}
//				else {
//					cout << "Employee not found.\n";
//				}
//			}
//			break;
//
//		case 4:
//			queue.display();
//			break;
//
//		case 5:
//			cout << "Enter filename to save to: ";
//			cin >> filename;
//			queue.saveToFile(filename);
//			break;
//
//		case 6:
//			cout << "Enter filename to load from: ";
//			cin >> filename;
//			queue.loadFromFile(filename);
//			break;
//
//		case 0:
//			return;
//
//		default:
//			cout << "Invalid choice, please try again.\n";
//		}
//	}
//}
//
//int main() {
//	menu();
//	return 0;
//}

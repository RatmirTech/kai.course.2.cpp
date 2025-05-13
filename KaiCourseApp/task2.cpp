//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <cstdlib>
//
//using namespace std;
//
//// Структура для представления бензоколонки
//struct FuelPump {
//	int number;         // Номер бензоколонки
//	string fuelType;    // Марка бензина
//
//	FuelPump(int n, const string& fuel) : number(n), fuelType(fuel) {}
//};
//
//// Структура для динамически приоритетной очереди
//struct DynamicPriorityQueue {
//	struct Element {
//		string name;    // Название элемента (например, бензоколонки)
//		int priority;   // Приоритет
//		Element* next;  // Указатель на следующий элемент
//
//		Element(const string& n, int p) : name(n), priority(p), next(nullptr) {}
//	};
//
//	Element* head;  // Указатель на голову очереди
//
//	DynamicPriorityQueue() : head(nullptr) {}
//
//	// Добавление элемента в очередь с приоритетом
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
//	// Извлечение элемента с максимальным приоритетом
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
//	// Отображение всех элементов очереди
//	void display() const {
//		if (!head) {
//			cout << "Очередь пуста!" << endl;
//			return;
//		}
//
//		Element* current = head;
//		while (current) {
//			cout << "Бензоколонка №" << current->name << ", Приоритет: " << current->priority << endl;
//			current = current->next;
//		}
//	}
//
//	// Освобождение памяти
//	~DynamicPriorityQueue() {
//		while (head) {
//			Element* temp = head;
//			head = head->next;
//			delete temp;
//		}
//	}
//};
//
//// Структура для представления автозаправки
//struct GasStation {
//	int number;                // Номер автозаправки
//	DynamicPriorityQueue fuelPumpsQueue;  // Очередь бензоколонок
//
//	GasStation(int num) : number(num) {}
//
//	// Добавление бензоколонки в очередь
//	void addFuelPump(int number, const string& fuelType, int priority) {
//		fuelPumpsQueue.insert(to_string(number), priority);
//	}
//
//	// Отображение информации о бензоколонках на автозаправке
//	void display() {
//		cout << "Заправка №" << number << ":" << endl;
//		fuelPumpsQueue.display();
//	}
//};
//
//// Структура для представления бензиновой компании
//struct GasCompany {
//	string name;               // Название компании
//	GasStation** gasStations;  // Массив автозаправок
//	int gasStationsCount;      // Количество автозаправок
//
//	GasCompany(const string& name, int count) : name(name), gasStationsCount(count) {
//		gasStations = new GasStation * [gasStationsCount];
//	}
//
//	// Добавление автозаправки в компанию
//	void addGasStation(int number, int index) {
//		gasStations[index] = new GasStation(number);
//	}
//
//	// Освобождение памяти
//	~GasCompany() {
//		for (int i = 0; i < gasStationsCount; i++) {
//			delete gasStations[i];
//		}
//		delete[] gasStations;
//	}
//
//	// Сохранение данных о компании в текстовый файл
//	void saveToFile(const string& filename) {
//		ofstream file(filename);
//		if (file.is_open()) {
//			file << "Компания: " << name << endl;
//			for (int i = 0; i < gasStationsCount; i++) {
//				file << "Заправка №" << gasStations[i]->number << ":" << endl;
//				// Здесь мы сохраняем только номера бензоколонок и их приоритеты
//				file << "\tБензоколонки: " << endl;
//				gasStations[i]->fuelPumpsQueue.display();
//			}
//			file.close();
//			cout << "Данные сохранены в файл " << filename << endl;
//		}
//		else {
//			cout << "Ошибка при открытии файла!" << endl;
//		}
//	}
//
//	// Загрузка данных о компании из текстового файла
//	void loadFromFile(const string& filename) {
//		ifstream file(filename);
//		if (file.is_open()) {
//			string line;
//			getline(file, line); // Читаем название компании
//			name = line.substr(9); // Убираем "Компания: "
//
//			int gasStationIndex = 0;
//			while (getline(file, line)) {
//				if (line.find("Заправка") != string::npos) {
//					int number = stoi(line.substr(10));
//					addGasStation(number, gasStationIndex++);
//				}
//			}
//
//			file.close();
//			cout << "Данные загружены из файла " << filename << endl;
//		}
//		else {
//			cout << "Ошибка при открытии файла!" << endl;
//		}
//	}
//
//	// Отображение всех автозаправок и их бензоколонок
//	void display() {
//		cout << "Компания: " << name << endl;
//		for (int i = 0; i < gasStationsCount; i++) {
//			gasStations[i]->display();
//		}
//	}
//};
//
//// Демонстрация работы с бензиновой компанией и автозаправками
//void menu() {
//	GasCompany company("Роснефть", 2); // Создаем компанию
//
//	// Добавляем автозаправки и бензоколонки
//	company.addGasStation(1, 0);
//	company.addGasStation(2, 1);
//	company.gasStations[0]->addFuelPump(1, "АИ-92", 10);
//	company.gasStations[0]->addFuelPump(2, "АИ-95", 20);
//	company.gasStations[1]->addFuelPump(1, "Дизель", 5);
//
//	int choice;
//	string filename;
//
//	while (true) {
//		cout << "\nСистема управления бензиновой компанией\n";
//		cout << "1. Отобразить все данные о компании\n";
//		cout << "2. Сохранить данные в файл\n";
//		cout << "3. Загрузить данные из файла\n";
//		cout << "0. Выход\n";
//		cout << "Введите ваш выбор: ";
//		cin >> choice;
//
//		switch (choice) {
//		case 1:
//			company.display();
//			break;
//
//		case 2:
//			cout << "Введите имя файла для сохранения: ";
//			cin >> filename;
//			company.saveToFile(filename);
//			break;
//
//		case 3:
//			cout << "Введите имя файла для загрузки: ";
//			cin >> filename;
//			company.loadFromFile(filename);
//			break;
//
//		case 0:
//			return;
//
//		default:
//			cout << "Неверный выбор, попробуйте снова.\n";
//		}
//	}
//}
//
//int main() {
//	setlocale(LC_ALL, "Ru");
//	menu();
//	return 0;
//}

Приложения
Листинг программы:
Company.cpp:
#pragma once
#include "Factory.cpp"

class Company
{
private:
	struct CompanyInfo {
		string name;
	}company;

	Factory* head;
	Factory* tail;

public:
	Company() {
		company.name = "";
		head = new Factory();
		tail = head;
	}
	Company(string name) {
		company.name = name;
		head = new Factory();
		tail = head;
	}
	~Company() {
		while (!IsEmpty()) {
			Factory* temp = head->GetNext();
			head->SetNext(temp->GetNext());
			delete temp;
		}
		delete head;
	}
	bool IsEmpty() {
		return head->GetNext() == nullptr;
	}
	void Add(Factory* manufacture) {
		tail->SetNext(manufacture);
		tail = manufacture;
	}
	string Delete() {
		if (IsEmpty())
			return nullptr;
		Factory* temp = head->GetNext();
		head->SetNext(temp->GetNext());
		
		if (IsEmpty())
			tail = head;

		string _temp = temp->GetText();
		delete temp;
		return _temp;
	}
	Factory* Search(string num){
		if (IsEmpty())
			return nullptr;
		
		Factory* temp = head->GetNext();
		while (temp != nullptr) {
			if (temp->GetText() == num)
				return temp;
			temp = temp->GetNext();
		}
		return nullptr;
	}
	Factory* SearchElement(string name) {
		if (IsEmpty())
			return nullptr;
		
		Factory* temp = head->GetNext();
		while (temp != nullptr) {
			Object* _temp = temp->Search(name);
			if (_temp != nullptr)
				return temp;
			temp = temp->GetNext();
		}
		return nullptr;
	}
	void Show() {
		cout << "Компания \"ООО " << company.name << "\"\n";
		if (IsEmpty())
			cout << "Производства отсутствуют\n";
		else {
			Factory* temp = head->GetNext();
			while (temp != nullptr) {
				temp->Show();
				temp = temp->GetNext();
			}
		}
	}
	void SetName(string _name) {
		company.name = _name;
	}

	void SetHead(Factory* _head) {
		head = _head;
	}

	void SetTail(Factory* _tail) {
		tail = _tail;
	}

	string GetName() {
		return company.name;
	}

	Factory* GetHead() {
		return head;
	}

	Factory* GetTail() {
		return tail;
	}
};

Factory.cpp:
#pragma once
#include "Object.cpp"
#include <iostream>
using namespace std;

class Factory
{
private:
	struct FactoryInfo {
		string num;
	}factory;
	
	Factory* next;
	Object* head;
	Object* tail;
public:
	Factory() {
		factory.num = -1;
		next = nullptr;

		head = new Object();
		tail = head;
	}
	Factory(string _num){
		factory.num = _num;
		next = nullptr;

		head = new Object();
		tail = head;
	}
	~Factory() {
		while (!IsEmpty()) {
			Object* temp = head->GetNext();
			head->SetNext(temp->GetNext());
			delete temp;
		}
		delete head;
		head = nullptr;
		tail = nullptr;
		next = nullptr;
	}
	bool IsEmpty() {
		return(head->GetNext() == nullptr);
	}
	void Add(Object* obj) {
		tail->SetNext(obj);
		tail = obj;
	}
	string Delete() {
		if (IsEmpty())
			return "";

		Object* temp = head->GetNext();
		head->SetNext(temp->GetNext());
		
		if (IsEmpty()) //Если после удаления очередь стала пустой
			head = tail;

		string _temp = temp->GetName();
		delete temp;
		return _temp;
	}

	Object* Search(string name){
		if (IsEmpty())
			return nullptr;
		
		Object* temp = head->GetNext();
		while (temp != nullptr)
		{
			if (temp->GetName() == name)
				return temp;
			temp = temp->GetNext();
		}
		return nullptr;
	}

	void Show() {
		cout << "\nФабрика <№" << factory.num << ">:\n";
		if (IsEmpty())
			cout << "Оборудование отсутствует!\n";
		else{
			Object* temp = head->GetNext();
			while (temp != nullptr) {
				cout << temp->GetName() << " в количестве " << temp->GetNum() << "шт.\n";
				temp = temp->GetNext();
			}
		}
	}

	void SetNext(Factory* _next) {
		next = _next;
	}

	void SetTNum(int _num) {
		factory.num= _num;
	}

	void SetHead(Object* _head) {
		head = _head;
	}

	void SetTail(Object* _tail) {
		tail = _tail;
	}

	string GetText() {
		return factory.num;
	}

	Factory* GetNext() {
		return next;
	}

	Object* GetHead() {
		return head;
	}

	Object* GetTail() {
		return tail;
	}
};
Object.cpp:
#pragma once
#include <string>
using namespace std;

class Object {
private:
	struct ObjectInfo {
		string name;
		string num;
	}object;

	Object* next;
public:
	Object(){
		object.name = "";
		object.num = -1;
		next = nullptr;
	}
	
	Object(string name, string num){
		object.name = name;
		object.num = num;
		next = nullptr;
	}
	
	~Object(){
		next = nullptr;
	}

	void SetName(string name){
		object.name = name;
	}

	void SetNum(int num){
		object.num = num;
	}

	void SetNext(Object* _next) {
		next = _next;
	}

	string GetName(){
		return object.name;
	}

	string GetNum(){
		return object.num;
	}

	Object* GetNext() {
		return next;
	}
	
};
CW_40.4.cpp:
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Company.cpp"

using namespace std;

Company* company = nullptr;

int GetNaturalValue() {
    int answer;
    while (!(cin >> answer) || (cin.peek() != '\n') || (answer < 0))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Ошибка: введено некорректное число. " << endl <<
            "Повторите ввод: " << endl;
    }
    return answer;
}

string GetCorrectString() {
    string str;
    getline(cin, str);
    while (str.empty())
    {
        cout << "Ошибка: введена некорректная строка." << endl <<
            "Повторите ввод: " << endl;
        getline(cin, str);
    }
    return str;
}

void Dialog() {
    int answer = -1;
    while (answer != 0)
    {
        cout <<
            "Выберите пункт: " << endl <<
            "1 - Создать компанию." << endl <<
            "2 - Удалить компанию." << endl <<
            "3 - Добавить завод." << endl <<
            "4 - Удалить завод." << endl <<
            "5 - Добавить объект." << endl <<
            "6 - Удалить объект." << endl <<
            "7 - Поиск объекта на заводе." << endl <<
            "8 - Поиск объекта в компании." << endl <<
            "9 - Вывести состояние компании в консоль." << endl <<
            "10 - Загрузить." << endl <<
            "11 - Сохранить." << endl <<
            "0 - Завершить работу с программой." << endl;

        answer = GetNaturalValue();
        system("cls");
        switch (answer)
        {
        case 1:
        {
            delete company;
            cout << "Введите название компании: " << endl;
            cin.ignore();
            string name = GetCorrectString();
            company = new Company(name);
            cout << "Компания <" << company->GetName() << "> успешно создана!" << endl;

            break;
        }
        case 2:

            if (company != nullptr)
            {
                delete company;
                company = nullptr;
                cout << "Компания успешно удалена!" << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 3:

            if (company != nullptr)
            {
                cout << "Введите номер создаваемого завода: " << endl;
                cin.ignore();
                string number = GetCorrectString();

                company->Add(new Factory(number));
                cout << "Завод <" << number << "> успешно добавлен!" << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 4:

            if (company != nullptr)
            {
                string number = company->Delete();
                if (!number.empty())
                    cout << "Завод <" << number << "> успешно удален!" << endl;
                else
                    cout << "Удаление невозможно: компания пуста." << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 5:

            if (company != nullptr)
            {
                company->Show();

                cout << "Введите номер завода, куда планируется добавить объект: " << endl;
                cin.ignore();
                string number = GetCorrectString();
                Factory* factory = company->Search(number);

                if (factory != nullptr)
                {
                    cout << "Введите название объекта: " << endl;
                    string name = GetCorrectString();
                    cout << "Укажите количество объектов: " << endl;
                    string num = GetCorrectString();

                    factory->Add(new Object(name, num));
                    cout << "Объект <" << name << "> добавлен на завод в количестве " << num << "!" << endl;
                }
                else
                    cout << "К сожалению, искомый завод не найден." << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 6:

            if (company != nullptr)
            {
                company->Show();

                cout << "Введите номер завода, откуда необходимо удалить объект: " << endl;
                cin.ignore();
                string number = GetCorrectString();
                Factory* factory = company->Search(number);

                if (factory != nullptr)
                {
                    string name = factory->Delete();

                    if (!name.empty())
                        cout << "Объект <" << name << "> успешно удален с завода!" << endl;
                    else
                        cout << "Ошибка удаления: завод пуст." << endl;
                }
                else
                    cout << "К сожалению, искомый завод не найден." << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 7:

            if (company != nullptr)
            {
                company->Show();

                cout << "Введите номер завода, где необходимо найти объект: " << endl;
                cin.ignore();
                string number = GetCorrectString();
                Factory* factory = company->Search(number);

                if (factory != nullptr)
                {
                    cout << "Введите название искомого объекта:" << endl;
                    string name = GetCorrectString();

                    Object* object = factory->Search(name);
                    if (object)
                        cout << "Объект <" << name << "> обнаружен!" << endl <<
                        "Количество объектов - " << object->GetNum() << endl;
                    else
                        cout << "Объект не найден." << endl;
                }
                else
                    cout << "К сожалению, искомый завод не найден." << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 8:
            if (company != nullptr)
            {
                company->Show();

                cout << "Введите название искомого объекта:" << endl;
                cin.ignore();
                string name = GetCorrectString();

                Factory* factory = company->SearchElement(name);
                if (factory)
                    cout << "Объект <" << name << "> обнаружен " <<
                    "на заводе <" << factory->GetText() << ">!" << endl;
                else
                    cout << "Объект не найден." << endl;
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 9:
            if (company != nullptr)
            {
                company->Show();
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;

        case 10:
        {
            ifstream in;
            in.open("save.txt");

            if (!in.is_open())
            {
                cout << "Ошибка чтения файла." << endl;
            }
            else
            {
                delete company;
                company = nullptr;

                char line[1000];

                in.getline(line, 1000);

                if (strlen(line) != 0)
                    company = new Company(line);
                else
                {
                    cout << "Ошибка чтения: файл пуст!" << endl;
                    break;
                }

                while (!in.eof()) {

                    in.getline(line, 1000);

                    char* parts = strtok(line, "><");

                    if (parts == NULL)
                        continue;

                    Factory* factory = new Factory(parts);
                    company->Add(factory);
                    parts = strtok(NULL, "><");

                    while (parts) {
                        string text = parts;
                        parts = strtok(NULL, "><");
                        string num = parts;
                        parts = strtok(NULL, "><");
                        Object* object = new Object(text, num);
                        factory->Add(object);
                    }
                }
            }
            in.close();
            cout << "Данные успешно загружены!" << endl;

            break;
        }
        case 11:
        {
            if (company != nullptr)
            {
                ofstream out;
                out.open("save.txt");

                if (!out.is_open())
                {
                    cout << "Ошибка записи файла." << endl;
                }
                else
                {
                    out << company->GetName() << endl;

                    Factory* factory = company->GetHead()->GetNext();
                    while (factory != nullptr) {
                        out << factory->GetText();
                        Object* object = factory->GetHead()->GetNext();
                        while (object != nullptr)
                        {
                            out << "><" << object->GetName() << "><" << object->GetNum();
                            object = object->GetNext();
                        }
                        factory = factory->GetNext();
                        out << endl;
                    }

                    out.close();
                    cout << "Данные успешно сохранены!" << endl;
                }
            }
            else
                cout << "Для работы с компанией необходимо её создание." << endl;

            break;
        }
        case 0:
            cout << "Всего доброго!" << endl;
            break;

        default:
            cout << "Ошибка: выбранного вами пункта не существует." << endl;
            break;
        }
        system("pause");
        system("cls");
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Dialog();
    return 0;
}

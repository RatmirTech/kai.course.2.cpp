#pragma once
#include <iostream>

using namespace std;

template <typename T>
class PriorityQueue {
private:
	struct Node {
		T data;
		int priority;
		Node* next;

		Node(const T& d, int p) : data(d), priority(p), next(nullptr) {}
	};

	Node* head;

public:
	PriorityQueue() : head(nullptr) {}

	PriorityQueue(const PriorityQueue& other) : head(nullptr) {
		Node* currentOther = other.head;
		Node* lastNewNode = nullptr;

		while (currentOther) {
			Node* newNode = new Node(currentOther->data, currentOther->priority);
			if (!head) {
				head = newNode;
			}
			else {
				lastNewNode->next = newNode;
			}
			lastNewNode = newNode;
			currentOther = currentOther->next;
		}
	}

	PriorityQueue& operator=(const PriorityQueue& other) {
		if (this == &other) {
			return *this;
		}

		clear();

		Node* currentOther = other.head;
		Node* lastNewNode = nullptr;

		while (currentOther) {
			Node* newNode = new Node(currentOther->data, currentOther->priority);
			if (!head) {
				head = newNode;
			}
			else {
				lastNewNode->next = newNode;
			}
			lastNewNode = newNode;
			currentOther = currentOther->next;
		}
		return *this;
	}

	PriorityQueue(PriorityQueue&& other) noexcept : head(other.head) {
		other.head = nullptr;
	}

	PriorityQueue& operator=(PriorityQueue&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		clear();

		head = other.head;
		other.head = nullptr;

		return *this;
	}

	~PriorityQueue() {
		if (head) {
			while (head) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
		}
	}

	void clear() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	bool enqueue(const T& data, int priority) {
		Node* newNode = new Node(data, priority);

		if (!head || priority < head->priority) {
			newNode->next = head;
			head = newNode;
			return true;
		}

		Node* current = head;
		while (current->next && current->next->priority <= priority) {
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
		return true;
	}

	bool dequeue() {
		if (!head) return false;

		Node* temp = head;
		head = head->next;
		delete temp;
		return true;
	}

	T* front() const {
		if (!head) return nullptr;
		return &head->data;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	bool remove(int priority) {
		if (!head) return false;

		if (head->priority == priority) {
			Node* temp = head;
			head = head->next;
			delete temp;
			return true;
		}

		Node* current = head;
		while (current->next && current->next->priority != priority) {
			current = current->next;
		}

		if (!current->next) return false;

		Node* temp = current->next;
		current->next = temp->next;
		delete temp;
		return true;
	}

	T* find(int priority) {
		Node* current = head;
		while (current) {
			if (current->priority == priority) {
				return &current->data;
			}
			current = current->next;
		}
		return nullptr;
	}

	void display() const {
		Node* current = head;
		while (current) {
			current->data.display();
			wcout << L"\n";
			current = current->next;
		}
	}

	wstring toString() const {
		wstring result;
		Node* current = head;
		while (current) {
			result += current->data.toString() + L"\n";
			current = current->next;
		}
		return result;
	}
};
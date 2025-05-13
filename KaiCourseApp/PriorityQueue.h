#pragma once
#include <iostream>

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

	~PriorityQueue() {
		clear();
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
			std::wcout << L"\n";
			current = current->next;
		}
	}

	std::wstring toString() const {
		std::wstring result;
		Node* current = head;
		while (current) {
			result += current->data.toString() + L"\n";
			current = current->next;
		}
		return result;
	}
};
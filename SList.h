//singly linked list
#ifndef _SLIST_H_
#define _SLIST_H_

#include <iostream>
#include "Node.h"


template <class T>
struct SList {
	NNode<T> * start;
	SList() {
		start = nullptr;
	}

	~SList() {
		if (start != nullptr) {
			while (start->next != nullptr) {
				NNode<T> * temp = start->next;
				delete start;
				start = temp;
			}
		}
	}

	void addFront(const T& data) {
		NNode<T> * temp = new NNode<T>;
		temp->value = data;
		temp->pre = nullptr;
		if (start == nullptr) {
			temp->next = nullptr;
			start = temp;
		} else {
			temp->next = start;
			start = temp;
		}
	}

	void removeFront() {
		if (start != nullptr) {
			if (start->next == nullptr) {
				delete start;
				start = nullptr;
			} else {
				NNode<T> * temp = start;
				start = start->next;
				delete temp;
			}
		}
	}

	void pushBack(const T& data) {
		NNode<T>* temp = new NNode<T>;
		temp->value = data;
		temp->next = nullptr;
		if (start == nullptr) {
			start = temp;
		} else {
			NNode<T> * curr = start;
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = temp;
		}
	}

	void removeBack() {
		if (start != nullptr) {
			if (start->next == nullptr) {
				delete start;
				start = nullptr;
			} else {
				NNode<T> * secondLast = start;
				while (secondLast->next->next != nullptr) {
					secondLast = secondLast->next;
				}
				delete secondLast->next;
				secondLast->next = nullptr;
			}
		}
	}

	void printEverything() {
		if (start == nullptr) {
			std::cout << "Nothing here!! " << std::endl;
		} else {
			NNode<T> * curr;
			for (curr = start; curr->next != nullptr ; curr = curr->next) {
				curr->display(std::cout);
				std::cout << " -- ";
			}
			curr->display(std::cout);
		}
	}
};
#endif
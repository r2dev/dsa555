
#ifndef __STACK_H_
#define __STACK_H_
#include "Node.h"
#include <iostream>
template <class T>
struct Stack {
	NNode<T> * start;
	Stack() {
		start = nullptr;
	}
	~Stack() {
		if (start != nullptr) {
			while (start->next != nullptr) {
				NNode<T> * tmp = start;
				start = start->next;
				delete tmp;
			}
		}
	}

	void push(const T& data) {
		NNode<T> * temp = new NNode<T>;
		temp->value = data;
		temp->next = start;
		start = temp;
	}

	T pop() {
		T tmp = start->value; 
		NNode<T> * temp = start;
		start = start->next;
		delete temp;
		return tmp;
	}
	void printEverything() const
	{
		if (start == nullptr) {
			std::cout << "Nothing here" << std::endl;	
		} else {
			NNode<T> * curr = start;
			for (; curr->next != nullptr; curr = curr->next) {
				curr->display(std::cout);
				std::cout << " -- ";
			}
			curr->display(std::cout);
		}
	}
};

#endif
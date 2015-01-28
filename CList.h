//Circular Linked list
#ifndef _CLIST_H_
#define _CLIST_H_
#include <iostream>
#include "Node.h"
template <class T>
struct CList {
	NNode<T> * curr;
	
	CList() {
		curr = nullptr;
	}
	void add(const T& data) {
		NNode<T> * temp = new NNode<T>;
		temp->value = data;
		temp->next = curr;
		if (curr == nullptr) {
			curr = temp;
		} else {
			curr->next = temp;
			curr = temp;
		}
	}

	void del() {
		if (curr != nullptr) {
			if (curr->next = curr) {// only one 
				delete curr;
				curr = nullptr;
			} else {
				NNode<T> * temp = curr->next;
				curr->next = temp->next;
				delete temp;
			}
		}
	}
};
#endif
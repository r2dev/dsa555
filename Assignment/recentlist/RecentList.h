#ifndef _RECENTLIST_H_
#define _RECENTLIST_H_

#include <iostream>
template <typename T>
struct Node
{
	T value;
	Node * next;
	Node * prev;
	Node() = delete;
	Node(const T& v, Node * p, Node * n)
	{
		value = v;
		prev = p;
		next = n;
	}
};

template <typename T>
class RecentList
{
private:
	Node<T> * start;



public:
	RecentList()
	{
		start = NULL;
	}

	~RecentList()
	{
		Node<T> * cur = start;
		while (cur) {
			Node<T> * tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}
	//test print function
	void print()
	{
		Node<T> * cur = start;
		while (cur) {
			std::cout << cur->value << std::endl;
			cur = cur->next;
		}
	}


	void insert(const T& data)
	{
		// add data at front of list
		Node<T> * tmp = new Node<T>(data, NULL, start);
		if (start != NULL)
			start->prev = tmp;
		start = tmp;
	}

	void remove(const T& key, bool(*isSame)(const T&, const T&))
	{
		Node<T> * cur = start;
		while (cur && !isSame(cur->value, key)) {
			cur = cur->next;
		}
		if (cur == start) {
			start = start->next;
			delete cur;
			return;
		}
		if (cur == NULL) {
			return;
		}
		else {
			if (cur->prev != NULL)
				cur->prev->next = cur->next;
			if (cur->next != NULL)
				cur->next->prev = cur->prev;
			delete cur;
			return;
		}

	}

	Node<T> * search(const T& key, bool(*isSame)(const T&, const T&))
	{
		Node<T> * cur = start;

		while (cur && !isSame(cur->value, key)) {
			cur = cur->next;
		}
		if (cur == start) {
			return start;
		}
		if (cur == NULL) {
			return NULL;
		}
		else {
			if (cur->prev != NULL)
				cur->prev->next = cur->next;
			if (cur->next != NULL)
				cur->next->prev = cur->prev;
			cur->prev = NULL;
			start->prev = cur;
			cur->next = start;
			start = cur;

			return cur;
		}

	}

	bool copyToArray(T array[], int capacity)
	{
		Node<T> * cur = start;
		int count = 0;
		while (cur) {
			array[count] = cur->value;
			cur = cur->next;
			if (count++ == capacity) {
				return false;
			}
		}
		return true;
	}

	RecentList(const RecentList<T>& src)
	{
		start = NULL;
		*this = src;
	}

	RecentList& operator=(const RecentList<T>& src)
	{
		if (this != &src) {
			Node<T> * cur = start;
			while (cur) {
				Node<T> * tmp = cur->next;
				delete cur;
				cur = tmp;
			}
			start = NULL;
			if (src.start != NULL) {
				Node<T> * tmp = src.start;
				Node<T> * end = start;
				Node<T> * pre = NULL;
				while (tmp) {

					end = new Node<T>(tmp->value, pre, NULL);

					if (pre != NULL) {
						pre->next = end;
					}
					else {
						start = end;
					}
					pre = end;
					tmp = tmp->next;
				}
			}
		}
		return *this;
	}

};












#endif
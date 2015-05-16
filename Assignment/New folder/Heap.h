#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>
template <typename T>
class Heap {
	T ** root;
	size_t size;
	size_t max;
	inline void swap(T* a, T* b)
	{
		if (a != b) {
			*a ^= *b;
			*b ^= *a;
			*a ^= *b;
		}
	}

	void adjust(int n) {
		if ((root[(2 * n) + 1] == nullptr && root[(2 * n) + 2] == nullptr) || (size < 2 * n)) {
			//leaf
			return;
		}
		else if (root[(2 * n) + 1] != nullptr && root[(2 * n) + 2] == nullptr){  // one <- child
			if (*root[n] < *root[(2 * n) + 1]) {
				swap(root[n], root[(2 * n) + 1]);
				adjust(2 * n + 1);
			}
		}
		else if (root[(2 * n) + 1] == nullptr && root[(2 * n) + 2] != nullptr) { // one -> child
			if (*root[n] < *root[(2 * n) + 2]) {
				swap(root[n], root[(2 * n) + 2]);
				adjust(2 * n + 2);
			}
		}
		else if (*root[n] < *root[(2 * n) + 1] || *root[n] < *root[(2 * n) + 2]){ // two child and one bigger than parent
			int bigger = (*root[(2 * n) + 1] > *root[(2 * n) + 2]) ?
				2 * n + 1 : 2 * n + 2;
			swap(root[n], root[bigger]);
			adjust(bigger);
		}

	}

public:
	Heap(int s)
	{
		root = new T*[s];
		for (int i = 0; i != s; i++) {
			root[i] = nullptr;
		}

		size = 0;
		max = s;
	}

	~Heap()
	{
		if (root != nullptr) {
			for (int i = 0; i != max; i++) {
				if (root[i] != nullptr) {
					delete root[i];
					root[i] = nullptr;
				}
			}
			delete[] root;
			root = nullptr;
		}
	}
	T get()
	{
		return *root[0];
	}
	void insert(const T& t)
	{
		if (size + 1 == max) {
			//grow
			T** tmp = new T*[max * 2];
			max *= 2;
			for (int i = 0; i != max; i++) {
				tmp[i] = nullptr;
			}
			for (int i = 0; i != size; i++) {
				tmp[i] = root[i];
			}
			delete[] root;
			root = tmp;
		}
		root[size] = new T(t);
		int n = size;
		size++;
		while (n != 0 && (*root[n] > *root[(n - 1) / 2])) {
			swap(root[n], root[(n - 1) / 2]);
			n = (n - 1) / 2;

		}
	}
	T remove(void)
	{
		T result = *(root[0]);
		delete root[0];
		root[0] = root[size - 1];
		root[size - 1] = nullptr;
		size--;
		adjust(0);
		return result;
	}
	void print() 
	{
		for (int i = 0; i != size; i++) {
			std::cout << "--" << *(root[i]);
		}
		std::cout << "\n";
	}
};

#endif
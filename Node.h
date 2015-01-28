#ifndef _NODE_H_
#define _NODE_H_
#include <iostream>
template <class T>
struct NPNode {
	//N0de contain next node point and previous node point
	//N(ext)P(revious)Node
	T value;
	NPNode * pre;
	NPNode * next;
	void display(std::ostream& os) const {
		os << value;
	}	
};

template <class T>
struct NNode {
	T value;
	NNode * next;
	void display(std::ostream& os) const {
		os << value;
	}
};

#endif
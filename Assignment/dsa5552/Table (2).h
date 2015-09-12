#ifndef _TABLE_H_
#define _TABLE_H_
#include <cstring>
#include <string>
#include <iostream>
#include <utility>
#include <fstream>

template <class T>
struct Record {
	char * key;
	T value;
	Record()
	{
		key = "";
	}
	Record(char* s, const T& v)
	{
		key = s;
		value = v;
	}
	bool isEmpty()
	{
		if (key == "") {
			return true;
		}
		else {
			return false;
		}

	}
};

struct Node {

};
template <class T>
class Table{
public:
	Table(){}
	Table(const Table& other){}
	virtual bool update(const char* key, const T& value) = 0;
	virtual bool remove(const char* key) = 0;
	virtual bool find(const char* key, T& value) = 0;
	virtual int size() const = 0;
	virtual bool isFull() const = 0;
	virtual bool isEmpty() const = 0;
	virtual const Table& operator=(const Table<T>& other){ return *this; }
	virtual ~Table(){}
};

template <class T>
class SimpleTable :public Table < T > {

	int size_;
	int maxSize_;
	Record<T> * data_;

	int binary_search(Record<T> records[], const char* key, int min, int max, T& value)
	{

		if (max < min) {
			return -1;
		}
		else {
			int mid = (min + max) / 2;
			if (strcmp(records[mid].key, key) > 0) {
				return binary_search(records, key, min, mid - 1, value);
			}
			else if (strcmp(records[mid].key, key) < 0) {
				return binary_search(records, key, mid + 1, max, value);
			}
			else {
				value = records[mid].value;
				return mid;
			}
		}
	}
public:
	SimpleTable()
	{
		data_ = nullptr;
		size_ = 0;
		maxSize_ = 0;
	}
	SimpleTable(int maxExpected)
	{
		data_ = new Record<T>[maxExpected];
		size_ = 0;
		maxSize_ = maxExpected;
	}
	SimpleTable(const SimpleTable& other)
	{
		data_ = nullptr;
		*this = other;
	}
	virtual bool update(const char* key, const T& value)
	{
		//if find update
		//if not find create

		for (int i = 0; i < maxSize_; i++) {
			if (data_[i].isEmpty()){
				data_[i].key = (char*)key;
				data_[i].value = value;
				size_++;
				return true;
			}
			else if (strcmp(data_[i].key, key) == 0) {
				data_[i].value = value;
				return true;
			}
			else if (strcmp(data_[i].key, key) > 0) {
				if (size_ + 1 <= maxSize_) {
					for (int j = size_ - 1; j >= i; j--) {
						data_[j + 1] = data_[j];
					}
					size_++;
					data_[i].key = (char*)key;
					data_[i].value = value;
					return true;
				}
				else {
					Record<T> * newData = new Record<T>[maxSize_ * 2];
					for (int i = 0; i != size_; i++) {
						newData[i] = data_[i];
					}
					maxSize_ *= 2;
					delete[] data_;
					data_ = newData;
					for (int j = size_ - 1; j >= i; j--) {
						data_[j + 1] = data_[j];

					}
					size_++;
					data_[i].key = (char*)key;
					data_[i].value = value;
					return true;
				}
			}

		}

	}
	void print()
	{
		for (int i = 0; i < size_; i++) {
			std::cout << data_[i].key << "-" << data_[i].value << std::endl;
		}

	}
	virtual bool remove(const char* key)
	{
		T tmp;
		int pos;
		Record<T> dummy;
		pos = binary_search(data_, key, 0, size_, tmp);
		if (pos == -1) {
			return false;
		}
		else {
			if (pos == size_ - 1) {
				data_[pos] = dummy;
			}
			for (int i = pos; i < size_ - 1; i++) {
				data_[i] = data_[i + 1];
			}
			size_ -= 1;
		}

	}
	virtual bool find(const char* key, T& value)
	{
		return (binary_search(data_, key, 0, size_, value) == -1) ? false : true;
	}
	virtual int size() const
	{
		return size_;
	}
	virtual bool isFull() const
	{
		if (size_ == maxSize_) {
			return true;
		}
		if (size_ < maxSize_) {
			return false;
		}
	}
	virtual bool isEmpty() const
	{
		return (size_ == 0) ? true : false;
	}
	virtual const SimpleTable& operator=(const SimpleTable& other)
	{
		if (this != &other) {
			size_ = other.size_;
			maxSize_ = other.size_;
			delete[] data_;
			if (other.data_ != nullptr) {
				data_ = new Record<T>[other.maxSize_];
				for (int i = 0; i != other.size_; i++) {
					data_[i].key = other.data_[i].key;
					data_[i].value = other.data_[i].value;
				}
			}
			else
				data_ = nullptr;
		}
		return *this;
	}
	virtual ~SimpleTable()
	{
		if (data_ != nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
	}
};



template <class T>
class HashTable :public Table<T>{
	Record<T> * data_;
	int maxSize_;
	int size_;
	Record<T> * probe(const char* key)
	{
		std::string key_string(key);
		std::hash<std::string> string_hash;
		Record<T> * cur = data_ + (string_hash(key_string) % (maxSize_ - 1));
		const Record<T> * end = data_ + maxSize_;
		while (cur->key != "" && strcmp(key, cur->key) != 0) {
			cur++;
			if (cur >= end) {
				cur = data_;
			}
		}
		return cur;
	}
public:
	HashTable()
	{
		data_ = nullptr;
		maxSize_ = 0;
		occupancy = 0;
	}
	HashTable(const HashTable& other)
	{
		data_ = nullptr;
		*this = other;
	}
	HashTable(int maxExpected)
	{
		data_ = new Record<T>[maxExpected];
		maxSize_ = maxExpected;
		size_ = 0;
		for (int i = 0; i != maxSize_; i++) {
			data_[i].key = "";
		}
	}
	void print()
	{
		for (int i = 0; i != maxSize_; i++) {
			std::cout << data_[i].value << std::endl;
		}
	}
	virtual bool update(const char* key, const T& value)
	{
		Record<T> * pos = probe(key);
		if (pos->key != "") {
			pos->value = value;
			return true;
		}
		else {
			//create
			pos->key = (char*)key;
			pos->value = value;
			size_++;
			if (size_ >= maxSize_ - size_ * 0.35) {
				//resize
				Record<T> * newData = data_;
				int newSize = size_;
				data_ = new Record<T>[maxSize_ * 2];
				maxSize_ *= 2;
				size_ = 0;
				for (int i = 0; i != maxSize_; i++) {
					data_[i].key = "";
				}
				Record<T> * temp = newData;
				for (int i = 0; i != newSize; i++) {
					if (temp->key != "") {

						Record<T> * reinsert_pos = probe(temp->key);
						if (reinsert_pos->key != "") {
							//reinsert (update)
							reinsert_pos->value = temp->value;
							return true;
						}
						else {
							reinsert_pos->key = temp->key;
							reinsert_pos->value = temp->value;
							size_++;
							return true;
						}
					}
				}
				return false;
			}
		}
	}
	virtual bool remove(const char* key)
	{
		std::string temp_key;
		std::hash<std::string> string_hash;
		Record<T> * pos = probe(key);
		if (pos->key == "") {
			return false;
		}
		else {
			//find
			Record<T> * cur = pos;
			while (cur->key != "") {
				cur++;
				if (cur == data_ + maxSize_) {
					cur = data_;
				}
				temp_key = cur->key;
				Record<T> * tempos = data_ + (string_hash(temp_key) % (maxSize_ - 1));
				if (((cur > pos) && (tempos <= pos || tempos > cur))      // the location before the space or after the position
					|| ((cur < pos) && (tempos <= pos && tempos > cur))) {
					*pos = *cur;
					pos = cur; // move space?
				}
			}
			pos->key = "";
			size_--;
			return true;
		}
	}
	virtual bool find(const char* key, T& value)
	{
		Record<T> * pos = probe(key);
		if (pos->key != "") {
			value = pos->value;
			return true;
		}
		else {
			return false;
		}
	}
	virtual int size() const
	{
		return size_;
	}
	virtual bool isFull() const
	{
		return (size_ == maxSize_) ? true : false;
	}
	virtual bool isEmpty() const
	{
		return (size_ == 0) ? true : false;
	}
	virtual const HashTable& operator=(const HashTable& other)
	{
		if (this != &other) {
			size_ = other.size_;
			maxSize_ = other.maxSize_;
			delete[] data_;
			if (other.data_ != nullptr) {
				data_ = new Record<T>[other.maxSize_];
				for (int i = 0; i != other.size_; i++) {
					data_[i].key = other.data_[i].key;
					data_[i].value = other.data_[i].value;
				}
			}
			else
				data_ = nullptr;
		}
		return *this;
	}
	virtual ~HashTable()
	{
		if (data_ == nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
	}

};



template <class T>
class TreeTable
{
	Record<T> * root;
};
#endif

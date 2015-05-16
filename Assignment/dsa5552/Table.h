#ifndef _TABLE_H_
#define _TABLE_H_
#include <cstring>
#include <string>
#include <iostream>
#include <utility>

template <class T>
struct Record {
	std::string key;
	T value;
	Record()
	{
		key = "";
	}
	Record(const char* s, const T& v)
	{
		key = s;
		value = v;
	}
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
class SimpleTable :public Table<T>{

	int size_;
	int maxSize_;
	Record<T> * data_;

	int binary_search(Record<T> records[], const char* key, int min, int max, T& value) 
	{
		std::string tmp(key);
		if (max < min) {
			return -1;
		}
		else {
			int mid = (min + max) / 2;
			if (records[mid].key.compare(tmp) > 0) {
				return binary_search(records, key, min, mid - 1,value);
			}
			else if (records[mid].key.compare(tmp) < 0) {
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
		//copy constructor	
	}
	virtual bool update(const char* key, const T& value)
	{
		//if find update
		//if not find create
		std::string tmp(key);
		
		for (int i = 0; i < size_ + 1; i++) {
			if (data_[i].key.compare("") == 0){
				data_[i].key = key;
				data_[i].value = value;
				size_++;
				return true;
			}
			else if (data_[i].key.compare(tmp) == 0) {
				data_[i].value = value;
				return true;
			}
			else if (data_[i].key.compare(tmp) > 0) {
				if (size_ + 1 <= maxSize_) {
					for (int j = size_ - 1; j >= i; j--) {
						data_[j + 1] = data_[j];
					}
					size_++;
					data_[i].key = key;
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
					data_[i].key = key;
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
			for (int i = pos; i < size_-1; i++) {
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

template<class T>
class HashTable : public Table<T>
{
	Record<T> * data_;
public:
	HashTable();
	HashTable(int maxExpected)
	{
		data_ = new Record<T>[maxExpected * 1.35];
	}
	HashTable(const HashTable& other);
	virtual bool update(const char * key, const T& value)
	{
		std::string key_string(key);
		std::hash<std::string> string_hash;
		
	}

	virtual bool remove(const char* key)
	{

	}
	virtual bool find(const char* key, T& value)
	{

	}
	virtual int size() const
	{

	}

	virtual bool isFull() const
	{

	}

	virtual bool isEmpty() const
	{

	}
};

#endif
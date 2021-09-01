#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include <vector>

#define Vector std::vector

// #define GROWTHRATE 0.25f

// template<typename T>
// class Vector {
// private:
// 	//Data Memebers
// 	std::size_t _size;
// 	std::size_t _cappacity;
// 	T* DataBuffer;

// 	//Private methods
// 	inline int GrowDataArray(T*& str, std::size_t size) {
// 		std::size_t growth = 0;
// 		if (size < 10) {
// 			growth = 10;
// 		}
// 		else {
// 			growth = GROWTHRATE * size;
// 		}
// 		T* temp = new T[size + growth];
// 		int i = 0;
// 		for (; i < size; ++i) {
// 			temp[i] = str[i];
// 		}
// 		if (str) {
// 			delete[] str;
// 		}
// 		str = temp;
// 		return size + growth;
// 	}
// public:
// 	Vector()
// 		: _size(0), _cappacity(0), DataBuffer(nullptr) {}
// 	inline std::size_t size() const { return this->_size; }
// 	inline std::size_t cappacity() const { return this->_cappacity; }
// 	inline bool isEmpty() const { return this->_size == 0; }

// 	T* end() { return this->DataBuffer + this->_size; }
// 	T* begin() { return this->DataBuffer; }

// 	Vector(const int cap)
// 		: _size(0), _cappacity(cap), DataBuffer(new T[_cappacity]) {}

// 	Vector(const Vector& other)
// 		: _size(other._size), _cappacity(other._cappacity), DataBuffer(new T[_cappacity]) {
// 		for (int i = 0; i < _size; ++i) {
// 			this->DataBuffer[i] = other.DataBuffer[i];
// 		}
// 	}
// 	Vector(const int cap, const T& element)
// 		: _size(cap), _cappacity(cap), DataBuffer(new T[_cappacity]) {
// 		for (std::size_t i = 0; i < _size; i++) {
// 			DataBuffer[i] = element;
// 		}
// 	}
// 	void push_back(const T& element) {
// 		if (this->_size >= _cappacity) {
// 			this->_cappacity = GrowDataArray(DataBuffer, _cappacity);
// 		}
// 		this->DataBuffer[_size++] = element;
// 	}

// 	const T& operator[](const std::size_t index) const {
// 		if (index >= 0 && index < _size) {
// 			return this->DataBuffer[index];
// 		}
// 		else {
// 			std::cout << "Index out of range\n";
// 			assert(false);
// 		}
// 	}
// 	T& operator[](const std::size_t index) {
// 		if (index >= 0 && index < _size) {
// 			return this->DataBuffer[index];
// 		}
// 		else {
// 			std::cout << "Index out of range\n";
// 			assert(false);
// 		}
// 	}

// 	Vector& operator=(const Vector& other) {
// 		if (this != &other) {
// 			if (this->DataBuffer) {
// 				delete[] DataBuffer;
// 			}
// 			this->_size = other._size;
// 			this->_cappacity = other._cappacity;
// 			DataBuffer = new T[_cappacity];
// 			for (int i = 0; i < _size; ++i) {
// 				DataBuffer[i] = other.DataBuffer[i];
// 			}
// 		}
// 		return *this;
// 	}
// 	void clear() {
// 		if (this->DataBuffer) {
// 			delete[] DataBuffer;
// 		}
// 		this->_size = 0;
// 		this->_cappacity = 0;
// 		this->DataBuffer = nullptr;
// 	}
// 	void reserve(const std::size_t size) {
// 		if (this->_cappacity < size) {
// 			T* temp = new T[size];
// 			this->_cappacity = size;
// 			for (size_t i = 0; i < this->_size; i++) {
// 				temp[i] = this->DataBuffer[i];
// 			}
// 			if (DataBuffer) {
// 				delete[] DataBuffer;
// 			}
// 			this->DataBuffer = temp;
// 		}
// 	}
// 	void erase(const int index) {
// 		if (index >= 0 && index < _size) {
// 			for (int i = index; i < this->_size - 1; i++) {
// 				this->DataBuffer[i] = this->DataBuffer[i + 1];
// 			}
// 			this->_size -= 1;
// 		}
// 	}

// 	void erase_to_extreme(const int& index) {
// 		assert(index >= 0 && index < _size);
// 		_size -= (_size - index);
// 	}

// 	void empty_contents() {
// 		_size = 0;
// 	}

// 	~Vector() {
// 		clear();
// 	}
// 	void insert_at(int index, const T& element) {
// 		if (index > _size)assert(false);
// 		if (this->_cappacity < this->_size + 1) {
// 			this->_cappacity = GrowDataArray(DataBuffer, _cappacity);
// 		}
// 		for (int i = this->_size - 1; i >= index; i--) {
// 			this->DataBuffer[i + 1] = DataBuffer[i];
// 		}
// 		this->DataBuffer[index] = element;
// 		this->_size += 1;
// 	}
// };

// #undef GROWTHRATE
#endif // !VECTOR_H
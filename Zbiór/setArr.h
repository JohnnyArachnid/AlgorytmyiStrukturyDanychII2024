//Autor: Daniel Szarek i Pan Tomek :)

#pragma once
#include <iostream>

class setArr
{
	int size;
	const int universeSize = 100;
	bool* table;
	bool checkRangeCorrectness(int x);
	public:
		setArr();
		void insert(int x);
		void withdraw(int x);
		bool isInSet(int i);
		int getSize();
		void clearSet();
		void printSet();
		setArr operator+(setArr& object);
		setArr operator*(setArr& object);
		setArr operator-(setArr& object);
		bool operator==(setArr& object);
		bool operator <= (setArr& object);
};

setArr::setArr() : size(100) { table = new bool[size](); }

bool setArr::checkRangeCorrectness(int x) {
	return x > 0 && x < universeSize;
}

void setArr::insert(int x) {
	if (!checkRangeCorrectness(x) || isInSet(x)) return;
	table[x] = true;
}

void setArr::withdraw(int x) {
	if (!checkRangeCorrectness(x) || !isInSet(x)) return;
	table[x] = false;
}

bool setArr::isInSet(int i) {
	return table[i];
}

int setArr::getSize() {
	return size;
}

void setArr::clearSet() {
	for (int i = 0; i < size; ++i) table[i] = false;
}

void setArr::printSet() {
	for (int i = 0; i < size; ++i) if (table[i]) std::cout << i << std::endl;
}

setArr setArr::operator+(setArr& object) {
	setArr sum;
	for (int i = 0; i < size; ++i) if (table[i] || object.isInSet(i)) sum.insert(i);
	return sum;
}

setArr setArr::operator*(setArr& object) {
	setArr intersection;
	for (int i = 0; i < size; ++i) if (table[i] && object.isInSet(i)) intersection.insert(i); 
	return intersection;
}

setArr setArr::operator-(setArr& object) {
	setArr difference;
	for (int i = 0; i < size; ++i) if (table[i] && !object.isInSet(i)) difference.insert(i); 
	return difference;
}

bool setArr::operator==(setArr& object) {
	for (int i = 0; i < size; ++i) if (table[i] != object.isInSet(i)) return false;
	return true; 
}

bool setArr::operator<=(setArr& object) {
	for (int i = 0; i < size; ++i) if (table[i] && !object.isInSet(i)) return false;
	return true; 
}













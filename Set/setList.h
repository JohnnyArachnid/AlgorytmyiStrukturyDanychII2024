//Autor: Daniel Szarek i Pan Tomek :)

#pragma once
#include<iostream>
#include <vector>

class setList
{
    std::vector<int> vec;

public:
    int getSize();  
    void printSet(); 
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int x); 
    setList operator+(setList& obj);  
    setList operator*(setList& obj);   
    setList operator-(setList& obj);
    bool operator==(setList& obj);  
    bool operator<=(setList& obj);
};

int setList::getSize() {
    return vec.size();
}

void setList::printSet() {
    for (int n : vec) std::cout << n << std::endl;
}

void setList::insert(int x) {
    if (isInSet(x)) return;
    vec.push_back(x);
}

void setList::withdraw(int x) {
    if (!isInSet(x)) return;
    int writeIndex = 0;
    for (int i = 0; i < getSize(); ++i) {
        if (vec.at(i) != x) {
            vec.at(writeIndex++) = vec.at(i);
        }
    }
    vec.resize(writeIndex);
}

bool setList::isInSet(int x) {
    for (int n : vec) if (x == n) return true;
    return false;
}

setList setList::operator+(setList& obj) {
    setList sum = *this; 
    for (int x : obj.vec) sum.insert(x);
    return sum;
}   

setList setList::operator*(setList& obj) {
    setList intersection;
    for (int x : obj.vec) if (isInSet(x)) intersection.vec.push_back(x);
    return intersection;
}

setList setList::operator-(setList& obj) {
    setList difference = *this; 
    for (int x : obj.vec) difference.withdraw(x); 
    return difference;
}

bool setList::operator==(setList& obj) {
    if (getSize() != obj.getSize()) return false;
    for (int x : vec) if (!obj.isInSet(x)) return false;
    return true;
}

bool setList::operator<=(setList& obj) {
    if (getSize() > obj.getSize()) return false;
    for (int x : vec) if (!obj.isInSet(x)) return false;
    return true;
}






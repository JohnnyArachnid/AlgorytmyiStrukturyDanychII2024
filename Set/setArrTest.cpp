//Autor: Daniel Szarek

#include <iostream>
#include "setArr.h"

void testInsertAndIsInSet() {
    setArr mySet;
    mySet.insert(5);
    mySet.insert(10);
    mySet.insert(20);

    std::cout << "\nTest insert and isInSet:" << std::endl;
    std::cout << "Our set:" << std::endl;
    mySet.printSet();
    std::cout << "5 isInSet: " << (mySet.isInSet(5) ? "true" : "false") << std::endl;
    std::cout << "10 isInSet: " << (mySet.isInSet(10) ? "true" : "false") << std::endl;
    std::cout << "20 isInSet: " << (mySet.isInSet(20) ? "true" : "false") << std::endl;
    std::cout << "25 isInSet: " << (mySet.isInSet(25) ? "true" : "false") << std::endl;
}

void testRemove() {
    setArr mySet;
    mySet.insert(5);
    mySet.insert(10);
    mySet.insert(20);
    mySet.withdraw(10);
    mySet.withdraw(15);

    std::cout << "\nTest remove:" << std::endl;
    std::cout << "Our set:" << std::endl;
    mySet.printSet();
    std::cout << "10 isInSet: " << (mySet.isInSet(10) ? "true" : "false") << std::endl;
}

void testSetOperations() {
    setArr set1, set2;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(2);
    set2.insert(3);
    set2.insert(4);

    std::cout << "\nTest set operations:" << std::endl;
    std::cout << "Our sets:" << std::endl;
    std::cout << "set1:" << std::endl;
    set1.printSet();
    std::cout << "set2:" << std::endl;
    set2.printSet();
    std::cout << "set1 + set2: " << std::endl;;
    (set1 + set2).printSet();

    std::cout << "set1 * set2: " << std::endl;;
    (set1 * set2).printSet();

    std::cout << "set1 - set2: " << std::endl;;
    (set1 - set2).printSet();
}

void testEquality() {
    setArr set1, set2, set3;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(1);
    set2.insert(2);
    set2.insert(3);
    set3.insert(1);
    set3.insert(2);

    std::cout << "\nTest equality:" << std::endl;
    std::cout << "Our sets:" << std::endl;
    std::cout << "set1:" << std::endl;
    set1.printSet();
    std::cout << "set2:" << std::endl;
    set2.printSet();
    std::cout << "set3:" << std::endl;
    set3.printSet();
    std::cout << "set1 == set2: " << (set1 == set2 ? "true" : "false") << std::endl;
    std::cout << "set1 == set3: " << (set1 == set3 ? "true" : "false") << std::endl;
}

void testSubset() {
    setArr set1, set2, set3;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(1);
    set2.insert(2);
    set3.insert(1);
    set3.insert(4);

    std::cout << "\nTest subset:" << std::endl;
    std::cout << "Our sets:" << std::endl;
    std::cout << "set1:" << std::endl;
    set1.printSet();
    std::cout << "set2:" << std::endl;
    set2.printSet();
    std::cout << "set3:" << std::endl;
    set3.printSet();
    std::cout << "set2 <= set1: " << (set2 <= set1 ? "true" : "false") << std::endl;
    std::cout << "set3 <= set1: " << (set3 <= set1 ? "true" : "false") << std::endl;
}

int main() {

    std::cout << "\nsetArr Tests: " << std::endl;
    testInsertAndIsInSet();
    testRemove();
    testSetOperations();
    testEquality();
    testSubset();
    return 0;
}

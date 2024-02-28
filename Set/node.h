//Autor: Daniel Szarek

#include <iostream>

struct Node {

        int value;
        Node *left, *right;
        Node(int item) : value(item), left(nullptr), right(nullptr) {}
        ~Node() {}
};
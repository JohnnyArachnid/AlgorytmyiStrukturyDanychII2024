//Autor: Daniel Szarek i Pan Tomek :)

#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;


class KolejkaPriorytetowa
{
    private:
    // Moja implementacja wyglada tak ze jako root element przyjmuje najmniejszy element w kolejce, kolejne klucze są uporządkowane niemalejąco. Jako kontener przyjmuje vector.
    vector<int> heap;
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    void heapify_up(int t);
    void heapify_down(int t);
    public:
    void insert(int x);
    int RemoveRootElem();
    void print();   //opcjonalnie dla wy�wietlenia kolejnych element�w macierzy, w kt�rej trzymany jest kopiec.
    int getRootElem();
    bool empty() const { return heap.empty(); }
};

void KolejkaPriorytetowa::heapify_up(int t) {
    if (heap.at(t) < heap.at(parent(t)) && t > 0) {
        int temp = heap.at(t);
        heap.at(t) = heap.at(parent(t));
        heap.at(parent(t)) = temp;
        heapify_up(parent(t));
    }
}

void KolejkaPriorytetowa::heapify_down(int t) {
    if (leftChild(t) >= heap.size() && rightChild(t) >= heap.size()) return;
    int min_child_index = t;
    if (leftChild(t) < heap.size() && heap.at(leftChild(t)) < heap.at(min_child_index)) { min_child_index = leftChild(t); }
    if (rightChild(t) < heap.size() && heap.at(rightChild(t)) < heap.at(min_child_index)) { min_child_index = rightChild(t); }
    if (min_child_index != t && heap.at(min_child_index) != heap.at(t)) {
        swap(heap.at(t), heap.at(min_child_index));
        heapify_down(min_child_index);
    }
}

void KolejkaPriorytetowa::insert(int x) {
    heap.push_back(x);
    heapify_up(heap.size() - 1);
}

int KolejkaPriorytetowa::RemoveRootElem() {
    if (heap.empty()) throw std::out_of_range("Priority Queue is empty!");
    int root = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    heapify_down(0);
    return root;
}

void KolejkaPriorytetowa::print() {
    if (heap.empty()) {
        cout << "Priority Queue is empty." << endl;
        return;
    } 
    cout << "{ ";
    for (int i = 0; i < heap.size(); i++) {
        if (i == heap.size() - 1) cout << heap.at(i) << " }" << endl;
        else cout << heap.at(i) << ",";
    }
}

int KolejkaPriorytetowa::getRootElem() {
    if (heap.empty()) throw std::out_of_range("Priority Queue is empty!");
    return heap.front();
}


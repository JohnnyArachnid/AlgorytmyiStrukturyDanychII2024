//Autor: Daniel Szarek

#include "KolejkaPriorytetowa.h"

int main() {

    KolejkaPriorytetowa pq;

    // Test wstawiania elementów

    pq.insert(5);
    pq.insert(3);
    pq.insert(7);
    pq.insert(2);
    pq.insert(5);

    // Test pobierania korzenia

    cout << "Root element: " << pq.getRootElem() << endl;

    // Test wyświetlania kolejki

    cout << "Queue before removal: ";
    pq.print();

    // Test usuwania korzenia

    cout << "Removed root element: " << pq.RemoveRootElem() << endl;

    cout << "Queue after removal: ";
    pq.print();

    // Test wstawienia i usunięcia wielu elementów

    cout << "Added element: " << 1 << endl;
    pq.insert(1);
    cout << "Priority Queue after adding: ";
    pq.print();
    cout << "Added element: " << 9 << endl;
    pq.insert(9);
    cout << "Priority Queue after adding: ";
    pq.print();
    cout << "Added element: " << 4 << endl;
    pq.insert(4);
    cout << "Priority Queue after adding: ";
    pq.print();
    cout << "Added element: " << 6 << endl;
    pq.insert(6);
    cout << "Priority Queue after adding: ";
    pq.print();
    cout << "Added element: " << 8 << endl;
    pq.insert(8);
    cout << "Priority Queue after adding: ";
    pq.print();

    while (!pq.empty()) {
        cout << "Removed element: " << pq.RemoveRootElem() << endl;
        cout << "Priority Queue after removal: ";
        pq.print();
    }

    // Test obsługi pustej kolejki

    try {
        cout << "Attempting to remove from empty priority queue..." << endl;
        pq.RemoveRootElem();
    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

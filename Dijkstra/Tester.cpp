//Autor: Daniel Szarek

#include "Graf.h"

void test1()
{
    Graf* G = new Graf();
    G->readFromFile("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\Dijkstra\\GrafD1.txt");
    int src = 5;
    int dest = 8;
    std::vector<std::pair<int, bool>> dij = G->dijkstraShortestPath(src, dest);
    for (size_t i = 0; i < dij.size(); ++i) {
        if (dij[i].second) {
            std::cout << "Odleglosc do wierzcholka " << i << ": " << dij[i].first << std::endl;
        } else {
            std::cout << "Wierzcholek " << i << " jest nieosiągalny." << std::endl;
        }
    }
}

int main()
{
    test1();  
}
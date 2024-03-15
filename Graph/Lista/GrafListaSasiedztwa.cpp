// Autor: Daniel Szarek i Pan Tomek :)

#include "Graf.cpp"


void test1()
{
    Graf* G = new Graf();    
    G->createVertices(10);
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    std::cout << G->vertexDegree(1)<<"\n";
    std::cout << G->vertexDegree(8) << "\n";
    G->printNeighbourIndices(1);
    G->printNeighbourIndices(8);
    std::cout << G->checkEdge(1, 2)<<"\n";
    G->removeEdge(1, 2);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2) << "\n\n\n\n\n";   
}

void test2()
{
    Graf* G = new Graf();
    // Poniżej potrzebna zmiana dla każdego komputera
    G->readFromFile("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\Graph\\GrafTesty.txt");
    G->printNeighbourIndices(1);
    std::cout << G->getNumberOfEdges();
}

int main()
{
    test1();
    test2();  
}
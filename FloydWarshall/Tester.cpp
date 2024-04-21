//Autor: Daniel Szarek

#include "Graf.h"

void test1()
{
    Graf* G = new Graf();
    G->readFromFile("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\FloydWarshall\\GrafZad.txt");
    G->floydWarshall();
}

int main()
{
    test1();  
}
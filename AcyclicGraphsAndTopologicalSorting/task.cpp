//Autor: Daniel Szarek

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

class Graf
{
    //od razu musimy zadeklarować maksymalną ilość wierzchołków - tutaj 1000;
    int matrix[101][101];
    int numberOfVertices;

public:
    Graf();
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path);
    std::vector<int> topologicalSort();
    bool isAcyclic();
    
private:
    void clear();
    void topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack);
};

void Graf::clear() {
    for (int j = 0; j < numberOfVertices; j++)
        for (int i = 0; i < numberOfVertices; i++)
            matrix[j][i] = 0;
}

Graf::Graf() { std::cout << "Tworzymy graf za pomocą implementacji macierzowej!" << std::endl; }

void Graf::createVertices(int ile) {
    if (ile > 101) return;
    else {
        numberOfVertices = ile;
        for (int j = 0; j < numberOfVertices; j++)
            for (int i = 0; i < numberOfVertices; i++)
                matrix[j][i] = 0;
    } 
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 1;
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) { 
        throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); 
    }
    else {
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2] == 1; 
    }
}

int Graf::vertexDegree(int idx) {
    if (idx >= numberOfVertices) { 
        throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); 
    }
    else {
        int counter = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] == 1) counter++;
        }
        return counter;
    }   
}

std::vector<int> Graf::getNeighbourIndices(int idx) {
    if (idx >= numberOfVertices) { 
        throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); 
    }
    else {
        std::vector<int> neighbours;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] == 1) neighbours.push_back(i); 
        }
        if (neighbours.empty()) std::cout << "Brak sąsiadów!" << std::endl;
        return neighbours;
    }
}

void Graf::printNeighbourIndices(int idx) {
    if (idx >= numberOfVertices) { 
        throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); 
    }
    else {
        std::cout << "Sąsiedzi podanego wierzchołka " << idx << ":" << std::endl;
        std::vector<int> neighbours = getNeighbourIndices(idx);
        for (int vertex : neighbours) std::cout << vertex << std::endl; 
    }
}

int Graf::getNumberOfEdges() {
    int counter = 0;
    for (int j = 0; j < numberOfVertices; j++)
        for (int i = 0; i < numberOfVertices; i++)
            if (matrix[j][i] == 1) counter++;
    return counter;
}

void Graf::readFromFile(std::string path) {
    int numberOfVerticesFromFile;
    int edge1, edge2;
    std::string line;
    std::ifstream myfile(path);
    myfile >> numberOfVerticesFromFile;
    createVertices(numberOfVerticesFromFile);
    while(myfile >> edge1 >> edge2) {
        addEdge(edge1, edge2); 
    }
    myfile.close();
}

std::vector<int> Graf::topologicalSort() {
    std::stack<int> Stack;
    std::vector<int> sortedVertices;

    bool* visited = new bool[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
        visited[i] = false;

    for (int i = 0; i < numberOfVertices; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);

    while (!Stack.empty()) {
        sortedVertices.push_back(Stack.top());
        Stack.pop();
    }

    delete[] visited;

    return sortedVertices;
}

void Graf::topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack) {
    visited[v] = true;

    for (int i = 0; i < numberOfVertices; ++i) {
        if (matrix[v][i] == 1 && !visited[i]) {
            topologicalSortUtil(i, visited, Stack);
        }
    }

    Stack.push(v);
}

bool Graf::isAcyclic() {
    std::vector<int> sortedVertices = topologicalSort();
    for (size_t i = 0; i < sortedVertices.size(); ++i) {
        std::vector<int> neighbours = getNeighbourIndices(sortedVertices[i]);
        for (int neighbour : neighbours) {
            for (size_t j = i + 1; j < sortedVertices.size(); ++j) {
                if (neighbour == sortedVertices[j])
                    return false;
            }
        }
    }
    return true;
}

int main() {
    Graf graf1;
    graf1.readFromFile("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\AcyclicGraphsAndTopologicalSorting\\Graf1.txt");

    std::cout << "Czy graf jest acykliczny? ";
    if (graf1.isAcyclic())
        std::cout << "Tak." << std::endl;
    else
        std::cout << "Nie, wykryto cykl." << std::endl;
    Graf graf2;
    graf2.readFromFile("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\AcyclicGraphsAndTopologicalSorting\\Graf2.txt");
    std::cout << "Sortowanie topologiczne: ";
    std::vector<int> sorted = graf2.topologicalSort();
    for (int vertex : sorted) {
        std::cout << vertex << " ";
    }
    std::cout << sorted.size() << std::endl;
    return 0;
}

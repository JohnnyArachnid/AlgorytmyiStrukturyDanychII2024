// Autor: Daniel Szarek

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <queue>
#include <algorithm>

class Graf {
    //od razu musimy zadeklarować maksymalną ilość wierzchołków - tutaj 100;
    int matrix[100][100];
    int numberOfVertices;

public:
    Graf();
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int cost);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path);
    std::vector<std::pair<int, bool>>dijkstraShortestPath(int src, int dest);
    std::vector<int> reconstructPath(std::vector<int> prev, int src, int dest);
    void floydWarshall();

private:
    void clear();
};

void Graf::clear() {
    for (int j = 0; j < numberOfVertices; j++)
        for (int i = 0; i < numberOfVertices; i++)
            matrix[j][i] = 0;
}

Graf::Graf() { std::cout << "Tworzymy graf za pomocą implementacji macierzowej!" << std::endl; }

void Graf::createVertices(int ile) {
    if (ile > 100) return;
    else {
        numberOfVertices = ile;
        for (int j = 0; j < numberOfVertices; j++)
            for (int i = 0; i < numberOfVertices; i++)
                matrix[j][i] = 0;
    } 
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int cost) {
    if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    matrix[i_Vertex_Index_1][i_Vertex_Index_2] = cost;
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (i_Vertex_Index_1 > numberOfVertices || i_Vertex_Index_2 > numberOfVertices) { throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); }
    else {
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_2] != 0) { return true; }
        return false; 
    }
}

int Graf::vertexDegree(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); }
    else {
        int counter = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] != 0) counter++;
        }
        return counter;
    }   
}

std::vector<int> Graf::getNeighbourIndices(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); }
    else {
        std::vector<int> neighbours;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] != 0) neighbours.push_back(i); 
        }
        if (neighbours.empty()) std::cout << "Brak sąsiadów!" << std::endl;
        return neighbours;
    }
}

void Graf::printNeighbourIndices(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzchołek poza zasięgiem podanym podczas tworzenia grafu!"); }
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
            if (matrix[j][i] != 0) counter++;
    return counter;
}

void Graf::readFromFile(std::string path) {
    int numberOfVerticesFromFile;
    int edge1, edge2, cost;
    std::ifstream myfile(path);
    if (!myfile.is_open()) {
        std::cout << "Nie można otworzyć pliku: " << path << std::endl;
        return;
    }
    myfile >> numberOfVerticesFromFile;
    createVertices(numberOfVerticesFromFile);
    while (myfile >> edge1 >> edge2 >> cost) {
        addEdge(edge1, edge2, cost); 
    }
    myfile.close();
}

void Graf::floydWarshall() {
    int dist[numberOfVertices][numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if (i == j)
                dist[i][j] = 0;
            else if (matrix[i][j] != 0)
                dist[i][j] = matrix[i][j];
            else
                dist[i][j] = INT_MAX;
        }
    }

    for (int k = 0; k < numberOfVertices; k++) {
        for (int i = 0; i < numberOfVertices; i++) {
            for (int j = 0; j < numberOfVertices; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < numberOfVertices; i++) {
        if (dist[i][i] < 0) {
            std::cout << "Graf zawiera ujemny cykl." << std::endl;
            return;
        }
    }
    std::cout << "Najkrótsze odległości pomiędzy wierzchołkami:" << std::endl;
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if (dist[i][j] == INT_MAX)
                std::cout << "INF\t";
            else
                std::cout << dist[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

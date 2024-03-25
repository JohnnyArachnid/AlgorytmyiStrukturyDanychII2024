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

std::vector<std::pair<int, bool>> Graf::dijkstraShortestPath(int src, int dest) {
    std::vector<int> dist(numberOfVertices, std::numeric_limits<int>::max());
    std::vector<int> prev(numberOfVertices, -1);
    dist[src] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < numberOfVertices; ++v) {
            if (matrix[u][v] != 0) {
                int alt = dist[u] + matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }

    
    std::vector<std::pair<int, bool>> result;
    for (int i = 0; i < numberOfVertices; ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            result.push_back(std::make_pair(dist[i], false));
        } else {
            result.push_back(std::make_pair(dist[i], true));
        }
    }

    std::vector<int> path = reconstructPath(prev, src, dest);
    
    std::cout <<"Najkrotsza sciezka grafu od: " << src << " do: " << dest<< " : ";
    if (!path.empty()) {
        path.pop_back();
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    return result;
}

std::vector<int> Graf::reconstructPath(std::vector<int> prev, int src, int dest) {
    std::vector<int> path;
    int at = dest;
    while (at != -1) {
        path.push_back(at);
        at = prev[at];
    }
    std::reverse(path.begin(), path.end());
    return path;
}






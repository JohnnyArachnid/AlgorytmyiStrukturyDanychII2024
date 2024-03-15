// Autor: Daniel Szarek
// Swoją implementację przyjąłem w następujący sposób: Graf skierowany, gdyż nie zauważyłem w poleceniu, aby było wskazane który typ wybrać

#include "Graf.h"
#include <algorithm>

Graf::Graf() { std::cout << "Tworzymy graf za pomoca implementacji listowej!" << std::endl; }

void Graf::createVertices(int ile) { 
    for (int i = 0; i < ile; i++) { 
        std::vector<edge> temp;
        vertexList.push_back(temp);
    }
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    std::vector<edge> &tempVec = vertexList.at(i_Vertex_Index_1);
    edge tempEdge(i_Vertex_Index_1, i_Vertex_Index_2);
    tempVec.push_back(tempEdge);
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) { return; }
    std::vector<edge> &tempVec = vertexList.at(i_Vertex_Index_1);
    edge tempEdge(i_Vertex_Index_1, i_Vertex_Index_2);
    tempVec.erase(std::remove(tempVec.begin(), tempVec.end(), tempEdge), tempVec.end());
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (i_Vertex_Index_1 > vertexList.size() || i_Vertex_Index_2 > vertexList.size()) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        std::vector<edge> tempVec = vertexList.at(i_Vertex_Index_1);
        for (edge krawedz : tempVec) {
            if (krawedz.vertex_Index2 == i_Vertex_Index_2) { return true; }
        }
        return false; 
    }
}

int Graf::vertexDegree(int idx) {
    if (idx > vertexList.size()) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        std::vector<edge> tempVec = vertexList.at(idx);
        return tempVec.size();
    }   
}

std::vector<int> Graf::getNeighbourIndices(int idx) {
    if (idx > vertexList.size()) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
            std::vector<int> neighbours;
            std::vector<edge> tempVec = vertexList.at(idx);
            for (edge krawedz : tempVec)
                neighbours.push_back(krawedz.vertex_Index2); 
            if (neighbours.empty()) std::cout << "Brak sasiadow!" << std::endl;
            return neighbours;
        }
}

void Graf::printNeighbourIndices(int idx) {
    if (idx > vertexList.size()) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        std::cout << "Sasiedzi podanego wierzcholka " << idx << ":" << std::endl;
        std::vector<int> neighbours = getNeighbourIndices(idx);
        for (int vertex : neighbours) std::cout << vertex << std::endl; 
    }
}

int Graf::getNumberOfEdges() {
    int counter = 0;
    std::vector<edge> tempVec;
    for (int i = 0; i < vertexList.size(); i++) {
        tempVec = vertexList.at(i);
        counter += tempVec.size();
    }
    return counter;
}

void Graf::readFromFile(std::string path) {
    int Vecsize;
    int edge1, edge2;
    std::string line;
    std::ifstream file_line(path);
    std::ifstream myfile(path);
    int count = 0;
    myfile >> Vecsize;
    Graf::createVertices(Vecsize);
    if(file_line.is_open()) 
	{
		while(file_line.peek() != EOF)
		{
			getline(file_line, line);
			count++;
		}
		file_line.close();
    } else { std::cout << "Nie można otworzyc pliku: "<< path << std::endl; }
    for (int i = 0; i < count-1; i++){
        myfile >> edge1 >> edge2;
        Graf::addEdge(edge1,edge2); 
    }
}


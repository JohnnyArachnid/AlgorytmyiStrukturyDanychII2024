// Autor: Daniel Szarek
/* Swoją implementację przyjąłem w następujący sposób: Graf skierowany, gdyż nie zauważyłem w poleceniu, aby było wskazane który typ wybrać
0 oznacza brak krawędzi pomiędzy wierzchołkami, natomiast 1 oznacza, że taka krawędź istnieje */

#include "Graf.h"

Graf::Graf() { std::cout << "Tworzymy graf za pomoca implementacji macierzowej!" << std::endl; }

void Graf::createVertices(int ile) {
    if (ile > 100) return;
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
    if (i_Vertex_Index_1 > numberOfVertices || i_Vertex_Index_2 > numberOfVertices) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_2] == 1) { return true; }
        return false; 
    }
}

int Graf::vertexDegree(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        int counter = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] == 1) counter++;
        }
        return counter;
    }   
}

std::vector<int> Graf::getNeighbourIndices(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        std::vector<int> neighbours;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] == 1) neighbours.push_back(i); 
        }
        if (neighbours.empty()) std::cout << "Brak sasiadow!" << std::endl;
        return neighbours;
    }
}

void Graf::printNeighbourIndices(int idx) {
    if (idx > numberOfVertices) { throw std::out_of_range("Wierzcholek po za zasiegiem podanym podczas tworzenia grafu!"); }
    else {
        std::cout << "Sasiedzi podanego wierzcholka " << idx << ":" << std::endl;
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
    std::ifstream file_line(path);
    std::ifstream myfile(path);
    int count = 0;
    myfile >> numberOfVerticesFromFile;
    Graf::createVertices(numberOfVerticesFromFile);
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

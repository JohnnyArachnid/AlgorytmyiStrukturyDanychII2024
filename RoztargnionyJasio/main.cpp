//Autor: Daniel Szarek

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

class Graph {
    
    int num_vertices;
    std::vector<std::unordered_set<int>> adjacency_list;

public:

    Graph();

    std::pair<std::unordered_set<int>, int> get_connected_vertices();

    void add_edge(int start_vertex, int end_vertex);

    void read_from_file(const std::string& filepath);

private:

    void dfs(int vertex, std::vector<bool>& visited);
};

Graph::Graph() : num_vertices(0) {}

std::pair<std::unordered_set<int>, int> Graph::get_connected_vertices() {
    std::vector<bool> visited(num_vertices + 1, false);
    std::unordered_set<int> connected_vertices;

    for (int vertex = 1; vertex <= num_vertices; ++vertex) {
        if (!visited[vertex]) {
            connected_vertices.insert(vertex);
            dfs(vertex, visited);
        }
    }
    return { connected_vertices, connected_vertices.size() };
}

void Graph::add_edge(int start_vertex, int end_vertex) {
    adjacency_list[start_vertex].insert(end_vertex);
    adjacency_list[end_vertex].insert(start_vertex);
}

void Graph::read_from_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "File not found!" << std::endl;
        return;
    }

    file >> num_vertices;
    adjacency_list.resize(num_vertices + 1);
    for (int idx = 1; idx <= num_vertices; ++idx) {
        int vertex;
        file >> vertex;
        add_edge(vertex, idx);
    }
    file.close();
}

void Graph::dfs(int vertex, std::vector<bool>& visited) {
    visited[vertex] = true;
    for (int neighbour : adjacency_list[vertex]) {
        if (!visited[neighbour]) {
            dfs(neighbour, visited);
        }
    }
}

int main() {
    Graph graph;
    graph.read_from_file("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\RoztargnionyJasio\\test.txt");
    auto [connected_vertices, connected_vertices_count] = graph.get_connected_vertices();
    std::cout << "Minimalna liczba skarbonek do zbicia: " << connected_vertices_count << std::endl;
    std::cout << "Przykladowe numery skarbonek do zbicia: ";
    for (int vertex : connected_vertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    return 0;
}

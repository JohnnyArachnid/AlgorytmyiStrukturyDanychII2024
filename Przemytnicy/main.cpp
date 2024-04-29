// Autor: Daniel Szarek

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

class Graph {

    std::unordered_map<int, std::unordered_map<int, int>> adjacency_list;

public:

    void add_edge(int from, int to, int weight);
    
    int dijkstra(int start, int end) const;
};

void Graph::add_edge(int from, int to, int weight) {
    adjacency_list[from].emplace(to, weight);
}

int Graph::dijkstra(int start, int end) const {
    std::unordered_map<int, int> distances;
    for (const auto& pair : adjacency_list)
        distances[pair.first] = std::numeric_limits<int>::max();
    distances[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        if (distance != distances[node])
            continue;

        for (const auto& [neighbor_node, cost] : adjacency_list.at(node)) {
            int old_cost = distances[neighbor_node];
            int new_cost = distances[node] + cost;
            if (new_cost < old_cost) {
                distances[neighbor_node] = new_cost;
                pq.push({new_cost, neighbor_node});
            }
        }
    }

    return distances[end];
}

std::pair<std::vector<int>, std::vector<std::pair<std::pair<int, int>, int>>> read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File not found!" << std::endl;
        exit(1);
    }

    int m;
    file >> m;

    std::vector<int> m_costs;
    m_costs.reserve(m);
    for (int i = 0; i < m; ++i) {
        int cost;
        file >> cost;
        m_costs.push_back(cost);
    }

    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.reserve(m);
    std::string line;
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        int from, to, cost;
        iss >> from >> to >> cost;
        edges.emplace_back(std::make_pair(from, to), cost);
    }

    file.close();
    return {std::move(m_costs), std::move(edges)};
}

double calculate_cost(const std::vector<int>& m_costs, const Graph& graph) {
    std::vector<double> m_cost_final(m_costs.size());
    for (size_t i = 0; i < m_costs.size(); ++i)
        m_cost_final[i] = m_costs[i] * 0.5;

    for (size_t m_cost_new = 1; m_cost_new < m_costs.size(); ++m_cost_new) {
        m_cost_final[m_cost_new] += graph.dijkstra(1, static_cast<int>(m_cost_new + 1));
        m_cost_final[m_cost_new] += graph.dijkstra(static_cast<int>(m_cost_new + 1), 1);
    }

    return *std::min_element(m_cost_final.begin(), m_cost_final.end());
}

int main() {
    auto [m_costs, edges] = read_file("C:\\Users\\dszar\\OneDrive\\Pulpit\\GitHub\\AlgorytmyiStrukturyDanychII2024\\Przemytnicy\\test.txt");
    Graph graph;
    for (const auto& edge : edges)
        graph.add_edge(edge.first.first, edge.first.second, edge.second);
    double result = calculate_cost(m_costs, graph);
    std::cout << "Koszt wykonania wyznacznonego ciagu procesow alchemicznych powiekszony o place na granicy clo: " << result << std::endl;
    return 0;
}

#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
#include <string>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class Graph {

private:
	std::map<T, std::list<T>> adj_list;

    std::vector<T> recovered_shortest_path(T target, std::unordered_map<T, T> parent) {
        std::vector<T> shortest_path;
        T current = target;
        while (current) {
            shortest_path.push_back(current);
            current = parent[current];
        }
        std::reverse(shortest_path.begin(), shortest_path.end());
        return shortest_path;
    }
    
public:
	void add_edge(T x, T y) {
		adj_list[x].push_back(y);
		adj_list[y].push_back(x);
	}

    std::map<T, std::list<T>> get_data() { return adj_list; }

	std::vector<T> get_shortest_path(T start, T target) {

		if (start == target) return { start };

		std::deque<T> deque;
		std::set<T> visited;
		std::unordered_map<T, T> parent;
        
		visited.insert(start);
		deque.push_back(start);

		while (!deque.empty()) {
			T current_vertex = deque.front();
			deque.pop_front();
            
			if (current_vertex == target)
				return recovered_shortest_path(target, parent);

			for (T neighbor : adj_list[current_vertex]) {
				if (!visited.count(neighbor)) {
					parent[neighbor] = current_vertex;
					deque.push_back(neighbor);
					visited.insert(neighbor);
				}
			}
		}
		return {};
	}
    
};

template<typename T>
void write_graph(Graph<T>& graph, int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        T source_vertex, target_vertex;
        std::cout << i+1 << " source "; std::cin >> source_vertex;
        std::cout << i+1 << " target "; std::cin >> target_vertex;
        std::cout << std::endl;
        graph.add_edge(source_vertex, target_vertex);
    }
}

template<typename T>
void print_graph(Graph<T>& graph) {
    std::map<T, std::list<T>> graph_data = graph.get_data();
    for (auto [vertex, neighbors]: graph_data) {
        std::cout << vertex << " : " << "[ ";
        for (char neighbor: neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "]" << std::endl;
    }
}

template<typename T>
void print_shortest_path(Graph<T>& graph, T start, T target) {
    std::vector<T> shortest_path = graph.get_shortest_path(start, target);
    for (T elem: shortest_path)
        std::cout << elem << " ";
}

int main() {
	Graph<char> graph;
    
    int edge_count;
    std::cout << "edge count: "; std::cin >> edge_count;
    write_graph(graph, edge_count);
    
    print_graph(graph);
    std::cout << std::endl;
    
    char start, target;
    std::cout << "Vertexes for shortest path(\"start\" then \"target\"" << std::endl;
    std::cin >> start >> target;
    print_shortest_path(graph, start, target);
    std::cout << std::endl;
}

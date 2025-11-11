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

    std::map<T, std::list<T>> get_data() {
        return adj_list;
    }

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

void print_graph(Graph<char> graph) {
    std::map<char, std::list<char>> graph_data = graph.get_data();
    for (auto [vertex, neighbors]: graph_data) {
        std::cout << vertex << " : " << "[ ";
        for (char neighbor: neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "]" << std::endl;
    }
}

void print_shortest_path(Graph<char> graph) {
    std::vector<char> shortest_path = graph.get_shortest_path('A', 'F');
    for (char elem: shortest_path) {
        std::cout << elem << " ";
    }
}

int main() {
	Graph<char> graph;
	graph.add_edge('A', 'B');
	graph.add_edge('A', 'E');
	graph.add_edge('A', 'D');
	graph.add_edge('B', 'E');
	graph.add_edge('B', 'C');
	graph.add_edge('C', 'F');
	graph.add_edge('F', 'E');
    print_graph(graph);
    std::cout << std::endl;
    print_shortest_path(graph);
    std::cout << std::endl;
}

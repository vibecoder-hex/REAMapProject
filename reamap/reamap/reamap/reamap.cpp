#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class Graph {

private:
	std::unordered_map<T, std::list<T>> adj_list;

public:
	void add_edge(T x, T y) {
		adj_list[x].push_back(y);
		adj_list[y].push_back(x);
	}

    std::map<T, std::list>> get_data() {
        return 
    }

	std::vector<T> get_shortest_path(T start, T target) {

		if (start == target) {
			return { start };
		}

		std::deque<T> deque;
		std::set<T> visited;
		std::vector<T> output;
		std::unordered_map<T, T> parent;

		visited.insert(start);
		deque.push_back(start);

		while (!deque.empty()) {
			T current_vertex = deque.front();
			deque.pop_front();
			output.push_back(current_vertex);

			if (current_vertex == target) {
				std::vector<T> shortest_path;
				T current = target;
				while (current) {
					shortest_path.push_back(current);
					current = parent[current];
				}
				std::reverse(shortest_path.begin(), shortest_path.end());
				return shortest_path;
			}

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

int main() {
	Graph<char> graph;
	graph.add_edge('A', 'B');
	graph.add_edge('A', 'E');
	graph.add_edge('A', 'D');
	graph.add_edge('B', 'E');
	graph.add_edge('B', 'C');
	graph.add_edge('C', 'F');
	graph.add_edge('F', 'E');
	graph.print_graph();
	std::cout << std::endl;
	std::vector<char> output = graph.get_shortest_path('A', 'C');
	for (char ch : output) {
		std::cout << ch << " ";
	}
	std::cout << std::endl;
}

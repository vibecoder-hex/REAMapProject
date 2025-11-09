#include <iostream>
#include <list>
#include <iomanip>
#include <map>
#include <string>

template<typename T>
class Graph {

private:
	std::map<T, std::list<T>> adj_list;

public:
	void add_edge(T x, T y) {
		adj_list[x].push_back(y);
		adj_list[y].push_back(x);
	}

	void print_graph() {
		for (auto key_value : adj_list) {
			std::cout << key_value.first << "-> [ ";
			for (auto elem : key_value.second) {
				std::cout << elem << " ";
			}
			std::cout << "]" << std::endl;
		}
	}
};

int main() {
	Graph<char> graph;
	graph.add_edge('A', 'B');
	graph.add_edge('A', 'C');
	graph.add_edge('C', 'B');
	graph.print_graph();
}
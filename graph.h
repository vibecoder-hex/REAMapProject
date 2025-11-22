#pragma once

#include <list>
#include <unordered_map>
#include <map>
#include <deque>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class Graph {

private:
    std::map<T, std::vector<T>> adj_list;

public:
    explicit Graph(std::map<T, std::vector<T>> adj): adj_list(std::move(adj)) {};

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

            if (current_vertex == target) {
                std::vector<T> shortest_path;
                T current = target;
                while (current != start) {
                    shortest_path.push_back(current);
                    current = parent[current];
                }
                shortest_path.push_back(start);
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

    std::vector<T> dfs_traversal(T start) {
        std::vector<T> result;
        std::set<T> visited;
        std::stack<T> stack;

        stack.push(start);
        visited.insert(start);

        while (!stack.empty()) {
            T current_vertex = stack.top();
            stack.pop();
            visited.insert(current_vertex);
            result.push_back(current_vertex);
            for (T neighbor: adj_list[current_vertex]) {
                if (!visited.count(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }
        return result;
    }
};
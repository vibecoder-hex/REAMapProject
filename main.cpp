#include "include/crow.h"
#include "graph.h"
#include <iostream>

std::map<std::string, std::vector<std::string>> graph_map(const crow::json::rvalue& graph_json) {
    std::map<std::string, std::vector<std::string>> adj_list;
    for (const auto& edges: graph_json["graph"].keys()) {
        auto neighbors = graph_json["graph"][edges].lo();
        std::vector<std::string> neighbors_array;
        for (const auto& neighbor: neighbors) {
            neighbors_array.push_back(neighbor.s());
        }
        adj_list[edges] = neighbors_array;
    }
    return adj_list;
}

crow::json::wvalue json_shortest_path(Graph<std::string>& graph, const crow::json::rvalue& graph_json) {
    crow::json::wvalue response_json;
    auto selected_edges = graph_json["edges"].lo();
    std::string start = selected_edges[0].s();
    std::string target = selected_edges[1].s();
    response_json["shortest_path"] = graph.get_shortest_path(start, target);
    return response_json;
}

int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/get_shortest_path").methods("POST"_method)
    ([](const crow::request& request) {
        auto graph_json = crow::json::load(request.body);

        auto graph_struct = graph_map(graph_json);
        Graph<std::string> graph(graph_struct);
        auto response = json_shortest_path(graph, graph_json);
        return crow::response(response);
    });

    app.port(18080).multithreaded().run();
}
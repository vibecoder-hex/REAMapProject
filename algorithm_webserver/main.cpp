#include <iostream>
#include <exception>

#include "httplib.h"
#include "graph.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::map<std::string, std::vector<std::string>> get_graph_structure(json& graph_data) {
    std::map<std::string, std::vector<std::string>> adj_list;
    for (const auto& [vertex, neighbors]: graph_data["graph"].items()) {
        std::vector<std::string> neighbors_vector;
        for (const auto& neighbor: neighbors) {
            neighbors_vector.push_back(neighbor);
        }
        adj_list[vertex] = neighbors_vector;
    }
    return adj_list;
}

std::vector<std::string> get_shortest_path_vector(json& graph_data, Graph<std::string>& graph) {
    std::string start = graph_data["selected_vertexes"][0];
    std::string target = graph_data["selected_vertexes"][1];
    std::vector shortest_path_vector = graph.get_shortest_path(start, target);
    return shortest_path_vector;
}

void set_cors_params(httplib::Server& svr) {
    svr.Options(R"(.*)", [](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204;
    });

    svr.set_pre_routing_handler([](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        return httplib::Server::HandlerResponse::Unhandled;
    });
}

void get_shortest_path_endpoint(httplib::Server& svr, std::string endpoint) {
    svr.Post(endpoint, [](const httplib::Request& req, httplib::Response &res){
        json graph_data = json::parse(req.body), response_json;

        try {
            auto graph_struct = get_graph_structure(graph_data);
            Graph<std::string> graph(graph_struct);
            response_json["shortest_path"] = get_shortest_path_vector(graph_data, graph);
        }
        catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }

        res.set_content(response_json.dump(), "application/json");
    });
}

int main() {
    httplib::Server svr;

    set_cors_params(svr);
    get_shortest_path_endpoint(svr, "/get_shortest_path");

    std::string host = "0.0.0.0";
    int port = 8080;

    std::cout << "Server is running on: " << host << ":" << port << std::endl;

    svr.listen(host, port);
}
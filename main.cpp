#include <iostream>

#include "httplib.h"
#include "graph.hpp"
#include "nlohmann/json.hpp"

std::map<std::string, std::vector<std::string>> get_graph_structure() {
    std::map<std::string, std::vector<std::string>> adj_list;
    adj_list = {
        {"A", {"B", "C"}},
        {"B", {"A", "C"}},
        {"C", {"A", "B"}},
    };
    return adj_list;

}

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request&, httplib::Response &res){
        nlohmann::json json;

        auto graph_struct = get_graph_structure();
        Graph<std::string> graph(graph_struct);
        auto path = graph.get_shortest_path("A", "C");

        json["graph"] = graph_struct;
        json["shortest_path"] = path;

        res.set_content(json.dump(), "application/json");
    });

    std::string host = "0.0.0.0";
    int port = 8080;

    std::cout << "Server is running on: " << host << ":" << port << std::endl;

    svr.listen(host, port);
}
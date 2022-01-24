#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <unordered_map>
#include "stop.h"

class Graph {
    struct Edge {
        std::string dest; // Stop destination
        double distance; // distance between stops
    };

    struct Node {
        const Stop* stop; // Information about the stop
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // As the node been visited on a search?
    };

    int n;
    bool hasDir; // false: undirect; true: directed
    std::unordered_map<std::string,Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes = 2487, bool dir = true);

    // Add node
    void addNode(std::string& stopCode, Stop& stop);

    // Add edge from source to destination with a certain weight
    void addEdge(std::string& oStop, std::string& dStop);

    // Depth-First Search: example implementation
    void dfs(std::string& cStop);

    // Breadth-First Search: example implementation
    void bfs(std::string& cStop);
};

#endif //PROJECT2_GRAPH_H

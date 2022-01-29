#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <set>
#include <queue>
#include <list>
#include <unordered_map>
#include <limits>

#include "stop.h"

#define INF (std::numeric_limits<double>::max()/2)

class Graph {
    struct Edge {
        std::string dest; // Stop destination
        double distance; // distance between stops
        std::string lineCode;
        bool disabled = false; // for closing down lines
    };

    struct Node {
        Stop* stop; // Information about the stop
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // As the node been visited on a search?
        std::string parentStopCodeDijkstra, parentStopCodeBFS, lineCodeDijkstra, lineCodeBFS; // used to create paths
        double distToSingleSource; // used in SSPS
    };

    int n;
    bool hasDir; // false: undirect; true: directed
    std::unordered_map<std::string, Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: directed)
    explicit Graph(int nodes, bool dir = true);
    ~Graph();

    // Add node
    void addNode(const std::string& stopCode, Stop* stop);

    // Add edge from source to destination with a certain weight
    void addEdge(const std::string& oStop, const std::string& dStop, const std::string& lineCode);

    // Depth-First Search: example implementation
    void dfs(const std::string& cStop, bool firstIteration = true);

    // Breadth-First Search: example implementation
    void bfs(const std::string& cStop);

    void dijkstraMinDistance(const std::string& origin);
    void dijkstraMinZones(const std::string& origin);

    Node& nodeAt(const std::string& key);

    std::set<std::string> getStopCodes() const;

    void visitedFalse();

    void clear();
};

#endif //PROJECT2_GRAPH_H

#include "../include/graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num) {}

void Graph::addNode(std::string& stopCode, Stop& stop) {
    nodes.insert({stopCode, {&stop,{},false}});
}

// Add edge from currentStop to destinationStop with a certain distance
void Graph::addEdge(std::string& cStop, std::string& dStop) {
    auto cItr = nodes.find(cStop); auto dItr = nodes.find(dStop);

    if (cItr == nodes.end() || dItr == nodes.end() || cItr == dItr) return;

    if (hasDir){
        double distance = Stop::distance(*(cItr->second.stop), *(dItr->second.stop));

        cItr->second.adj.push_back({dStop, distance});
    }
}

// Depth-First Search: example implementation
void Graph::dfs(std::string& cStop) {
    for (auto& node : nodes) node.second.visited = false;

    Node& cNode = nodes[cStop];
    std::cout << cStop << " - " << *(cNode.stop); // show node order
    cNode.visited = true;

    for (auto e : cNode.adj) {
        std::string dStop = e.dest;
        Node& dNode = nodes[dStop];

        if (!dNode.visited)
            dfs(dStop);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(std::string& cStop) {
    for (auto& node : nodes) node.second.visited = false;

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(cStop);
    nodes[cStop].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front(); q.pop();
        std::cout << u << " - " << *(nodes[u].stop); // show node order

        for (auto e : nodes[u].adj) {
            std::string dStop = e.dest;

            if (!nodes[dStop].visited) {
                q.push(dStop);
                nodes[dStop].visited = true;
            }
        }
    }
}

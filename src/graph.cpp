#include "../include/graph.h"
#include "../include/utils.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num) {}

Graph::~Graph() {
    for (const auto& pair : nodes)
        delete pair.second.stop;
}

void Graph::addNode(const std::string& stopCode, Stop* stop) {
    nodes.insert({stopCode, {stop,{},false}});
}

// Add edge from originStop to destinationStop with the distance between them as the edge weigth
void Graph::addEdge(const std::string& oStop, const std::string& dStop, const std::string& lineCode) {
    auto oItr = nodes.find(oStop); auto dItr = nodes.find(dStop);

    if (oItr == nodes.end() || dItr == nodes.end() || oItr == dItr) return;

    double distance = Stop::distance(*(oItr->second.stop), *(dItr->second.stop));

    auto existingEdge = std::find_if(oItr->second.adj.begin(), oItr->second.adj.end(), [dStop](const Edge &e){return e.dest==dStop;});

    if (existingEdge != oItr->second.adj.end())
        existingEdge->lineCodes.push_back(lineCode);
    else {
        oItr->second.adj.push_back({dStop, distance, {lineCode}});
        if (!this->hasDir)
            dItr->second.adj.push_back({oStop, distance, {lineCode}});
    }
}

// Depth-First Search: example implementation
void Graph::dfs(const std::string& cStop, bool firstIteration) {
    if (firstIteration)
        for (auto& node : nodes) node.second.visited = false;

    Node& cNode = nodes[cStop];
    std::cout << cStop << " - " << *(cNode.stop); // show node order
    cNode.visited = true;

    for (auto e : cNode.adj) {
        std::string dStop = e.dest;
        Node& dNode = nodes[dStop];

        if (!dNode.visited)
            dfs(dStop, false);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(const std::string& cStop) {
    for (auto& node : nodes) node.second.visited = false;

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(cStop);
    nodes[cStop].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front(); q.pop();

        auto node = nodes.at(u);

        std::cout << u << " - " << *(node.stop); // show node order

        for (auto e : node.adj) {
            std::string dStop = e.dest;

            if (!nodes[dStop].visited) {
                q.push(dStop);
                nodes[dStop].visited = true;
            }
        }
    }
}

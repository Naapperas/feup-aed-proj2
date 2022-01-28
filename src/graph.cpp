#include <algorithm>

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

    oItr->second.adj.push_back({dStop, distance, lineCode});
    if (!this->hasDir)
        dItr->second.adj.push_back({oStop, distance, lineCode});
}

// Depth-First Search: example implementation
void Graph::dfs(const std::string& cStop, bool firstIteration) {
    if (firstIteration)
        this->visitedFalse();

    Node& cNode = nodes[cStop];
    std::cout << cStop << " - " << *(cNode.stop) << '\n'; // show node order
    cNode.visited = true;

    for (const auto& e : cNode.adj) {
        std::string dStop = e.dest;
        Node& dNode = nodes[dStop];

        if (!dNode.visited)
            dfs(dStop, false);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(const std::string& cStop) {
    this->visitedFalse();

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(cStop);
    nodes[cStop].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front(); q.pop();

        auto node = nodes.at(u);

        std::cout << u << " - " << *(node.stop) << '\n'; // show node order

        for (const auto& e : node.adj) {
            std::string dStop = e.dest;

            if (!nodes[dStop].visited) {
                q.push(dStop);
                nodes[dStop].visited = true;
            }
        }
    }
}

void Graph::dijkstraMinDistance(const std::string &origin) {
    std::set<std::pair<double, std::string>> q;
    for (auto& node : nodes) {
        node.second.distToSingleSource = INF;
        q.insert({INF, node.second.stop->getStopCode()});
        node.second.visited = false;
        node.second.lineCodeDijkstra = "";
    }
    nodes[origin].distToSingleSource = 0;
    q.erase({INF, nodes[origin].stop->getStopCode()});
    q.insert({0, nodes[origin].stop->getStopCode()});
    nodes[origin].parentStopCodeDijkstra = origin;
    nodes[origin].lineCodeDijkstra = "Begin";
    while (!q.empty()) {
        std::string u = q.begin()->second;
        q.erase(q.begin());
        nodes[u].visited = true;
        for (const auto& e : nodes[u].adj) {
            std::string v = e.dest;
            double w = e.distance;
            if (!nodes[v].visited && nodes[u].distToSingleSource + w < nodes[v].distToSingleSource) {
                q.erase({nodes[v].distToSingleSource, v});
                nodes[v].distToSingleSource = nodes[u].distToSingleSource + w;
                nodes[v].parentStopCodeDijkstra = u;
                nodes[v].lineCodeDijkstra = e.lineCode;
                q.insert({nodes[v].distToSingleSource, v});
            }
        }
    }
}

Graph::Node& Graph::nodeAt(const std::string &key) {
    return this->nodes[key];
}

void Graph::visitedFalse() {
    for (auto& node : nodes) node.second.visited = false;
}

void Graph::clear() {
    this->nodes.clear();
}

std::set<std::string> Graph::getStopCodes() const {

    std::set<std::string> ret;

    for (const auto& node : nodes)
        ret.insert(node.first);

    return ret;
}

void Graph::dijkstraMinZones(const std::string &origin) {
    std::set<std::pair<double, std::string>> q;
    for (auto& node : nodes) {
        node.second.distToSingleSource = INF;
        q.insert({INF, node.second.stop->getStopCode()});
        node.second.visited = false;
        node.second.lineCodeDijkstra = "";
    }
    nodes[origin].distToSingleSource = 0;
    q.erase({INF, nodes[origin].stop->getStopCode()});
    q.insert({0, nodes[origin].stop->getStopCode()});
    nodes[origin].parentStopCodeDijkstra = origin;
    nodes[origin].lineCodeDijkstra = "Begin";
    while (!q.empty()) {
        std::string u = q.begin()->second;
        q.erase(q.begin());
        nodes[u].visited = true;
        for (const auto& e : nodes[u].adj) {
            std::string v = e.dest;
            double w = e.distance + (nodes[v].stop->getZone() != nodes[u].stop->getZone()) * e.distance; // add zone change overhead

            if (!nodes[v].visited && nodes[u].distToSingleSource + w < nodes[v].distToSingleSource) {
                q.erase({nodes[v].distToSingleSource, v});
                nodes[v].distToSingleSource = nodes[u].distToSingleSource + w;
                nodes[v].parentStopCodeDijkstra = u;
                nodes[v].lineCodeDijkstra = e.lineCode;
                q.insert({nodes[v].distToSingleSource, v});
            }
        }
    }
}

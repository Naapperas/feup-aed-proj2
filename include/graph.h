#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include "stop.h"

class Graph {
    static double getDistance(const Stop& cStop,const Stop& dStop){
        {
            // distance between latitudes
            // and longitudes
            double dLat = (dStop.getLatitude() - cStop.getLatitude()) *
                          M_PI / 180.0;
            double dLon = (dStop.getLongitude() - cStop.getLongitude()) *
                          M_PI / 180.0;

            // convert to radians
            double cStopLat = (cStop.getLatitude()) * M_PI / 180.0;
            double dStopLat = (dStop.getLatitude()) * M_PI / 180.0;

            // apply formulae
            double a = pow(sin(dLat / 2), 2) +
                       pow(sin(dLon / 2), 2) *
                       cos(cStopLat) * cos(dStopLat);
            double rad = 6371;
            double c = 2 * asin(sqrt(a));
            return rad * c;
        }
    }

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
    void addEdge(std::string& cStop, std::string& dStop);

    // Depth-First Search: example implementation
    void dfs(std::string& cStop);

    // Breadth-First Search: example implementation
    void bfs(std::string& cStop);
};

#endif //PROJECT2_GRAPH_H

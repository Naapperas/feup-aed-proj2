//
// Created by naapperas on 18/01/22.
//

#ifndef PROJECT2_BUSCOMPANY_H
#define PROJECT2_BUSCOMPANY_H

#include <vector>

#include "graph.h"
#include "busLine.h"

class BusCompany {

    Graph* dayNetwork;
    Graph* nightNetwork;
    std::vector<BusLine*> lines;

    std::string companyName, lastOriginStop;
public:
    BusCompany(const std::string& companyName);
    ~BusCompany();

    // Depth-First Search: example implementation
    void dfs(const std::string& cStop, bool night = false);

    // Breadth-First Search: example implementation
    void bfs(const std::string& cStop, bool night = false);

    double minDistance(const std::string& originStop, const std::string& destinyStop, bool night = false);
    std::list<std::pair<const Stop*, std::string>> minDistancePath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    int minStops(const std::string& originStop, const std::string& destinyStop, bool night = false);
    std::list<std::pair<const Stop*, std::string>> minStopsPath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    std::set<const Stop*> nearbyStops(double lattittude, double longitude) const;
};

#endif //PROJECT2_BUSCOMPANY_H
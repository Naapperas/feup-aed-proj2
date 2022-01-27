//
// Created by naapperas on 18/01/22.
//

#ifndef PROJECT2_BUSCOMPANY_H
#define PROJECT2_BUSCOMPANY_H

#include <vector>

#include "graph.h"
#include "busLine.h"

class BusCompany {

    Graph* networkDayTime;
    Graph* networkNocturnal;
    std::vector<BusLine*> lines;

    std::string companyName, lastOriginStop;
public:
    BusCompany(const std::string& companyName);
    ~BusCompany();

    // Depth-First Search: example implementation
    void dfs(const std::string& cStop);

    // Breadth-First Search: example implementation
    void bfs(const std::string& cStop);

    double minDistance(const std::string& originStop, const std::string& destinyStop);
    std::list<std::pair<const Stop*, std::string>> minDistancePath(const std::string& originStop, const std::string& destinyStop);

    int minStops(const std::string& originStop, const std::string& destinyStop);
    std::list<std::pair<const Stop*, std::string>> minStopsPath(const std::string& originStop, const std::string& destinyStop);
};

#endif //PROJECT2_BUSCOMPANY_H
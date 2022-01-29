//
// Created by naapperas on 18/01/22.
//

#ifndef PROJECT2_BUSCOMPANY_H
#define PROJECT2_BUSCOMPANY_H

#include <vector>

#include "graph.h"
#include "busLine.h"

class BusCompany {

    constexpr static double MAX_NEARBY_DISTANCE = 0.05;
    double userWalkingDistance = Stop::MAX_WALKING_DISTANCE; // set as default, to be changed later

    Graph* dayNetwork;
    Graph* nightNetwork;
    std::vector<BusLine*> lines;

    std::string companyName, lastOriginStop, lastSearchOperation;

    bool inputNightDay();

public:
    BusCompany(const std::string& companyName);
    ~BusCompany();

    std::string getName(){
        return companyName;
    }

    // Depth-First Search: example implementation
    void dfs(const std::string& cStop, bool night = false);

    // Breadth-First Search: example implementation
    void bfs(const std::string& cStop, bool night = false);

    double minDistance(const std::string& originStop, const std::string& destinyStop, bool night = false);
    std::list<std::pair<const Stop*, std::string>> minDistancePath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    int minStops(const std::string& originStop, const std::string& destinyStop, bool night = false);
    std::list<std::pair<const Stop*, std::string>> minStopsPath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    int minZones(const std::string& originStop, const std::string& destinyStop, bool night = false);
    std::list<std::pair<const Stop*, std::string>> minZonesPath(const std::string& originStop, const std::string& destinyStop, bool night = false);


    std::set<const Stop*> nearbyStops(double lattittude, double longitude) const;
    std::set<const Stop*> nearbyStops(const std::string& stopCode) const;

    void calculateWalkingEdges(double walkingDistance);
    void addWalkingEdges();

    void listStops();
    void listLines();
    void travelMinDistance();
    void travelMinDistanceCoord();
    void travelMinStops();
    void travelMinStopsCoord();
    void travelMinZones();
    void travelMinZonesCoord();
    void travelPossibleTicket();
    void changeWalkingDistance();

};

#endif //PROJECT2_BUSCOMPANY_H
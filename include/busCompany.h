//
// Created by naapperas on 18/01/22.
//

#ifndef PROJECT2_BUSCOMPANY_H
#define PROJECT2_BUSCOMPANY_H

#include "graph.h"
#include "busLine.h"

/**
 * The BusCompany responsible for gluing every component together.
 */
class BusCompany {

    constexpr static double MAX_NEARBY_DISTANCE = 0.05;
    double userWalkingDistance = Stop::MAX_WALKING_DISTANCE; // set as default, to be changed later

    Graph* dayNetwork;
    Graph* nightNetwork;
    std::unordered_map<std::string, BusLine*> lines;

    std::string companyName;

    bool inputNightDay();

public:
    BusCompany(const std::string& companyName);
    ~BusCompany();

    std::string getName(){
        return companyName;
    }

    /**
     * Performs a DFS search on one of this company's networks, controlled by 'night'. This method basically delegates the work to one of the underlying graphs.
     *
     * Time complexity: the same as Graph::dfs
     *
     * @param cStop the origin stop from which to perform the DFS
     * @param night weather the search is performed on the daytime graph on the nighttime graph
     */
    void dfs(const std::string& cStop, bool night = false);

    /**
     * Performs a BFS search on one of this company's networks, controlled by 'night'. This method basically delegates the work to one of the underlying graphs.
     *
     * Time complexity: the same as Graph::bfs
     *
     * @param cStop the origin stop from which to perform the BFS
     * @param night weather the search is performed on the daytime graph on the nighttime graph
     */
    void bfs(const std::string& cStop, bool night = false);

    /**
     * Returns the minimum distance between two nodes of a network.
     *
     * Time complexity: the same as Graph::dijkstraMinDistance (O(|E|*log(|V|)))
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the distance from destinyStop to originStop
     */
    double minDistance(const std::string& originStop, const std::string& destinyStop, bool night = false);

    /**
     * Returns the path with the minimum distance between two nodes of a network.
     *
     * Time complexity: the same as Graph::dijkstraMinDistance (O(|E|*log(|V|)))
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the path from destinyStop to originStop
     */
    std::list<std::pair<const Stop*, std::string>> minDistancePath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    /**
     * Returns the minimum number of stops needed to go from the origin stop to the destination stop.
     *
     * Time complexity: O(|E|+|V|)
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the minimum number of stops needed to go from the origin stop to the destination stop
     */
    int minStops(const std::string& originStop, const std::string& destinyStop, bool night = false);
    /**
     * Returns the path that minimizes the number of stops needed to go from the origin stop to the destination stop.
     *
     * Time complexity: O(|E|+|V|)
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the path that minimizes the number of stops needed to go from the origin stop to the destination stop
     */
    std::list<std::pair<const Stop*, std::string>> minStopsPath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    /**
     * Returns the minimum number of zones to traverse to go from the origin stop to the destination stop.
     *
     * Time complexity: O(|E|*log(|V|))
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the minimum number of zones to traverse to go from the origin stop to the destination stop
     */
    int minZones(const std::string& originStop, const std::string& destinyStop, bool night = false);

    /**
     * Returns the path that minimizes the number of zones to traverse to go from the origin stop to the destination stop.
     *
     * Time complexity: O(|E|*log(|V|))
     *
     * @param originStop the departure stop
     * @param destinyStop the arrival stop
     * @param night weather the trip is to be made during the day or during the night
     * @return the path that minimizes the number of zones to traverse to go from the origin stop to the destination stop
     */
    std::list<std::pair<const Stop*, std::string>> minZonesPath(const std::string& originStop, const std::string& destinyStop, bool night = false);

    /**
     * Returns a set of stops that are within BusCompany::MAX_NEARBY_DISTANCE of the given coordinates
     *
     * Time complexity: O(|V|)
     *
     * @param latitude the latitude of the given coordinates
     * @param longitude the longitude of the given coordinates
     * @return the nearby stops to the given location
     */
    std::set<const Stop*> nearbyStops(double latitude, double longitude) const;

    /**
     * Returns a set of stops that are near the given stop.
     *
     * Time complexity: O(|V|)
     *
     * @param stopCode the code of the desired stop
     * @return the nearby stops to the given stop
     */
    std::set<const Stop*> nearbyStops(const std::string& stopCode) const;

    /**
     * Adapts the pre-calculated bus-network to accommodate for edges that make 2 different stops reachable on foot.
     *
     * Time complexity: O(|V|²)
     *
     * @param walkingDistance the new walking distance
     */
    void calculateWalkingEdges(double walkingDistance);

    /**
     * Adds all the "walking edges", i.e., all the edges representing a foot travel (in the context of the program), dynamically.
     *
     * Time complexity: O(|V|²)
     */
    void addWalkingEdges();

    /**
     * Processes a path generated from one of the path searching algorithms.
     */
    void processPath(const std::list<std::pair<const Stop*, std::string>>&);

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
    void toggleStop();
    void toggleLine();
};

#endif //PROJECT2_BUSCOMPANY_H
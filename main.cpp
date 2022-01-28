#include <iostream>
#include "include/busCompany.h"

int main() {
    std::string stopAcode = "AL3";
    std::string stopBcode = "MTSP1";

    BusCompany company{"STCP"};

    std::cout << "Search by bfs :" << std::endl;
    //company.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    // company.dfs(stopAcode);

    std::cout << company.minDistance(stopAcode, stopBcode, true) << std::endl;

    auto path = company.minDistancePath(stopAcode, stopBcode, true);

    for (const auto& stop : path)
        std::cout << *stop.first << " " << stop.second << '\n';

    std::cout << std::endl;

    std::cout << company.minStops(stopAcode, stopBcode, true) << std::endl;

    auto path1 = company.minStopsPath(stopAcode, stopBcode, true);

    for (const auto& stop : path1)
        std::cout << *stop.first << " " << stop.second << '\n';

    std::cout << path.size() << ' ' << path1.size() << std::endl;

    std::cout << std::endl;

    auto stops = company.nearbyStops(41.14954216, -8.610023615);

    for (auto stop : stops)
        std::cout << *stop << std::endl;

    std::cout << std::endl;

    auto stops2 = company.nearbyStops("1AL2");

    for (auto stop : stops2)
        std::cout << *stop << std::endl;

    std::cout << (stops == stops2) << std::endl;

    company.calculateWalkingEdges(0.1);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

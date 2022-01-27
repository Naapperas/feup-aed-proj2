#include <iostream>
#include "include/busCompany.h"

int main() {
    std::string stopAcode = "TRD6";
    std::string stopBcode = "VN2";

    BusCompany company{"STCP"};

    std::cout << "Search by bfs :" << std::endl;
    // company.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    // company.dfs(stopAcode);

    std::cout << company.minDistance(stopAcode, stopBcode) << std::endl;

    auto path = company.minDistancePath(stopAcode, stopBcode);

    for (const auto& stop : path)
        std::cout << *stop.first << " " << stop.second << '\n';

    std::cout << std::endl;

    std::cout << company.minStops(stopAcode, stopBcode) << std::endl;

    auto path1 = company.minStopsPath(stopAcode, stopBcode);

    for (const auto& stop : path1)
        std::cout << *stop.first << " " << stop.second << '\n';

    std::cout << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

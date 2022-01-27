#include <iostream>
#include "include/busCompany.h"

int main() {
    std::string stopAcode = "ZOID1";
    std::string stopBcode = "VN2";

    BusCompany company{"STCP"};

    std::cout << "Search by bfs :" << std::endl;
    // company.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    // company.dfs(stopAcode);

    std::cout << company.minDistance(stopAcode, stopBcode) << std::endl;

    auto path = company.minPath(stopAcode, stopBcode);

    for (auto stop : path)
        std::cout << *stop;

    std::cout << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

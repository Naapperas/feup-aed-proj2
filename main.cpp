#include <iostream>
#include "include/busCompany.h"

int main() {
    std::string stopAcode = "1AL2";
    std::string stopBcode = "1AL5";

    BusCompany company{"STCP"};

    std::cout << "Search by bfs :" << std::endl;
    company.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    company.dfs(stopAcode);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

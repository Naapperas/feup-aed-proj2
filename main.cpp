#include <iostream>
#include "include/graph.h"

int main() {
    Graph graph(2487);
    std::string stopAcode = "1AL2";
    std::string stopBcode = "1AL5";

    graph.addEdge(stopAcode, stopBcode);

    std::cout << "Search by bfs :" << std::endl;
    graph.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    graph.dfs(stopAcode);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

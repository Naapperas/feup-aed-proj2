#include <iostream>
#include "include/graph.h"

int main() {
    Graph graph(2487, false);
    Stop stopA("AV.ALIADOS","PRT1",41.14954216,-8.610023615);
    std::string stopAcode = "1AL2";
    Stop stopB("ALIADOS","PRT1",41.14969203,-8.611312751);
    std::string stopBcode = "1AL5";

    graph.addNode(stopAcode, stopA);
    graph.addNode(stopBcode, stopB);

    graph.addEdge(stopAcode, stopBcode);

    std::cout << "Search by bfs :" << std::endl;
    graph.bfs(stopAcode);
    std::cout << "Search by dfs :" << std::endl;
    graph.dfs(stopAcode);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

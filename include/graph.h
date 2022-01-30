#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <set>
#include <queue>
#include <list>
#include <unordered_map>
#include <limits>

#include "stop.h"

#define INF (std::numeric_limits<double>::max()/2)

/**
 * A graph class.
 * In the context of this program this is going to represent the STCP network.
 *
 * Due to the design choices made throughout the project, this class is a mix of the theoretical classes' "abstract" graph and a context-aware graph tailored to the STCP network.
 */
class Graph {
    /**
     * An edge between 2 nodes on this graph.
     */
    struct Edge {
        std::string dest; // Stop destination
        double distance; // distance between stops
        std::string lineCode;
        bool disabled = false; // for closing down lines
    };

    /**
     * A node on the graph.
     */
    struct Node {
        Stop* stop; // Information about the stop
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // As the node been visited on a search?
        std::string parentStopCodeDijkstra, parentStopCodeBFS, lineCodeDijkstra, lineCodeBFS; // used to create paths using the various
        double distToSingleSource; // used in SSPS
    };

    int n;
    bool hasDir; // false: undirect; true: directed
    std::unordered_map<std::string, Node> nodes; // The list of nodes being represented. For performance purposes, an unordered_map is used over a normal map or linear collection

public:
    // Constructor: nr nodes and direction (default: directed)
    explicit Graph(int nodes, bool dir = true);
    ~Graph();

    /**
     * Adds a node to this graph, using the given stopCode as a key and the Stop as the value.
     *
     * @param stopCode the code of the Stop being added
     * @param stop the Stop being added
     */
    void addNode(const std::string& stopCode, Stop* stop);

    /**
     * Adds an edge on the graph connecting the two given nodes (represented here by their stop codes), it is a valid edge.
     * Associated with the edge itself is the code of the BusLine that edge belongs to.
     *
     * @param oStop the origin stop of this edge
     * @param dStop the destination stop of this edge
     * @param lineCode the line code associated with the given edge
     */
    void addEdge(const std::string& oStop, const std::string& dStop, const std::string& lineCode);

    /**
     * Performs a Depth-First search on the entire graph. Uses a SSSP methodology
     *
     * Time complexity: O(|V| + |E|), with |V| being the number of nodes in the graph and |E| the collected number of edges in the graph
     *
     * @param cStop the single source from which to perform the DFS
     * @param firstIteration since this method is recursive, used to verify the first call
     */
    void dfs(const std::string& cStop, bool firstIteration = true);

    /**
     * Performs a Breadth-First search on this graph. Uses a SSSP methodology.
     *
     * Time complexity: O(|V| + |E|), with |V| being the number of nodes in the graph and |E| the collected number of edges in the graph
     *
     * @param cStop the single source from which to perform the DFS
     */
    void bfs(const std::string& cStop);

    /**
     * Performs a Dijkstra search on this graph. Uses a SSSP methodology.
     *
     * This version of the algorithm updates this graph's nodes according to the accumulated distance from the source node to each node.
     *
     * Time complexity: O(|E|*log(|V|)), with |V| being the number of nodes in the graph and |E| the collected number of edges in the graph.
     *
     * @param origin the single source from which to perform the search
     */
    void dijkstraMinDistance(const std::string& origin);

    /**
     * Performs a Dijkstra search on this graph. Uses a SSSP methodology.
     *
     * This version of the algorithm updates this graph's nodes according to the stops being in the same network zone or not: if the are, the edge weight is artificially increased.
     *
     * Time complexity: O(|E|*log(|V|)), with |V| being the number of nodes in the graph and |E| the collected number of edges in the graph.
     *
     * @param origin the single source from which to perform the search
     */
    void dijkstraMinZones(const std::string& origin);

    /**
     * Returns the node associated to the given key.
     *
     * @param key the key of the node to retrieve.
     * @return the node associated to the given key
     */
    Node& nodeAt(const std::string& key);

    /**
     * Returns all the stop codes.
     *
     * @return all the stop codes
     */
    std::set<std::string> getStopCodes() const;

    /**
     * Resets all the nodes to be unvisited.
     */
    void visitedFalse();

    /**
     * Clears this graph.
     */
    void clear();
};

#endif //PROJECT2_GRAPH_H

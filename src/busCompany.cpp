#include "../include/busCompany.h"

BusCompany::BusCompany(const std::string& companyName) : companyName(companyName), lastOriginStop("") {

    auto stopLines = utils::file::readFile("../resources/stops.csv");
    std::vector<Stop*> stops;

    this->network = new Graph(stopLines.size());

    for (const auto& line : stopLines) {
        Stop* s = Stop::parseLine(line);

        this->network->addNode(s->getStopCode(), s);

        stops.push_back(s);
    }

    // add walking edges
    for (auto it0 = stops.begin(); it0 != stops.end(); it0++)  {
        for (auto it1 = it0; it1 != stops.end(); it1++) {
            if (it0 == it1) continue;

            auto distance = (*it0)->distance(*(*it1));

            if (distance <= Stop::MAX_WALKING_DISTANCE) {

                this->network->addEdge((*it0)->getStopCode(), (*it1)->getStopCode(), "FOOT");
                this->network->addEdge((*it1)->getStopCode(), (*it0)->getStopCode(), "FOOT");
            }
        }
    }

    auto lineLines = utils::file::readFile("../resources/lines.csv");

    // add network edges
    for (const auto& line : lineLines) {
        BusLine* l = BusLine::parseLine(line);

        for (auto itr = l->getStops().begin(); itr < l->getStops().end()-1; itr++) {

            auto currentStop = *itr, nextStop = *(itr+1);

            this->network->addEdge(currentStop, nextStop, l->getLineCode());
        }

        if (!l->getReverseStops().empty())
            for (auto itr = l->getReverseStops().begin(); itr < l->getReverseStops().end()-1; itr++) {

                auto currentStop = *itr, nextStop = *(itr+1);

                this->network->addEdge(currentStop, nextStop, l->getLineCode());
            }

        this->lines.push_back(l);
    }
}

BusCompany::~BusCompany() {
    delete network;

    for (auto line : this->lines)
        delete line;
}

// Depth-First Search: example implementation
void BusCompany::dfs(const std::string& cStop) {
    this->network->dfs(cStop);
};

// Breadth-First Search: example implementation
void BusCompany::bfs(const std::string& cStop) {
    this->network->bfs(cStop);
};

double BusCompany::minDistance(const std::string& originStop, const std::string& destinyStop) {
    if (lastOriginStop != originStop) {
        this->network->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (this->network->nodeAt(destinyStop).distToSingleSource == INF) return -1;
    return this->network->nodeAt(destinyStop).distToSingleSource;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minDistancePath(const std::string& originStop, const std::string& destinyStop) {
    if (lastOriginStop != originStop) {
        this->network->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (this->network->nodeAt(destinyStop).distToSingleSource == INF) return {};

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(this->network->nodeAt(destinyStop).stop, this->network->nodeAt(destinyStop).lineCodeDijkstra);
    std::string v = destinyStop;
    while (v != originStop) {
        v = this->network->nodeAt(v).parentStopCodeDijkstra;
        path.emplace_front(this->network->nodeAt(v).stop, this->network->nodeAt(v).lineCodeDijkstra);
    }
    return path;
}

int BusCompany::minStops(const std::string& originStop, const std::string& destinyStop){
    if (originStop == destinyStop)
        return 0;
    this->network->visitedFalse();
    std::queue<std::pair<std::string ,int>> q; // queue of unvisited nodes with distance to v
    q.push({originStop, 0});
    this->network->nodeAt(originStop).visited = true;
    int nStops = -1;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front().first;
        int u1 = q.front().second; q.pop();
        for (auto e : this->network->nodeAt(u).adj) {
            std::string w = e.dest;
            if (!this->network->nodeAt(w).visited) {
                if (w == destinyStop) {
                    nStops = u1+1;
                }
                q.push({w, u1 + 1});
                this->network->nodeAt(w).visited = true;
                this->network->nodeAt(w).parentStopCodeBFS = u;
                this->network->nodeAt(w).lineCodeBFS = *e.lineCodes.begin();
            }
        }
    }
    return nStops;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minStopsPath(const std::string& originStop, const std::string& destinyStop){
    int aux = this->minStops(originStop, destinyStop);
    if (aux <= 0) return {};  // maybe separate same stop from no path

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(this->network->nodeAt(destinyStop).stop, this->network->nodeAt(destinyStop).lineCodeBFS);
    std::string v = destinyStop;
    while (v != originStop) {
        v = this->network->nodeAt(v).parentStopCodeBFS;
        path.emplace_front(this->network->nodeAt(v).stop, this->network->nodeAt(v).lineCodeBFS);
    }
    return path;
}
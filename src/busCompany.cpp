#include "../include/busCompany.h"

BusCompany::BusCompany(const std::string& companyName) : companyName(companyName) {

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
    this->network->dijkstra(originStop);
    if (this->network->nodeAt(destinyStop).distToSingleSource == INF) return -1;
    return this->network->nodeAt(destinyStop).distToSingleSource;
}

std::list<const Stop*> BusCompany::minPath(const std::string& originStop, const std::string& destinyStop) {
    this->network->dijkstra(originStop);
    if (this->network->nodeAt(destinyStop).distToSingleSource == INF) return {};

    std::list<const Stop*> path;
    path.push_back(this->network->nodeAt(destinyStop).stop);
    std::string v = destinyStop;
    while (v != originStop) {
        v = this->network->nodeAt(v).parentStopCode;
        path.push_front(this->network->nodeAt(v).stop);
    }
    return path;
}
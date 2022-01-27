#include "../include/busCompany.h"

BusCompany::BusCompany(const std::string& companyName) : companyName(companyName), lastOriginStop("") {

    auto stopLines = utils::file::readFile("../resources/stops.csv");
    std::vector<Stop*> stops;

    this->dayNetwork = new Graph(stopLines.size());
    this->nightNetwork = new Graph(stopLines.size());

    for (const auto& line : stopLines) {
        Stop* s = Stop::parseLine(line);

        this->dayNetwork->addNode(s->getStopCode(), s);
        this->nightNetwork->addNode(s->getStopCode(), s);

        stops.push_back(s);
    }

    // add walking edges
    for (auto it0 = stops.begin(); it0 != stops.end(); it0++)  {
        for (auto it1 = it0; it1 != stops.end(); it1++) {
            if (it0 == it1) continue;

            auto distance = (*it0)->distance(*(*it1));

            if (distance <= Stop::MAX_WALKING_DISTANCE) {

                this->dayNetwork->addEdge((*it0)->getStopCode(), (*it1)->getStopCode(), "FOOT");
                this->dayNetwork->addEdge((*it1)->getStopCode(), (*it0)->getStopCode(), "FOOT");

                this->nightNetwork->addEdge((*it0)->getStopCode(), (*it1)->getStopCode(), "FOOT");
                this->nightNetwork->addEdge((*it1)->getStopCode(), (*it0)->getStopCode(), "FOOT");
            }
        }
    }

    auto lineLines = utils::file::readFile("../resources/lines.csv");

    // add network edges
    for (const auto& line : lineLines) {
        BusLine *l = BusLine::parseLine(line);

        auto &network = l->isNocturn() ? this->nightNetwork : this->dayNetwork;

        for (auto itr = l->getStops().begin(); itr < l->getStops().end() - 1; itr++) {

            auto currentStop = *itr, nextStop = *(itr + 1);

            network->addEdge(currentStop, nextStop, l->getLineCode());
        }

        if (!l->getReverseStops().empty())
            for (auto itr = l->getReverseStops().begin(); itr < l->getReverseStops().end() - 1; itr++) {

                auto currentStop = *itr, nextStop = *(itr + 1);

                network->addEdge(currentStop, nextStop, l->getLineCode());
            }

        this->lines.push_back(l);
    }
}

BusCompany::~BusCompany() {
    delete dayNetwork;
    nightNetwork->clear();
    delete nightNetwork;

    for (auto line : this->lines)
        delete line;
}

// Depth-First Search: example implementation
void BusCompany::dfs(const std::string& cStop, bool night) {
    auto &network =  night ? this->nightNetwork : this->dayNetwork;
    network->dfs(cStop);
};

// Breadth-First Search: example implementation
void BusCompany::bfs(const std::string& cStop, bool night) {
    auto &network =  night ? this->nightNetwork : this->dayNetwork;
    network->bfs(cStop);
};

double BusCompany::minDistance(const std::string& originStop, const std::string& destinyStop, bool night) {
    auto &network =  night ? this->nightNetwork : this->dayNetwork;
    if (lastOriginStop != originStop) {
        network->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (network->nodeAt(destinyStop).distToSingleSource == INF) return -1;
    return network->nodeAt(destinyStop).distToSingleSource;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minDistancePath(const std::string& originStop, const std::string& destinyStop, bool night) {
    auto &network =  night ? this->nightNetwork : this->dayNetwork;

    if (lastOriginStop != originStop) {
        network->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (network->nodeAt(destinyStop).distToSingleSource == INF) return {};

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(network->nodeAt(destinyStop).stop, network->nodeAt(destinyStop).lineCodeDijkstra);
    std::string v = destinyStop;
    while (v != originStop) {
        v = network->nodeAt(v).parentStopCodeDijkstra;
        path.emplace_front(network->nodeAt(v).stop, network->nodeAt(v).lineCodeDijkstra);
    }
    return path;
}

int BusCompany::minStops(const std::string& originStop, const std::string& destinyStop, bool night){
    if (originStop == destinyStop)
        return 0;

    auto &network = night ? this->nightNetwork : this->dayNetwork;

    network->visitedFalse();
    std::queue<std::pair<std::string ,int>> q; // queue of unvisited nodes with distance to v
    q.push({originStop, 0});
    network->nodeAt(originStop).visited = true;
    int nStops = -1;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front().first;
        int u1 = q.front().second; q.pop();
        for (const auto& e : network->nodeAt(u).adj) {
            std::string w = e.dest;
            if (!network->nodeAt(w).visited) {
                if (w == destinyStop) {
                    nStops = u1+1;
                }
                q.push({w, u1 + 1});
                network->nodeAt(w).visited = true;
                network->nodeAt(w).parentStopCodeBFS = u;
                network->nodeAt(w).lineCodeBFS = *e.lineCodes.begin();
                if (w == destinyStop)
                    return nStops;
            }
        }
    }
    return nStops;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minStopsPath(const std::string& originStop, const std::string& destinyStop, bool night){
    int aux = this->minStops(originStop, destinyStop, night);
    if (aux <= 0) return {};  // maybe separate same stop from no path

    auto& network = night ? this->nightNetwork : this->dayNetwork;

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(network->nodeAt(destinyStop).stop, network->nodeAt(destinyStop).lineCodeBFS);
    std::string v = destinyStop;
    while (v != originStop) {
        v = network->nodeAt(v).parentStopCodeBFS;
        path.emplace_front(network->nodeAt(v).stop, network->nodeAt(v).lineCodeBFS);
    }
    return path;
}

std::set<const Stop *> BusCompany::nearbyStops(double lattittude, double longitude) const {

    Stop dummyStop{"", "", "", lattittude, longitude};
    std::set<const Stop *> ret;

    for (const auto& stopCode : this->dayNetwork->getStopCodes()) { // can be any of them, they both have the same stops

        auto stop = this->dayNetwork->nodeAt(stopCode).stop;

        if (stop->distance(dummyStop) <= BusCompany::MAX_NEARBY_DISTANCE)
            ret.insert(stop);
    }

    for (auto stop : ret) {
        if (stop->getLatitude() == lattittude && stop->getLongitude() == longitude) {
            ret.erase(stop);
            break;
        }
    }

    return ret;
}

std::set<const Stop *> BusCompany::nearbyStops(const std::string& stopCode) const {
    auto node = this->dayNetwork->nodeAt(stopCode);

    return this->nearbyStops(node.stop->getLatitude(), node.stop->getLongitude());
}

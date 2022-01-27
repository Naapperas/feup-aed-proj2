#include "../include/busCompany.h"

BusCompany::BusCompany(const std::string& companyName) : companyName(companyName), lastOriginStop("") {

    auto stopLines = utils::file::readFile("../resources/stops.csv");
    std::vector<Stop*> stops;

    this->networkDayTime = new Graph(stopLines.size());
    this->networkNocturnal = new Graph(stopLines.size());

    for (const auto& line : stopLines) {
        Stop* s = Stop::parseLine(line);

        this->networkDayTime->addNode(s->getStopCode(), s);
        this->networkNocturnal->addNode(s->getStopCode(), s);

        stops.push_back(s);
    }

    // add walking edges
    for (auto it0 = stops.begin(); it0 != stops.end(); it0++)  {
        for (auto it1 = it0; it1 != stops.end(); it1++) {
            if (it0 == it1) continue;

            auto distance = (*it0)->distance(*(*it1));

            if (distance <= Stop::MAX_WALKING_DISTANCE) {

                this->networkDayTime->addEdge((*it0)->getStopCode(), (*it1)->getStopCode(), "FOOT");
                this->networkDayTime->addEdge((*it1)->getStopCode(), (*it0)->getStopCode(), "FOOT");

                this->networkNocturnal->addEdge((*it0)->getStopCode(), (*it1)->getStopCode(), "FOOT");
                this->networkNocturnal->addEdge((*it1)->getStopCode(), (*it0)->getStopCode(), "FOOT");
            }
        }
    }

    auto lineLines = utils::file::readFile("../resources/lines.csv");

    // add network edges
    for (const auto& line : lineLines) {
        BusLine* l = BusLine::parseLine(line);

        if(l->isNocturn()) {
            for (auto itr = l->getStops().begin(); itr < l->getStops().end() - 1; itr++) {

                auto currentStop = *itr, nextStop = *(itr + 1);

                this->networkNocturnal->addEdge(currentStop, nextStop, l->getLineCode());
            }

            if (!l->getReverseStops().empty())
                for (auto itr = l->getReverseStops().begin(); itr < l->getReverseStops().end() - 1; itr++) {

                    auto currentStop = *itr, nextStop = *(itr + 1);

                    this->networkNocturnal->addEdge(currentStop, nextStop, l->getLineCode());
                }
        }
        else {
            for (auto itr = l->getStops().begin(); itr < l->getStops().end() - 1; itr++) {

                auto currentStop = *itr, nextStop = *(itr + 1);

                this->networkDayTime->addEdge(currentStop, nextStop, l->getLineCode());
            }

            if (!l->getReverseStops().empty())
                for (auto itr = l->getReverseStops().begin(); itr < l->getReverseStops().end() - 1; itr++) {

                    auto currentStop = *itr, nextStop = *(itr + 1);

                    this->networkDayTime->addEdge(currentStop, nextStop, l->getLineCode());
                }
        }

        this->lines.push_back(l);
    }
}

BusCompany::~BusCompany() {
    delete networkDayTime;
    delete networkNocturnal;

    for (auto line : this->lines)
        delete line;
}

// Depth-First Search: example implementation
void BusCompany::dfs(const std::string& cStop) {
    this->networkDayTime->dfs(cStop);
};

// Breadth-First Search: example implementation
void BusCompany::bfs(const std::string& cStop) {
    this->networkDayTime->bfs(cStop);
};

double BusCompany::minDistance(const std::string& originStop, const std::string& destinyStop) {
    if (lastOriginStop != originStop) {
        this->networkDayTime->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (this->networkDayTime->nodeAt(destinyStop).distToSingleSource == INF) return -1;
    return this->networkDayTime->nodeAt(destinyStop).distToSingleSource;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minDistancePath(const std::string& originStop, const std::string& destinyStop) {
    if (lastOriginStop != originStop) {
        this->networkDayTime->dijkstra(originStop);
        lastOriginStop = originStop;
    }
    if (this->networkDayTime->nodeAt(destinyStop).distToSingleSource == INF) return {};

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(this->networkDayTime->nodeAt(destinyStop).stop, this->networkDayTime->nodeAt(destinyStop).lineCodeDijkstra);
    std::string v = destinyStop;
    while (v != originStop) {
        v = this->networkDayTime->nodeAt(v).parentStopCodeDijkstra;
        path.emplace_front(this->networkDayTime->nodeAt(v).stop, this->networkDayTime->nodeAt(v).lineCodeDijkstra);
    }
    return path;
}

int BusCompany::minStops(const std::string& originStop, const std::string& destinyStop){
    if (originStop == destinyStop)
        return 0;
    this->networkDayTime->visitedFalse();
    std::queue<std::pair<std::string ,int>> q; // queue of unvisited nodes with distance to v
    q.push({originStop, 0});
    this->networkDayTime->nodeAt(originStop).visited = true;
    int nStops = -1;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front().first;
        int u1 = q.front().second; q.pop();
        for (auto e : this->networkDayTime->nodeAt(u).adj) {
            std::string w = e.dest;
            if (!this->networkDayTime->nodeAt(w).visited) {
                if (w == destinyStop) {
                    nStops = u1+1;
                }
                q.push({w, u1 + 1});
                this->networkDayTime->nodeAt(w).visited = true;
                this->networkDayTime->nodeAt(w).parentStopCodeBFS = u;
                this->networkDayTime->nodeAt(w).lineCodeBFS = *e.lineCodes.begin();
            }
        }
    }
    return nStops;
}

std::list<std::pair<const Stop*, std::string>> BusCompany::minStopsPath(const std::string& originStop, const std::string& destinyStop){
    int aux = this->minStops(originStop, destinyStop);
    if (aux <= 0) return {};  // maybe separate same stop from no path

    std::list<std::pair<const Stop*, std::string>> path;
    path.emplace_front(this->networkDayTime->nodeAt(destinyStop).stop, this->networkDayTime->nodeAt(destinyStop).lineCodeBFS);
    std::string v = destinyStop;
    while (v != originStop) {
        v = this->networkDayTime->nodeAt(v).parentStopCodeBFS;
        path.emplace_front(this->networkDayTime->nodeAt(v).stop, this->networkDayTime->nodeAt(v).lineCodeBFS);
    }
    return path;
}
#include "../include/busCompany.h"

BusCompany::BusCompany(const std::string& companyName) : companyName(companyName) {

    auto stopLines = utils::file::readFile("../resources/stops.csv");
    std::vector<Stop*> stops;

    this->network = new Graph(stopLines.size());

    for (const auto& line : stopLines) {
        Stop* s = Stop::parseLine(line);

        stops.push_back(s);
    }

    for (auto currentStop : stops)  {
        this->network->addNode(currentStop->getStopCode(), currentStop);

        for (auto otherStop : stops) {
            if (otherStop == currentStop) continue;

            auto distance = currentStop->distance(*otherStop);

            if (distance <= Stop::MAX_WALKING_DISTANCE) {

                this->network->addEdge(currentStop->getStopCode(), otherStop->getStopCode(), "FOOT");
                this->network->addEdge(otherStop->getStopCode(), currentStop->getStopCode(), "FOOT");
            }
        }
    }

    auto lineLines = utils::file::readFile("../resources/lines.csv");

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
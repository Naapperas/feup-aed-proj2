#include <vector>
#include <string>

#include "../include/stop.h"

std::ostream& operator <<(std::ostream& out , const Stop& stop) {
    out << stop.getStopCode() << " - " << stop.getName() << std::endl;
    return out;
}

double Stop::distance(const Stop &oStop, const Stop &dStop) {
    // distance between latitudes
    // and longitudes
    double dLat = (dStop.getLatitude() - oStop.getLatitude()) *
                  M_PI / 180.0;
    double dLon = (dStop.getLongitude() - oStop.getLongitude()) *
                  M_PI / 180.0;

    // convert to radians
    double oStopLat = (oStop.getLatitude()) * M_PI / 180.0;
    double dStopLat = (dStop.getLatitude()) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(oStopLat) * cos(dStopLat);
    double rad = 6371; // earths radius in meters
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

Stop* Stop::parseLine(const std::string& line) {
    std::string stopCode, stopName, stopZone;
    double longitude, lattitude;

    std::stringstream ss(line);

    std::vector<std::string> lineTokens;
    std::string token;

    while (std::getline(ss, token, ','))
        lineTokens.push_back(token);

    if (lineTokens.size() != 5)
        return nullptr;

    stopCode = lineTokens.at(0);
    stopName = lineTokens.at(1);
    stopZone = lineTokens.at(2);
    lattitude = std::stod(lineTokens.at(3));
    longitude = std::stod(lineTokens.at(4));

    return new Stop{stopCode, stopName, stopZone, lattitude, longitude};
}

double Stop::distance(const Stop &s) const {
    return Stop::distance(*this, s);
}
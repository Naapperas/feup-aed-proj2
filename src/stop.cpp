#include "../include/stop.h"

std::ostream& operator <<(std::ostream& out , const Stop& stop) {
    out << stop.getName() << std::endl;
    return out;
}

double Stop::distance(const Stop &cStop, const Stop &dStop) {
    // distance between latitudes
    // and longitudes
    double dLat = (dStop.getLatitude() - cStop.getLatitude()) *
                  M_PI / 180.0;
    double dLon = (dStop.getLongitude() - cStop.getLongitude()) *
                  M_PI / 180.0;

    // convert to radians
    double cStopLat = (cStop.getLatitude()) * M_PI / 180.0;
    double dStopLat = (dStop.getLatitude()) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(cStopLat) * cos(dStopLat);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double Stop::distance(const Stop &s) const {
    return Stop::distance(*this, s);
}
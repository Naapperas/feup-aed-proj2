#include "../include/stop.h"

std::ostream& operator <<(std::ostream& out , const Stop& stop) {
    out << stop.getName() << std::endl;
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

double Stop::distance(const Stop &s) const {
    return Stop::distance(*this, s);
}
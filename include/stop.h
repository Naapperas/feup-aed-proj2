#ifndef PROJECT2_STOP_H
#define PROJECT2_STOP_H

#include <string>
#include <iostream>

class Stop{
    std::string const name, zone;
    double latitude, longitude;
    friend std::ostream& operator <<(std::ostream& out ,const Stop& stop);
public:
    Stop(std::string name, std::string zone, double latitude, double longitude) : name(name), zone(zone), latitude(latitude), longitude(longitude) {}

    std::string getName() const {
        return name;
    }

    std::string getZone() const {
        return zone;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }
};

#endif //PROJECT2_STOP_H

#ifndef PROJECT2_STOP_H
#define PROJECT2_STOP_H

#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

class Stop{
    std::string const code, name, zone;
    double latitude, longitude;

    bool closed = false;

    friend std::ostream& operator <<(std::ostream& out ,const Stop& stop);

public:
    constexpr static double MAX_WALKING_DISTANCE = 0.100; // KMs

    Stop(const std::string& stopCode, const std::string& name, const std::string& zone, double latitude, double longitude) : code(stopCode), name(name), zone(zone), latitude(latitude), longitude(longitude) {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getZone() const {
        return zone;
    }

    const std::string& getStopCode() const {
        return code;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    void toggleStop() {
        this->closed = !this->closed;
    }


    bool isClosed() const {
        return closed;
    }

    static double distance(const Stop& oStop, const Stop& dStop);

    double distance(const Stop& s) const;

    static Stop* parseLine(const std::string& line);
};

#endif //PROJECT2_STOP_H

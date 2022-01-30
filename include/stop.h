#ifndef PROJECT2_STOP_H
#define PROJECT2_STOP_H

#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

/**
 * Represents a Stop in the STCP network.
 * In the context of this program this is going to act as a graph node.
 */
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

    /**
     * Toggles the 'closed' status of this line.
     */
    void toggleStop() {
        this->closed = !this->closed;
    }


    bool isClosed() const {
        return closed;
    }

    /**
     * Calculates the great-circle distance between 2 stops on the surface of the Earth.
     *
     * @param oStop the first stop
     * @param dStop the second stop
     * @return the great-circle distance between 2 stops
     */
    static double distance(const Stop& oStop, const Stop& dStop);

    /**
     * Calculates the great-circle distance from the given stop to this stop along the surface of the earth.
     *
     * @param s the other stop
     * @return the great-circle distance between this and the other stop
     */
    double distance(const Stop& s) const;

    /**
     * Parses a line read from a CSV file containing data needed to construct a Stop object.
     *
     * @param line a string containing comma-separated-values representing a stop.
     * @return a dynamically allocated Stop object with the given data
     */
    static Stop* parseLine(const std::string& line);
};

#endif //PROJECT2_STOP_H

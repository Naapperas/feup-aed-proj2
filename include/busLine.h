#ifndef PROJECT2_BUSLINE_H
#define PROJECT2_BUSLINE_H

#include <fstream>
#include <sstream>
#include <vector>

#include "utils.h"

class BusLine{
    std::string code, name;
    bool nocturn;
    std::vector<std::string> stops, stopsReverse;  // both directions7

    bool closed = false;

    friend std::ostream& operator <<(std::ostream& out ,const BusLine& line);

public:
    BusLine(const std::string &code, const std::string &name, bool nocturn);

    const std::string& getLineCode() const {
        return code;
    }

    const std::string& getLineName() const {
        return name;
    }

    bool isNocturn(){
        return nocturn;
    }

    const std::vector<std::string>& getStops() const {
        return this->stops;
    }

    const std::vector<std::string>& getReverseStops() const {
        return this->stopsReverse;
    }

    void toggleLine() {
        this->closed = !this->closed;
    }

    bool isClosed() const {
        return closed;
    }

    static BusLine* parseLine(const std::string& line);
};

#endif //PROJECT2_BUSLINE_H

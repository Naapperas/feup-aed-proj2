#ifndef PROJECT2_BUSLINE_H
#define PROJECT2_BUSLINE_H

#include <fstream>
#include <list>
#include <sstream>
#include <vector>

#include "utils.h"

class BusLine{
    std::string code, name;
    bool nocturn;
    std::list<std::string> stops0, stops1;  // both directions

    static std::list<std::string> readSequence(const std::string& filePath);

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

    static BusLine* parseLine(const std::string& line);
};

#endif //PROJECT2_BUSLINE_H

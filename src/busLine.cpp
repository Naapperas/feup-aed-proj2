#include "../include/busLine.h"

BusLine::BusLine(const std::string &code, const std::string &name, bool nocturn) : code(code), name(name), nocturn(nocturn) {
    // handle the actual sequence of stops here in constructor
    stops0 = readSequence("../resources/line_" + this->code + "_0.csv");
    stops1 = readSequence("../resources/line_" + this->code + "_1.csv");
}

std::list<std::string> BusLine::readSequence(const std::string& filePath){
    std::ifstream file(filePath);

    if (!file.is_open())
        return {}; // error

    file.ignore(INT32_MAX, '\n');

    std::list<std::string> stops;

    std::string line;
    while(std::getline(file, line))
        stops.push_back(line);

    return stops;
}

BusLine* BusLine::parseLine(const std::string& line) {
    std::string code, name;

    std::stringstream ss(line);

    std::vector<std::string> lineTokens;
    std::string token;

    while (std::getline(ss, token, ','))
        lineTokens.push_back(token);

    if (lineTokens.size() != 2)
        return nullptr;

    code = lineTokens.at(0);
    name = lineTokens.at(1);

    if (name.back() == 'M')
        return new BusLine(code, name, true);
    else
        return new BusLine(code, name, false);
}


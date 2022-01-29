#include "../include/busLine.h"

BusLine::BusLine(const std::string &code, const std::string &name, bool nocturn) : code(code), name(name), nocturn(nocturn) {
    // handle the actual sequence of stops here in constructor
    stops = utils::file::readFile("../resources/line_" + this->code + "_0.csv");
    stopsReverse = utils::file::readFile("../resources/line_" + this->code + "_1.csv");
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

    return new BusLine(code, name, code.back() == 'M');
}

std::ostream& operator <<(std::ostream& out , const BusLine& line) {
    out << line.getLineName();
    return out;
}


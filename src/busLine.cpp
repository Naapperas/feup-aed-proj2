#include "../include/busLine.h"

BusLine::BusLine(const std::string &code, const std::string &name, bool nocturn) : code(code), name(name), nocturn(nocturn) {
    // handle the actual sequence of stops here in constructor
    std::vector<std::string> stops0Vector = utils::file::readFile("../resources/line_" + this->code + "_0.csv");
    std::vector<std::string> stops1Vector = utils::file::readFile("../resources/line_" + this->code + "_1.csv");

    stops0 = std::list<std::string>(stops0Vector.begin(), stops0Vector.end());
    stops1 = std::list<std::string>(stops1Vector.begin(), stops1Vector.end());
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

    return new BusLine(code, name, name.back() == 'M');
}


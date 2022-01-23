#include "../include/stop.h"

std::ostream& operator <<(std::ostream& out , const Stop& stop) {
    out << stop.getName() << std::endl;
    return out;
}
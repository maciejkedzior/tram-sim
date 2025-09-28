#ifndef TRAMSIM_STOPS_LOADER_HPP
#define TRAMSIM_STOPS_LOADER_HPP

#include <map>
#include <string>
#include "stop.hpp"

namespace TramSim {
    std::map<std::string, Stop> loadStops(const std::string& filepath);
    std::map<std::string, std::vector<std::string>> loadRoutes(const std::string& filepath);
}

#endif
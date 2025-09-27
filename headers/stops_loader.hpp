#pragma once

#include <map>
#include <string>
#include "stop.hpp"

std::map<std::string, Stop> loadStops(const std::string& filepath);

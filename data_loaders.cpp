#include "headers/data_loaders.hpp"
#include "headers/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <format>

namespace TramSim {

    std::map<std::string, Stop> loadStops(const std::string& filepath) {
        std::ifstream ifs(filepath);
        if (!ifs.is_open()) throw std::runtime_error("Cannot open stops file: " + filepath);

        nlohmann::json j;
        try {
            ifs >> j;
        } catch (const nlohmann::json::exception& e) {
            throw std::runtime_error(std::string("JSON parse error: ") + e.what());
        }

        std::map<std::string, Stop> stops;
        
        for (const auto& item : j.items()) {
            const std::string name = item.key();
            const auto& data = item.value();

            if (!data.is_object() || !data.contains("x") || !data.contains("y") || !data.contains("on_demand")
                || !data["x"].is_number_unsigned() || !data["y"].is_number_unsigned() || !data["on_demand"].is_boolean()) {
                throw std::logic_error("Incorrect data for " + name + " stop!");
            }

            unsigned int x = data["x"].get<unsigned int>();
            unsigned int y = data["y"].get<unsigned int>();
bool on_demand = data["on_demand"].get<bool>();
            stops.try_emplace(name, name, x, y, on_demand);
        }

        std::cout << std::format("[JSON DEBUG] [{}] {} stops loaded!\n", filepath, stops.size());

        ifs.close();
        return stops;
    }


    std::map<std::string, std::vector<std::string>> loadRoutes(const std::string& filepath){
        std::ifstream ifs(filepath);
        if (!ifs.is_open()) throw std::runtime_error("Cannot open stops file: " + filepath);

        nlohmann::json j;
        try {
            ifs >> j;
        } catch (const nlohmann::json::exception& e) {
            throw std::runtime_error(std::string("JSON parse error: ") + e.what());
        }

        std::map<std::string, std::vector<std::string>> routes;
        
        for (const auto& item : j.items()) {
            const std::string name = item.key();
            const auto& data = item.value();
            if (!data.is_array()) {
                throw std::logic_error("Incorrect data for " + name + " route!");
            }
            if (data.is_array() && data.size() <= 2){
                throw std::logic_error("Route list is too short, must be at least 2 but found " + data.size());
            }
            routes.try_emplace(name, data);
        }

        std::cout << std::format("[JSON DEBUG] [{}] {} routes loaded!\n", filepath, routes.size());

        ifs.close();
        return routes;
    }
};
#include <iostream>                  
#include <map>
#include <vector>
#include <string>
#include "headers/city_structure.hpp"
#include "headers/graph.hpp"
#include "headers/stop.hpp"
#include "headers/data_loaders.hpp"


int main(){
    std::map<std::string, Stop> stops;
    std::map<std::string, std::vector<std::string>> routes;
    std::vector<std::pair<Stop, Stop>> connections;

    try {
        stops = TramSim::loadStops("data/stops.json");
        routes = TramSim::loadRoutes("data/routes.json");
        for (const auto& [first, second]: TramSim::loadConnections("data/stops.json")){
            connections.push_back(std::make_pair(stops.at(first), stops.at(second)));
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load data file: " << e.what() << std::endl;
        return 1;
    }

    TramSim::TransitNetwork network("Krakow", connections);
    std::cout << "Created network!" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    network.printWholeNetwork();
    std::cout << "----------------------------------" << std::endl << std::endl;

    for (const auto& [route_number, route]: routes){
        std::vector<Stop> transformed_route;
        for (const auto& stop_name: route)
            transformed_route.push_back(stops.at(stop_name));
        network.addNewTramLine(std::stoul(route_number), transformed_route);
        std::cout << std::format("Added new line [{}]!", route_number) << std::endl;
    }

    std::cout << "----------------------------------" << std::endl;
    network.printSpecifiedTramLine(72);
    network.printSpecifiedTramLine(11);
    return 0;
}
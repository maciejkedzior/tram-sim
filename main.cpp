#include <iostream>                  
#include <map>
#include <vector>
#include <string>
#include <exception>
#include "headers/city_structure.hpp"
#include "headers/graph.hpp"
#include "headers/stop.hpp"
#include "headers/data_loaders.hpp"


int main(){
    std::map<std::string, Stop> stops;
    std::map<std::string, std::vector<std::string>> routes;
    try {
        stops = TramSim::loadStops("data/stops.json");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load stops: " << e.what() << std::endl;
        return 1;
    }

    std::vector<std::pair<Stop, Stop>> connections = {
        std::make_pair(stops.at("Czerwone Maki P+R"), stops.at("Chmieleniec")),
        std::make_pair(stops.at("Chmieleniec"), stops.at("Kampus UJ")),
        std::make_pair(stops.at("Kampus UJ"), stops.at("Ruczaj")),
        std::make_pair(stops.at("Ruczaj"), stops.at("Norymberska")),
        std::make_pair(stops.at("Norymberska"), stops.at("Grota-Roweckiego")),
        std::make_pair(stops.at("Grota-Roweckiego"), stops.at("Lipinskiego")),
        std::make_pair(stops.at("Lipinskiego"), stops.at("Kobierzynska")),
        std::make_pair(stops.at("Kobierzynska"), stops.at("Slomiana")),
        std::make_pair(stops.at("Slomiana"), stops.at("Kapelanka")),
        std::make_pair(stops.at("Kapelanka"), stops.at("Szwedzka")),
        std::make_pair(stops.at("Szwedzka"), stops.at("Rondo Grunwaldzkie")),
        std::make_pair(stops.at("Lipinskiego"), stops.at("Borsucza")),
        std::make_pair(stops.at("Borsucza"), stops.at("Brozka")),
        std::make_pair(stops.at("Brozka"), stops.at("Lagiewniki")),
    };

    try {
        routes = TramSim::loadRoutes("data/routes.json");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load routes: " << e.what() << std::endl;
        return 1;
    }

    
    TramSim::TransitNetwork network("Krakow", connections);
    std::cout << "Created network!" << std::endl;

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
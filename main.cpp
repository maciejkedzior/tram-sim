#include <iostream>                  
#include <map>
#include <vector>
#include <exception>
#include "headers/city_structure.hpp"
#include "headers/graph.hpp"
#include "headers/stop.hpp"
#include "headers/data_loaders.hpp"


int main(){
    std::map<std::string, Stop> stops;
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

    std::vector<Stop> route = {
        stops.at("Czerwone Maki P+R"),
        stops.at("Chmieleniec"),
        stops.at("Kampus UJ"),
        stops.at("Ruczaj"),
        stops.at("Norymberska"),
        stops.at("Grota-Roweckiego"),
        stops.at("Lipinskiego"),
        stops.at("Kobierzynska"),
        stops.at("Slomiana"),
        stops.at("Kapelanka"),
        stops.at("Szwedzka"),
        stops.at("Rondo Grunwaldzkie"),
    };
    
    TransitNetwork network = TransitNetwork("Krakow", connections);
    std::cout << "Created network!" << std::endl;
    network.addNewTramLine(72, route);
    std::cout << "Added new line!" << std::endl;
    network.printSpecifiedTramLine(72);
    return 0;
}
#include <iostream>                  
#include <map>
#include <vector>
#include <exception>
#include "headers/graph.hpp"


struct Stop {
    std::string name;
    unsigned int x, y;
    Stop (std::string n, unsigned int _x, unsigned int _y): name(n), x(_x), y(_y) {}
    friend std::ostream& operator<<(std::ostream& os, const Stop& obj) {
        os << obj.name << " (" << obj.x << "," << obj.y << ")";
        return os;
    }
    bool operator == (const Stop& other) const { return std::tie(name, x, y) == std::tie(other.name, other.x, other.y);}
    bool operator != (const Stop& other) const { return !((*this) == other);}
    bool operator < (const Stop& other) const { return std::tie(name, x, y) < std::tie(other.name, other.x, other.y);}
    bool operator > (const Stop& other) const { return std::tie(name, x, y) > std::tie(other.name, other.x, other.y);}
};

template <>
struct std::hash<Stop>{
    std::size_t operator ()(const Stop& stop) const {
        return ( ( std::hash<std::string>()(stop.name) ^ (std::hash<unsigned int>()(stop.x) << 1) ) >> 1) ^ (std::hash<unsigned int>()(stop.y) << 1);
    }
};


class TramRoutes {
    private:
        const Graph<Stop>& grid;
        std::map<unsigned int, std::vector<Stop>> tram_lines;
    public:
        explicit TramRoutes(const Graph<Stop>& _grid): grid(_grid) {}
        void addTramLine(unsigned int number, const std::vector<Stop>& route){
            if (!grid.routeIsCorrect(route))
                throw std::logic_error("There's no correct connection somewhere in this route! Check it again!");
            tram_lines[number] = route;
        }
        const std::vector<Stop>& getRoute(unsigned int number) const {
            return tram_lines.at(number);
        }
};

class TransitNetwork {
    private:
        std::string city_name;
        Graph<Stop> grid;
        TramRoutes routes;
    public:
        TransitNetwork(const std::string& city, const std::vector<std::pair<Stop,Stop>>& connections): city_name(city), grid(), routes(grid){
            for (const auto& connection: connections)
                grid.addEdge(connection);
        }

        void addNewTramLine(unsigned int number, const std::vector<Stop>& route){
            routes.addTramLine(number, route);
        }

        void printSpecifiedTramLine(unsigned int number){
            const auto& line = routes.getRoute(number); // avoid copy
            std::cout << "Route for line [" << number << "]:" << std::endl;
            if (line.empty()) { std::cout << "(empty route)\n"; return; }
            std::cout << "- " << line.front() << std::endl;
            for (size_t i = 1; i + 1 < line.size(); ++i)
                std::cout << "| " << line[i] << std::endl;
            if (line.size() > 1) std::cout << "- " << line.back() << std::endl;
        }
};

std::map<std::string, Stop> stops = {
    std::make_pair("Czerwone Maki P+R", Stop("Czerwone Maki P+R", 0, 0)),
    std::make_pair("Chmieleniec", Stop("Chmieleniec", 1, 1)),
    std::make_pair("Kampus UJ", Stop("Kampus UJ", 2, 2)),
    std::make_pair("Ruczaj", Stop("Ruczaj", 3, 3)),
    std::make_pair("Norymberska", Stop("Norymberska", 4, 4)),
    std::make_pair("Grota-Roweckiego", Stop("Grota-Roweckiego", 6, 5)),
    std::make_pair("Lipinskiego", Stop("Lipinskiego", 7, 5)),
    std::make_pair("Kobierzynska", Stop("Kobierzynska", 8, 6)),
    std::make_pair("Slomiana", Stop("Slomiana", 8, 7)),
    std::make_pair("Kapelanka", Stop("Kapelanka", 8, 8)),
    std::make_pair("Borsucza", Stop("Borsucza", 9, 5)),
    std::make_pair("Brozka", Stop("Brozka", 10, 4)),
    std::make_pair("Lagiewniki", Stop("Lagiewniki", 11, 4)),
    std::make_pair("Szwedzka", Stop("Szwedzka", 9, 9)),
    std::make_pair("Rondo Grunwaldzkie", Stop("Rondo Grunwaldzkie", 10, 10)),

};

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
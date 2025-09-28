#ifndef CITY_STRUCTURE
#define CITY_STRUCTURE
#include <format>
#include "graph.hpp"
#include "stop.hpp"


namespace TramSim{
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
                std::cout << std::format("Route for line [{}]:", number) << std::endl;
                if (line.empty()) { std::cout << "(empty route)\n"; return; }
                std::cout << std::format("- {}", line.front()) << std::endl;
                for (size_t i = 1; i + 1 < line.size(); ++i)
                    std::cout << std::format("| {}", line[i]) << std::endl;
                if (line.size() > 1) std::cout << std::format("- {}", line.back()) << std::endl;
            }

            void searchGrid(const Stop& starting_point){
                grid.depthFirstSearch(starting_point, [](const Stop& name){std::cout << std::format("Tram stop: {}", name) << std::endl; } );
            }
    };
}
#endif
#ifndef GRAPHLIST
#define GRAPHLIST

#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <stdexcept>

enum class GraphType {DIRECTED, UNDIRECTED};
enum class WeightCase {WEIGHTED, WEIGHTLESS};

template <typename T>
class Graph{
    using Weight = double;
    public:
        struct Vertex{
            T value;
            Vertex(T x): value(x) {}
            bool operator < (const Vertex& other) const { return value < other.value; }
            bool operator > (const Vertex& other) const { return value > other.value; }
            bool operator == (const Vertex& other) const { return value == other.value; }
            bool operator != (const Vertex& other) const { return !((*this) == other); }
        };
    private:
        struct CustomHash{
            std::size_t operator()(Vertex const& v) const noexcept {
                return std::hash<T>{}(v.value);
            }
        };

    private:
    std::unordered_map<Vertex, std::list<std::pair<Vertex, Weight>>, CustomHash> edge_list;
    std::map<Vertex, bool> visited;
    GraphType graph_type;
    WeightCase weight_case;

    public:
    Graph(GraphType type=GraphType::UNDIRECTED, WeightCase weight=WeightCase::WEIGHTLESS): graph_type(type), weight_case(weight) {}

    public:
    std::vector<Graph::Vertex> getVertexes() const { 
        std::vector<Graph::Vertex> keys;
        for (const auto& i: edge_list) keys.push_back(i.first);
        return keys;
    }

    void depthFirstSearch(T x){
        Vertex v(x);
        visited[v] = true;
        std::cout << v.value << std::endl;

        for (auto i=edge_list[v].begin(); i != edge_list[v].end(); i++)
            if(!visited[(*i).first.value])
                depthFirstSearch((*i).first.value); 
    }

    
    double sizeOfGraph() const {
        int size=0;
        for (const auto& i: edge_list)
            size += i.second.size();
        return size/2;    
    }
    
    void addVertex(const T& x) { 
        edge_list[Vertex(x)] = std::list<std::pair<Vertex, Weight>>();
    }

    void removeVertex(const T& x) { 
        if (edge_list.find(Vertex(x)) != edge_list.end()) edge_list.erase(Vertex(x));
        for (auto& vertex: edge_list){
            auto list = vertex.second;
            if (std::find_if(list.begin(), list.end(), [&](std::pair<Vertex,Weight> const& b){ return b.first == Vertex(x); }) != vertex.second.end())
                vertex.second.remove(Vertex(x));
        }
    }

    // If graph is DIRECTED then it creates arrow x -> y
    void addEdge(const T&x, const T&y, Weight weight=0) {
        if (edge_list.find(Vertex(x)) == edge_list.end()) addVertex(x);
        if (edge_list.find(Vertex(y)) == edge_list.end()) addVertex(y);

        edge_list.at(Vertex(x)).emplace_back(std::make_pair(Vertex(y), weight));
        
        if (graph_type == GraphType::UNDIRECTED)
            edge_list.at(Vertex(y)).emplace_back(std::make_pair(Vertex(x), weight));
    }
    
    void addEdge(const std::pair<T,T>& vertexes, Weight weight=0){
        if (!keyInGraph(vertexes.first)) addVertex(vertexes.first);
        if (!keyInGraph(vertexes.second)) addVertex(vertexes.second);

        edge_list.at(Vertex(vertexes.first)).emplace_back(std::make_pair(Vertex(vertexes.second), weight));
        
        if (graph_type == GraphType::UNDIRECTED)
            edge_list.at(Vertex(vertexes.second)).emplace_back(std::make_pair(Vertex(vertexes.first), weight));

    }

    void removeEdge(const T& x, const T& y){
        auto& list1 = edge_list.at(Vertex(x));
        auto& list2 = edge_list.at(Vertex(y));
        list1.remove_if([&](std::pair<Vertex,Weight> const& b){ return b.first == Vertex(y); });
        list2.remove_if([&](std::pair<Vertex,Weight> const& b){ return b.first == Vertex(x); });
    }

    std::list<std::pair<Vertex, Weight>> neighbours(const T& x) const { 
        return edge_list.at(Vertex(x)); 
    }

    bool adjacent(const T& x, const T& y) const {
        auto neighbours_list = neighbours(x);
        auto it = std::find(neighbours_list.begin(), neighbours_list.end(), std::make_pair(Vertex(y), 0.0));
        return it != neighbours_list.end();
    }

    bool keyInGraph(const T& x) const {
        return edge_list.find(Vertex(x)) != edge_list.end();
    }

    T getVertexValue(const T& x) const {
        return Vertex(x).value;
    }

    void setVertexValue(const T& x, const T& v) {
        auto temp = edge_list.extract(Vertex(x));   // here I get std::pair(x, list_of_neighbours_of_x)
        temp.key() = Vertex(v);
        edge_list.insert(std::move(temp));
        for (auto& adj_list: edge_list)
            std::replace(adj_list.second.begin(), adj_list.second.end(), Vertex(x), Vertex(v));
    }
    
    int getEdgeValue(const T& x, const T& y) const {
        if (weight_case == WeightCase::WEIGHTLESS) throw std::logic_error("Graph is not weighted!");

        auto list = neighbours(x);
        auto place = std::find_if(list.begin(), list.end(), [&](std::pair<Vertex,Weight> const& b){ return b.first == Vertex(y); });
        if (place == list.end())
            throw std::logic_error("There's no connection between these vertexes!");
        return (*place).second;
        
    }

    void printConnections(){
        for (const auto& i: edge_list){
            if (graph_type == GraphType::DIRECTED) std::cout << i.first.value << " -> "; else std::cout << i.first.value << " -- ";
            
            for (const auto& j: i.second)
                if (weight_case == WeightCase::WEIGHTED) std::cout << j.first.value << "[" << j.second << "], "; else std::cout << j.first.value << ", ";
            std::cout << std::endl;
        }
    }

    bool routeIsCorrect(const std::vector<T>& route) const {
        for (std::size_t i=0; i < route.size()-1; i++){
            if (!adjacent(route[i], route[i+1]))
                return false;
        }
        return true;
    }
};


#endif
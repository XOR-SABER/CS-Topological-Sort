#include "headers/vertex.hpp"

// Copy constructor
Vertex::Vertex(const Vertex& v) {
    this->name = v.name;
    this->connections = v.connections;
    this->total_edge_weight = v.total_edge_weight;
    this->weight = v.weight; 
    this->topo_cache = v.topo_cache;
}

// std::string constructor
Vertex::Vertex(const std::string & new_name) {
    this->name = new_name;
}

// Adds a connection to the connections list.. 
void Vertex::add_connection(const std::string &new_name) {
    // Basically means to update the cache...
    if(!topo_cache.empty()) topo_cache.clear();
    connections.push_back(new_name);
    total_edge_weight++; 
}

// Updates the topo cache 
void Vertex::update_cache(const std::vector<std::string> &new_cache) {
    topo_cache = new_cache;
}

// Gets a refrence to the cache
std::vector<std::string> &Vertex::get_topo_cache() {
    return topo_cache;
}

// Gets a refrence to the connections list
std::vector<std::string> &Vertex::get_connnections() {
    return connections;
}

// Increases the weight of the vertex.. 
void Vertex::operator++() {
    weight++;
}

// Makes my life a little easier
std::string &Vertex::operator[](const size_t &index) {
    return connections.at(index);
}

// Print out each vertex
std::ostream &operator<<(std::ostream &outs, const Vertex &v) {
    outs << "Class: " << v.name << "\n\tPrereqs: ";
    if(v.connections.empty()) outs << "None ";
    else for(const std::string &s : v.connections) outs << s << " ";
    outs << "\n\tPrereq weight : " << v.weight;
    outs << "\n\tTotal Edge weight : " << v.total_edge_weight;
    return outs;
}

// It would read in something like this: 
// Name : Connections ; Cache
// CSCI-60 : CSCI-40! ; CSCI-40 MATH-75
// What I actually want
// 60C : 40 ; 40 75M
// When I think about it
// 60C : 40 ; 75M 
// TODO: 
// Which needs to generate a symbol table for shorter strings 

// This is for the cache file.. 
std::istream& operator>>(std::istream &ins, Vertex &v) {
    std::string retval = readline(ins);
    std::istringstream sts(retval);
    sts >> v.name;
    while(sts) {
        std::string temp;
        sts >> temp;
        if(!sts) break;
        // This is for CoReqs 
        if(temp.back() == '!') temp.pop_back();
        if(temp == ":") continue;
        else v.connections.push_back(temp);
    }
    return ins; 
}
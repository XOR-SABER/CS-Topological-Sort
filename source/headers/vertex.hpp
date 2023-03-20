#ifndef _ALEX_VERTEX_HPP
#define _ALEX_VERTEX_HPP

// Standard Headers:
#include <vector>
#include <string>
#include <iostream>

//Custom headers
#include "serialize.hpp"

class Vertex : public Serializable{
    public:
    //Name of the class
    Vertex() = delete; 
    Vertex(const std::string &new_name) : name(new_name) {}
    std::string name;
    std::vector<std::string> connections;
    std::vector<std::string> topo_cache; 
    std::string operator[](size_t);
    //How common its a preq
    size_t weight = 0;
    size_t total_edge_weight;
    std::string Serialize();
    constexpr std::ifstream Deserialize() const; 
    friend std::ostream &operator<<(std::ostream &outs, const Vertex &v);
};

#endif
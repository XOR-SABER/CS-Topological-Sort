#ifndef _ALEX_VERTEX_HPP
#define _ALEX_VERTEX_HPP

// Standard Headers:
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//Custom headers
#include "serialize.hpp"

struct Vertex : public Serializable{
    Vertex() = default;
    Vertex(const std::string &line);
    Vertex(const Vertex& v);
    std::string name;
    std::vector<std::string> connections;
    std::vector<std::string> topo_cache; 
    //How common its a preq
    size_t weight = 0;
    size_t total_edge_weight;
    void build_by_string(const std::string &); 
    // OK, this is the first time I actually used a pure virtual function to do serialization..
    //Returns a formatted string, with all the info nessecary to remake the class 
    std::string Serialize() override;
    //It's a input overload function, that does the Deserialization in a seperate function
    std::istream &Deserialize(std::istream &) override;
    //Operator overloads.. 
    std::string operator[](size_t);
    friend std::ostream &operator<<(std::ostream &, const Vertex &);
    friend std::istream& operator>>(std::istream &, Vertex &);
};

#endif
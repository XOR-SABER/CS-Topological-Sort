#ifndef _ALEX_VERTEX_HPP
#define _ALEX_VERTEX_HPP

// Standard Headers:
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//Custom headers
#include "read.h"

class Vertex {
protected:
    //Course_ID 
    std::string name;
    // Which Courses are a immediate, prereqs
    std::vector<std::string> connections;
    //We made a cache for after topologically sorting
    std::vector<std::string> topo_cache; 
    //How common its a preq
    size_t weight = 0;
    size_t total_edge_weight = 0;
public:
    Vertex() = default;
    Vertex(const Vertex&);
    Vertex(const std::string&);
    // I got Getters and setters now.. 
    void add_connection(const std::string&);
    bool check_cache() const { return topo_cache.empty();}
    void update_cache(const std::vector<std::string>&);
    std::vector<std::string> &get_topo_cache(); 
    std::vector<std::string> &get_connnections();
    // Operator Overloads: 
    void operator++();
    std::string &operator[](const size_t&);
    friend std::ostream &operator<<(std::ostream&, const Vertex&);
    friend std::istream& operator>>(std::istream&, Vertex&);
};



#endif
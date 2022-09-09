#ifndef _ALEX_VERTEX_HPP
#define _ALEX_VERTEX_HPP
#include <vector>
#include <string>
#include <iostream>

struct Vertex{
    //Name of the class
    std::string name;
    std::vector<std::string> connections;
    std::string operator[](size_t);
    //How common its a preq
    size_t weight = 0;
    size_t total_edge_weight;
    friend std::ostream &operator<<(std::ostream &outs, const Vertex &v);
};

#endif
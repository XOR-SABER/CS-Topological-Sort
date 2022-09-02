#ifndef _ALEX_GRAPH_HPP
#define _ALEX_GRAPH_HPP
#include <string>
#include <vector>

struct Edge{
    //Name of the class
    std::string name;
    //How many times it hows up as a prereq
    unsigned int importance = 0;
};

struct Vertex{
    //Name of the class
    std::string name;

    //We using bitfields!
    std::vector<Edge> connections;
};

#endif
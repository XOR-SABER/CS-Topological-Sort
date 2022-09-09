#include "headers/vertex.hpp"

//Makes my life a little easier
std::string Vertex::operator[](size_t index) {
    return connections[index];
}

//Print out each vertex
std::ostream &operator<<(std::ostream &outs, const Vertex &v) {
    outs << "Class: " << v.name << "\n\tPrereqs: ";
    if(v.connections.empty()) outs << "None ";
    else for(const std::string &s : v.connections) outs << s << " ";
    outs << "\n\tPrereq weight : " << v.weight;
    return outs;
}


#include "headers/vertex.hpp"

//Makes my life a little easier
std::string Vertex::operator[](size_t index) {
    return connections.at(index);
}

//Print out each vertex
std::ostream &operator<<(std::ostream &outs, const Vertex &v) {
    outs << "Class: " << v.name << "\n\tPrereqs: ";
    if(v.connections.empty()) outs << "None ";
    else for(const std::string &s : v.connections) outs << s << " ";
    outs << "\n\tPrereq weight : " << v.weight;
    return outs;
}

std::string Vertex::Serialize() {
    std::string retval; 
    retval += name + " : ";
    if(connections.empty()); 
    else for(const std::string &s : connections) retval += s + " ";
    return retval;
}

void Vertex::Deserialize(std::istream &input) {
    std::string input_buffer; 
    input >> input_buffer;
    std::cout << input_buffer << std::endl;
    //Bingo, he has a nameo 
    this->name = input_buffer;
    std::cout << *this << std::endl;
    std::getline(input, input_buffer);
    // FIX:
    // TODO:
    std::stringstream sts(input_buffer);
    std::cout << *this << std::endl;
}

Vertex::Vertex(const Vertex& v) {
    this->name = v.name;
    this->connections = v.connections;
    this->total_edge_weight = v.total_edge_weight;
    this->weight = v.weight; 
    this->topo_cache = v.topo_cache;
}
#include "headers/vertex.hpp"

//This should be gone by the time, I give graph a serialize function.. 
Vertex::Vertex(const std::string &line) {
    build_by_string(line);
}

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

std::istream& operator>>(std::istream &in, Vertex &v) {
    return v.Deserialize(in);
}

std::string Vertex::Serialize() {
    std::string retval; 
    retval += name + " : ";
    if(connections.empty()); 
    else for(const std::string &s : connections) retval += s + " ";
    return retval;
}

std::istream &Vertex::Deserialize(std::istream &input) {
    input.ignore();
    std::string input_buffer; 
    std::getline(input, input_buffer);
    build_by_string(input_buffer);
    return input;
}

void Vertex::build_by_string(const std::string &input_string) {
    std::istringstream sts(input_string);
    sts >> this->name;
    while(sts) {
        std::string temp;
        sts >> temp;
        if(!sts) break;
        // This is for CoReqs 
        if(temp.back() == '!') temp.pop_back();
        if(temp == ":") continue;
        else this->connections.push_back(temp);
    }
}

Vertex::Vertex(const Vertex& v) {
    this->name = v.name;
    this->connections = v.connections;
    this->total_edge_weight = v.total_edge_weight;
    this->weight = v.weight; 
    this->topo_cache = v.topo_cache;
}
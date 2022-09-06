#ifndef _ALEX_GRAPH_HPP
#define _ALEX_GRAPH_HPP
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "read.h"

//Just a neat macro set up for file not
#define FILE_NOT_FOUND std::cout << "File not found, exiting program.. \n", exit(0)
#define COURSE_NOT_FOUND std::cout << "Course not found.. \n"

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

class Graph{
    private:
        std::unordered_map<std::string, size_t> hash;
        std::vector<Vertex> list;
        std::vector<std::string> common_prereqs(std::string a, std::string b);
        void find_prereqs(std::string&, std::string, std::unordered_set<std::string>&);     
        void find_prereqs(std::vector<std::string>&, std::string, std::unordered_set<std::string>&);
        void find_intersect(std::vector<std::string>&, std::string, std::unordered_set<std::string>&);   
    public:
        Graph() = delete;
        Graph(std::string);
        void build_graph(std::string);
        bool hash_query(std::string);
        size_t hash_get(std::string);
        std::string print_all_prereqs(std::string);
        std::vector<std::string> list_all_prereqs(std::string);
        std::string print_common_prereqs(std::string, std::string);
        std::vector<std::string> list_common_prereqs(std::string, std::string);
        Vertex operator[](size_t);
        friend std::ostream &operator<<(std::ostream&, const Graph&);
        
};
#endif
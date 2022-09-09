#ifndef _ALEX_GRAPH_HPP
#define _ALEX_GRAPH_HPP
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stack>

#include "vertex.hpp"
#include "read.h"

//Just a neat macro set up for file not
#define FILE_NOT_FOUND std::cout << "File not found, exiting program.. \n", exit(0)
#define COURSE_NOT_FOUND std::cout << "Course not found.. \n"

class Graph{
    private:
        std::vector<Vertex> list;
        std::unordered_map<std::string, size_t> hash;
    protected:
        void DFS(std::string, std::unordered_set<std::string>&);
        std::vector<std::string> common_prereqs(std::string, std::string);
        void DFS_intersect(std::string, std::unordered_set<std::string> &);
        void find_prereqs(std::string&, std::string, std::unordered_set<std::string>&);     
        void find_prereqs(std::vector<std::string>&, std::string, std::unordered_set<std::string>&);
        void intersect_traversal(std::vector<std::string>&, std::string, std::unordered_set<std::string>&, std::unordered_set<std::string>&);
    public:
        Graph() = delete;
        Graph(std::string);
        void print_DFS(std::string);
        void print_BFS(std::string);
        void build_graph(std::string);
        bool hash_query(std::string);
        size_t hash_get(std::string);
        //Am probably gonna make helper functions for format string and vector
        std::string print_all_prereqs(std::string);
        std::string print_find_classes(std::vector<std::string>);
        std::string print_common_prereqs(std::string, std::string);
        std::vector<std::string> list_all_prereqs(std::string);
        std::vector<std::string> list_find_classes(std::vector<std::string>);
        std::vector<std::string> list_common_prereqs(std::string, std::string);
        Vertex operator[](size_t);
        friend std::ostream &operator<<(std::ostream&, const Graph&);
};
#endif
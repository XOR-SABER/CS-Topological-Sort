#ifndef _ALEX_GRAPH_HPP
#define _ALEX_GRAPH_HPP

// Standard headers: 
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stack>


// Custom Headers:
#include "vertex.hpp"
#include "read.h"

class Graph{
    private:
        std::vector<Vertex> list;
        std::unordered_map<std::string, size_t> hash;
    protected:
        void DFS(std::string, std::unordered_set<std::string>&);
        bool check_prereqs(std::unordered_set<std::string>&,size_t);
        std::vector<std::string> find_classes(const std::vector<std::string> &);
        std::vector<std::string> common_prereqs(std::string, std::string);
        void DFS_intersect(std::string, std::unordered_set<std::string> &);
        void find_prereqs(std::string&, const std::string &, std::unordered_set<std::string>&);     
        void find_prereqs(std::vector<std::string>&, const std::string &, std::unordered_set<std::string>&);
        void intersect_traversal(std::vector<std::string>&, std::string, std::unordered_set<std::string>&, std::unordered_set<std::string>&);
    public:
        Graph() = delete;
        Graph(const std::string &);
        void print_DFS(const std::string &);
        void print_BFS(const std::string &);
        void build_graph(const std::string &);
        bool hash_query(const std::string &);
        size_t hash_get(const std::string &);
        //Am probably gonna make helper functions for format string and vector
        std::string print_all_prereqs(const std::string &);
        std::string print_common_prereqs(const std::string &, const std::string &);
        std::vector<std::string> list_all_prereqs(const std::string &);
        std::vector<std::string> list_common_prereqs(const std::string &, const std::string &);
        friend std::ostream &operator<<(std::ostream&, const Graph&);
};

void screen_wipe();
void menu();

#endif
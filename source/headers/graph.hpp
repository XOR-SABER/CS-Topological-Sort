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
#include <queue>

// Custom Headers:
#include "vertex.hpp"
#include "read.h"

class Graph{
    private:
        std::vector<Vertex> list; //This is very simular to the Markov.. 
        std::unordered_map<std::string, size_t> hash; //This map, is used to speed up query times, to a O(1)
    protected:
        // Ok, I know what I was doing here, and yeah it was kinda smart. 
        // Using private methods to do the actual methods, and public being a accessible alliases. 

        // DFS recusrive function.. 
        void DFS(std::string, std::unordered_set<std::string>&); 
        // We call this in list_all_prereqs
        void find_prereqs(std::vector<std::string>&, const std::string &, std::unordered_set<std::string>&);
    public:
        Graph() = delete;
        Graph(const std::string &);
        // Prints graph in DFS
        void print_DFS(const std::string &);
        // Prints graph in BFS
        void print_BFS(const std::string &);
        // A Function that calls the constructor.. 
        void build_graph(const std::string &);
        // Prints all prereqs
        std::string print_all_prereqs(const std::string &);
        // This is the topological sorting.. 
        std::vector<std::string> list_all_prereqs(const std::string &);
        // Overload to print out the graph
        friend std::ostream &operator<<(std::ostream&, const Graph&);
};

void screen_wipe();
void menu();

#endif
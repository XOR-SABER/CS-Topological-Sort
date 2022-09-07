#include "headers/Graph.hpp"

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

//Interface for the graph
Vertex Graph::operator[](size_t index) {
    return list.at(index);
}

std::ostream &operator<<(std::ostream &outs, const Graph &g) {
    for(const Vertex &v : g.list) outs << v << std::endl;
    return outs;
}

Graph::Graph(std::string filename) {
    build_graph(filename);
}

//Builds and adds to a graph
void Graph::build_graph(std::string filename) {
    //Build the graph
    std::ifstream file(filename);
    if(!file) 
        FILE_NOT_FOUND;

    //File processing:
    //std::cout << "Processing files!" << std::endl;
    size_t index = 0;
    while(true) {
        //This loop is for lines
        bool is_preq = false;
        std::string current_line = readline(file);
        std::string current_class;
        if(!file) break;
        if(!current_line.size()) continue;
        std::stringstream sts(current_line);
        while (true) {
            size_t word_index;
            bool is_coreq = false;
            std::string current_word = read(sts);
            if(!current_word.size() || !sts) break;
            if(current_word == ":") {
                is_preq = true;
                continue;
            }
            if(current_word.back() == '!') {
                current_word.pop_back();
                is_coreq = true;
            }
            //std::cout << current_word << ": current index: " << index << ((is_preq) ? " is a preq" : " its a course") << std::endl;
            if(!is_preq) {
                //Skips if the class is repeated it's not a prereq
                if(hash.count(current_word)) {
                   break; 
                }
                //std::cout << "We found a new course" << std::endl;
                Vertex v = {current_word};
                list.push_back(v);
                hash[current_word] = index;
                index++;
                current_class = current_word;
            } else {
                //Check if the word exists
                if(hash.count(current_word)) {
                    word_index = hash[current_word];
                    list[word_index].weight++;
                }
                //std::cout << word_index << std::endl;
                word_index = hash[current_class];
                list[word_index].connections.push_back(current_word);
            }
        }
    }
}
//Interface for doing a query on a hash table
bool Graph::hash_query(std::string course) {
    if(hash.count(course)) {
        return true;
    }
    COURSE_NOT_FOUND;
    return false;
}

//Interface for the hash function that gets the index
size_t Graph::hash_get(std::string course) {
    if(hash_query(course)) return hash[course];
    return size_t(-1);
}

//Returns a formated string with all the prereqs
std::string Graph::print_all_prereqs(std::string course) {
    std::unordered_set<std::string> check; 
    std::string retval;
    if(!hash.count(course)) {
        COURSE_NOT_FOUND; 
        return retval;
    }
    retval += "All prereqs for ";
    retval += course;
    retval += ": ";
    //Recursion?
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) {
        find_prereqs(retval, s, check);
    }
    return retval;
}
//Returns a vector with all the prereqs
void Graph::find_prereqs(std::string &retval, std::string course, std::unordered_set<std::string> &check) {
    //if this in the hash
    if(check.count(course)) {
        return;
    }
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) {
        find_prereqs(retval, s, check);
    }
    if(!check.empty()) retval += " -> ";
    check.insert(course);
    retval += course;
}
//Helper function to list_all_prereqs
std::vector<std::string> Graph::list_all_prereqs(std::string course) {
    std::unordered_set<std::string> check; 
    std::vector<std::string> retval;
    if(!hash.count(course)) {
        COURSE_NOT_FOUND; 
        return retval;
    }
    //Recursion?
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) find_prereqs(retval, s, check);
    return retval;
}
//Helper function to list_all_prereqs
void Graph::find_prereqs(std::vector<std::string> &retval, std::string course, std::unordered_set<std::string> &check) {
    //if this in the hash
    if(check.count(course)) {
        return;
    }
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) {
        find_prereqs(retval, s, check);
    }
    check.insert(course);
    retval.push_back(course);
}
//Step One: Create a list of all the preqreqs in the class A
//Step Two: Go through class B and check for overlap then return the overlap
//Step Three: This should be faster???  
std::vector<std::string> Graph::common_prereqs(std::string a, std::string b) {
    std::unordered_set<std::string> check;
    std::unordered_set<std::string> check1;
    std::vector<std::string> result;
    //Check if A and B exists
    if(!hash.count(a)) return result;
    if(!hash.count(b)) return result;
    //Insert them into a the hash browns
    check.insert(a);
    check.insert(b);
    //We are doing a DFS at A
    //Optimization
    //Some classes just have another class in the same series as a preq just list the prereqs of that class
    if(list[hash[a]].connections.at(0) == b) return list_all_prereqs(b);
    if(list[hash[b]].connections.at(0) == a) return list_all_prereqs(a);
    for(std::string s : list[hash[a]].connections) DFS_intersect(s, check);
    for(std::string s : list[hash[b]].connections) intersect_traversal(result, s, check, check1);
    //then checking by doing a DFS at B for overlap
    return result;
}

void Graph::DFS_intersect(std::string course, std::unordered_set<std::string> &check) {
    //std::cout << course << std::endl;
    //Did we vist it?
    if(check.count(course)) return;
    check.insert(course);
    size_t index = hash[course];
    for(std::string s : list.at(index).connections) DFS_intersect(s, check);
    return;
}

void Graph::intersect_traversal(std::vector<std::string> &retval, std::string course, std::unordered_set<std::string> &check, std::unordered_set<std::string> &check1) {
    //Have we seen in our current hash?
    if(check1.count(course)) return;
    size_t index = hash[course];
    for(std::string s : list.at(index).connections) intersect_traversal(retval, s, check, check1);
    //Have we not seen it in our old hash? 
    if(!check.count(course)) return;
    //We seen it
    check1.insert(course);
    retval.push_back(course);
    return;
}

std::string Graph::print_common_prereqs(std::string a, std::string b) {
    std::vector<std::string> result = common_prereqs(a,b);
    std::string retval;
    retval += "Common prereqs between ";
    retval = retval + (a + " and " + b);
    retval += " :";

    if(result.empty()) return (retval + " None");

    for(std::string s : result) {
        retval += " ";
        retval += s;
    }

    return retval;
}

std::vector<std::string> Graph::list_common_prereqs(std::string a, std::string b) {
    return common_prereqs(a,b);
}

void Graph::print_BFS(std::string course) {
    if(!hash.count(course)) {
        COURSE_NOT_FOUND;
        return;
    }
    std::unordered_set<std::string> check; 
    std::stack<std::string> queue; 
    check.insert(course);
    queue.push(course);
    
    while (!queue.empty()) {
        std::string current_course = queue.top();
        queue.pop();
        std::cout << current_course << " ";
        for(std::string s : list.at(hash[current_course]).connections) {
            if(!check.count(s)) {
                check.insert(s);
                queue.push(s);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::print_DFS(std::string course) {
    if(!hash.count(course)) {
        COURSE_NOT_FOUND;
        return;
    }
    std::unordered_set<std::string> check; 
    std::cout << course << " ";
    for(std::string s : list.at(hash[course]).connections) {
        DFS(s, check);
    }
    std::cout << std::endl;
}
void Graph::DFS(std::string course, std::unordered_set<std::string> &check) {
    //Did we vist it?
    if(check.count(course)) return;

    std::cout << course << " ";
    check.insert(course);
    size_t index = hash[course];
    for(std::string s : list.at(index).connections) DFS(s, check);
    return;
}
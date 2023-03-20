#include "headers/Graph.hpp"

//Just a neat macro set up for file not
#define FILE_NOT_FOUND std::cout << "File not found, exiting program.. \n", exit(0)
#define COURSE_NOT_FOUND std::cout << "Course not found.. \n"

//This is for screen clearing, since the command is different on diffetent platforms.
void screen_wipe(){
	#if defined __WIN64__ || __WIN32__
	system("cls");
	#endif                                                                          
	
	#if defined __linux__
	if(system("clear")){}
	#endif

	#if defined __MACH__1 || __APPLE__1
	system("clear");
	#endif     
}

// Prints the graph
std::ostream &operator<<(std::ostream &outs, const Graph &g) {
    // This depends on the Vertex operator overload
    for(const Vertex &v : g.list) outs << v << std::endl;
    return outs;
}

//This abstracts out the format function, using templates. 
template<typename Container, 
         typename = std::enable_if_t<std::is_same_v<typename Container::value_type, 
         std::string>>>
constexpr void format_str(const Container& c, std::string &retval) {
    if(c.empty()) return;
    for(const std::string &s : c) {
        retval += " ";
        retval += s;
    }
}

//This abstracts out the format function, using templates. 
// if the vector is {"CSCI-1", "CSCI-40", "CSCI-41"} returns "CSCI-1 -> CSCI-40 -> CSCI-41"
template<typename Container, 
         typename = std::enable_if_t<std::is_same_v<typename Container::value_type, 
         std::string>>>
constexpr void format_str_arrow(const Container& c, std::string &retval) {
    if(c.empty()) return;
    for(const std::string &s : c) {
        retval += s;
        retval += " -> ";
    }
}

// Non-default Constructor / Main menu.. 
Graph::Graph(const std::string &filename) {
    // Constructor:
    build_graph(filename);
    #define PROMPT "Please input a course: "

    // Main menu: 
    bool in_menu = true;
		while(in_menu) {
			std::string course; 
			std::cout << "\n1: Print out the graph\n";
            std::cout << "2: Search for a class\n";
            std::cout << "3: Print all prereqs topologically for a class\n";
            std::cout << "4: Common prereqs between classes\n";
            std::cout << "5: Print a class in DFS\n";
            std::cout << "6: Print a class in BFS\n";
            std::cout << "7: Exit program\n";
            std::cout << "Please enter a number: ";
			int input = read<int>();
			switch (input)
			{
			case 1:
				screen_wipe();
				std::cout << *this << std::endl;
				break;
			case 2:
				course = read<std::string>(PROMPT); 
				screen_wipe();
                if(hash.count(course)) {
                    std::cout << list.at(hash.at(course)) << std::endl ;
                } else COURSE_NOT_FOUND;
				break;
			case 3:
				course = read<std::string>(PROMPT); 
				screen_wipe();
				if(hash.count(course)) {
					std::cout << this->print_all_prereqs(course) << std::endl;
				} else COURSE_NOT_FOUND;
				break;
			case 4:
                std::cout << this->list[23].Serialize() << std::endl;
                std::cout << "TODO: \n";
				break;
			case 5:
				course = read<std::string>(PROMPT); 
				screen_wipe();
				std::cout << std::endl;
				this->print_DFS(course);
				break;
			case 6:
				course = read<std::string>(PROMPT); 
				screen_wipe();
				std::cout << std::endl;
				this->print_BFS(course);
				break;
			case 7:
				in_menu = false;
				break;
			default:
				break;
			}
		}
}

//Builds and adds to a graph
void Graph::build_graph(const std::string &filename) {
    //Build the graph
    std::ifstream file(filename);
    if(!file) FILE_NOT_FOUND;

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
            if(!is_preq) {
                //Skips if the class is repeated it's not a prereq
                if(hash.count(current_word)) break; 

                Vertex v(current_word);
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

                word_index = hash[current_class];
                list[word_index].connections.push_back(current_word);
            }
        }
    }
}

//These don't need to be changed 
//Prints the node and its connections in Depth First Search
void Graph::print_DFS(const std::string &course) {
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

//Recursive function that is called
void Graph::DFS(std::string course, std::unordered_set<std::string> &check) {
    //Did we vist it?
    if(check.count(course)) return;

    std::cout << course << " ";
    check.insert(course);
    size_t index = hash[course];
    for(std::string s : list.at(index).connections) DFS(s, check);
    return;
}

// Returns a formated string with all the prereqs
std::string Graph::print_all_prereqs(const std::string &course) {
    std::vector<std::string> list = list_all_prereqs(course);
    std::string retval;
    format_str_arrow(list, retval);
    retval += course;
    return retval;
}

// Helper function to list_all_prereqs
std::vector<std::string> Graph::list_all_prereqs(const std::string &course) {
    // Check get vertex to check if this precached.. 
    Vertex &curr_vertex = list.at(hash.at(course));
    if(!curr_vertex.topo_cache.empty()) return curr_vertex.topo_cache;

    // We start the algo.. 
    std::unordered_set<std::string> check; 
    std::vector<std::string> retval;
    if(!hash.count(course)) {
        COURSE_NOT_FOUND; 
        return retval;
    }
    // Recursion is useful sometimes. 
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) find_prereqs(retval, s, check);
    curr_vertex.topo_cache = retval;
    return retval;
}

//Helper function to list_all_prereqs
void Graph::find_prereqs(std::vector<std::string> &retval, const std::string & course, std::unordered_set<std::string> &check) {
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


// This is a BFS using a Stack as a data structure..
// Prints the node and its connections in Breath First Search
void Graph::print_BFS(const std::string &course) {
    if(!hash.count(course)) {
        COURSE_NOT_FOUND;
        return;
    }
    std::unordered_set<std::string> check;
    //Stacks are underrated..  
    std::stack<std::string> stack; 
    check.insert(course);
    stack.push(course);
    
    while (!stack.empty()) {
        std::string current_course = stack.top();
        stack.pop();
        std::cout << current_course << " ";
        for(std::string s : list.at(hash[current_course]).connections) {
            if(!check.count(s)) {
                check.insert(s);
                stack.push(s);
            }
        }
    }
    std::cout << std::endl;
}
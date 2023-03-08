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

// Non-default Constructor / Main menu.. 
Graph::Graph(const std::string &filename) {
    // Constructor:
    build_graph(filename);

    // Main menu: 
    bool in_menu = true;
		while(in_menu) {
			std::string course, course1; 
			std::cout << "1: Print out the graph\n";
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
				course = read<std::string>(); 
				screen_wipe();
				if(this->hash_query(course)) {
					std::cout << list.at(hash_get(course)) << std::endl;
					std::cout << std::endl;
				} else {
					COURSE_NOT_FOUND;
				}
				break;
			case 3:
				course = read<std::string>(); 
				screen_wipe();
				if(this->hash_query(course)) {
					std::cout << this->print_all_prereqs(course) << std::endl;
					std::cout << std::endl;
				} else {
					COURSE_NOT_FOUND;
				}
				break;
			case 4:
				course = read<std::string>(); 
				course1 = read<std::string>(); 
				screen_wipe();
				if(!this->hash_query(course)) {
					COURSE_NOT_FOUND;
					break;
				}
				if(!this->hash_query(course1)) {
					COURSE_NOT_FOUND;
					break;
				}
				std::cout << this->print_common_prereqs(course,course1) << std::endl;
				std::cout << std::endl;
				break;
			case 5:
				course = read<std::string>(); 
				screen_wipe();
				std::cout << std::endl;
				this->print_DFS(course);
				std::cout << std::endl;
				break;
			case 6:
				course = read<std::string>(); 
				screen_wipe();
				std::cout << std::endl;
				this->print_BFS(course);
				std::cout << std::endl;
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

                word_index = hash[current_class];
                list[word_index].connections.push_back(current_word);
            }
        }
    }
}
// Interface for doing a query on a hash table
bool Graph::hash_query(const std::string &course) {
    if(hash.count(course)) {
        return true;
    }
    COURSE_NOT_FOUND;
    return false;
}
// Interface for the hash function that gets the index
size_t Graph::hash_get(const std::string &course) {
    if(hash_query(course)) return hash[course];
    return size_t(-1);
}
// Returns a formated string with all the prereqs
std::string Graph::print_all_prereqs(const std::string &course) {
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
// Returns a vector with all the prereqs
void Graph::find_prereqs(std::string &retval, const std::string &course, std::unordered_set<std::string> &check) {
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
// Helper function to list_all_prereqs
std::vector<std::string> Graph::list_all_prereqs(const std::string &course) {
    std::unordered_set<std::string> check; 
    std::vector<std::string> retval;
    if(!hash.count(course)) {
        COURSE_NOT_FOUND; 
        return retval;
    }
    // Recursion is useful sometimes. 
    size_t current_index = hash[course];
    for(std::string s : list[current_index].connections) find_prereqs(retval, s, check);
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
//Step One: Create a list of all the preqreqs in the class A
//Step Two: Go through class B and check for overlap then return the overlap
//Step Three: This should be faster???  I Belive it. But a bitmore wastefull of memory

// TODO: just do this at graph build time..  HOLY FUCK SOME OF MY CODE IS BAD. 
// This is horrible for memory, this just bad. 
// I would imagine pre-computing the prereqs would make this step faster. 
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
    //0(N) case
    if(list[hash[a]].connections.at(0) == b) return list_all_prereqs(b);
    if(list[hash[b]].connections.at(0) == a) return list_all_prereqs(a);
    //0((V*E))
    for(std::string s : list[hash[a]].connections) DFS_intersect(s, check);
    for(std::string s : list[hash[b]].connections) intersect_traversal(result, s, check, check1);
    //then checking by doing a DFS at B for overlap
    return result;
}
//Recursive function
void Graph::DFS_intersect(std::string course, std::unordered_set<std::string> &check) {
    //Did we vist it?
    if(check.count(course)) return;
    check.insert(course);
    size_t index = hash[course];
    for(std::string s : list.at(index).connections) DFS_intersect(s, check);
    return;
}
//Recursive function that returns a set that is a intersection of prereqs while traversing
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
//Helper function for Common_prereqs that creates and returns a format string
std::string Graph::print_common_prereqs(const std::string &a, const std::string &b) {
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
//Helper function for Common_prereqs that returns a vector of strings
std::vector<std::string> Graph::list_common_prereqs(const std::string &a, const std::string &b) {
    return common_prereqs(a,b);
}
//Prints the node and its connections in Breath First Search
void Graph::print_BFS(const std::string &course) {
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

// ? I forgot what this does.. 
bool Graph::check_prereqs(std::unordered_set<std::string> &check, size_t current_index) {
    for(std::string s : list[current_index].connections) {
        if(!check.count(s)) return false;
    }
    return true;
}


std::vector<std::string> Graph::find_classes(const std::vector<std::string> &courses) {
    std::unordered_set<std::string> courses_taken;
    std::vector<std::string> retval; 
    //Insert them into the hash
    for(std::string s : courses) courses_taken.insert(s);
    for (size_t i = 0; i < list.size(); i++) {
        if(courses_taken.count(list[i].name)) continue;
        //The Course hasn't been taken
        if(!courses_taken.count(list[i].connections[0])) {
            //The Prereq has been taken
            //Call the recursive function
            if(check_prereqs(courses_taken, i)) retval.push_back(list[i].name);
        }
    }
    return retval;
}


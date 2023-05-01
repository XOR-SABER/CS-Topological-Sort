#include "headers/course_catalog.hpp"

//Just a neat macro set up for file not
#define FILE_NOT_FOUND std::cout << "File not found, exiting program.. \n", exit(0)
#define COURSE_NOT_FOUND std::cout << "Course not found.. \n"

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

/*
It should look like this: 

CSCI-40 : Introduction to Programming and Problem Solving
Introduction to problem solving, algorithm development, procedural and data abstraction; program design, coding, debugging, testing and documentation; a high-level programming language. (3 lecture, 2 lab hours)
Prerequisites: Math 75
Units: 4

*/

Catalog::Catalog(const std::string &filename) {
    //Build the graph
    std::ifstream file(filename);
    if(!file) FILE_NOT_FOUND;

    // O(n) blehh.. 
    while(true) {
        //This we reached the end of the file.. 
        if(!file) break;
        std::string current_line = readline(file);
        if(current_line.empty()) break;
        std::stringstream sts(current_line);
        std::vector<std::string> build_vec(4);
        std::vector<std::string> preqs; 
        uint16_t units; 
        // Just a temporary buffers.. 
        std::string temp, temp2;
        sts >> build_vec[0];
        while(sts) {
            temp = "";
            sts >> temp;
            build_vec[1] += temp + " ";
        }
        // Get the next line.. 
        sts.clear(); 
        current_line = readline(file);
        sts.str(current_line);
        sts >> temp;
        // Prereqs done..
        while(sts) {
            temp = "";
            sts >> temp;
            if(temp.back() == ',') temp.pop_back();
            preqs.push_back(temp);
        }
        // Get the next line.. 
        build_vec[2] = readline(file);
        current_line = readline(file);
        sts.clear(); 
        sts.str(current_line);
        sts >> temp;
        temp = "";
        sts >> temp;
        try{
            units = std::stoi(temp);
        } catch(std::invalid_argument) {
            units = 0;
        }
        // Then build the course class.. 
        Course new_course(build_vec[0], build_vec[1],build_vec[2], units);
        for (const std::string& str : preqs) {
            std::optional<Course> other = get(str);
            if(other.has_value()) {
                Course &c = other.value();
                new_course.add_connection(str);
            } else continue;
        }
        // Add back into our vector and hash map..
        course_list.push_back(new_course);
        hash_map.insert({new_course.course_id, course_list.size() - 1});
    }
    menu();
}

std::ostream &operator<<(std::ostream& outs, const Catalog& cat) {
    size_t index = 0;
    for(const Course& c : cat.course_list) {
        outs << "Index: " << index << std::endl;
        index++;
        outs << c << std::endl;
        Vertex &v = const_cast<Course&>(c);
        outs << v << std::endl;
    }
    return outs;
}

// Get's a course from the hash table, and returns a optional refrence.. 
std::optional<Course> Catalog::get(const std::string& c_id) const {
    // if no course found return a empty optional.. 
    if(!check(c_id)) return std::optional<Course>();
    return std::optional<Course>(course_list[hash_map.at(c_id)]);
}
// Check if a course exists.. 
bool Catalog::check(const std::string& c_id) const {
    return hash_map.count(c_id);
}

void Catalog::menu() {
    do{
        std::cout << "1. Search up a look for a class\n";
        std::cout << "2. Print statstics on the graph\n";
        std::cout << "3. Topologically sort prereqs for class\n";
        std::cout << "4. Print out the graph\n";
        const int choice = read(": ");  
        if(choice == 1) {
            const std::string course_id = read("Please type in a Course ID: ");
            std::optional<Course> check = get(course_id);
            if(check.has_value()) std::cout << check.value() << std::endl;
            else COURSE_NOT_FOUND;
        } else if(choice == 2) {
            // TODO: 
            // Print the highest weight (The most common Prereq / Most important class in the series..)
            // Print the lowest weight (Least common Preqreq / The least impotant class in the series..)
            std::cout << "TODO: \n";
        } else if(choice == 3) {
            const std::string course_id = read("Please type in a Course ID: ");
            std::optional<Course> check = get(course_id);
            if(check.has_value()) std::cout << print_all_prereqs(course_id) << std::endl;
            else COURSE_NOT_FOUND;
        } else if(choice == 4) {
            std::cout << *this;
        } else break;
    } while(true);

    exit(EXIT_SUCCESS);
}

// Returns a formated string with all the prereqs
std::string Catalog::print_all_prereqs(const std::string &course) {
    std::vector<std::string> vec = list_all_prereqs(course);
    std::string retval;
    format_str_arrow(vec, retval);
    retval += course;
    return retval;
}

// Helper function to list_all_prereqs
std::vector<std::string> Catalog::list_all_prereqs(const std::string &course) {
    // Check get vertex to check if this precached.. 
    Course &curr_vertex = course_list.at(hash_map.at(course));
    if(!curr_vertex.check_cache()) return curr_vertex.get_topo_cache();
    // We start the algo.. 
    std::unordered_set<std::string> check; 
    std::vector<std::string> retval;
    // Recursion is useful sometimes. 
    size_t current_index = hash_map.at(course);
    for(std::string s : course_list.at(current_index).get_connnections()) find_prereqs(retval, s, check);
    curr_vertex.update_cache(retval);
    return retval;
}

//Helper function to list_all_prereqs
void Catalog::find_prereqs(std::vector<std::string> &retval, const std::string & course, std::unordered_set<std::string> &check) {
    //if this in the hash
    if(check.count(course)) return; 
    std::optional<Course> tmp = get(course);
    if(!tmp.has_value()) return;
    size_t current_index = hash_map.at(course);
    Course &current_course = course_list.at(current_index);
    for(std::string s : current_course.get_connnections()) find_prereqs(retval, s, check);
    check.insert(course);
    retval.push_back(course);
}



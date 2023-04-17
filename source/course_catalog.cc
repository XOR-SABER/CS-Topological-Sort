#include "headers/course_catalog.hpp"

//Just a neat macro set up for file not
#define FILE_NOT_FOUND std::cout << "File not found, exiting program.. \n", exit(0)
#define COURSE_NOT_FOUND std::cout << "Course not found.. \n"


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

    std::vector<std::string> temp(3);
    uint16_t unit_cost = 0;
    bool units = false, preqs = false, descript = false, c_id = false;
    while(true) {
        //This loop is for lines
        std::string current_line = readline(file);
        if(!file) break;
        if(!current_line.size()) continue;
        // this a temp fix.. 
        // if(course_constructed) {
        //     course_constructed = false;
        //     temp.clear();
        // }
        
        std::cout << current_line << std::endl;
        std::stringstream sts(current_line);
        std::deque<std::string> queue;
        std::string word; 
        // Okay lets turn it into a vector of strings
        while (sts >> word) queue.push_back(word);
        if(queue.empty()) continue;
        // Now we get the C_ID, Course name
        if(temp.empty()) {
            temp[0] = queue[0] + "-" + queue[1];
            queue.pop_front(), queue.pop_front();
            if(temp[0].back() == '.') temp[0].pop_back(); 
            // Combine the strings.. 
            for(const std::string& str : queue) temp[1] += str + " ";
        }
        else {
            // Now we look for the other stuff... 
            std::regex preq("prereq", std::regex_constants::icase);
            std::regex units("units", std::regex_constants::icase);
            std::smatch match;
            // This is the preqs
            if(std::regex_search(queue[0], match, preq)) {
                queue.pop_front();
                for(const std::string& str : queue) {
                    temp.push_back(str); 
                }
            } else if (std::regex_search(queue[0], match, units)) {
                unit_cost = std::stoi(queue[1]);
            } else {
                for(const std::string& str : queue) temp[2] += str + " ";
            }
        }
        

    }
}

// Overload for output stream... 
std::ostream &operator<<(std::ostream& outs, const Course& c) {
    outs << c.course_id << " : " << c.course_name << std::endl;
    outs << c.course_description << std::endl;
    outs << "Prerequisites : ";
    for(const std::string &s : c.connections) {
        outs << s << " ";
    }
    outs << std::endl;
    outs << "Units: " << c.units; 
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
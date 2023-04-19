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
        // I feel like if I formated the document correctly it wouldn't be like this.. 
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
            if(other.has_value()) ++other.value();
            new_course.add_connection(str);
        }
        // Add back into our vector and hash map..
        course_list.push_back(new_course);
        hash_map.insert({new_course.course_id, course_list.size() - 1});
    }
    for (const Course& c : course_list) std::cout << c << std::endl;
}

// Overload for output stream... 
std::ostream &operator<<(std::ostream& outs, const Course& c) {
    outs << c.course_id << " : " << c.course_name << std::endl;
    outs << c.course_description << std::endl;
    outs << "Prerequisites : ";
    for(const std::string &s : c.connections) {
        outs << s << " ";
    }
    if(c.connections.empty()) outs << "None";
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
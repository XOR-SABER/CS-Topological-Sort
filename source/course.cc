#include "headers/course.hpp"

// Overload for output stream... 
std::ostream &operator<<(std::ostream& outs, const Course& c) {
    outs << c.course_id << " : " << c.course_name << std::endl;
    outs <<  "\t" << c.course_description << std::endl;
    outs << "\t" << "Prerequisites : ";
    if(c.connections.empty()) outs << "None";
    else for(const std::string &s : c.connections) outs << s << " ";
    outs << std::endl;
    outs << "Units: " << c.units; 
    return outs;
}
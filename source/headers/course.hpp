#ifndef _ALEX_COURSE_HPP
#define _ALEX_COURSE_HPP

#include <string>

#include "vertex.hpp"

struct Course : public Vertex {
    const std::string course_id; 
    const std::string course_name;
    const std::string course_description;
    const std::string deparment; 
    const uint16_t units; 
    // No empty courses
    Course() = delete;
    // Non-default constructor.. 
    Course(const std::string &new_id, const std::string &new_name, 
           const std::string& cd, const uint16_t &u) 
           : course_id(new_id), course_description(cd), course_name(new_name),
           deparment(new_id), units(u), Vertex(new_id) {}
    void operator++();
    friend std::ostream &operator<<(std::ostream&, const Course&);
};

#endif
#ifndef _ALEX_COURSE_HPP
#define _ALEX_COURSE_HPP

#include "vertex.hpp"
#include "serialize.hpp"

// We might need this for later.. 

struct course : public Vertex {
    const std::string course_description;
    const std::string deparment; 
    const uint16_t units; 
    // No empty course classes
    course() = delete;
    // Non-default constructor.. 
    course(const std::string new_name, const std::string& cd, 
           const std::string dep, const uint16_t &u) 
           : course_description(cd), deparment(dep), units(u), Vertex(new_name) {}
};

#endif
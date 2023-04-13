#ifndef _ALEX_COURSE_CATALOG_HPP
#define _ALEX_COURSE_CATALOG_HPP

#include <unordered_map>
#include <optional>

#include "graph.hpp"


struct Course : public Formatable{
    const std::string course_id; 
    const std::string course_name;
    const std::string course_description;
    const std::string deparment; 
    const uint16_t units; 
    // No empty courses
    Course() = delete;
    // Non-default constructor.. 
    Course(const std::string &new_id, const std::string &new_name, 
           const std::string& cd, const std::string &dep, const uint16_t &u) 
           : course_id(new_id), course_description(cd), course_name(new_name),
           deparment(dep), units(u) {}
    // Create format string
    std::string Format_string() override;
};

class Catalog : public Formatable {
private:
    std::unordered_map<std::string, Course> hash_map;
public:
    // No default, since no file to build from.. 
    Catalog() = delete;
    Catalog(const std::string &filename);
    std::optional<Course> get(const std::string& c_id) const;
    constexpr bool check(const std::string& c_id) const;
    std::string Format_string() override;
};

#endif
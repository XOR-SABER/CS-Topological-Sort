#ifndef _ALEX_COURSE_CATALOG_HPP
#define _ALEX_COURSE_CATALOG_HPP

#include <unordered_map>
#include <unordered_set>
#include <optional>

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
    friend std::ostream &operator<<(std::ostream&, const Course&);
};

class Catalog {
private:
    // So a entry in the hash table would be {CSCI-40, 0} 
    // which 0 is the index which CSCI-40 is located in the course list
    std::unordered_map<std::string, size_t> hash_map;
    std::vector<Course> course_list; 
protected:
    // Ok, I know what I was doing here, and yeah it was kinda smart. 
    // Using private methods to do the actual methods, and public being a accessible alliases.
    // We call this in list_all_prereqs
    void find_prereqs(std::vector<std::string>&, const std::string &, std::unordered_set<std::string>&);
public:
    // No default, since no file to build from.. 
    Catalog() = delete;
    // Build catalog from file.. 
    Catalog(const std::string &filename);
    void menu();
    // Prints all prereqs
    std::string print_all_prereqs(const std::string &);
    // This is the topological sorting.. 
    std::vector<std::string> list_all_prereqs(const std::string &);
    // Get's a course from the hash table, and returns a optional refrence.. 
    std::optional<Course> get(const std::string& c_id) const;
    // Check if a course exists.. 
    bool check(const std::string& c_id) const;
    friend std::ostream &operator<<(std::ostream&, const Catalog&);
};

#endif
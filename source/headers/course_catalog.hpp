#ifndef _ALEX_COURSE_CATALOG_HPP
#define _ALEX_COURSE_CATALOG_HPP

#include <unordered_map>
#include <optional>

#include "vertex.hpp"
#include "serialize.hpp"

struct Course : public Serializable {
    const std::string course_id; 
    const std::string course_description;
    const std::string deparment; 
    const uint16_t units; 
    // No empty course classes
    Course() = delete;
    // Non-default constructor.. 
    Course(const std::string &new_id, const std::string &new_name, 
           const std::string& cd, const std::string &dep, const uint16_t &u) 
           : course_id(new_id), course_description(cd), deparment(dep), units(u) {}
    std::string Serialize() override;
    std::istream& Deserialize(std::istream& input) override;
};

class Catalog : public Serializable {
private:
    std::unordered_map<std::string, Course> hash_map;
public:
    // No default, since no file to build from.. 
    Catalog() = delete;
    Catalog(const std::string &filename);
    std::string Serialize() override;
    std::istream& Deserialize(std::istream& input) override;
    std::optional<Course> get(const std::string& c_id) const;
};

#endif
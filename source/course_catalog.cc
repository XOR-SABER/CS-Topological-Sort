#include "headers/course_catalog.hpp"

Catalog::Catalog(const std::string &filename) {

}

std::optional<Course> Catalog::get(const std::string& c_id) const {

}

constexpr bool Catalog::check(const std::string& c_id) const {

}

std::string Catalog::Format_string() {

}


std::string Course::Format_string() {
    std::string retval; 
    retval += course_id + " : " + course_name + "\n";
    retval += course_description;
}
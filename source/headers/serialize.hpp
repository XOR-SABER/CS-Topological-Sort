#ifndef _ALEX_SERIALIZE_HPP
#define _ALEX_SERIALIZE_HPP

//Standard Headers
#include <string>

// This has to be the first time, I used a interface class.. 
struct Serializable { 
    // Generally Speaking, Serialize returns a format string that the data can be recreated from
    virtual std::string Serialize() = 0; 
    // Meanwhile, Deserailize is used for getting a input and turning it into a object 
    virtual std::istream& Deserialize(std::istream& input) = 0; 
};

#endif
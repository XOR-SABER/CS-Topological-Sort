#ifndef _ALEX_SERIALIZE_HPP
#define _ALEX_SERIALIZE_HPP

//Standard Headers
#include <string>

// This has to be the first time, I used a pure virual function.. 
// I might use this.. 
struct Serializable { 
    constexpr virtual std::string Serialize() const = 0; 
};

#endif
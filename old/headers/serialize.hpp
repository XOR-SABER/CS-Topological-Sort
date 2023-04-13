#ifndef _ALEX_SERIALIZE_HPP
#define _ALEX_SERIALIZE_HPP
/*
Serialize.hpp: 
    Purpose: Virtual interfaces to make and use format strings for a object.

I might make this into a full on header as another project in the future.. 
*/

//Standard Headers
#include <string>

// This has to be the first time, I used a interface class.. 
struct Formatable { 
    // Generally Speaking, Serialize returns a format string that the data can be recreated from
    virtual std::string Format_string() = 0; 
};

struct Deserializable {
    // Meanwhile, Deserailize is used for getting a input and turning it into a object 
    virtual std::istream &Deserialize(std::istream &) = 0;
};

//While somthing that is Serializable means that it can create and take a format string,
struct Serializable : public Formatable, public Deserializable {};


//Then again, I wouldn't mind making a header that serializes all of the standard libary containers.. 

#endif
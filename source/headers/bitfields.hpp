#ifndef _ALEX_BITFIELDS_HPP_
#define _ALEX_BITFIELDS_HPP_
#include <cstdint>

class Bitfield_8bit{
    private:
        uint8_t bitfield;
    public:
        bool enable(uint8_t);
        bool disable(uint8_t);
        bool check(uint8_t);
        bool clear();
        uint8_t size();
};
#endif
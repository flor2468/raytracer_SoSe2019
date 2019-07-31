#ifndef AMBIENT_HPP
#define AMBIENT_HPP   
#include "color.hpp"
#include "light.hpp"

struct Ambient /*: public Light*/ {
    Color standard_;
    Ambient(Color standard) : standard_(standard) {}
};

#endif
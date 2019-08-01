#ifndef AMBIENT_HPP
#define AMBIENT_HPP   
#include "color.hpp"
#include "light.hpp"

struct Ambient /*: public Light*/ {
    Color standard_ = {0.1f, 0.1f, 0.1f};
    Ambient(Color standard = {0.1f, 0.1f, 0.1f}) : standard_(standard) {}
};

#endif
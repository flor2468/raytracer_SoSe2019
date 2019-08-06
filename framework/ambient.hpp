#ifndef AMBIENT_HPP
#define AMBIENT_HPP   
#include "color.hpp"
#include "light.hpp"

struct Ambient /*: public Light*/ {

    /* Grundbeleuchtung in der Szene */

    Color standard_ = {0.4f, 0.4f, 0.4f};
    Ambient(Color standard = {0.4f, 0.4f, 0.4f}) : standard_(standard) {}
};

#endif
#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP   
#include <string>
#include <glm/glm.hpp>

struct Transformation {

    std::string name_;
    float winkel_;
    glm::vec3 verschiebung_;
    glm::vec3 zoom_;
    glm::vec3 rotationsachse_;

};

#endif
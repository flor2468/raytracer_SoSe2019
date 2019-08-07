#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP   
#include <string>
#include <glm/glm.hpp>

struct Transformation {

    std::string transformationsart_; // Translation, Skalierung oder Rotation
    float winkel_;
    glm::vec3 verschiebung_;
    glm::vec3 zoom_;
    glm::vec3 rotationsachse_;
    std::string objekt_name_; // Objekt, dass transformiert werden soll

};

#endif
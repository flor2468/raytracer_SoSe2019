#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <string>
#include "color.hpp"
#include <glm/vec3.hpp>

struct hitpoint{
    bool cut  = {false};
    float distance = {0.0f};
    std::string name = {' '};
    Color col = {0.0f, 0.0f, 0.0f};
    glm::vec3 point3d = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, 0.0f};

};
#endif

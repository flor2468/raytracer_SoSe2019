#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <string>
#include "color.hpp"
#include <glm/vec3.hpp>
#include <limits>
#include "material.hpp"
#include <memory>

struct hitpoint{
    bool cut  = false;
    float distance = {std::numeric_limits<float>::max()};
    std::string name = {" "};
    std::shared_ptr<Material> col = std::make_shared<Material>(Material{"black",{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f},0});
    // std::shared_ptr<Material> col = std::make_shared<Material>(Material{"rosa",{1.0f, 0.5f, 0.5f},{1.0f, 0.5f, 0.5f},{1.0f, 0.5f, 0.5f},0});
    // std::shared_ptr<Material> col = std::make_shared<Material>(Material{"yellow",{1.0f, 1.0f, 0.8f},{1.0f, 1.0f, 0.8f},{1.0f, 1.0f, 0.8f},0});
    glm::vec3 point3d = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, 0.0f};

};
#endif

#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

class Light {
    public:

    private:
        std::string name_;
        glm::vec3 position_;
        Color farbe_;
        float helligkeit_ = 1.0f;
};

#endif
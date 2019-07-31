#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"
#include "ambient.hpp"

// class Light {
//     public:
//         Light();

//     private:
//         std::string name_;
//         glm::vec3 position_;
//         Color farbe_;
//         float helligkeit_ = 1.0f;
        
// };

struct Light /* : public Ambient*/ {

    Light(std::string name, glm::vec3 position, Color farbe, float helligkeit) : name_{name}, position_{position}, farbe_{farbe}, helligkeit_{helligkeit} {}

    std::string name_;
    glm::vec3 position_;
    Color farbe_;
    float helligkeit_ = 1.0f;
};

#endif
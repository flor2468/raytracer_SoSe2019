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

    // Light();
    Light(std::string name = " ", glm::vec3 position = {0,0,0}, Color farbe = {1,1,1}, float intensitaet = 1.0f) : name_{name}, position_{position}, farbe_{farbe}, intensitaet_{intensitaet} {}

    std::string name_ = " ";
    glm::vec3 position_ = {0,0,0};
    Color farbe_ = {1,1,1};
    float intensitaet_ = 1.0f;
};

#endif
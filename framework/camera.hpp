#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include "ray.hpp"


class Camera {
    public:
        Camera(unsigned int breite = 800, unsigned int hoehe = 600, float oeffnungswinkel = 60.0f);
        Ray calcEyeRay(unsigned int x, unsigned int y);

    private: 
        unsigned int breite_; // breite und leange = aufloesung
        unsigned int hoehe_;
        float oeffnungswinkel_;
        glm::vec3 startpunkt_ = {0.0f, 0.0f, 0.0f};
        float d;
};

#endif
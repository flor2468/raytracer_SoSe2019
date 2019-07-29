#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include "ray.hpp"


class Camera {
    public:
        Camera();
        Camera(int breite_, int laenge_);
        Ray calcEyeRay(int x, int y);

    private: 
        int breite_; // breite und leange = aufloesung
        int laenge_;
        int oeffnungswinkel_ = 60;
        glm::vec3 startpunkt_ = {0.0f, 0.0f, 0.0f};
};

#endif